#pragma once

#include "stdafx.h"

#include <assert.h>
#include <exception>
#include <iostream>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

#include "Exception.h"

namespace phys {
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

		Unit operator + (const Unit& u) const { if (*this != u) throw Exception("Units are not the same (" + this->toString() + " & " + u.toString() + ")"); return u; }
		Unit operator - (const Unit& u) const { if (*this != u) throw Exception("Units are not the same (" + this->toString() + " & " + u.toString() + ")"); return u; }

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
		Quantity operator /= (const Quantity& q) { quantity /= q.quantity; unit /= q.unit; return *this; }

		Quantity operator + (const Quantity& q) const { return Quantity(quantity + q.quantity, unit + q.unit); }
		Quantity operator + (double d) const { return Quantity(quantity + d, unit); }

		Quantity operator - (const Quantity& q) const { return Quantity(quantity - q.quantity, q.unit - unit); }
		friend Quantity operator - (double d, const Quantity& q) { return Quantity(d - q.quantity, q.unit); }
		Quantity operator - () const { return Quantity(-quantity, unit); }

		bool operator < (const Quantity& q) const { unit - q.unit; return quantity < q.quantity; }
		inline bool operator > (const Quantity& q) const { q < *this; }
		friend bool operator < (double d, const Quantity& q) { return d < q.quantity; }
		friend bool operator > (double d, const Quantity& q) { return d > q.quantity; }

		inline friend std::ostream& operator << (std::ostream& o, const Quantity& q) { return o << q.toString(); }
	};

	class Vector {
	public:
		double x, y, z;
		Unit unit;

		Vector(double x = 0, double y = 0, double z = 0, Unit unit = "") : x(x), y(y), z(z), unit(unit) {}
		Vector(double angle, Quantity magnitude) : x(magnitude.quantity * cos(angle)), y(magnitude.quantity * sin(angle)), z(0), unit(magnitude.unit) {}
		Vector(Quantity magnitude, double angle) : x(magnitude.quantity * cos(angle)), y(magnitude.quantity * sin(angle)), unit(magnitude.unit) {}

		inline Quantity magnitude() const { return Quantity(sqrt(x*x + y * y + z * z), unit); }

		inline Vector unitV() const { return *this / magnitude(); }

		inline Quantity operator * (const Vector& v) const { return Quantity(x * v.x + y * v.y + z * v.z, unit * v.unit); }
		inline friend Vector operator * (const Quantity& q, const Vector& v) { return Vector(q.quantity * v.x, q.quantity * v.y, q.quantity * v.z, q.unit * v.unit); }

		Vector operator / (double d) const { return Vector(x / d, y / d, z / d, unit); }
		Vector operator / (const Quantity& q) const { return Vector(x / q.quantity, y / q.quantity, z / q.quantity, unit / q.unit); }

		Vector operator - () const { return Vector(-x, -y, -z, unit); }

		Vector operator + (const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z, unit + v.unit); }
		Vector operator - (const Vector& v) const { return *this + -v; }

		std::string toString() const;

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
	className(superClass q) : superClass(enforce(q)) {}


#define MAKE_SPECIALIZED_QUANTITY(className, unitName) \
MAKE_SPECIALIZED_CLASS(className, Quantity, unitName) \
		className(double d) : Quantity(d, unitName) {} \
	}

	MAKE_SPECIALIZED_QUANTITY(Mass, "kg");
	MAKE_SPECIALIZED_QUANTITY(Charge, "C");
	MAKE_SPECIALIZED_QUANTITY(Energy, "J");
	MAKE_SPECIALIZED_QUANTITY(Voltage, "V");

#define MAKE_SPECIALIZED_VECTOR(className, unitName) \
MAKE_SPECIALIZED_CLASS(className, Vector, unitName) \
		className(double x = 0.0, double y = 0.0, double z = 0.0) : Vector(x, y, z, unitName) {} \
	};\
MAKE_SPECIALIZED_QUANTITY(className##M, unitName)

	MAKE_SPECIALIZED_VECTOR(Force, "N");
	MAKE_SPECIALIZED_VECTOR(Distance, "m");
	MAKE_SPECIALIZED_VECTOR(Acceleration, "m / s^2");
	MAKE_SPECIALIZED_VECTOR(Velocity, "m / s");

#undef MAKE_SPECIALIZED_VECTOR
#undef MAKE_SPECIALIZED_QUANTITY
#undef MAKE_SPECIALIZED_CLASS

	// Constant Quantities
	namespace cnstQ {
		const Quantity epsilon0 = Quantity(8.854187817e-12, "C^2 / N m^2");
		const Quantity K = 1 / (4 * M_PI * epsilon0);
		const Quantity G = Quantity(6.67e-11, "m^3 / s^2 kg");

		const Charge e = Quantity(1.602e-19, "C");
		const Mass electronMass = Quantity(9.11e-31, "kg");
		const Acceleration g = { 0, -9.81 };
	}

	inline double micro(double micros)		{ return micros * 0.000001; }
	inline double nano(double nanos)		{ return nanos * 1e-9; }
	inline double kilo(double kilos)		{ return kilos * 1000; }

	inline double toKilo(double base) { return base / 1000; }

	Force elecForce(const Charge&, const Charge&, const Distance&);
	ForceM elecForce(const Charge&, const Charge&, const DistanceM&);

	Vector elecField(const Charge&, const Distance&);
	Quantity elecField(const Charge&, const DistanceM&);

	Force gravForce(const Mass&, const Mass&, const Distance&);
	ForceM gravForce(const Mass&, const Mass&, const DistanceM&);

	Force gravForce(const Mass&);
	ForceM gravForceM(const Mass&);

	VelocityM circularVelocity(const DistanceM& r, const AccelerationM& a);

	Quantity elecPotEnergy(const Charge&, const Charge&, const DistanceM&);
	Quantity gravPot(const Mass&, const Mass&, const DistanceM&);

	Quantity elecPotential(const Charge&, const DistanceM&);

	VelocityM velocity(const Energy& KE, const Mass& m);
};