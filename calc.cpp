#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "calc.h"
#include "converter.h"

using namespace std;

//const size_t SIZE_T_MAX = 18446744073709551615;

TNumeral::TNumeral(void) {
	this->Atoms.resize(1);
	this->Atoms[0] = 0;
	this->Error = false;
}

TNumeral::~TNumeral(void) {
}

TNumBasic DecPow(size_t index) {
	TNumBasic res = 1;
	for (size_t i = 0; i < index; i++) {
		res *= 10;
	}
	return res;
}

const TNumBasic DEC_POW_ATOM = DecPow(ATOM_SIZE);

TNumeral& TNumeral::operator =(const TNumeral &num) {
	this->Atoms.resize(num.Atoms.size());
	for (size_t i = 0; i < this->Atoms.size(); i++) {
		this->Atoms[i] = num.Atoms[i];
	}
	this->Error = num.Error;
	return *this;
}
bool TNumeral::IsZero(void) const {
	if (this->Atoms.size() == 1 && this->Atoms[0] == 0) {
		return true;
	}
	return false;
}
bool TNumeral::IsEven(void) const {
	if (this->Atoms[0] % 2 == 0) {
		return true;
	}
	return false;
}
void TNumeral::RemovePreZeros(void) {
	if (this->Atoms.size() == 1) {
		return;
	}
	size_t cnt = 0;
	for (size_t i = this->Atoms.size(); i > 0; i--) {
		//size_t i = j - 1;
		if (this->Atoms[i - 1] != 0) {
			break;
		}
		cnt++;
	}
	this->Atoms.resize(this->Atoms.size() - cnt);
}

TNumeral StrToTNumeral(string str) {
	TNumeral res;
	size_t begin = 0;
	for (size_t j = 0; j < str.size(); j++) {
		if (str[j] != '0') {
			break;
		}
		begin++;
	}
	size_t real_size = max(str.size() - begin, (size_t) 1);
	size_t n_size = real_size / ATOM_SIZE;
	if (real_size % ATOM_SIZE > 0) {
		n_size++;
	}
	res.Atoms.resize(n_size);

	size_t current_tmp = 0;
	size_t current_size = 0;
	TNumBasic tmp = 0;
	bool first = true;


	for (size_t j = str.size(); j > begin; j--) {
		size_t i = j - 1;
		if (!IsCharNum(str[i])) {
			res.Error = true;
			break;
		}

		//tmp *= 10;
		tmp += (TNumBasic) CharToUNum(str[i]) * DecPow(current_tmp);
		current_tmp++;
		//cout << "PNT1" << endl;
		//cout << "TMP = " << tmp << endl;
		//cout << "CURRENT_TMP = " << current_tmp << endl;
		//TNumBasic DEC_POW_ATOM = DecPow(ATOM_SIZE);
		if (current_tmp > ATOM_SIZE) {
			TNumBasic current_value = tmp % DEC_POW_ATOM;
			//size_t current_size = res.Atoms.size();
			//cout << "current_size = " << current_size << endl;
			if (!first) {
				current_size++;
			}
			res.Atoms[current_size] = current_value;
			tmp /= DEC_POW_ATOM;
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

TNumeral UNumToTNumeral(size_t num) {
	TNumeral res;
	bool first = true;
	while (num > 0) {
		if (!first) {
			res.Atoms.resize(res.Atoms.size() + 1);
		}
		first = false;
		size_t current = res.Atoms.size() - 1;
		res.Atoms[current] = num % DEC_POW_ATOM;
		num /= DEC_POW_ATOM;
	}
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
			/*if (!first) {
				cout << ".";
			}*/
			//TNumBasic DEC_POW_ATOM = DecPow(ATOM_SIZE);
			for (TNumBasic k = 10; k < DEC_POW_ATOM; k *= 10) {
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
bool operator !=(TNumeral const &a, TNumeral const &b) {
	if (a == b) {
		return false;
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
	
	TNumBasic tmp = 0;
	
	//res.Atoms.resize(max(a.Atoms.size(), b.Atoms.size()));
	if (a.Atoms.size() > b.Atoms.size()) {
		res = a;
	} else if (a.Atoms.size() < b.Atoms.size()) {
		res = b;
	} else {
		res.Atoms.resize(a.Atoms.size());
	}
	size_t max_i = min(a.Atoms.size(), b.Atoms.size());
	TNumBasic divider = DecPow(ATOM_SIZE);
	//cout << "max_i = " << max_i << endl;
	for (size_t i = 0; i < max_i; i++) {
		//cout << "i = " << i << endl;
		res.Atoms[i] = a.Atoms[i] + b.Atoms[i];
		//cout << "res.Atoms[i] (0) = " << res.Atoms[i] << endl;
		res.Atoms[i] += tmp;
		//cout << "res.Atoms[i] (1) = " << res.Atoms[i] << endl;
		tmp = res.Atoms[i] / divider;
		res.Atoms[i] %= divider;
		//cout << "res.Atoms[i] (2) = " << res.Atoms[i] << endl;
		//cout << "res = " << res << endl;
	}
	while (tmp != 0) {
		size_t current = max_i;
		if (current >= res.Atoms.size()) {
			res.Atoms.resize(current + 1);
			res.Atoms[current] = 0;
		}
		/*size_t current = res.Atoms.size();
		res.Atoms.resize(res.Atoms.size() + 1);*/
		res.Atoms[current] += tmp;
		tmp = res.Atoms[current] / divider;
		res.Atoms[current] %= divider;
		max_i++;
	}
	//cout << "res.Atoms.size() = " << res.Atoms.size() << endl;

	res.RemovePreZeros();
	return res;
}

TNumeral operator -(TNumeral const &a, TNumeral const &b) {
	TNumeral res;
	if (a < b || a.Error || b.Error) {
		res.Error = true;
		return res;
	}

	res = a;
	
	//TNumBasic DEC_POW_ATOM = DecPow(ATOM_SIZE);
	TNumBasic max_atom = DEC_POW_ATOM - 1;

	for (size_t i = 0; i < b.Atoms.size(); i++) {
		if (res.Atoms[i] < b.Atoms[i]) {
			size_t j = i + 1;
			for (; res.Atoms[j] == 0; j++) {
				res.Atoms[j] = max_atom;
			}
			res.Atoms[j]--;
			res.Atoms[i] += DEC_POW_ATOM;
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

	res.RemovePreZeros();
	return res;
}

TNumeral operator *(TNumeral const &a, TNumeral const &b) {
	TNumeral res;
	if (a.Error || b.Error) {
		res.Error = true;
		return res;
	}

	//Now `res` is zero
	if (a.IsZero() || b.IsZero()) {
		return res;
	}
	
	TNumBasic tmp = 0;
	
	TNumBasic divider = DecPow(ATOM_SIZE);

	for (size_t j = 0; j < b.Atoms.size(); j++) {
		tmp = 0;
		TNumeral res_tmp;
		res_tmp.Atoms.resize(1 + j);
		for (size_t i = 0; i <= j; i++) {
			res_tmp.Atoms[i] = 0;
		}
		size_t k = 0;
		for (size_t i = 0; i < a.Atoms.size(); i++) {
			k = i + j;
			if (k >= res_tmp.Atoms.size()) {
				res_tmp.Atoms.resize(k + 1);
			}
			res_tmp.Atoms[k] = a.Atoms[i] * b.Atoms[j];
			res_tmp.Atoms[k] += tmp;
			tmp = res_tmp.Atoms[k] / divider;
			res_tmp.Atoms[k] %= divider;
		}

		if (tmp != 0) {
			//cout << "j = " << j << endl;
			//cout << "Tmp = " << tmp << endl;
			size_t current = res_tmp.Atoms.size();
			//cout << "Current = " << current << endl;
			res_tmp.Atoms.resize(res_tmp.Atoms.size() + 1);
			res_tmp.Atoms[current] = tmp;
		}
		//cout << "res_tmp = " << res_tmp << endl;
		res = res + res_tmp;
	}
	//cout << "res.Atoms.size() = " << res.Atoms.size() << endl;
	res.RemovePreZeros();
	return res;
}

TNumeral operator /(TNumeral const &a, TNumeral const &b) {
	/*TNumeral zero = UNumToTNumeral(0);
	if (a == zero) {
		return zero;
	}*/

	TNumeral res;

	//Now `res` is zero
	if ((a.IsZero() && !b.IsZero()) || a < b) {
		return res;
	}
	
	if(b.IsZero()) {
		res.Error = true;
		return res;
	}

	TNumeral d_number;
	d_number.Atoms[0] = DEC_POW_ATOM / (b.Atoms[b.Atoms.size() - 1] + 1);
	TNumeral a_nw = a * d_number;
	TNumeral b_nw = b * d_number;

	res.Atoms.resize(a_nw.Atoms.size());

	TNumeral r;

	TNumeral dpa = UNumToTNumeral(DEC_POW_ATOM);

	for (size_t j = a_nw.Atoms.size(); j > 0; j--) {
		size_t i = j - 1;
		r = r * dpa;
		r = r + UNumToTNumeral(a_nw.Atoms[i]);

		TNumBasic c[2];
		if(r.Atoms.size() <= b_nw.Atoms.size()) {
			c[0] = 0;
		} else {
			c[0] = r.Atoms[b_nw.Atoms.size()];
		}

		if(r.Atoms.size() <= b_nw.Atoms.size() - 1) {
			c[1] = 0;
		} else {
			c[1] = r.Atoms[b_nw.Atoms.size() - 1];
		}

		TNumBasic tmp = (c[0] * DEC_POW_ATOM + c[1]) / b_nw.Atoms[b_nw.Atoms.size() - 1];

		TNumeral sub = b_nw * UNumToTNumeral(tmp);
		while (sub > r) {
			tmp--;
			sub = sub - b_nw;
		}
		r = r - sub;
		res.Atoms[i] = tmp;
	}
	res.RemovePreZeros();
	return res;
}

TNumeral TNumeral::Power(TNumeral pk) {
	TNumeral one = UNumToTNumeral(1);
	TNumeral two = UNumToTNumeral(2);
	TNumeral res = one;
	if (pk.IsZero()) {
		if (this->IsZero()) {
			one.Error = true;
		}
		return one;
	}
	if (this->IsZero()) {
		res = UNumToTNumeral(0);
		return res;
	}

	if (pk == one) {
		return *this;
	}
	if (pk.IsEven()) {
		TNumeral new_pk = pk / two;
		res = this->Power(new_pk);
		return res * res;
	} else {
		return this->Power(pk - one) * (*this);
	}
}

