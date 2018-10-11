#pragma once

#include "stdafx.h"
#include "HW.h"

class HW7 : public HW {
public:
	HW7() : HW(7, 10) {}

	void p1() {
		Quantity degrees = { 64, "degrees" };
		model("Two mirrors are oriented at right angles. A narrow light beam strikes the horizontal mirror at an incident angle of theta1 = " << degrees << ", reflects from it, and then hits the vertical mirror.");

		Q(A, "Determine the direction of the light after leaving the vertical mirror.");
		A("Same angle as in");

		Q(B, "Determine the angle of incidence at the vertical mirror of the light after leaving the vertical mirror.");
		A(90 - degrees);
	}

	void p2() {
		model(
			"Your eye is designed to work in air. Surrounding it with water impairs its ability to form images. Consequently, scuba divers wear masks to allow them to form images properly underwater. However, this does affect the perception of distance, as you will calculate.\n"
			"Consider a flat piece of plastic(index of refraction np) with water(index of refraction nw) on one side and air (index of refraction na) on the other. If light is to move from the water into the air, it will be refracted twice: once at the water / plastic interface and once at the plastic / air interface."
		);

		Q(A, "If the light strikes the plastic (from the water) at an angle thetaW, at what angle thetaA does it emerge from the plastic (into the air)?");
		A("asin(nw / na * sin(thetaW)");

		model("Humans estimate distance based on several different factors, such as shadows and relative positions. The most important method for estimating distance, triangulation, is performed unconsciously. Triangulation is based on the fact that light from distant objects strikes each eye at a slightly different angle. Your brain can then use that information to determine the angle thetaW as shown in the figure. (Figure 1) In the figure, points L and R represent your left and right eyes, respectively. The distance between your eyes is 2l, and the distance to the object, point O, is D.");
		Q(A, "What is the distance to the object in terms of thetaW and l?");
		A("l / tan(thetaW)");

		Q(C, "If the distance to the object is more than about 0.4 m, then you can use the small-angle approximation tan(theta) ~ theta. What is the formula for the distance D to the object, if you make use of this approximation?");
		A("l / thetaW");

		model(
			"Your eyes determine thetaW by assuming that thetaA and thetaW (in the figure) are equal. This is true, unless the light rays are bent before they reach your eyes, as they are if you're wearing a scuba mask underwater.\n"
			"Underwater, the situation changes, as shown in the figure. (Figure 2).Your eyes will calculate an apparent distance d using the angle thetaA that reaches your eyes, instead of the correct geometric angle thetaW. This is the same thetaA that you calculated in Part A. Note that there are no important geometric considerations arising from the refraction except the substitution of thetaA for thetaW, because the refraction takes place so close to your eyes. If the problem discussed someone looking out of the porthole of a submarine, the geometry would become more complicated."
		);

		Q(D, "Now use the expression found in Part C for the distance between your eyes and the object at point O, and find the ratio of the apparent distance to the real distance, d/D. Remember that the apparent distance is the distance calculated by your eyes using the angle thetaA instead of the angle thetaW. Since we are dealing with small angles, you may use the approximations sin(x) ~ x and asin(x) ~ x.");
		A("na / nw");

		double nw = 1.33;
		double na = 1.00;
		Q(E, "Given that nw=" << nw << " and na=" << na << ", by what percent do objects underwater appear closer than they actually are?");
		A((1 - na / nw) * 100 << '%');
	}

	void p3() {
		DistanceM d = centi(30);
		Quantity degrees = { 45, "degrees" };
		double radians = R(degrees.quantity);
		double nw = 1.33;
		model("An aquarium open at the top has " << d << "-deep water in it. You shine a laser pointer into the top opening so it is incident on the air-water interface at a " << degrees << " angle relative to the vertical. You see a bright spot where the beam hits the bottom of the aquarium. The index of refraction of water is " << nw << ".");

		DistanceM delta = centi(5);
		Q(A, "How much water (in terms of height) should you add to the tank so the bright spot on the bottom moves " << delta << "?");
		double thetaW = asin(sin(radians) / nw);
		DistanceM water = delta / tan(thetaW);
		A("13 cm");
	}

	void p4() {
		double n = 1.5;
		model("A beam of light from a monochromatic laser shines into a piece of glass. The glass has thickness L and index of refraction n=" << n << ". The wavelength of the laser light in vacuum is L/10 and its frequency is f. In this problem, neither the constant c nor its numerical value should appear in any of your answers.");

		Q(A, "How long does it take for a short pulse of light to travel from one end of the glass to the other?");
		A("15 / f");
	}

	void p5() {
		DistanceM depth = 1.4;
		DistanceM length = 12;
		model("A swimming pool is " << depth << " deep and " << length << " long. Is it possible for you to dive to the very bottom of the pool so people standing on the deck at the end of the pool do not see you?");

		Quantity degrees = { 48.5, "degrees" };
		double radians = R(degrees.quantity);
		double nw = 1.33;
		Q(A, "Assume you dive to the very bottom of the pool so people standing on the deck at the end of the pool can see you. Find the minimum height of the person's eyes at the far side of the pool, so you would be observable by this person. Take an angle " << degrees << " for a ray that is incident at the water-air interface (nwater = " << nw << ").");
		DistanceM refractionPoint = depth * tan(radians);
		double thetaAir = asin(nw * sin(radians));
		DistanceM minHeight = (length - refractionPoint) / tan(thetaAir);
		A(minHeight);

		Q(B, "Therefore, is it possible for you to dive to the very bottom of the pool so people standing on the deck at the end of the pool do not see you?");
		A("no");
	}
};