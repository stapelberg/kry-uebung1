// vim:ts=4:sw=4:expandtab
// © 2012 Kristian Kraljic, Tim Braner, Michael Stapelberg
// KRY, Übung 1, Aufgabe 5c
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

static long convert_or_die(char *input) {
    char *endptr = NULL;
    long converted = strtol(input, &endptr, 10);
    if (converted == LONG_MIN ||
        converted == LONG_MAX ||
        *endptr != '\0') {
        cerr << "Fehler: Keine ganze Zahl angegeben (" << input << ")" << endl;
        exit(1);
    }

    return converted;
}

// Wie pow(), aber für natürliche Zahlen.
static const int npow(const int base, const int exponent) {
    int result = base;
    for (int i = 0; i < exponent; i++)
        result *= base;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Syntax: " << argv[0] << " g e n" << endl;
        cerr << "(Berechnet g^e % n)" << endl;
        return 1;
    }
    int g = convert_or_die(argv[1]);
    int e = convert_or_die(argv[2]);
    int n = convert_or_die(argv[3]);

    int product = 1;

    // Wir berechnen g^2 % n vor, weil wir es in jedem Schritt brauchen.
    int zw = (g * g) % n;

    // Wir betrachten den Exponent 'e' binär und bilden das Produkt aller
    // g^(2^i) bei denen e_i = 1 ist.
    for (int i = 0; i < 32; i++) {
        if (((e >> i) & 0x1) == 1) {
            product *= (npow(zw, i) % n);
        }
    }

    cout << g << "^" << e << " % " << n << " = " << (product % n) << endl;

    return 0;
}
