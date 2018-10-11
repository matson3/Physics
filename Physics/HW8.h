#pragma once

#include "HW.h"

class HW8 : public HW {
public:
	HW8() : HW(8, 6) { }

	void p1() {
		Conceptual;
	}

	void p2() {
		Conceptual;
	}

	void p3() {
		Conceptual;
	}

	void p4() {
		model("There is a light pole on one bank of a small pond. You are standing up while fishing on the other bank. After reflection from the surface of the water, part of the light from the bulb at the top of the pole reaches your eyes. Use a ray diagram to help find a point on the surface of the water from where the reflected ray reaches your eyes.");

		Q(A, "Determine an expression for the distance from this point on the water to the bottom of the light pole if the height of the pole is H, your height is h, and the distance between you and the light pole is l.");
		A("l / (1 + h / H)");
	}

	void p5() {
		DistanceM f = centi(20);
		double m = 1.4;
		Q(A, "A person views his face in a +" << f << " focal length concave mirror. Where should his face be in order to form an up right image that is magnified by a factor of " << m << "?");
		DistanceM s = (m - 1) / m * f;
		A(s);
	}

	void p6() {
		Conceptual;
	}
};