#include "TypographyHelper.h"

/*
 * replaces the soft-hyphen character by itself and a dash. pango does break text at soft-hyphens, but doesnt instert the actual hyphen.
 */
string TypographyHelper::hyphenate(string input) {
	ofStringReplace(input, "\u00AD", "\u00AD-");
	return input;
}
