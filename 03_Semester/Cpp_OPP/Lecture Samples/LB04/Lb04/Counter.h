#pragma once

class Counter {
public:
	int ObjectCount() {
		static int counter = 0;
		/*
		static wird nur ein mal beim ersten aufruf ausgef�hrt
		Counter wird quasi zu einer Globalen variable
		Vermeinden wenn m�glich
		*/
		return counter++;
	}

	static int ClassCount() {
		static int counter = 0;
		return counter++;
	}

	static int ctr;
};