/*
Methode:
	c ≡ m^e (mod N). // Verschlüsselung
	m ≡ c^d (mod N). // Entschlüsselung
Beispiel:
 	 m = 7, e = 29, d = 85 und N = 391
 	 	-> c = 74
 	 		-> m = 7 Funktion OK
*/

#include <iostream>
#include <gmpxx.h>
#include "dbghelp.h"

int main(const int argc, const char * const argv [])
{
	/* Abfrage der Eingabeparameter */
    if (argc < 4)
    {
        std::cerr << "Description: Adds two numbers" << std::endl;
        std::cerr << "Usage: " << argv [0] << " <a> <b>" << std::endl;
        std::cerr << "  m     : First number to add" << std::endl;
        std::cerr << "  e or d: Second number to add" << std::endl;
        std::cerr << "  N     : Second number to add" << std::endl;
        return 1;
    }
	/* Initalisieren der Parameter */
    mpz_class m(argv[1]);
    mpz_class eORd(argv[2]);
    mpz_class N(argv[3]);
    mpz_class val(0);

    /* Berechnung der Ent/Verschlüsselung */
    // Function: void mpz_powm (Rückgabe, Basis, Exponent, Modulus)
    mpz_powm(val.get_mpz_t(),  m.get_mpz_t(), eORd.get_mpz_t(),  N.get_mpz_t());

    /* Ausgabe des Ergebnisses an die Console */
    std::cout << val.get_mpz_t() << std::endl;

    return 0;
}
