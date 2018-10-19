#pragma once

#include "stdafx.h"
#include "HW.h"

static inline DistanceM imageDistance(DistanceM f, DistanceM d) {
	return 1 / (1 / f - 1 / d);
}

static inline Quantity magnification(DistanceM imageD, DistanceM distance) {
	return -imageD / distance;
}

static Quantity toCenti(const DistanceM d) {
	return Quantity(d.quantity * 100, "cm");
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

class HW9 : public HW {
public:
	HW9() : HW(9, 10) { }

	void p1() {
		DistanceM h = 1.9;
		DistanceM eyeD = centi(5.5);
		Q(A, "A person is " << h << " tall. Where should he place the top of a mirror on the wall so he can see the top of his head? Assume his eyes are " << eyeD << " below the top of his head. Find a minimal vertical distance from the level of the persons eyes to the top of the mirror.");

		A(eyeD / 2);
	}

	void p2() {
		DistanceM moonD = kilo(3.5e3);
		DistanceM moonToEarth = kilo(3.8e5);
		DistanceM f = 16.9;

		Q(A, "The Moon's diameter is " << moonD << ", and its distance from Earth is " << moonToEarth << ". The image is formed by the Hale Telescope reflecting mirror, which has a focal length of " << f << ". Determine the distance from the image to the mirror.");

		DistanceM distanceToImage = imageDistance(f, moonToEarth);
		A(distanceToImage);

		Q(B, "Determine the size of the image.");

		Quantity mag = magnification(distanceToImage, moonToEarth);
		Quantity imageHeight = mag * moonD;
		A(imageHeight.magnitude());
	}

	void p3() {
		DistanceM f = centi(20);
		model("Use ray diagrams and the mirror equation to locate the position, orientation, and type of image of an object placed in front of a concave mirror of focal length " << f << ".");

		DistanceM objDist = centi(200);
		Q(A, "The object distance is " << objDist << " , find the distance from the image to the mirror (positive for real image and negative for virtual image).");
		Quantity imageDist = imageDistance(f, objDist);
		A(imageDist);

		Q(B, "The object distance is " << objDist << " , find the magnification (positive for upright image and negative for inverted image).");
		A(magnification(imageDist, objDist));

		objDist = centi(45);
		Q(C, "The object distance is " << objDist << ", find the distance from the image to the mirror (positive for real image and negative for virtual image).");
		
		imageDist = imageDistance(f, objDist);
		A(imageDist);

		Q(D, "The object distance is " << objDist << " , find the magnification (positive for upright image and negative for inverted image).");
		A(magnification(imageDist, objDist));

		objDist = centi(14);
		Q(E, "The object distance is " << objDist << ", find the distance from the image to the mirror (positive for real image and negative for virtual image).");

		imageDist = imageDistance(f, objDist);
		A(imageDist);

		Q(E, "The object distance is " << objDist << ", find the magnification (positive for upright image and negative for inverted image).");
		A(magnification(imageDist, objDist));
	}

	void p4() {
		Conceptual;
	}

	void p5() {
		DistanceM d = 2.5;
		Quantity mag = 0.9;
		Q(A, "A cylindrical mirror in a clothing store causes the customer's width to have a linear magnification of " << mag << " when the customer stands " << d << " from the mirror. Determine the focal lenght of the mirror (positive for concave mirror and negative for convex mirror).");

		DistanceM imageDist = -d * mag;
		DistanceM f = 1 / (1 / d + 1 / imageDist);
		A(f);
	}

	void p6() {
		DistanceM f = centi(5);
		model("You examine the fine print in a legal contract with a magnifying glass of focal length " << f << ".");

		DistanceM imageDist = centi(30);
		Q(A, "How far from the lens should you hold the print to see a final virtual image " << imageDist << " from the lens (at the eye's near point)?");

		// virtual, therefore -imageDist
		DistanceM objDist = imageDistance(f, -imageDist);
		A(objDist);

		Q(B, "Determine the angular magnification of the magnifying glass.");

		Quantity angMag = imageDist / objDist;
		A(angMag);
	}

	void p7() {
		DistanceM lens1x = centi(-20);
		DistanceM lens1f = centi(10);
		DistanceM lens2x = centi(20);
		DistanceM lens2f = centi(8);
		DistanceM objH = centi(1);
		DistanceM objX = centi(-50);
		model("A compound lens system consists of two converging lenses, one at x=" << lens1x << " with focal length f1=" << lens1f << ", and the other at x=" << lens2x << " with focal length f2=" << lens2f << ". An object " << objH << " tall is placed at x=" << objX << ".");

		Q(A, "What is the location of the final image produced by the compound lens system? Give the x coordinate of the image.");
		DistanceM image1so = lens1x - objX;
		DistanceM image1si = imageDistance(lens1f, image1so);
		DistanceM image1x = image1si + lens1x;

		DistanceM image2so = lens2x - image1x;
		Quantity image2si = imageDistance(lens2f, image2so);
		Quantity image2x = image2si + lens2x;
		A(toCenti(image2x));

		Q(B, "How tall is the image?");
		Quantity mag1 = magnification(image1si, image1so);
		Quantity mag2 = magnification(image2si, image2so);
		Quantity sysMag = mag1 * mag2;
		Quantity height = objH * sysMag;
		A(toCenti(height));

		Q(C, "Is the final image upright or inverted, relative to the original object at x=" << objX);
		A((height.quantity < 0 ? "inverted" : "upright"));

		DistanceM lens3x = 0;
		Q(D, "Now remove the two lenses at x=" << lens1x << " and x=" << lens2x << " and replace them with a single lens of focal length f3 at x=" << lens3x << ". We want to choose this new lens so that it produces an image at the same location as before.");
		DistanceM image3so = lens3x - objX;
		DistanceM image3si = image2x - lens3x;
		DistanceM f = 1 / (1 / image3so + 1 / image3si);
		A(toCenti(f));

		Q(E, "Is the image formed by f3 the same size as the image formed by the compound lens system? Does it have the same orientation?");
		Quantity mag3 = magnification(image3si, image3so);
		A(
			"The image is " <<
			((abs(abs(mag3.quantity) - abs(sysMag.quantity)) <= 1e-2) ? "the same" : "a different") <<
			" size and oriented " <<
			((sgn(mag3.quantity) == sgn(sysMag.quantity)) ? "the same" : "differently") <<
			"."
		);
	}

	void p8() {
		DistanceM objLensF = centi(3);
		DistanceM eyeLensF = centi(0.4);
		DistanceM so = 20;
		model("A telescope consisting of a " << toCenti(objLensF) << " objective lens and a " << toCenti(eyeLensF) << " eyepiece is used to view an object that is " << so << " from the objective lens.");

		DistanceM si = centi(100);
		Q(A, "What must be the distance between the objective lens and eyepiece to produce a final virtual image " << toCenti(si) << " to the left of the eyepiece?");
		si = -si;
		DistanceM objLensI = imageDistance(objLensF, so);
		DistanceM d = 1 / (1 / eyeLensF + 1 / si) + objLensI;
		A(toCenti(d));

		Q(B, "What is the total angular magnification?");
		Quantity mag = magnification(objLensI, so) * magnification(si, d - objLensI);
		// pick a height
		DistanceM ho = 1;
		DistanceM hi = ho * mag;
		Quantity thetao = ho / so;
		Quantity thetai = hi / si;

		Quantity angMag = thetai / thetao;
		A(angMag);
	}

	void p9() {
		DistanceM width = kilo(2);
		DistanceM height = kilo(5);
		DistanceM f = 0.4;

		model("To photograph a landscape " << width << " wide from a height of " << height << ", Joe uses an aerial camera with a lens of " << f << " focal length.");

		Q(A, "What is the width of the image on the detector surface?");
		DistanceM si = imageDistance(f, height);
		Quantity mag = magnification(si, height);
		A(toCenti(width * mag));
	}

	void p10() {
		DistanceM f = centi(50);
		DistanceM so = centi(25);
		DistanceM so2 = centi(40);
		model("A 35-year-old patent clerk needs glasses of " << toCenti(f) << " focal length to read patent applications that he holds " << toCenti(so) << " from his eyes. Five years later, he notices that while wearing the same glasses, he has to hold the patent applications " << toCenti(so2) << " from his eyes to see them clearly.");

		Q(A, "What should be the focal length of new glasses so that he can read again at " << so << "?");
		DistanceM si2 = imageDistance(f, so2);
		DistanceM f2 = 1 / (1 / si2 + 1 / so);
		A(f2);
	}
};