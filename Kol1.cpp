#include "Wybor.h"
#include "kolokwium.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif. 
*/

#ifdef Kol_1

int main()
{
	Dane d;
	wypelnij(d, 12, '+', 1,0,1,0);
	d == (dekompresuj(kompresuj(d)));
}

#endif
