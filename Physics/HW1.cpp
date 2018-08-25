#include "stdafx.h"

#include <iostream>
#include "Physics.h"

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

using namespace std;
using namespace phys;
using namespace phys::cnstQ;

int main() {
#define EXIT_CHK do {\
if (cin.fail()) {\
	std::string resp;\
	cin >> resp;\
	if (resp == "exit") return 0;\
}\
} while(0)

	cout << "HW01" << endl;
	while (1) {
		int hw;
		cin >> hw;
		EXIT_CHK;
		while (cin.fail() || hw < 1 || hw > 10) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Enter a HW number problem [1 - 10]." << endl;
			cin >> hw;
			EXIT_CHK;
		}

#define C(n) case n: p##n(); return 0; break

		//try {
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
		/*} catch (Exception e) {
			cout << e.what() << endl;
			return EXIT_FAILURE;
		}*/
	}
	return 0;
}

void p1() {
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

	cout << " D. Determine the period of the circular motion." << endl;
	Quantity period = (2 * M_PI * r) / rv;
	cout << "  " << period << endl;
}

#define R(x) (M_PI * (x) / 180)

void p2() {
	DistanceM l = 1.0e3;
	Charge c = -3;
	cout << "Model: A triangle with equal sides of length " << l << " has " << c << " charged objects at each corner." << endl << endl;
	Distance p1 = Distance(0, 0, 0);
	Distance p2 = Vector(l.magnitude(), R(0));
	Distance p3 = Vector(R(60), l.magnitude());

	cout << "Question 2" << endl;
	cout << " A. Determine the magnitude of the electrical force exerted on the object at the top corner due to the two objects at the base of the triangle." << endl;
	Distance d13 = p3 - p1;
	Distance d23 = p3 - p2;
	Force net3 = elecForce(c, c, d13) + elecForce(c, c, d23);
	cout << "  " << net3.magnitude() << endl << endl;

	cout << " B. Determine the direction of the electrical force exerted on the object at the top corner due to the two objects at the base of the triangle. Assume +x to be to the right, and +y to be up." << endl;
	cout << "  " << net3 << endl;
}

void p3() {
	cout << "Conceptual, not mathematical" << endl;
}

void p4() {
	cout << "Conceptual, not mathematical" << endl;
}

void p5() {
	Charge c1 = micro(1);
	Charge c2 = micro(2);
	Charge c3 = nano(-1);

	DistanceM d = 60;

	cout << "Model: A " << c1 << " charged object and a " << c2 << " charged object are separated by " << d << '.' << endl << endl;

	cout << " A. Where should a " << c3 << " charged object be located on a line between the positively charged objects (from " << c1 << " charged object)  so that the net electrical force exerted on the negatively charged object is zero? " << endl;
	// Quadratic Formula
	double a = (c2 / c1).quantity - 1.0;
	double b = 2 * d.quantity;
	double c = -d.quantity * d.quantity;
	DistanceM df = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	DistanceM df2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	if (0 < df && df < d)
		cout << "  " << df << endl;

	if (0 < df2 && df2 < d)
		cout << "  " << df2 << endl;
}

void p6() {
	Charge c1 = -1.6;
	Charge c2 = -4.2;
	DistanceM di = kilo(500);
	DistanceM df = kilo(110);

	cout << " A. Determine the change in electric potential energy of a system of two charged objects when a " << c1 << " charged object and a " << c2 << " charged object move from an initial separation of " << di << " to a final separation of " << df << '.' << endl;

	auto Ui = elecPot(c1, c2, di);
	auto Uf = elecPot(c1, c2, df);
	auto dU = Uf - Ui;
	cout << "  " << dU << endl << endl;

	cout << " B. The potential energy is zero at infinity. Calculate the potential energy of the initial state." << endl;
	cout << "  " << Ui << endl << endl;

	cout << " C. Calculate the potential energy of the final state." << endl;
	cout << "  " << Uf << endl << endl;
}

void p7() {
	Mass m = 16;
	Charge q = 1e-4;
	DistanceM dCharge = 0.1;
	double angle = R(37);
	Vector barrel = Vector(angle, DistanceM(3));

	cout << " B. Find the change in gravitational potential energy." << endl;
	Quantity dUgrav = 0 - m * g * barrel;
	cout << "  " << dUgrav << endl << endl;

	cout << " C. Find the change in electric potential energy." << endl;
	Quantity UelecI = elecPot(q, q, dCharge);
	UelecI.unit = "kg m^2 / s^2";
	Quantity UelecF = elecPot(q, q, dCharge + barrel.magnitude());
	UelecF.unit = "kg m^2 / s^2";
	Quantity dUelec = UelecF - UelecI;
	cout << "  " << dUelec << endl << endl;

	cout << " D. Find the final speed of the charge as it leaves the barrel." << endl;
	Quantity kinetic = UelecI - (UelecF + dUgrav);
	Quantity vf = ((2 * kinetic) / m).sqrt();
	cout << "  " << vf << endl;
}

void p8() {
	cout << "Conceptual" << endl;
}

void p9() {
	cout << "Conceptual" << endl;
}

void p10() {
	cout << "Conceptual" << endl;
}