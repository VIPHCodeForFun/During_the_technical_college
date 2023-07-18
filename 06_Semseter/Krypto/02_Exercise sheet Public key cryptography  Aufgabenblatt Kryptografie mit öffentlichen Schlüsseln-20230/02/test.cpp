/*
 Wurde mit Aufgabe 2 getestet -> OK
*/

#include <iostream>
#include <gmpxx.h>
#include "dbghelp.h"

int main()
{
    /* Zufallszahl */
    int seed = 1000;
    gmp_randstate_t rnd_state;
    gmp_randinit_default(rnd_state);
    gmp_randseed_ui(rnd_state,seed);

    /* Erzeuge zwei voneinander verschiedene Primzahlen p & q */
    int bitSize = 1000;
    mpz_class p(0);
    mpz_urandomb(p.get_mpz_t(), rnd_state, bitSize);
    mpz_nextprime(p.get_mpz_t(),p.get_mpz_t());

    mpz_class q(0);
    mpz_urandomb(q.get_mpz_t(), rnd_state, bitSize);
    mpz_nextprime(q.get_mpz_t(),q.get_mpz_t());

    while (p.get_mpz_t() == q.get_mpz_t()) // Sicherstellen das die beiden Zahlen p & q unterschiedlich sind
    {
        mpz_urandomb(q.get_mpz_t(), rnd_state, bitSize);
        mpz_nextprime(q.get_mpz_t(),q.get_mpz_t());
    }

    /* Berechnen N = pq. Die Bitlänge von N, soll exakt 2.048 Bit betragen. */
    mpz_class N(0);
    N = p * q;

    while ( (int)mpz_sizeinbase(N.get_mpz_t(), 2) != 2048 )
    {
        p = p * 2; 									// Aus p*2 wird eine Zahl die um max 1 Bit länger ist.
        mpz_nextprime(p.get_mpz_t(),p.get_mpz_t()); // Wir suchen die nächste Primzahl
        while (p.get_mpz_t() == q.get_mpz_t()) 	 	// Sicherstellen das die beiden Zahlen p & q unterschiedlich sind
        {
            mpz_urandomb(q.get_mpz_t(), rnd_state, bitSize);
            mpz_nextprime(q.get_mpz_t(),q.get_mpz_t());
        }
        N = p * q;									// 2^(p+1) * 2^q = 2^(p+1)+q
        if ((int)mpz_sizeinbase(N.get_mpz_t(), 2) > 2048) // N > 2048byte -> error neuen seed
        {
        	std::cout << "N > 2048byte -> Anderen random seed verwenden" << std::endl;
        	return 1;
        }
    }

    /* Berechnen Sie φ(N) = (p − 1)(q − 1) */
    mpz_class phi_N = (p - 1) * (q - 1);

    /* Ermittel den Öffentlichen Schlüssel = Zahl e zwischen 1 und φ(N), die zu φ(N) teilerfremd ist */
    mpz_class e(1);
    mpz_class gcd(0); // ggT
    mpz_class mpzOne(1);

    while( gcd != mpzOne )
    {
        e = e  + mpzOne;
        mpz_gcd(gcd.get_mpz_t(), e.get_mpz_t(), phi_N.get_mpz_t());
        if (e == phi_N)
        {
            std::cout << "e == phi_N" << std::endl;
            return 1;
        }
    }

    /* Berechnen für den privaten Schlüssel die Inverse von e modulo φ(N) */
    mpz_class d(0);
    mpz_invert(d.get_mpz_t(),  e.get_mpz_t(),  phi_N.get_mpz_t()); // d ≡ e^−1 (mod φ(N)).

    /* Ausgabe */
    std::cout << "Public key: (" << e.get_mpz_t() << ", " << N.get_mpz_t() << ")" << std::endl;
    std::cout << "Private key: (" << d.get_mpz_t() << ", " << N.get_mpz_t() << ")" << std::endl;

    return 0;
}
