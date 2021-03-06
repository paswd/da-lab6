#include <iostream>
#include "calc.h"

using namespace std;

void PrintBool(bool value) {
	if (value) {
		cout << "true" << endl;
	} else {
		cout << "false" << endl;
	}
}

int main(void) {
	/*TNumeral a;
	TNumeral b;
	cin >> a >> b;
	//cout << a << endl;
	//cout << b << endl;
	cout << a.Power(b) << endl;
	size_t num;
	cin >> num;
	TNumeral res = UNumToTNumeral(num);
	cout << res << endl;*/

	TNumeral a, b;
	char op;

	while (cin >> a >> b >> op) {
		if (a.Error || b.Error) {
			cout << "Error" << endl;
			continue;
		}
		
		if (op == '+') {
			cout << a + b << endl;
			continue;
		}
		if (op == '-') {
			cout << a - b << endl;
			continue;
		}
		if (op == '*') {
			cout << a * b << endl;
			continue;
		}
		if (op == '/') {
			cout << a / b << endl;
			continue;
		}
		if (op == '^') {
			cout << a.Power(b) << endl;
			continue;
		}
		if (op == '<') {
			PrintBool(a < b);
			continue;
		}
		if (op == '>') {
			PrintBool(a > b);
			continue;
		}
		if (op == '=') {
			PrintBool(a == b);
			continue;
		}
	}
	return 0;
}
