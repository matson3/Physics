#include "stdafx.h"

#include "HW.h"

#ifdef  HW1
int main() {
	return run(1, 10);
}

void p1() {
	DistanceM r = DistanceM(0.53e-10);

	model("Hydrogen atom; electron moves around proton nucleus in circular orbit of radius " << r);

	Q(A, "Determine force between electron & proton.");
	ForceM electricForce = elecForce(e, -e, r);
	A(electricForce);

	Q(B, "Determine the radial acceleration of the electron.");
	Quantity radialAcceleration = electricForce / electronMass;
	radialAcceleration.unit = Unit("m / s^2"); // TODO: Automatically convert units
	A(radialAcceleration);

	Q(C, "Determine the speed of the electron.");
	VelocityM rv = circularVelocity(r, radialAcceleration);
	A(rv);

	Q(D, "Determine the period of the circular motion.");
	Quantity period = (2 * M_PI * r) / rv;
	A(period);
}


void p2() {
	DistanceM l = 1.0e3;
	Charge c = -3;
	model("A triangle with equal sides of length " << l << " has " << c << " charged objects at each corner.");
	Distance p1 = Distance(0, 0, 0);
	Distance p2 = Vector(l.magnitude(), R(0));
	Distance p3 = Vector(R(60), l.magnitude());


	Q(A, "Determine the magnitude of the electrical force exerted on the object at the top corner due to the two objects at the base of the triangle.");
	Distance d13 = p3 - p1;
	Distance d23 = p3 - p2;
	Force net3 = elecForce(c, c, d13) + elecForce(c, c, d23);
	A(net3.magnitude());

	Q(B, "Determine the direction of the electrical force exerted on the object at the top corner due to the two objects at the base of the triangle. Assume +x to be to the right, and +y to be up.");
	A(net3);
}

void p3() {
	Conceptual;
}

void p4() {
	Conceptual;
}

void p5() {
	Charge c1 = micro(1);
	Charge c2 = micro(2);
	Charge c3 = nano(-1);

	DistanceM d = 60;

	model("A " << c1 << " charged object and a " << c2 << " charged object are separated by " << d << '.');

	Q(A, "Where should a " << c3 << " charged object be located on a line between the positively charged objects (from " << c1 << " charged object)  so that the net electrical force exerted on the negatively charged object is zero?");
	// Quadratic Formula
	double a = (c2 / c1).quantity - 1.0;
	double b = 2 * d.quantity;
	double c = -d.quantity * d.quantity;
	DistanceM df = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	DistanceM df2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	if (0 < df && df < d)
		A(df);

	if (0 < df2 && df2 < d)
		A(df2);
}

void p6() {
	Charge c1 = -1.6;
	Charge c2 = -4.2;
	DistanceM di = kilo(500);
	DistanceM df = kilo(110);

	Q(A, "Determine the change in electric potential energy of a system of two charged objects when a " << c1 << " charged object and a " << c2 << " charged object move from an initial separation of " << di << " to a final separation of " << df << '.');
	auto Ui = elecPotEnergy(c1, c2, di);
	auto Uf = elecPotEnergy(c1, c2, df);
	auto dU = Uf - Ui;
	A(dU);

	Q(B, "The potential energy is zero at infinity. Calculate the potential energy of the initial state.");
	A(Ui);

	Q(C, "Calculate the potential energy of the final state.");
	A(Uf);
}

void p7() {
	Mass m = 16;
	Charge q = 1e-4;
	DistanceM dCharge = 0.1;
	double angle = R(37);
	Vector barrel = Vector(angle, DistanceM(3));

	Q(B, "Find the change in gravitational potential energy.");
	Quantity dUgrav = - m * g * barrel;
	A(dUgrav);

	Q(C, "Find the change in electric potential energy.");
	Quantity UelecI = elecPotEnergy(q, q, dCharge);
	UelecI.unit = "kg m^2 / s^2";
	Quantity UelecF = elecPotEnergy(q, q, dCharge + barrel.magnitude());
	UelecF.unit = "kg m^2 / s^2";
	Quantity dUelec = UelecF - UelecI;
	A(dUelec);

	Q(D, "Find the final speed of the charge as it leaves the barrel.");
	Quantity kinetic = UelecI - (UelecF + dUgrav);
	Quantity vf = ((2 * kinetic) / m).sqrt();
	A(vf);
}

void p8() {
	Conceptual;
}

void p9() {
	Conceptual;
}

void p10() {
	Conceptual;
}

#endif // HW1