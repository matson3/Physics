#include "stdafx.h"

#include "HW.h"

#define HW2
#ifdef HW2
int main() {
	return run(2, 10);
}

void p1() {
	model("An electron is ejected into a horizontal uniform Electric field at a parallel horizontal velocity of v0.");

	Q(A, "Assume the Electric field is in the same direction as the initial velocity. Define the equation for the electron's velocity. Neglect gravity.");
	A("v(t) = v0 - E*|e|*t/m");

	Q(B, "Define the equation for the electron's position.");
	A("x(t) = x0 + v0*t - E*|e|*t^2/(2m)");

	Q(C, "Assume the Electric field is in the direction opposite to the electron's initial velocity. Define the equation for the electron's velocity.");
	A("v(t) = v0 + E*|e|*t/m");

	Q(D, "Define the equation for the electron's position.");
	A("x(t) = x0 + v0*t + E*|e|*t^2/(2m)");
}

void p2() {
	Quantity m = { 3.5, "g" };
	Mass mass = toKilo(m.quantity);
	Charge q = 4.5e-9;
	double angle = R(30 + 90);
	model("A " << m << " aluminum foil ball with a charge of " << q << " is suspended on a string in a uniform horizontal Electric field. The string deviates to the right and makes an angle of 30 degrees with the vertical.");

	Q(A, "What information about the Electric field can you determine for this situation?");
	A("Both the magnitude and direction of the Electric field");

	Force grav = gravForce(mass);
	double Ty = -grav.y;
	double Tmag = Ty / sin(angle);
	Force tension = Vector(Quantity(Tmag, "N"), angle);
	Force E = -tension.x;
	Vector Efield = E / q;

	Q(B, "Determine the magnitude of the electric field.");
	A(Efield.magnitude());

	Q(C, "Determine the direction of the electric field.");
	A("to the right.");
}

void p3() {
	Charge q = 4.8e-19;
	model("A particle with charge " << q << " is placed on the x axis in a region where the electric potential due to other charges increases in the +x direction but does not change in the y or z direction.");

	Energy dKE = 3.2e-19;
	Q(A, "The particle, initially at rest, is acted upon only by the electric force and moves from point a to point b along the x axis, increasing its kinetic energy by " << dKE << " . In what direction and through what potential difference Vb - VA does the particle move?");
	Quantity dV = -dKE / q;
	A("To the left, dv = " << dV);
}

void p4() {
	Voltage v = 22'000;
	model("The potential difference from the cathode (negative electrode) to the screen of an old television set is " << v << ". An electron leaves the cathode with an initial speed of zero.");

	Q(A, "Determine the kinetic energy of the electron.");
	Energy ke = (v.quantity * cnstQ::e.quantity);
	A(ke);

	Q(B, "Determine the speed of the electron.");
	VelocityM vel = velocity(ke, cnstQ::electronMass);
	A(vel);
}

void p5() {
	Voltage v = 1;
	Voltage A = 1, B = 1, C = -1.5, D = 0;
	model("The dashed lines in the diagram represent cross sections of equipotential surfaces drawn in " << v << " increments. ");

	Charge c = 1;
	Q(A, "What is the work done by the electric force to move a " << c << " charge from A (" << A << ") to B (" << B << ")?");
	Voltage dv = B - A;
	Energy W = -Quantity(c.quantity * dv.quantity, "J");
	A(W);

	Q(B, "What is the work done by the electric force to move a " << c << " charge from A (" << A << ") to D (" << D << ")?");
	dv = D - A;
	W = -Quantity(c.quantity * dv.quantity, "J");
	A(W);

	Conceptual;
}

void p6() {
	Voltage v = 2.6e4;
	Energy E = 3.0e-7;
	model("An electric spark jumps from a person's finger to your nose and through your body. While passing through the air, the spark travels across a potential difference of " << v << " and releases " << E << " of electric potential energy.");

	Q(A, "What is the charge in coulombs?");
	v.unit = "J / C";
	Charge c = E / v;
	A(c);

	Q(B, "How many electrons flow?");
	Quantity N = c / cnstQ::e;
	A(N);
}

void p7() {
	model("Two small metal spheres A and B have different electric potentials (A has a higher potential).");

	Q(A, "Describe mathematically what happens if you connect them with a wire. Let the charges of the two spheres after connection be q'A and q'B and radiuses be RA and RB.\nExpress your answer in terms of the variables RA and RB.");
	A("RA/RB");

	Q(B, "Describe in words what happens if you connect them with a wire.");
	A("If the two spheres have the same radius, then positive charge must flow from A to B.");
}

void p8() {
	model("A metal sphere of radius R has an electric charge +q on it.");

	Q(A, "Determine an expression for the electric potential V on the sphere's surface. Assume k is the constant used in Coulomb's law.\n Express your answer in terms of the variables R, q, and k.");
	A("V = kq/R");

	Q(B, "Determine an expression for the capacitance of a metal sphere of radius R.\n Express your answer in terms of the variables R, q, and k.");
	A("C = R/k");
}

void p9() {
	model("An electron moving horizontally from left to right across the page enters a uniform Electric field that points toward the top of the page.");

	Q(A, "Choose the correct direction of the electric force exerted by the field on the electron.");
	A("Down");

	Q(B, "Choose the correct direction of the acceleration of the electron.");
	A("Down");

	Q(C, "What motion in the gravitational field is similar to the motion of the electron?");
	A("The motion of an object that is thrown horizontally.");
}

void p10() {
	model("An electric field can be created by a single charge or a distribution of charges. The electric field a distance r from a point charge q' has magnitude\n"
		"E = k |q'| / r^2.\n"
		"The electric field points away from positive charges and toward negative charges. A distribution of charges creates an electric field that can be found by taking the vector sum of the fields created by individual point charges. Note that if a charge q is placed in an electric field created by q', q will not significantly affect the electric field if it is small compared to q'.\n"
		"Imagine an isolated positive point charge with a charge Q (many times larger than the charge on a single electron)."
	);

	Q(A, "There is a single electron at a distance from the point charge. On which of the following quantities does the force on the electron depend?");
	A(
		"  the charge on the electron\n"
		"  the charge of the positive charge\n"
		"  the distance between the positive charge and the electron"
	);

	Q(B, "For the same situation as in Part A, on which of the following quantities does the electric field at the electron's position depend?");
	A(
		"  the charge of the positive charge\n"
		"  the distance between the positive charge and the electron"
	);

	Charge Q = 1.62e-6;
	DistanceM d = 1.53;
	Q(C, "If the total positive charge is " << Q << ", what is the magnitude of the electric field caused by this charge at point P, a distance " << d << " from the charge?");
	
	Quantity EP = cnstQ::K * Q / (d * d);
	A(EP);

	Q(D, "What is the direction of the electric field at this point (previously marked P)?");
	A("G (->)");

	Charge e = 1.60e-19;
	Q(E, "Now find the magnitude of the force on an electron placed at this same point. Recall that the charge on an electron has magnitude.");
	ForceM force = EP * e;
	A(force);

	Q(F, "What is the direction of the force on the electron placed at this point?");
	A("C (<-)");
}


#endif 
