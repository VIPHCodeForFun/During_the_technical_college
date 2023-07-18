
#include <stdio.h>

int main()
{
	int zahl = 7;
	int *zeiger = NULL;

	if (zeiger != NULL)
	{
		printf("Versuch 1, Zeiger-Wert: %d\n", *zeiger);
	}

	zeiger = &zahl;

	if (zeiger != NULL)
	{
		printf("Versuch 2, Zeiger-Wert: %d\n", *zeiger);
	}
	return 0;
}
