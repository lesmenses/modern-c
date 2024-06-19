#include <assert.h>
#include <ctype.h>
/* Supposes that lowercase characters are contiguous . */
static_assert ('z'-'a' == 25, "alphabetic characters not contiguous");
/* Converts an alphanumeric digit to an unsigned */
/* '0' ... '9' => 0 .. 9u */
/* 'A' ... 'Z' => 10 .. 35u */
/* 'a' ... 'z' => 10 .. 35u */
/* Other values => Greater */
unsigned hexatridecimal (int a) {
    if (isdigit(a)) {
    /* This is guaranteed to work : decimal digits
    are consecutive , and isdigit is not
    locale dependent . */
        return a - '0';
    } else {
        /* Leaves a unchanged if it is not lowercase */
        a = toupper(a);
        /* Returns value >= 36 if not Latin uppercase */
        return (isupper(a)) ? 10 + (tolower(a) - 'a') : -1;
    }
}