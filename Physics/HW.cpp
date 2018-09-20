#include "stdafx.h"

#include "HW.h"
#include "HW1.h"
#include "HW2.h"
#include "HW3.h"
#include "HW4.h"
#include "HW5.h"

int main() {
	HW* hw = &HW5();
	return run(hw);
}

int run(HW* hw, bool exitAfterShowingProblem) {
#define EXIT_CHK do {\
if (std::cin.fail()) {\
	std::string resp;\
	getline(std::cin, resp);\
	if (resp == "exit") return 0;\
	cout << '[' << resp << "] ignored" << endl;\
}\
} while(0)

	cout << "HW " << hw->getHWnumber() << endl;
	while (1) {
		int problem;
		std::cin >> problem;
		EXIT_CHK;
		while (std::cin.fail() || problem < 1 || problem > hw->maxHWproblems()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			cout << "Enter a HW number problem [1 - " << hw->maxHWproblems() << "]." << endl;
			std::cin >> problem;
			EXIT_CHK;
		}

#define C(n) case n: hw->p##n(); if (exitAfterShowingProblem) return 0; break

		try {
			switch (problem) {
				C(1);
				C(2);
				C(3);
				C(4);
				C(5);
				C(6);
				C(7);
				C(8);
				C(9);
				C(10);
			}
		}
		catch (Exception e) {
			cout << e.what() << endl;
			return EXIT_FAILURE;
		}
		cout << endl;
	}
	return 0;
}