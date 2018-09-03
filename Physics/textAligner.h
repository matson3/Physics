#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

#include "Exception.h"

class BetterOutstream : std::ostream {
	private:
		int outputWidth = 80;
		int charsPerLine, charsRemaining;
		bool newLine = true;
		std::string lMargin = "";
		std::string rMargin = "";

		std::stringstream buffer;

		inline void recalc() {
			charsPerLine = outputWidth - (int)lMargin.length() - (int)rMargin.length();
			if (newLine) charsRemaining = charsPerLine;
			else if (charsRemaining > charsPerLine) charsRemaining = charsPerLine;
		}

		inline void resetLine() { charsRemaining = charsPerLine; newLine = true; }
		inline void newline() { std::ostream::put('\n'); resetLine(); }

		bool canHyphenate() { return outputWidth >= 4; }
		void hyphenate(const std::string& s);

		template <class type> std::string toString(type val) {
			std::stringstream ss; 
			ss << val;
			return ss.str();
		}

		inline void output(const std::string& val) { buffer << val; }
		inline void output(char c) { buffer << c; }
		inline void output(const char* cs, std::streamsize n) { buffer.write(cs, n); }

		void printChar(char);
		void printWord(const std::string&);

	public:
		void flush();

		inline void setLeftMargin(const std::string& s) {
			if (s.length() > outputWidth)
				throw Exception("Left margin is too long! Must be <= " + toString(outputWidth));

			lMargin = s;
			recalc();
		}

		inline std::string getLeftMargin() const { return lMargin; }

		BetterOutstream(const std::ostream& o) : std::ostream(o.rdbuf()) {
			recalc();
			resetLine();
		}

		void setOutputWidth(int w) {
			if (w < 1) throw Exception("Width must be greater than 0");
			if (w < lMargin.length() + rMargin.length()) throw Exception("Size too small for the margins");


			if (w != outputWidth) {
				outputWidth = w;
				recalc();
				if (!newLine) newline();
			}
		}

		int getOutputWidth() { return outputWidth; }

		BetterOutstream& put(char c) { output(c); return *this; }
		BetterOutstream& write(const char* s, std::streamsize n) { output(s, n); return *this; }

		template <class type> BetterOutstream& operator << (type val) { output(toString(val)); return *this; }

		BetterOutstream& operator << (const std::string& val) { output(val); return *this; }
		BetterOutstream& operator << (const char* val) { output(val); return *this; }

		BetterOutstream& operator<< (BetterOutstream& (*pf)(BetterOutstream&)) { pf(*this); return *this; }
		//BetterOutstream& operator<< (std::ios& (*pf)(std::ios&)) { pf(this->); return *this; }
		//BetterOutstream& operator<< (std::ios_base& (*pf)(std::ios_base&)) { pf(*this); return *this; }

};

BetterOutstream& endl(BetterOutstream& os);
BetterOutstream& ends(BetterOutstream& os);
BetterOutstream& flush(BetterOutstream& os);

// puts 2 '\n's in the stream, then flushes
BetterOutstream& para(BetterOutstream& os);

// Useful operator: n*str = str + str + str + ..., n times;
std::string operator * (unsigned int n, const std::string& s);