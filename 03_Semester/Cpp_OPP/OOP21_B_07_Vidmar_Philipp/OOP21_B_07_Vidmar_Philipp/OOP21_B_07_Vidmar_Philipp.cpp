// OOP21_B_07_Vidmar_Philipp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

#include <iostream>
#include "GeoRect.h"
#include "GeoSquare.h"
#include "GeoCirlce.h"
#include "GeoEllipse.h"
#include "GeoTriangle.h"
#include "GeoContainer.h"
#include "GeoHouse.h"
#include "IUniqueID.h"

//Aufgabe A 
//	Antwort: virtual void output() = 0; //pure virtual function
//Aufgabe B
//	GeoSquare kann von GeoRect erben
//  GeoCirlce kann von GeoEllips erben
//  GeoTriangle kann von nichts sinvollen erben
//  Nachteil Mögliches Diamantproblem ()
//	Vorteil Codeersparniss
//Aufgabe E
//	In dem Beispiel würde der Copy Constructor bei den Oberen klassen ausreichen 
//	-> GeoRect
//	-> GeoEllips
//	-> GeoTriangle
// weil die abgeleiteten Klassen gleich bleiben
int main()
{
	GeoRect A(2, 3);
	A.output();
	GeoSquare B(2);
	B.output();
	GeoCirlce C(2);
	C.output();
	GeoEllipse D(2, 3);
	D.output();
	GeoTriangle E(2, 3, 4, 5);
	E.output();

	GeoContainer sack;
	sack.container.push_back(&A);
	sack.container.push_back(&B);
	sack.container.push_back(&C);
	sack.output();

	GeoHouse meinhaus(A, E); //Diamantproblem 
	return 0;
}

