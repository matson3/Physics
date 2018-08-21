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

		friend std::ostream& operator << (std::ostream& o, const Unit& u);
	};

	class Quantity {
	public:
		double quantity;
		Unit unit;

		Quantity(double value, Unit unit) : quantity(value), unit(unit) {}
		Quantity(double value) : quantity(value) {}
		Quantity() : quantity(0), unit("") {}

		Quantity magnitude() { return Quantity((quantity < 0) ? -quantity : quantity, unit); }

		friend Quantity operator * (double d, const Quantity& q) { return Quantity(d) * q; }
		inline Quantity operator * (const Quantity& q) const { return Quantity(quantity * q.quantity, unit * q.unit); }

		friend Quantity operator / (double d, const Quantity& q) { return Quantity(d) / q; }
		Quantity operator / (double d) const { return Quantity(quantity / d, unit); }
		Quantity operator / (const Quantity& q) const { return Quantity(quantity / q.quantity, unit / q.unit); }
		Quantity operator /= (const Quantity& q) { quantity /= q.quantity; unit /= q.unit; }

		Quantity operator + (const Quantity& q) const { if (unit != q.unit) throw Exception("Units are not the same"); return Quantity(quantity + q.quantity, q.unit); }

		Quantity operator - (const Quantity& q) const { if (unit != q.unit) throw Exception("Units are not the same"); return Quantity(quantity - q.quantity, q.unit); }
		Quantity operator - () const { return Quantity(-quantity, unit); }

		friend std::ostream& operator << (std::ostream& o, const Quantity& q) { return o << q.quantity << ' ' << q.unit; }
	};

	class Vector {
	public:
		double x, y, z;
		Unit unit;

		Vector(double x = 0, double y = 0, double z = 0, Unit unit = "") : x(x), y(y), z(z), unit(unit) {}

		inline Quantity magnitude() const { return Quantity(sqrt(x*x + y * y + z * z), unit); }

		inline Vector unitV() const { return *this / magnitude();	}

		inline Quantity operator * (const Vector& v) const { return Quantity(x * v.x + y * v.y + z * v.z, unit * v.unit); }
		inline friend Vector operator * (const Quantity& q, const Vector& v) { return Vector(q.quantity * v.x, q.quantity * v.y, q.quantity * v.z, q.unit * v.unit); }

		Vector operator / (double d) const { return Vector(x / d, y / d, z / d, unit); }
		Vector operator / (const Quantity& q) const { return Vector(x / q.quantity, y / q.quantity, z / q.quantity, unit / q.unit); }

		friend std::ostream& operator << (std::ostream& o, Vector v) { return o << '<' << v.x << ", " << v.y << ", " << v.z << "> " << v.unit; }
	};


	// Constant Quantities
	namespace cnstQ {
		const Quantity epsilon0 = Quantity(8.854187817e-12, "C^2 / N m^2");
		const Quantity K = 1 / (4 * M_PI * epsilon0);
		const Quantity e = Quantity(1.602e-19, "C");
		const Quantity G = Quantity(6.67e-11, "m^3 / s^2 kg");
	}

	inline Vector elecForce(Quantity e1, Quantity e2, Vector distance) { return cnstQ::K * e1 * e2 * distance.unitV() / (distance * distance); }
	inline Quantity elecForce(Quantity e1, Quantity e2, Quantity distance) { return (cnstQ::K * e1 * e2 / (distance * distance)).magnitude(); }

	inline Vector gravForce(Quantity m1, Quantity m2, Vector distance) { return cnstQ::G * m1 * m2 / (distance * distance) * distance.unitV(); }
	inline Quantity gravForce(Quantity m1, Quantity m2, Quantity distance) { return cnstQ::G * m1 * m2 / (distance * distance); }
}