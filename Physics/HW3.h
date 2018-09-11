#pragma once
#include "stdafx.h"

#include "HW.h"
#include "Physics.h"
#include "textAligner.h"

class HW3 : public HW {
private:
	HW3() : HW(3, 5) {}

public:
	void p1() {
		Time time = 9.6;
		Quantity electrons = { 9.6e20, "electrons" };
		model("A long wire is connected to the terminals of a battery. In " << time << ", " << electrons << " pass a cross section along the wire. The electrons flow from left to right.");

		Q(A, "Determine the current in the wire.");
		Charge dq = electrons.quantity * cnstQ::e;
		Quantity current = dq / time;
		A(current);

		Q(B, "What is the direction of the electric current?");
		A("from right to left");
	}

	void p2() {
		Voltage v = 9.0;
		Ampage i = 0.5;
		model("A " << v << " battery is connected to a resistor so that there is a " << i << " current through the resistor.");

		Work w = 220;
		Q(A, "For how long should the battery be connected in order to do " << w << " of work while separating charges?");
		Power pow = power(i, v);
		pow.unit = "J / s";

		Time t = w / pow;
		A(t);
	}

	void p3() {
		Ampage I = 1.0;
		Voltage V = 12;

		Q(A, "An automobile light has a " << I << " current when it is connected to a " << V << " battery. Determine the resistance of the light.");
		Resistance R = resistance(I, V);
		A(R);

		Q(B, "Determine the power delivered to the same automobile light.");
		Power P = power(I, V);
		A(P);

		I = milli(50);
		R = 2.0;
		Q(C, "What potential difference is needed to produce a current of " << I << " through a " << R << " resistor?");
		V = voltage(I, R);
		A(V);
	}

	void p4() {
		Quantity x = { 3, "cm" };
		Quantity y = { 10, "cm" };
		Quantity z = { 4, "cm" };
		model("The rectangular block below has front-face dimensions of " << y << " by " << z << ", with a depth of " << x << ". You will be asked to treat this object as an electrical resistor.");

		Q(A, "Rank the block based on its electrical resistance along the three illustrated coordinate directions (x, y, and z).\n"
			"Rank from largest to smallest.To rank items as equivalent, overlap them.");
		Quantity RatioX = x / (y * z);
		Quantity RatioY = y / (x * z);
		Quantity RatioZ = z / (x * y);
#define Ratio(x) "Along " #x ": " << Ratio##x
		A(Ratio(X) << "\n"Ratio(Y) << "\n"Ratio(Z));

		Q(B, "If all of the dimensions of the block double (to become " << 2 * x << " wide, " << 2 * z << " tall, and " << 2 * y << " deep), what happens to the resistance along each axis?");
		A("The resistance is halved.");
	}

	void p5() {
		Conceptual;
	}
}