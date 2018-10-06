#pragma once

#include "stdafx.h"

#include "HW.h"

class HW6 : public HW {
public:
	HW6() : HW(6, 10) {}

	void p1() {
		Quantity B = { 5.8e-5, "T" };
		int angle = 72;
		Quantity area = { 5, "m^2" };
		Q(A, "Determine the magnitude of the magnetic flux through the south-facing window of a house in British Columbia, where Earth's B field has a magnitude of " << B << " and the direction of B field is " << angle << "degrees below horizontal with the horizontal component of B field directed to the north. Assume the area of the window is " << area << ".");

		double angleR = R(72);
		Quantity flux = B * area * cos(angleR);
		A(flux);

		Q(B, "Determine the magnitude of the magnetic flux through the west-facing window that has the same area.");
		A(Quantity(0, "T"));
	}

	void p2() {
		model(
			"Figure 1: iron core rod with wire coiled around it. The wire is connected to a battery with the positive end facing left and an open switch. There is a wire loop to the right of the iron core.\n"
			"Figure 2: The same as figure 1, but the battery is reversed.\n"
			"Consider the arrangement shown in (Figure 1)."
		);

		Q(A, "When the switch is open, which of the following statements about the magnetic flux through the wire loop is true? Assume that the direction of the vector area of the wire loop is to the right.");
		A("There is no magnetic flux through the wire loop.");

		Q(B, "What is the direction of the induced current in the wire loop (as seen from the left) when the switch is open?");
		A("There is no induced current.");

		Q(C, "Now the switch on the electromagnet is closed. What is the direction of the induced current in the wire loop immediately after the switch is closed (as seen from the left)?");
		A("The induced current is counterclockwise.");

		Q(D, "Finally, the switch on the electromagnet is reopened. The magnitude of the external magnetic flux through the wire loop ______ (A. increases, B. decreases, C. remains constant), and there is _______ (A. zero, B. a clockwise, C. a counterclockwise) current induced in the loop (as seen from the left).");
		A("B, B");

		model("Now consider the new arrangement shown in (Figure 2). Note that the orientation of the battery is reversed with respect to the first arrangement you considered. Answer the following questions related to the arrangment with the new battery orientation.");
		Q(E, "The switch on the electromagnet, initially open, is closed. What is the direction of the induced current in the wire loop (as seen from the left)?");
		A("The induced current is clockwise.");

		Q(F, "Now the switch on the electromagnet is reopened. The magnitude of the external magnetic flux through the wire loop ______ (A. increases, B. decreases, C. remains constant), and there is _______ (A. zero, B. a clockwise, C. a counterclockwise) current induced in the loop (as seen from the left.");
		A("B, C");
	}

	void p3() {
		model(
			"A bar magnet induces a current in an N-turn coil as the magnet moves closer to it as shown in (Figure 1). The coil's radius is R m, and the average induced emf across the bulb during the time interval is e V.\n"
			"Figure 1: Bar magnet, N pole up, S down. Over wire loop with bulb attached."
		);

		Q(A, "Find the rate of change of magnetic field.");
		A("e / N pi R^2");

		Q(B, "Determine the induced current. Assume that R0 is the resistance of the coil.");
		A("e / R0");

		Q(C, "Is the direction of the induced current from lead a to b, or from b to a?");
		A("From a to b.");
	}

	void p4() {
		DistanceM d = 1;
		Resistance R = 4;
		Quantity v = { 25, "m / s" };
		Quantity B = { 5e-5, "T" };
		int angle = 53;
		model("An experimental apparatus has two parallel horizontal metal rails separated by " << d << ". A " << R << " resistor is connected from the left end of one rail to the left end of the other. A metal axle with metal wheels is pulled toward the right along the rails at a speed of " << v << ". Earth's uniform " << B << " field points down at an angle of " << angle << " degrees below the horizontal.");

		Q(A, "Determine the the average induced emf.");
		double angleR = R(angle + 90);
		Quantity dB = (B - B);
		Quantity A = d * DistanceM(0);
		Quantity dA = d * v * Time(1);
		Quantity dMagFlux = (dB * A + B * dA) * cos(angleR);
		Time dt = 1;
		Voltage V = -(dMagFlux / dt).quantity;
		A(V);

		Q(B, "Determine the induced current.");
		Ampage I = current(V, R);
		A(I);

		Q(C, "Determine the power dissipated through the resistor.");
		Quantity P = { (I * V).quantity, "W" };
		A(P);
	}

	void p5() {
		Voltage V = 4.2;
		int N = 55;
		Quantity B = { 0.04, "T" };
		model("You need to make a generator for your bicycle light that will provide an alternating emf whose peak value is " << 4.2 << ". The generator coil has " << N << " turns and rotates in a " << B << " magnitude B field.");

		int rpm = 400;
		Q(A, "If the coil rotates at " << rpm << " revolutions per second, what must the area of the coil be to develop this emf?");
		double omega = 2 * M_PI * rpm;

		Quantity A = { (V / (N * B * omega) ).quantity, "m^2" };
		A(A);
	}

	void p6() {
		Voltage V1 = 120;
		Voltage V2 = 8;
		Quantity N2 = 40;
		model("You are fixing a transformer for a toy truck that uses an " << V2 << " emf to run it. The primary coil of the transformer is broken; the secondary coil has " << N2 << " turns. The primary coil is connected to a " << V2 << " wall outlet.");

		Q(A, "How many turns should you have in the primary coil?");
		Quantity N1 = 1 / (V2 / N2 / V1);
		A(N1);

		Voltage V1prime = 240;
		Q(B, "If you then connect this primary coil to a " << V1prime << " source, what emf would be across the secondary coil?");
		Quantity V2prime = V1prime / N1 * N2;
		A(V2prime);
	}

	void p7() {
		Quantity turns = 200;
		DistanceM radius = centi(15);
		Quantity B = { 0.10, "T" };
		model("You want to build a generator for a multi-day canoe trip. You have a fairly large permanent magnet, some wire, and a lightbulb. You may build it as follows. Wind the wire for about 200 turns into a coil of 15 cm radius. Tape up the coil and place it in the region between the poles of the magnet that produces a 0.10 T magnetic field. Connect a hand crank to the coil and rotate it at a rotational speed w.");

		Voltage V = 6;
		Q(A, "Suppose we need " << V << " to light the bulb (the peak voltage). What is the required rotational speed?");
		Quantity A = M_PI * radius * radius;
		Quantity w = { (V / (B * A * turns)).quantity, "rad / s" };
		A(w);
	}
	
	void p8() { Conceptual; }

	void p9() {
		Q(A, "One coil is placed on top of another. The bottom coil is connected in series to a battery and a switch. With the switch closed, there is a clockwise current in the bottom coil. When the switch is opened, the current in the bottom coil decreases abruptly to zero. What is the direction of the induced current in the top coil, as seen from above while the current in the bottom coil decreases?");
		A("Clockewise");
	}

	void p10() {
		DistanceM L = 1.5;
		Resistance R = 2;
		Mass m = 0.22;
		Quantity B = { 0.5e-4, "T" };

		model("In a new lab experiment, two parallel vertical metal rods are separated by L = " << L << ". A R = " << R << " resistor is connected from the top of one rod to the top of the other. A m = " << m << " horizontal metal bar falls between the rods and makes contact at its ends with the rods. A B field of " << B << " points horizontally between the rods. The bar should eventually reach a terminal falling velocity (constant speed) when the magnetic force of the magnetic field on the induced current in the bar balances the downward force due to the gravitational pull of the Earth.");
		Q(A, "Develop in symbols an expression for the current through the bar as it falls.");
		// I didn't want to use paper to figure out the formula, so I used the Unit class to serve as variables and built the formula from there
		Unit dAform = Unit("L") * Unit("v");
		Unit dFluxForm = Unit("B") * dAform;
		Unit dTimeForm = "";
		Unit Vform = dFluxForm / dTimeForm;
		Unit Iformula = Vform / "R";
		A("I = " << Iformula);

		Q(B, "Determine in symbols an expression for the magnetic force exerted on the falling bar (and determine the direction of that force). Remember that an electric current passes through it, and the bar is falling in the magnetic field.");
		Unit FbForm = Iformula * "L" * "B";
		A(FbForm);

		Q(C, "Determine the final constant speed of the falling bar for the given values.");
		Quantity Fg = (g.magnitude() * m);
		VelocityM vT = (Fg * R / (L * L * B * B)).quantity;
		A(vT);

		Q(D, "Is this process realistic?");
		A("Speed of light = " << VelocityM(3e8));
	}
};