#include "stdafx.h"

#include "textAligner.h"

#include <assert.h>
#include <ctype.h>
#include <iomanip>
#include <sstream>
#include <string>

BetterOutstream& endl(BetterOutstream& os) { os.put('\n'); os.flush(); return os; }
BetterOutstream& ends(BetterOutstream& os) { os.put('\0'); os.flush(); return os; }
BetterOutstream& flush(BetterOutstream& os) { os.flush(); return os; }
BetterOutstream& para(BetterOutstream& os) { os.put('\n').put('\n'); os.flush(); return os; }

std::string operator * (unsigned int n, const std::string& s) {
	if (n == 0) return std::string();
	if (n == 1) return s;
	if (n == 2) return s + s;

	std::string ret = (n / 2) * s;
	ret += ret;
	// If n is odd
	if (n & 1) {
		ret += s;
	}

	return ret;
}

void BetterOutstream::printChar(char c) {
	if (newLine) {
		std::ostream::write(lMargin.c_str(), lMargin.length());
		newLine = false;
	}

	if (charsRemaining == 0) {
		resetLine();
		if (iswspace(c))
			return;
	}

	if (c == '\n') {
		newline();
		return;
	}

	std::ostream::put(c);
	charsRemaining--;
}

void BetterOutstream::hyphenate(const std::string& s) {
	// section1-section2
	int sizeOfSection1= charsRemaining - 1;
	int sizeOfSection2 = (int)s.length() - (sizeOfSection1);

	assert(sizeOfSection1 + sizeOfSection2 == s.length());

	// Check if section 1 is too long
	if (sizeOfSection1 / sizeOfSection2 > 1) {
		// TODO: Auto-hyphenate
		//std::cerr << "Need to implement hyphenation filtering!" << std::endl;
	}

	std::string section1 = s.substr(0, sizeOfSection1) + '-';
	std::string section2 = s.substr(sizeOfSection1);

	printWord(section1);
	printWord(section2);
}

void BetterOutstream::printWord(const std::string& s) {
	if (charsRemaining == 0) {
		resetLine();
		if (s.length() > charsRemaining && canHyphenate()) {
			hyphenate(s);
			return;
		}

	} else if (s.length() > charsRemaining) {
		if (newLine) {
			if (canHyphenate()) {
				hyphenate(s);
				return;
			}
		} else
			newline();
		// Optional: implement auto-hyphenation in words that don't exceed max length.
	}


	if (newLine) {
		std::ostream::write(lMargin.c_str(), lMargin.length());
		newLine = false;
	}

	std::ostream::write(s.c_str(), s.length());
	charsRemaining -= (int)s.length();
}

void BetterOutstream::flush() {
	/* We have a stream of characters in buffer. Turn these into words and fit them into lines.
		Expectations:
			Don't carry spaces over from the end of a line to the next line so that there is an unnecessary indent
			Preserve leading characters as intentional.
	*/
	while (buffer.good()) {
		// Manually extract words to preserve every char
		std::stringstream word("");

		// First character has special behavior
		int nextChar = buffer.get();
		if (nextChar < 0) break;
		if (iswspace(nextChar)) {
			printChar(nextChar);
			continue;
		}

		word << (char)nextChar;

		// While the character being read is not white space
		while (buffer.good() && !iswspace(buffer.peek())) {
			if (nextChar < 0) {
				printWord(word.str());
				break;
			}

			word << (char)buffer.get();
		}

		// Word built
		printWord(word.str());
	}

	buffer.str("");
	buffer.clear();
	std::ostream::flush();
}

BetterOutstream cout = std::cout;

static void test() {
	BetterOutstream cout = std::cout;

	// Testing basic ability
	cout << "hi" << para;

	// Testing word wrap
	cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse vel ultricies elit. Sed consequat pretium nunc, non rhoncus est pulvinar vitae. Donec sem eros, feugiat et arcu eget, fermentum egestas magna. Interdum et malesuada fames ac ante ipsum primis in faucibus. Aliquam erat volutpat. Aliquam aliquam, lorem ac maximus convallis, risus lacus hendrerit erat, quis semper sem nisi a ex. Vivamus id dictum metus. Duis rutrum fermentum sodales. Duis in purus porttitor, porta enim quis, tempor lacus. Fusce eleifend mattis dui, aliquam aliquam nisl tempor eu. Donec aliquet nec diam vitae finibus. Duis commodo justo eu massa rutrum mattis. Integer sit amet vulputate odio." << para;

	// also testing Margins
	cout.setLeftMargin("|");
	cout << "Maecenas placerat ut nibh ac consequat. Suspendisse sit amet ligula diam. Sed maximus malesuada vestibulum. Etiam porttitor turpis vitae sem rhoncus imperdiet. Pellentesque eget vehicula nibh, ut ornare urna. Aliquam quis lacus sem. Fusce facilisis, mi sed eleifend cursus, odio orci faucibus enim, sed sagittis mi nisi eget nibh. Ut porttitor nunc nec turpis congue, ac congue nisi eleifend. Donec aliquet arcu vitae diam laoreet condimentum. Integer in odio tristique, viverra massa lacinia, rutrum est. Donec risus erat, blandit ac varius at, lacinia quis tellus. Integer dui purus, tincidunt et laoreet at, posuere a elit. Pellentesque viverra felis a sem sollicitudin ornare. Integer at eros tortor." << para;

	cout.setLeftMargin(" |");
	cout << "Nulla facilisi. Sed neque nisl, pharetra in egestas a, luctus ut purus. In vel mauris auctor, lacinia lectus ac, scelerisque orci. Donec placerat massa ac varius iaculis. Morbi varius ullamcorper nisl, sed venenatis leo efficitur eu. Integer faucibus est metus. Ut sed aliquam tortor." << para;

	cout.setLeftMargin("  |");
	cout << "Ut scelerisque tincidunt neque, a suscipit risus eleifend quis. Ut egestas sapien sit amet nisl iaculis fermentum. Cras quis suscipit nibh, ac maximus arcu. Duis pulvinar neque augue, ac egestas tellus cursus eget. Etiam sollicitudin tincidunt ligula, euismod mattis leo euismod vitae. Cras eu sagittis tortor, id ultricies urna. Sed pellentesque leo ligula, at dictum ante pulvinar ut. Mauris ut volutpat ex, dapibus interdum erat. Suspendisse tincidunt libero hendrerit enim ultrices feugiat. Donec consequat leo ac orci cursus volutpat. Proin vel semper diam. Nulla eu mi vel eros ultricies tempor at a arcu." << para;

	cout.setLeftMargin("   |");
	cout << "Nunc malesuada id massa eu viverra. Vestibulum scelerisque, urna in sodales rhoncus, leo arcu iaculis turpis, a ultrices tellus nibh a eros. Mauris bibendum consectetur arcu. Donec eu tincidunt mauris, id venenatis urna. Vestibulum in magna consectetur, suscipit nisl a, rutrum dui. Vivamus sed vulputate nibh. Nulla est elit, varius sed mattis eu, tincidunt quis sem. Sed vel velit interdum, aliquet justo maximus, tincidunt ante. Vivamus fringilla nibh a ullamcorper vulputate. Sed vestibulum consequat auctor. Etiam feugiat faucibus justo, a viverra ex sodales vitae. Nullam vitae felis consectetur, commodo mauris a, bibendum ante. Donec sed risus magna." << para << endl;

	// Testing edge cases with white space word wrapping uglyly or unnecessary deletions.
	cout.setLeftMargin("");
	cout << "  Testing." << endl;
	cout << "^^There should be spaces there." << endl;
	cout << "12345678901234567890123456789012345678901234567890123456789012345678901234567890 123456789012345678901234567890" << endl;
	cout << "^ There should be no space here" << para;
	cout << "12345678901234567890123456789012345678901234567890123456789012345678901234567890\n123456789012345678901234567890" << endl;
	cout << "^ These lines should be contiguous" << para;

	// Testing hyphenation with large words
	int width = 6;
	cout << (width * std::string("-")) << endl;
	cout.setOutputWidth(width);
	cout << "Ambulation" << endl;
	cout << "Kalishnikova" << endl;
	cout << "Extemporaneous" << endl;
	// Commonly accepted as the longest non-technical English Word
	cout << "Antidisestablishmentarianism" << endl;
	// Some thyroid disorder
	cout << "PSEUDOPSEUDOHYPOPARATHYROIDISM" << endl;
	// Some lung inflamation disease
	cout << "PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS" << endl;
}

/*
int main() {
	test();
	return 0;
}
*/