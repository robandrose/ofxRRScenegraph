#include "StringValidator.h"


/**
 *  Validates an email-address roughly following RFC 822
 *  danggerscheen O'Reilly (http://www.onlamp.com/pub/a/network/excerpt/spcookbook_chap03/index3.html)
 */
bool StringValidator::isEmailValid(string _emailAddress) {
    const char *address = _emailAddress.c_str();
    int        count = 0;
    const char *c, *domain;
    static char *rfc822_specials = "()<>@,;:\\\"[]";
    
    /* first we validate the name portion (name@domain) */
    for (c = address;  *c;  c++) {
        if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == 
                           '\"')) {
            while (*++c) {
                if (*c == '\"') break;
                if (*c == '\\' && (*++c == ' ')) continue;
                if (*c <= ' ' || *c >= 127) return 0;
            }
            if (!*c++) return 0;
            if (*c == '@') break;
            if (*c != '.') return 0;
            continue;
        }
        if (*c == '@') break;
        if (*c <= ' ' || *c >= 127) return 0;
        if (strchr(rfc822_specials, *c)) return 0;
    }
    if (c == address || *(c - 1) == '.') return 0;
    
    /* next we validate the domain portion (name@domain) */
    if (!*(domain = ++c)) return 0;
    do {
        if (*c == '.') {
            if (c == domain || *(c - 1) == '.') return 0;
            count++;
        }
        if (*c <= ' ' || *c >= 127) return 0;
        if (strchr(rfc822_specials, *c)) return 0;
    } while (*++c);
    
    return (count >= 1);
}