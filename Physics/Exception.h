#pragma once

#include "stdafx.h"

#include <exception>
#include <string>

class Exception : std::exception {
private:
	std::string msg;

public:
	Exception(std::string msg) : msg(msg) {}
	const char* what() const throw() { return msg.c_str(); }
};