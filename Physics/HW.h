#pragma once

#include "stdafx.h"

#include <iostream>
#include <string>

#include "Physics.h"
#include "textAligner.h"

using namespace phys;
using namespace phys::cnstQ;

extern BetterOutstream cout;

#define model(x) do {\
cout.setLeftMargin("");\
cout << "Model: " << x << para;\
} while(0)

#define Q(letter, question) do {\
cout.setLeftMargin("  ");\
cout << #letter". " << question << endl;\
} while(0)

#define A(answer) do {\
cout.setLeftMargin("     ");\
cout << answer << para;\
} while(0)

#define Conceptual A("Conceptual, not mathematical")

/*
model("");

Q(A, "");
A("");

Q(B, "");
A("");

Q(C, "");
A("");

Q(D, "");
A("");

Q(E, "");
A("");

Q(F, "");
A("");
*/

class HW {
private:
	int maxProblem;
	int hwNumber;

public:
	HW(int hwNumber, int maxHWproblems) {
		if (hwNumber <= 0) throw Exception("hwNumber must be > 0");
		if (maxHWproblems <= 0) throw Exception("maxHWproblems must be > 0");

		this->hwNumber = hwNumber;
		this->maxProblem = maxHWproblems;
	}

	virtual void p1() {}
	virtual void p2() {}
	virtual void p3() {}
	virtual void p4() {}
	virtual void p5() {}
	virtual void p6() {}
	virtual void p7() {}
	virtual void p8() {}
	virtual void p9() {}
	virtual void p10() {}

	int maxHWproblems() const { return maxProblem; }
	int getHWnumber() const { return hwNumber; }
};

#define R(x) (M_PI * (x) / 180)

#define D(x) std::cout << #x " = " << x << std::endl

int run(HW* hw, bool exitAfterShowingProblem = false);