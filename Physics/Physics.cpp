#include "stdafx.h"

#include "Physics.h"

using namespace phys;

void Unit::init(const char* unit) {
	std::stringstream ss(unit);

	std::string token;

	bool numerator = true;
	while (ss.good()) {
		ss >> token;

		if (token == "") continue;

		if (token == "1")
			continue;

		if (token == "/") {
			numerator = false;
			continue;
		}


		auto caret = token.find('^');
		std::string cUnit = token.substr(0, caret);
		int exponent = 1;
		if (caret != std::string::npos) {
			std::stringstream number(token.substr(caret + 1));
			int exp;
			number >> exp;
			if (number.fail())
				throw Exception("Bad exponent in token " + token);
			exponent = exp;
		}

		if (exponent == 0)
			continue;

		if ((units[cUnit] += (numerator) ? exponent : -exponent) == 0)
			units.erase(cUnit);
	}
}

Unit Unit::operator *= (const Unit& u) {
	for (auto unit : u.units) {
		if ((units[unit.first] += unit.second) == 0)
			units.erase(unit.first);
	}

	return *this;
}

Unit Unit::operator * (const Unit& u) const {
	if (units.size() == 0)
		return u;
	if (u.units.size() == 0)
		return *this;

	Unit ret;
	for (auto unit : units) {
		ret.units[unit.first] = unit.second;
	}

	for (auto unit : u.units) {
		if ((ret.units[unit.first] += unit.second) == 0)
			ret.units.erase(unit.first);
	}

	return ret;
}

Unit Unit::operator /= (const Unit& u) {
	for (auto unit : u.units) {
		if ((units[unit.first] -= unit.second) == 0)
			units.erase(unit.first);

	}

	return *this;
}

Unit Unit::operator / (const Unit& u) const {
	Unit ret;

	for (auto unit : units) {
		ret.units[unit.first] = unit.second;
	}

	for (auto unit : u.units) {
		if ((ret.units[unit.first] -= unit.second) == 0)
			ret.units.erase(unit.first);

	}

	return ret;
}

bool Unit::operator == (const Unit& u) const {
	if (units.size() != u.units.size())
		return false;

	if (units.size() == 0) {
		if (u.units.size() == 0)
			return true;
		else
			return false;
	}

	if (units.size() == 0)
		return false;

	assert(units.size() != 0 && u.units.size() != 0);

	for (auto thisUnit = units.begin(), thatUnit = u.units.begin(); ; thisUnit++, thatUnit++) {
		if (thisUnit == units.end() && thatUnit == u.units.end()) return true;

		if (thisUnit->first != thatUnit->first) return false;
		if (thisUnit->second != thatUnit->second) return false;
	}
}

Unit Unit::sqrt() const {
	Unit ret;

	for (auto unit : units) {
		if (unit.second % 2 != 0)
			throw Exception("Unit does not have a power that is a multiple of two! (" + unit.first + "^" + std::to_string(unit.second) + ")");
		ret.units [unit.first] = unit.second / 2;
	}

	return ret;
}

std::string Unit::toString() const {
	if (units.size() == 0) return "";

	std::stringstream ss;
	bool outputNumerator = false;

	for (auto unit = units.begin(); unit != units.end(); unit++) {
		assert(unit->second != 0);
		if (unit->second < 0) continue;

		if (outputNumerator)
			ss << ' ';
		else
			outputNumerator = true;

		ss << unit->first;
		if (unit->second > 1)
			ss << '^' << unit->second;
	}

	if (outputNumerator == false)
		ss << '1';

	bool outputDenominator = false;

	for (auto unit = units.begin(); unit != units.end(); unit++) {
		assert(unit->second != 0);
		if (unit->second > 0) continue;

		if (!outputDenominator) {
			outputDenominator = true;
			ss << " /";
		}

		ss << ' ' << unit->first;

		if (unit->second < -1)
			ss << '^' << -unit->second;
	}

	return ss.str();
}


std::string Vector::toString() const {
	std::stringstream ss;
	if (!y && !z) {
		ss << x;
	} else {
		ss << "<" << x;

		if (y) {
			ss << ", " << y;
			if (z) {
				ss << ", " << z;
			}
		}
		ss << ">";
	}
	std::string unitStr = unit.toString();
	if (unitStr != "")
		ss << ' ' << unit.toString();

	return ss.str();
}


Vector elecField(const Charge& q, const Distance& d) {
	return cnstQ::K * q * d.unitV() / (d * d);
}


Quantity elecField(const Charge& q, const DistanceM& d) {
	return cnstQ::K * q / (d * d);
}


Force phys::elecForce(const Charge& e1, const Charge& e2, const Distance& d) {
	return cnstQ::K * e1 * e2 * d.unitV() / (d * d);
}

ForceM phys::elecForce(const Charge& e1, const Charge& e2, const DistanceM& d) {
	return (cnstQ::K * e1 * e2 / (d * d)).magnitude();
}

Force phys::gravForce(const Mass& m1, const Mass& m2, const Distance& d) {
	return cnstQ::G * m1 * m2 / (d * d) * d.unitV();
}

ForceM phys::gravForce(const Mass& m1, const Mass& m2, const DistanceM& d) {
	return cnstQ::G * m1 * m2 / (d * d);
}

Force phys::gravForce(const Mass& m) {
	Vector f = m * cnstQ::g;
	f.unit = "N";
	return f;
}

ForceM phys::gravForceM(const Mass& m) { return gravForce(m).magnitude(); }

VelocityM phys::circularVelocity(const DistanceM& r, const AccelerationM& a) { return (r * a).sqrt(); }

std::string phys::Quantity::toString() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

std::ostream & phys::operator<<(std::ostream & o, const Quantity & q) {
	std::string unitStr = q.unit.toString();
	o << q.quantity;
	if (unitStr.length() != 0)
		o << ' ' << unitStr;

	return o;
}


Quantity phys::elecPotEnergy(const Charge& q1, const Charge& q2, const DistanceM& r) {
	return phys::cnstQ::K * q1 * q2 / r;
}

Quantity phys::elecPotential(const Charge& q, const DistanceM& r) {
	return cnstQ::K * q / r;
}

VelocityM phys::velocity(const Energy& KE, const Mass& m) { 
	Quantity KE_ = { KE.quantity, "kg m^2 / s^2" };
	return (2 * KE_ / m).sqrt();
}

Voltage phys::voltage(const Resistance & r, const Ampage & i) { return phys::voltage(i, r); }
Voltage phys::voltage(const Ampage & i, const Resistance & r) { return Voltage(i.quantity * r.quantity); }

Resistance phys::resistance(const Voltage & v, const Ampage & i) { return phys::resistance(i, v); }
Resistance phys::resistance(const Ampage & i, const Voltage & v) { return Resistance(v.quantity / i.quantity); }

Ampage phys::current(const Voltage & v, const Resistance & r) { return phys::current(r, v); }
Ampage phys::current(const Resistance & r, const Voltage & v) { return Ampage(v.quantity / r.quantity); }

Power phys::power(const Ampage & i, const Voltage & r) { return Power(i.quantity * r.quantity); }
