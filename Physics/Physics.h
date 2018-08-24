#pragma once

#include "stdafx.h"

#include <assert.h>
#include <exception>
#include <iostream>
#include <map>

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

namespace phys {
	class Exception : std::exception {
	private:
		std::string msg;

	public:
		Exception(std::string msg) : msg(msg) {}
		const char* what() const throw() { return msg.c_str(); }
	};

	class Unit {
	private:
		std::map<const std::string, int> units;

		void init(const char* unit);

	public:
		inline Unit(std::string unit) { init(unit.c_str()); }
		inline Unit(const char* unit) { init(unit); }
		Unit() {}

		Unit operator *= (const Unit& u);
		Unit operator * (const Unit& u) const;

		Unit operator /= (const Unit& u);
		Unit operator / (const Unit& u) const;

		bool operator == (const Unit& u) const;
		bool operator != (const Unit& u) const { return !(*this == u); }

		inline friend std::ostream& operator << (std::ostream& o, const Unit& u) { return o << u.toString(); }

		Unit sqrt() const;
		std::string toString() const;
	};

	class Quantity {
	public:
		double quantity;
		Unit unit;

		Quantity(double value, Unit unit) : quantity(value), unit(unit) {}
		Quantity(double value) : quantity(value) {}
		Quantity() : quantity(0), unit("") {}

		Quantity magnitude() const { return Quantity((quantity < 0) ? -quantity : quantity, unit); }
		Quantity sqrt() const { return Quantity(::sqrt(quantity), unit.sqrt()); }
		std::string toString() const;

		friend Quantity operator * (double d, const Quantity& q) { return Quantity(d) * q; }
		inline Quantity operator * (const Quantity& q) const { return Quantity(quantity * q.quantity, unit * q.unit); }

		friend Quantity operator / (double d, const Quantity& q) { return Quantity(d) / q; }
		Quantity operator / (double d) const { return Quantity(quantity / d, unit); }
		Quantity operator / (const Quantity& q) const { return Quantity(quantity / q.quantity, unit / q.unit); }
		Quantity operator /= (const Quantity& q) { quantity /= q.quantity; unit /= q.unit; }

		Quantity operator + (const Quantity& q) const { if (unit != q.unit) throw Exception("Units are not the same"); return Quantity(quantity + q.quantity, q.unit); }

		Quantity operator - (const Quantity& q) const { if (unit != q.unit) throw Exception("Units are not the same"); return Quantity(quantity - q.quantity, q.unit); }
		Quantity operator - () const { return Quantity(-quantity, unit); }

		inline friend std::ostream& operator << (std::ostream& o, const Quantity& q) { return o << q.toString(); }
	};

	class Vector {
	public:
		double x, y, z;
		Unit unit;

		Vector(double x = 0, double y = 0, double z = 0, Unit unit = "") : x(x), y(y), z(z), unit(unit) {}

		inline Quantity magnitude() const { return Quantity(sqrt(x*x + y * y + z * z), unit); }

		inline Vector unitV() const { return *this / magnitude(); }

		inline Quantity operator * (const Vector& v) const { return Quantity(x * v.x + y * v.y + z * v.z, unit * v.unit); }
		inline friend Vector operator * (const Quantity& q, const Vector& v) { return Vector(q.quantity * v.x, q.quantity * v.y, q.quantity * v.z, q.unit * v.unit); }

		Vector operator / (double d) const { return Vector(x / d, y / d, z / d, unit); }
		Vector operator / (const Quantity& q) const { return Vector(x / q.quantity, y / q.quantity, z / q.quantity, unit / q.unit); }

		std::string toString() const { return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "> " + unit.toString(); }

		friend std::ostream& operator << (std::ostream& o, Vector v) { return o << v.toString(); }
	};

#define MAKE_SPECIALIZED_CLASS(className, superClass, unitName) \
class className : public superClass {\
private:\
	superClass enforce(const superClass& q) {\
		if (q.unit != unitName) throw Exception("Unit must be " unitName " (was " + q.toString() + ")"); \
		return q;\
	}\
public:\
	className(superClass q) : superClass(enforce(q)) {}\


#define MAKE_SPECIALIZED_QUANTITY(className, unitName) \
MAKE_SPECIALIZED_CLASS(className, Quantity, unitName) \
	className(double d) : Quantity(d, unitName) {} \
}

	MAKE_SPECIALIZED_QUANTITY(Mass, "kg");
	MAKE_SPECIALIZED_QUANTITY(Charge, "C");

#define MAKE_SPECIALIZED_VECTOR(className, unitName) \
MAKE_SPECIALIZED_CLASS(className, Vector, unitName) \
	className(double x = 0.0, double y = 0.0, double z = 0.0) : Vector(x, y, z, unitName) {} \
};\
MAKE_SPECIALIZED_QUANTITY(className##M, unitName)

	MAKE_SPECIALIZED_VECTOR(Force, "N");
	MAKE_SPECIALIZED_VECTOR(Distance, "m");
	MAKE_SPECIALIZED_VECTOR(Acceleration, "m / s^2");
	MAKE_SPECIALIZED_VECTOR(Velocity, "m / s");

#undef MAKE_SPECIALIZED_QUANTITY
#undef MAKE_SPECIALIZED_VECTOR
#undef MAKE_SPECIALIZED_CLASS

	// Constant Quantities
	namespace cnstQ {
		const Quantity epsilon0 = Quantity(8.854187817e-12, "C^2 / N m^2");
		const Quantity K = 1 / (4 * M_PI * epsilon0);
		const Quantity G = Quantity(6.67e-11, "m^3 / s^2 kg");

		const Charge e = Quantity(1.602e-19, "C");
		const Mass electronMass = Quantity(9.11e-31, "kg");
	}

	Force elecForce(const Charge&, const Charge&, const Distance&);
	ForceM elecForce(const Charge&, const Charge&, const DistanceM&);

	Force gravForce(const Mass&, const Mass&, const Distance&);
	ForceM gravForce(const Mass&, const Mass&, const DistanceM&);
	VelocityM circularVelocity(const DistanceM& r, const AccelerationM& a);
}