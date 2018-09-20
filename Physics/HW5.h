#pragma once

#include "HW.h"

class HW5 : public HW {
public:
	HW5() : HW(5, 5) {}

	void p1() {
		model("A coil of radius r is made of N circular loops. It is connected to a battery of known emf and internal resistance. The coil produces a magnetic field whose magnitude at the center of the coil is B.");

		Q(A, "What physical quantities can you determine using this information?");
		A("the current in the circuit\n"
			"the magnetic dipole moment of the coil\n"
			"the resistance in the circuit");

		Q(B, "Determine the current in the circuit.");
		A("I = 2 B r / N mu0");

		Q(C, "Determine the magnetic dipole moment of the coil.");
		A("p = 2 B r^3 pi / mu0");
	}

	void p2() {
		Quantity magField = { 5.2e-5, "T" };
		Quantity angle = { 57, "degrees" };
		model("In Houston, Earth's B field has a magnitude of " << magField << " and points in a direction " << angle << " below a horizontal line pointing north.");

		DistanceM length = 11;
		Ampage I = 15;
		Q(A, "Determine the magnitude of the magnetic force exerted by the magnetic field on a " << length << "-long vertical wire carrying a " << I << " current straight upward.");
		angle = 90 - angle;
		ForceM F = (I * length * magField * sin(R(angle.quantity))).quantity;
		A(F);

		Q(B, "Determine the direction of the magnetic force.");
		A("to the west");
	}

	void p3() {
		Quantity N = 25;
		DistanceM l = centi(18);
		Quantity B = { 0.28, "T" };
		Quantity torque = { 0.60, "N m" };
		model("A square coil with " << N << " turns has sides that are " << l << " long. When it is placed in a " << B << " magnetic field, a maximum torque of " << torque << " is exerted on the coil.");

		Q(A, "Find the current in the coil.");
		Quantity area = l * l;
		Ampage I = (torque / (N * B * area)).quantity;
		A(I);
	}

	void p4() {
		Mass m = toKilo(50);
		Resistance R = 0.3;
		DistanceM L = centi(5);
		Voltage V = 5;
		Quantity B = { 0.294, "T" };
		AccelerationM g = 9.8;
		model(
			"A rail gun uses electromagnetic forces to accelerate a projectile to very high velocities. The basic mechanism of acceleration is relatively simple and can be illustrated in the following example. A metal rod of mass " << m << " and electrical resistance " << R << " rests on parallel horizontal rails that have negligible electric resistance. The rails are a distance L = " << L << " apart. (Figure 1) The rails are also connected to a voltage source providing a voltage of V = " << V << ".\n"
			"The rod is placed in a vertical magnetic field.The rod begins to slide when the field reaches the value B = " << B << ". Assume that the rod has a slightly flattened bottom so that it slides instead of rolling. Use " << g << " for the magnitude of the acceleration due to gravity.\n"
			"Figure 1: B pointing up (+z), x to the right, y into the page. Current moves left on the lower rail."
		);

		Q(A, "Find mu_s, the coefficient of static friction between the rod and the rails.");

		ForceM Fgrav = (m * g).quantity;
		Ampage I = current(R, V);
		ForceM Fmag = (I * L * B).quantity;
		Quantity mu_s = Fmag / Fgrav;
		A("mu_s = " << mu_s);
	}

	void p5() {
		DistanceM L = 2.2;
		Ampage I = 27;
		model("Two long, parallel wires are separated by " << L << " . Each wire has a " << I << " current, but the currents are in opposite directions.");

		Q(A, "Determine the magnitude of the net magnetic field midway between the wires.");
		Quantity mu0 = { 4 * M_PI* 1e-7, "T m / A" };
		Quantity r = L / 2;
		Quantity B = mu0 / (2 * M_PI) * I / r;
		Quantity Bnet = 2 * B;
		A(Bnet);

		DistanceM d1 = 1.1;
		DistanceM d2 = 3.3;
		Q(B, "Determine the magnitude of the net magnetic field at a point " << d1 << " to the side of one wire and " << d2 << " from the other wire. The point is in the same plane as the wires.");

		Quantity B1 = mu0 / (2 * M_PI) * I / d1;
		Quantity B2 = mu0 / (2 * M_PI) * I / d2;
		Quantity Bnet2 = B1 - B2;
		A(Bnet2);
	}
};