#include <iostream>
#include "calc.h"

using namespace std;

const size_t MAX_SIZE_T = 1000;

TNumeral Long(size_t a_num, size_t b_num) {
	TNumeral a = UNumToTNumeral(a_num);
	TNumeral b = UNumToTNumeral(b_num);

	TNumeral res = a / b;
	return res;
}

TNumeral Basic(size_t a, size_t b) {
	TNumeral res;
	if (b == 0) {
		res.Error = true;
		return res;
	}
	size_t res_num = a / b;
	res = UNumToTNumeral(res_num);

	return res;
}

int main(void) {
	for (size_t i = 0; i < MAX_SIZE_T; i++) {
		for (size_t j = 0; j < MAX_SIZE_T; j++) {
			TNumeral res[2];
			res[0] = Long(i, j);
			res[1] = Basic(i, j);

			if (res[0].Error && res[1].Error) {
				continue;
			}

			if (res[0] != res[1]) {
				cout << "FALSE: " << i << " / " << j << " = " << res[0] << " | " << res[1] << endl; 
			}
		}
	}
}
