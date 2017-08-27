#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <vector>
#include <string>

//The best value is 6
const size_t ATOM_SIZE = 6;

typedef unsigned long long TNumBasic;

class TNumeral {
public:
	std::vector <TNumBasic> Atoms;
	bool Error;

	TNumeral(void);
	~TNumeral(void);

	TNumeral& operator =(const TNumeral &num);

	bool IsZero(void) const;
	bool IsEven(void) const;
	void RemovePreZeros(void);
	TNumeral Power(TNumeral pk);
};

TNumeral StrToTNumeral(std::string str);
TNumeral UNumToTNumeral(size_t num);

std::istream & operator >>(std::istream &is, TNumeral &n);
std::ostream & operator <<(std::ostream &os, TNumeral const &n);

bool operator <(TNumeral const &a, TNumeral const &b);
bool operator >(TNumeral const &a, TNumeral const &b);
bool operator ==(TNumeral const &a, TNumeral const &b);
bool operator !=(TNumeral const &a, TNumeral const &b);
bool operator <=(TNumeral const &a, TNumeral const &b);
bool operator >=(TNumeral const &a, TNumeral const &b);

TNumeral operator +(TNumeral const &a, TNumeral const &b);
TNumeral operator -(TNumeral const &a, TNumeral const &b);
TNumeral operator *(TNumeral const &a, TNumeral const &b);
TNumeral operator /(TNumeral const &a, TNumeral const &b);

#endif //CALC_H
