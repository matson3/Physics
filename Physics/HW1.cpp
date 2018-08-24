#include "stdafx.h"

#include <iostream>
#include "Physics.h"

int main() {
	using namespace std;
	using namespace phys;
	using namespace phys::cnstQ;

	cout << "HW01" << endl << endl;

	DistanceM r = DistanceM(0.53e-10);
	cout << "Model: hydrogen atom; electron moves around proton nucleus in circular orbit of radius " << r << endl << endl;

	cout << "Question 1" << endl;
	cout << " A. Determine force between electron & proton." << endl;
	ForceM electricForce = elecForce(e, -e, r);
	cout << "  " << electricForce << endl << endl;

	cout << " B. Determine the radial acceleration of the electron." << endl;
	Quantity radialAcceleration = electricForce / electronMass;
	radialAcceleration.unit = Unit("m / s^2"); // TODO: Automatically convert units
	cout << "  " << radialAcceleration << endl << endl;

	cout << " C. Determine the speed of the electron." << endl;
	VelocityM rv = circularVelocity(r, radialAcceleration);
	cout << "  " << rv << endl << endl;


	return 0;
}