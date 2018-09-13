#pragma once
#include "stdafx.h"

#include "HW.h"
#include "Physics.h"
#include "textAligner.h"

#include <vector>

class HW4 : public HW {
public:
	HW4() : HW(4, 10) {}

	void p1() {
		VelocityM v = 2.0e5;
		model(
			"An alien from a planet in the galaxy M31(Andromeda) has a ray gun that shoots protons at a speed of " << v << ". Design a magnetic shield that will deflect the protons away from your body.\n"
			"Figure 1: proton enter from left, moves right into rectangular magnetic region B, where it is deflected upwards in a semicircle arc, allowing it to leave on a path parallel to the entering path. R touches the edge of B region and extends into the region, meeting at the path of the proton."
		);

		Mass mProton = 1.67e-27;
		Charge qProton = 1.6e-19;
		DistanceM R = 2.0;
		Q(A, "Suppose that the magnetic field has horizontal direction and you want to deflect the beam through a path with radius R = " << R << " as shown in (Figure 1). Find the field strength needed to achieve the desired deflection. The mass of a proton is " << mProton << " and its charge is " << qProton << '.');

		Quantity force = mProton * v * v / R;
		Quantity Bmag = force / (qProton * v);
		Bmag.unit = "T";
		A(Bmag);

		Q(B, "What is the direction of the magnetic field in the region, that would cause the deflection shown for the proton beam?");
		A("into the page");
		// If you don't understand why, make sure you REALLY understand the right-hand rule, because you clearly don't

		Q(C, "What is the direction of the magnetic force in the region defined in (Figure 1), that would cause the deflection shown for the proton beam?");
		A("toward the center of the curved path");
	}

	void p2() {
		Quantity magField = { 0.02, "T" };
		DistanceM orbitRadius = milli(9);
		model("An electron and a proton, moving side by side at the same speed, enter a " << magField << " magnetic field. The electron moves in a circular path of radius " << orbitRadius << '.');

		Q(A, "Determine the radius of the proton");
		Quantity electronW = e * magField / electronMass; // Angular Velocity
		electronW.unit = "1 / s";
		Quantity electronV = electronW * orbitRadius;

		VelocityM protonV = electronV;
		Quantity magForce = e * protonV * magField;
		magForce.unit = "kg m / s^2";
		DistanceM protonRadius = protonMass * protonV * protonV / magForce;
		A(protonRadius);
	}

	void p3() {
		Quantity Efield = { 60'000, "N / C" };
		Quantity Bfield = { 0.05, "T" };
		model("A mass spectrometer has a velocity selector that allows ions traveling at only one speed to pass with no deflection through slits at the ends. While moving through the velocity selector, the ions pass through a " << Efield << " E field and a " << Bfield << " B field. The quantities v, E, and B are mutually perpendicular.");

		Q(A, "Determine the speed of the ions that are not deflected.");
		Charge q = e;
		ForceM eForce = q * Efield;
		// eForce = bForce = qvB
		VelocityM requisiteVelocity = (eForce / (q * Bfield)).quantity;
		A(requisiteVelocity);

		Mass mLi = 1.16e-26;
		Q(B, "After leaving the velocity selector, the ions continue to move in the " << Bfield << " magnetic field. Determine the radius of curvature of a singly charged lithium ion, whose mass is " << mLi << ".");
		// |q| / m = v / (B r)
		DistanceM radius = (mLi * requisiteVelocity / (Bfield * q.magnitude())).quantity;
		A(radius);
	}

	void p4() {
		VelocityM v = 9e6;
		Quantity magField = { 0.14, "T" };
		model(
			"An electron moves at speed " << v << " toward the right between two parallel plates, such as shown in (Figure 1). A " << magField << " magnetic field points into the paper parallel to the plate surfaces.\n"
			"Figure 1: electron is between two plates, a positive one above and a negative one below."
		);

		Q(A, "Determine the magnitude of the magnetic force that the magnetic field exerts on the electron.");
		ForceM magForce = (-e * v * magField).magnitude().quantity;
		A(magForce);

		Q(B, "Determine the direction of the magnetic force that the magnetic field exerts on the electron.");
		A("downward");

		Q(C, "What should be the magnitude of an E field caused by oppositely charged plates to produce an electric force that just balances the magnetic force?");
		Quantity eField = { (magForce / e).quantity, "N / C" };
		A(eField);

		Q(D, "What should be the direction of an E field caused by oppositely charged plates to produce an electric force that just balances the magnetic force?");
		A("downward");
	}
	
	void p5() {
		Mass m = 1100;
		Quantity earthT = { 3.5e-5, "T" };
		model("A " << m << " car moves west along the equator. At this location Earth's magnetic field is " << earthT << " and points north parallel to Earth's surface.");

		Charge q = -2.5e-3;
		double percent = 0.010 / 100;
		std::string percentString = std::to_string(percent * 100) + "%";
		Q(A, "If the car carries a charge of " << q << ", how fast must it move so that the magnetic force balances " << percentString << " of Earth's gravitational force exerted on the car?");
		ForceM grav = (m * g).magnitude().quantity;
		// FB = qvB
		Velocity v = ((percent * grav) / (q.magnitude() * earthT)).quantity;
		A(v);
	}

	void p6() { Conceptual; }

	void p7() {
		model(
			"circuit:\n"
			"A R1 J I -E1+ B C R3 D E +E2- F G R2 H\n"
			"I ->"
		);
		Q(A, "Write Kirchhoff's loop rule (clockwise) for the circuit");
		A("IR3 + E2 + IR2 + IR1");

		Voltage e1 = 12.0;
		Voltage e2 = 3.0;
		Resistance R1 = 1;
		Resistance R2 = R1;
		Resistance R3 = 16;
		Q(B, "Determine the current in the circuit for the case in which E1 = " << e1 << " , E2 = " << e2 << ", R1 = R2 = " << R1 << ", and R3 = " << R3 << ".");
		Resistance R = R1 + R2 + R3;
		Voltage V = e1 - e2;
		Ampage I = current(R, V);
		A(I);

		Q(C, "Determine the potential difference from A to B.");
		Resistance RAB = R1;
		Voltage VAB = e1 - voltage(I, RAB);
		A(VAB);
	}

	void p8() {
		Power w1 = 30;
		Power w2 = 60;
		Voltage v = 120;
		model("Two lightbulbs use " << w1 << " and " << w2 << ", respectively, when connected in parallel to a " << v << " source.");

		Q(A, "How much power does each bulb use when connected in series across the " << v << " source, assuming that their resistances remain the same?");
		Resistance r1 = (v * v / w1).quantity;
		Resistance r2 = (v * v / w2).quantity;

		Resistance Rs = r1 + r2;
		Ampage Is = current(v, Rs);
		Power w1s = (Is * Is * r1).quantity;
		Power w2s = (Is * Is * r2).quantity;
		A(w1s << ", " << w2s);
	}

#define MAKE_LIST_STRING(ss, arr) do {\
for (int i = 0; i < arr.size() - 1; i++) \
	ss << arr[i].quantity << ", ";\
ss << "and " << arr[arr.size() - 1] << '.';\
} while(0)

	void p9() {
		Voltage v = 12;
		Resistance ri = 3;
		std::vector<Resistance> R = { 1, 2, 3, 4, 5, 6 };
		model("A battery has an emf of " << v << " and an internal resistance of " << ri << ".");

		std::stringstream ss;
		MAKE_LIST_STRING(ss, R);
		Q(A, "Determine the power delivered to a resistor R connected to the battery terminals for values of R equal to " << ss.str());
		ss.str("");

		std::vector<Power> P;
		for (int i = 0; i < R.size(); i++) {
			Ampage I = current(v, ri + R[i]);
			Power p = (I * I * R[i]).quantity;
			P.push_back(p);
		}

		MAKE_LIST_STRING(ss, P);
		A(ss.str());
		ss.str("");

		Q(C, "At what resistance the maximum power is delivered?");
		Power maxPower = P[0];
		int maxIndex = 0;
		for (int i = 1; i < P.size(); i++) {
			if (P[i] > maxPower) {
				maxPower = P[i];
				maxIndex = i;
			}
		}
		A(R[maxIndex]);
	}

	void p10() {
		model("A wire whose resistance is R is stretched so that its length is tripled while its volume remains unchanged.");
		
		Q(A, "Determine the resistance of the stretched wire.");
		double L = 3;
		// V = LA
		double a = 1 / L;
		double ratio = L / a;

		A(ratio << " * R");
	}
};