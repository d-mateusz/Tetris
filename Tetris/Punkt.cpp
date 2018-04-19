#include "Punkt.h"
#include<iostream>


Punkt::Punkt()
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			pole[i][j] = 0;
}


Punkt::~Punkt()
{
}

bool Punkt::sprawdz()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else if (pole[a[i].y][a[i].x])
			return 0;

	return 1;
}

void Punkt::przesun(int dodaj_x) {
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dodaj_x;
	}
	if (!sprawdz())
		for (int i = 0; i < 4; i++)
			a[i] = b[i];

}

void Punkt::obrot() {
	int x1 = a[1].x;
	int y1 = a[1].y;
	for (int i = 0; i < 4; i++) {
		int x = a[i].y - y1;
		int y = a[i].x - x1;
		a[i].x = x1 - x;
		a[i].y = y1 + y;
	}
	if (!sprawdz())
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
}

int Punkt::postaw(int kolorNumer) {
	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].y += 1;
	}

	if (!sprawdz())
	{
		for (int i = 0; i < 4; i++)
			pole[b[i].y][b[i].x] = kolorNumer;
		return 1;
	}
	return 0;
}

int Punkt::losuj(int kolorNumer) {
	if (!sprawdz()) {
		kolorNumer = 1 + rand() % 7;

		int n = rand() % 7;

		for (int i = 0; i < 4; i++) {
			a[i].x = figury[n][i] % 2;
			a[i].y = figury[n][i] / 2;
		}

	}
	return kolorNumer;
}


void Punkt::sprawdz_linie(int & wynik) {
	int k = M - 1;
	for (int i = M - 1; i > 0; i--) {
		int count = 0;
		for (int j = 0; j < N; j++) {
			if (pole[i][j])
				count++;
			pole[k][j] = pole[i][j];
		}

		if (count < N)
			k--;
		else wynik++;
	}
}

bool Punkt::koniec_gry() {
	for (int i = 0; i < 4; i++)
		if (a[i].y <= 1 && pole[a[i].y][a[i].x]) {
			return 0;
		}
	return 1;
}



int Punkt::sprawdz_pole(int i, int j)
{
	return pole[i][j];
}

int Punkt::sprawdz_punkt_x(int i)
{
	return a[i].x;
}

int Punkt::sprawdz_punkt_y(int i)
{
	return a[i].y;
}

