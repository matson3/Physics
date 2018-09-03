#include "stdafx.h"

#include "HW.h"

int run(int hwNumber, int maxHWProblems, bool exitAfterShowingProblem) {
	if (maxHWProblems < 1) throw Exception("The maximum number of homework problems can't be nonpositive, ya primbo.");

#define EXIT_CHK do {\
if (std::cin.fail()) {\
	std::string resp;\
	getline(std::cin, resp);\
	if (resp == "exit") return 0;\
	cout << '[' << resp << "] ignored" << endl;\
}\
} while(0)

	cout << "HW " << hwNumber << endl;
	while (1) {
		int hw;
		std::cin >> hw;
		EXIT_CHK;
		while (std::cin.fail() || hw < 1 || hw > maxHWProblems) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			cout << "Enter a HW number problem [1 - " << maxHWProblems << "]." << endl;
			std::cin >> hw;
			EXIT_CHK;
		}

#define C(n) case n: p##n(); if (exitAfterShowingProblem) return 0; break

		try {
			switch (hw) {
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