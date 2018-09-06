#pragma once

#include "stdafx.h"

#include <iostream>
#include <string>
#include "Physics.h"
#include "textAligner.h"

using namespace phys;
using namespace phys::cnstQ;

extern BetterOutstream cout;

#define HW3

#define model(x) do {\
cout.setLeftMargin("");\
cout << "Model: " << x << para;\
} while(0)

#define Q(letter, x) do {\
cout.setLeftMargin("  ");\
cout << #letter". " << x << endl;\
} while(0)

#define A(x) do {\
cout.setLeftMargin("     ");\
cout << x << para;\
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

void p1();
void p2();
void p3();
void p4();
void p5();
void p6();
void p7();
void p8();
void p9();
void p10();

#define R(x) (M_PI * (x) / 180)

#define D(x) std::cout << #x " = " << x << std::endl

int run(int hwNumber, int maxHWProblems, bool exitAfterShowingProblem = false);