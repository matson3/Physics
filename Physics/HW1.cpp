#include "stdafx.h"

#include <iostream>
#include "Physics.h"

int main() {
	using namespace std;
	using namespace phys;
	using namespace phys::cnstQ;

	cout << "HW01" << endl << endl;

	Quantity r = Quantity(0.53e-10, "m");
	cout << "Model: hydrogen atom; electron moves around proton nucleus in circular orbit of radius " << r << endl << endl;

	cout << "Question 1" << endl;
	cout << "Determine force between electron & proton.\n " << elecForce(e, -e, r) << endl;

	return 0;
}