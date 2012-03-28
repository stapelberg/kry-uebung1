// vim:ts=4:sw=4:expandtab
// © 2012 Kristian Kraljic, Tim Braner, Michael Stapelberg
// KRY, Übung 1, Aufgabe 5b
#include <iostream>
#include <cstdlib>
#include <climits>
#include <cmath>

using namespace std;

struct ee_result {
    /* d ist der größte gemeinsame Teiler */
    int d;
    /* ggT = s * a + t * b */
    int s;
    int t;
};

static const struct ee_result erweiterter_euklid(const int a, const int b) {
    if (b == 0)
        return (struct ee_result) { a, 1, 0 };
    const int rest = (a % b);
    struct ee_result recursed = erweiterter_euklid(b, rest);
    return (struct ee_result) {
        recursed.d,
        recursed.t,
        recursed.s - floor(a / b) * recursed.t
    };
}

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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Syntax: " << argv[0] << " n k" << endl;
        return 1;
    }
    long n = convert_or_die(argv[1]);
    long k = convert_or_die(argv[2]);
    struct ee_result ee = erweiterter_euklid(n, k);
    cout << ee.d << " = " << ee.s << " * " << n << " + " << ee.t << " * " << k << endl;
    if (ee.d != 1) {
        cerr << "ggt != 1, Berechnung des Inversen nicht moeglich" << endl;
        return 1;
    }
    cout << "k^{-1} mod n = " << ee.t << endl;
    return 0;
}
