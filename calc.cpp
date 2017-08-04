#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "calc.h"
#include "converter.h"

using namespace std;

const size_t SIZE_T_MAX = -1;

TNumeral::TNumeral(void) {
	this->Atoms.resize(1);
	this->Atoms[0] = 0;
	this->Error = false;
}

TNumeral::~TNumeral(void) {
}

unsigned int DecPow(size_t index) {
	unsigned int res = 1;
	for (size_t i = 0; i < index; i++) {
		res *= 10;
	}
	return res;
}

TNumeral& TNumeral::operator =(const TNumeral &num) {
	this->Atoms.resize(num.Atoms.size());
	for (size_t i = 0; i < this->Atoms.size(); i++) {
		this->Atoms[i] = num.Atoms[i];
	}
	this->Error = num.Error;
	return *this;
}
TNumeral StrToTNumeral(string str) {
	TNumeral res;
	size_t n_size = str.size() / ATOM_SIZE;
	if (str.size() % ATOM_SIZE > 0) {
		n_size++;
	}
	//cout << "N_SIZE = " << n_size << endl;
	res.Atoms.resize(n_size);

	size_t current_tmp = 0;
	unsigned int tmp = 0;
	bool first = true;

	for (size_t j = str.size(); j > 0; j--) {
		size_t i = j - 1;
		if (!IsCharNum(str[i])) {
			res.Error = true;
			break;
		}

		//tmp *= 10;
		tmp += (unsigned int) CharToUNum(str[i]) * DecPow(current_tmp);
		current_tmp++;
		//cout << "PNT1" << endl;
		//cout << "TMP = " << tmp << endl;
		//cout << "CURRENT_TMP = " << current_tmp << endl;
		unsigned int dec_pow = DecPow(ATOM_SIZE);
		if (current_tmp > ATOM_SIZE) {
			unsigned int current_value = tmp % dec_pow;
			size_t current_size = res.Atoms.size();
			if (first) {
				current_size = 0;
			}/* else {
				res.Atoms.resize(res.Atoms.size() + 1);
				cout << "Current size = " << res.Atoms.size() << endl;
			}*/
			res.Atoms[current_size] = current_value;
			tmp /= dec_pow;
			current_tmp = 1;
			first = false;
		}
		//cout << "PNT2" << endl;
		//cout << "TMP = " << tmp << endl;
		//cout << "CURRENT_TMP = " << current_tmp << endl;
	}
	//cout << "N_SIZE1 = " << res.Atoms.size() << endl;
	if (tmp != 0) {
		size_t current_size = res.Atoms.size() - 1;
		if (first) {
			current_size = 0;
		}/* else {
			res.Atoms.resize(res.Atoms.size() + 1);
			cout << "TRUE" << endl;
		}*/
		res.Atoms[current_size] = tmp;
	}
	//cout << "N_SIZE2 = " << res.Atoms.size() << endl;

	return res;
}

std::istream &operator >>(std::istream &is, TNumeral &n) {
	string str;
	is >> str;
	n = StrToTNumeral(str);

	return is;
}
std::ostream &operator <<(std::ostream &os, TNumeral const &n) {
	if (!n.Error) {
		bool first = true;

		for (size_t j = n.Atoms.size(); j > 0; j--) {
			size_t i = j - 1;
			if (!first) {
				cout << ".";
			}
			unsigned int dec_pow = DecPow(ATOM_SIZE);
			for (unsigned int k = 10; k < dec_pow; k *= 10) {
				if (n.Atoms[i] < k && !first) {
					os << 0;
					//cout << n.Atoms[i] << " < " << i << endl; 
				}
			}

			os << n.Atoms[i];
			first = false;
		}
	} else {
		os << "Error";
	}

	return os;
}

bool operator <(TNumeral const &a, TNumeral const &b) {
	if (a.Error || b.Error) {
		return false;
	}

	if (a.Atoms.size() < b.Atoms.size()) {
		return true;
	}
	if (a.Atoms.size() > b.Atoms.size()) {
		return false;
	}
	size_t i = a.Atoms.size() - 1;
	for (; a.Atoms[i] == b.Atoms[i] && i > 0; i--);

	if (a.Atoms[i] < b.Atoms[i]) {
		return true;
	} else {
		return false;
	}
}
bool operator >(TNumeral const &a, TNumeral const &b) {
	if (a.Error || b.Error) {
		return false;
	}
	
	if (a.Atoms.size() > b.Atoms.size()) {
		return true;
	}
	if (a.Atoms.size() < b.Atoms.size()) {
		return false;
	}
	size_t i = a.Atoms.size() - 1;
	for (; a.Atoms[i] == b.Atoms[i] && i > 0; i--);

	if (a.Atoms[i] > b.Atoms[i]) {
		return true;
	} else {
		return false;
	}
}
bool operator ==(TNumeral const &a, TNumeral const &b) {
	if (a.Error || b.Error) {
		return false;
	}
	
	if (a.Atoms.size() != b.Atoms.size()) {
		return false;
	}
	for (size_t i = 0; i < a.Atoms.size(); i++) {
		if (a.Atoms[i] != b.Atoms[i]) {
			return false;
		}
	}
	return true;
}
bool operator <=(TNumeral const &a, TNumeral const &b) {
	if (a < b || a == b) {
		return true;
	}
	return false;
}
bool operator >=(TNumeral const &a, TNumeral const &b) {
	if (a > b || a == b) {
		return true;
	}
	return false;
}

TNumeral operator +(TNumeral const &a, TNumeral const &b) {
	TNumeral res;
	if (a.Error || b.Error) {
		res.Error = true;
		return res;
	}
	
	unsigned int tmp = 0;
	
	res.Atoms.resize(max(a.Atoms.size(), b.Atoms.size()));
	if (res.Atoms.size() < a.Atoms.size() || res.Atoms.size() < b.Atoms.size()) {
		res.Error = true;
		return res;
	}
	size_t max_i = min(a.Atoms.size(), b.Atoms.size());
	unsigned int divider = DecPow(ATOM_SIZE);
	for (size_t i = 0; i < max_i; i++) {
		res.Atoms[i] = a.Atoms[i] + b.Atoms[i];
		res.Atoms[i] += tmp;
		tmp = res.Atoms[i] / divider;
		res.Atoms[i] %= divider;
	}
	if (tmp != 0) {
		size_t current = res.Atoms.size();
		res.Atoms.resize(res.Atoms.size() + 1);
		res.Atoms[current] = tmp;
	}
	//cout << "res.Atoms.size() = " << res.Atoms.size() << endl;
	return res;
}

TNumeral operator -(TNumeral const &a, TNumeral const &b) {
	TNumeral res;
	if (a < b || a.Error || b.Error) {
		res.Error = true;
		return res;
	}

	res = a;
	
	unsigned int dec_pow = DecPow(ATOM_SIZE);
	unsigned int max_atom = dec_pow - 1;

	for (size_t i = 0; i < b.Atoms.size(); i++) {
		if (res.Atoms[i] < b.Atoms[i]) {
			size_t j = i + 1;
			for (; res.Atoms[j] == 0; j++) {
				res.Atoms[j] = max_atom;
			}
			res.Atoms[j]--;
			res.Atoms[i] += dec_pow;
		}
		//cout << "a = " << res.Atoms[i] << " - " << b.Atoms[i] << endl;
		res.Atoms[i] -= b.Atoms[i];
	}
	size_t pre_nulls_cnt = 0;
	for (size_t i = res.Atoms.size() - 1; i > 0 && res.Atoms[i] == 0; i--) {
		//cout << "true" << endl;
		pre_nulls_cnt++;
	}
	res.Atoms.resize(a.Atoms.size() - pre_nulls_cnt);

	return res;
}

/*TNumeral operator *(TNumeral const &a, TNumeral const &b) {
	TNumeral res;
	if (a.Error || b.Error) {
		res.Error = true;
		return res;
	}
	
	unsigned int tmp = 0;
	
	res.Atoms.resize(max(a.Atoms.size(), b.Atoms.size()));
	if (res.Atoms.size() < a.Atoms.size() || res.Atoms.size() < b.Atoms.size()) {
		res.Error = true;
		return res;
	}
	size_t max_i = min(a.Atoms.size(), b.Atoms.size());
	unsigned int divider = DecPow(ATOM_SIZE);
	for (size_t i = 0; i < max_i; i++) {
		res.Atoms[i] = a.Atoms[i] * b.Atoms[i];
		res.Atoms[i] += tmp;
		tmp = res.Atoms[i] / divider;
		res.Atoms[i] %= divider;
	}
	if (tmp != 0) {
		size_t current = res.Atoms.size();
		res.Atoms.resize(res.Atoms.size() + 1);
		res.Atoms[current] = tmp;
	}
	//cout << "res.Atoms.size() = " << res.Atoms.size() << endl;
	return res;
}*/

