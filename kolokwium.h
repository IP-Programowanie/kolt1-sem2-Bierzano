#pragma once
#define _CRT_SECURE_ALL_WARNINGS
#include "PK1_kolA.h"
#include <cstdio>
#include <cstdint>
#include <stdexcept>

namespace Maski {
	enum maski : uint32_t {
		E_mask = 0x2,
		W_mask = 0x8,
		O_mask = 0x20,
		L_mask = 0x7FFF80,
		A_mask = 0x800000,
		S_mask = 0xFF000000
	};
}

uint32_t kompresuj(Dane& d);

Dane dekompresuj(uint32_t skompresowane);

void ustawPole(uint32_t skompresowane);

bool odczytajPole(uint32_t skompresowane);

uint32_t** alokujDane(uint32_t rozmiar);

void dealokujDane(uint32_t**& tablica);

void modyfikujElement(uint32_t** tablica, uint32_t indeks, uint32_t noweDane);

void modyfikujElement(uint32_t** tablica, uint32_t indeks, Dane& noweDane);

uint32_t odczytajRozmiar(uint32_t** tablica);

void zapisDoPliku(uint32_t** tablica, const char* nazwaPliku);

uint32_t** odczytZPliku(const char* nazwaPliku);
