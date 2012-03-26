// vim:ts=4:sw=4:expandtab
// © 2012 Kristian Kraljic, Tim Braner, Michael Stapelberg
// KRY, Übung 1, Aufgabe 5a
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

static const int euklid(const int a, const int b) {
    if (b == 0)
        return a;
    if (a == 0)
        return b;
    const int rest = (b % a);
    if (rest == 0)
        return a;
    return euklid(rest, a);
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
        cerr << "Syntax: " << argv[0] << " a b" << endl;
        return 1;
    }
    long a = convert_or_die(argv[1]);
    long b = convert_or_die(argv[2]);
    cout << "ggt(" << a << ", " << b << ") = " << euklid(a, b) << endl;
    return 0;
}
