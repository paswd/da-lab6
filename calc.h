#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <vector>
#include <string>

const size_t ATOM_SIZE = 3;

class TNumeral {
public:
	std::vector <unsigned int> Atoms;
	bool Error;

	TNumeral(void);
	~TNumeral(void);

	TNumeral& operator =(const TNumeral &num);
};

TNumeral StrToTNumeral(std::string str);

std::istream & operator >>(std::istream &is, TNumeral &n);
std::ostream & operator <<(std::ostream &os, TNumeral const &n);

bool operator <(TNumeral const &a, TNumeral const &b);
bool operator >(TNumeral const &a, TNumeral const &b);
bool operator ==(TNumeral const &a, TNumeral const &b);
bool operator <=(TNumeral const &a, TNumeral const &b);
bool operator >=(TNumeral const &a, TNumeral const &b);

//TNumeral& operator =(TNumeral &num);
TNumeral operator +(TNumeral const &a, TNumeral const &b);
TNumeral operator -(TNumeral const &a, TNumeral const &b);
TNumeral operator *(TNumeral const &a, TNumeral const &b);
TNumeral operator /(TNumeral const &a, TNumeral const &b);

#endif //CALC_H
