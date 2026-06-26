#include "kolokwium.h"

uint32_t kompresuj(Dane& d)
{
	uint32_t kompozyt = 0;

	kompozyt |= (d.estymowana << 1) & Maski::E_mask;
	kompozyt |= (d.wczytana << 3) & Maski::W_mask;
	kompozyt |= (d.obliczona << 5) & Maski::O_mask;
	kompozyt |= (d.liczba << 7) & Maski::L_mask;
	kompozyt |= (d.aktywna << 23) & Maski::A_mask;
	kompozyt |= (d.symbol << 24) & Maski::S_mask;

	return kompozyt;
}

Dane dekompresuj(uint32_t skompresowane)
{
	Dane d;

	d.estymowana = (skompresowane & Maski::E_mask) >> 1;
	d.wczytana = (skompresowane & Maski::W_mask) >> 3;
	d.obliczona = (skompresowane & Maski::O_mask) >> 5;
	d.liczba = (skompresowane & Maski::L_mask) >> 7;
	d.aktywna = (skompresowane & Maski::A_mask) >> 23;
	d.symbol = (skompresowane & Maski::S_mask) >> 24;

	return d;
}

void ustawPole(uint32_t skompresowane)
{
	skompresowane |= (skompresowane << 1) & Maski::E_mask;
}

bool odczytajPole(uint32_t skompresowane)
{
	return (skompresowane & Maski::L_mask) >> 7 != 0;
}

uint32_t** alokujDane(uint32_t rozmiar)
{
	uint32_t* pamiec = new uint32_t[1 + rozmiar]{};
	pamiec[0] = rozmiar;

	uint32_t** tablica = new uint32_t * [2];
	tablica[1] = &pamiec[0];
	tablica[0] = &pamiec[1];

	return tablica;
}

void dealokujDane(uint32_t**& tablica)
{
	delete[] tablica[1];
	delete[] tablica;
	tablica = nullptr;
}

void modyfikujElement(uint32_t** tablica, uint32_t indeks, uint32_t noweDane)
{
	if (0 > indeks || indeks >= *tablica[1]) throw std::domain_error("");
	tablica[0][indeks] = noweDane;
}

void modyfikujElement(uint32_t** tablica, uint32_t indeks, Dane& noweDane)
{
	modyfikujElement(tablica, indeks, kompresuj(noweDane));
}

uint32_t odczytajRozmiar(uint32_t** tablica)
{
	return tablica[1][0];
}

void zapisDoPliku(uint32_t** tablica, const char* nazwaPliku)
{
	FILE* plik = fopen(nazwaPliku, "w");

	int rozmiar = *tablica[1];

	for (int i = 0; i < rozmiar; i++)
	{
		uint32_t element = tablica[0][i];
		fprintf(plik, "%u", element);

		if (i < rozmiar - 1)
		{
			fprintf(plik, ";");
		}
	}
	fscanf(plik, "\n");

	fprintf(plik, "%d", rozmiar);

	fclose(plik);
}

uint32_t** odczytZPliku(const char* nazwaPliku)
{
	FILE* plik = fopen(nazwaPliku, "r");

	uint32_t element;
	size_t rozmiar;

	constexpr size_t roz = 100;
	char tekst[roz] = {};

	while (true)
	{
		fgets(tekst, roz, plik);

		if (feof(plik)) break;
	}
	int x = 0;
	while (tekst[x] != '\0')
	{
		tekst[x] = rozmiar;
		x++;
	}

	uint32_t** odczytanaTablica = alokujDane(rozmiar);

	for (int i = 0; i < rozmiar; i++)
	{
		if (i < rozmiar - 1)
		{
			fscanf(plik, "%u;", &element);
		}
		else
		{
			fscanf(plik, "%u", &element);
		}

		odczytanaTablica[0][i] = element;
	}

	fclose(plik);

	return odczytanaTablica;
}