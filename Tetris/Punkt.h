#pragma once
#pragma once
#include<SFML/Graphics.hpp>
class Punkt
{
private:
	struct punkt {
		int x = 0;
		int y = 0;
	} a[4], b[4];

	const int M = 20;
	const int N = 10;

	int pole[20][10];

	int figury[7][4] =
	{
		1,3,5,7, // I - klocek prostokat 4x1
		2,4,5,7, // Z - klocek w ksztalcie litery Z odwroconej w prawa strone
		3,5,4,6, // S - klocek w ksztalcie litery Z odwroconej w lewa strone
		3,5,4,7, // T - klocek w ksztalcie litery T odwroconej w prawa strone
		2,3,5,7, // L - klocek w ksztalcie litery L odwroconej do gory nogami
		3,5,7,6, // J - klocek w ksztalcie litery L odwroconej w lewa strone
		2,3,4,5, // O - klocek kwadrat 2x2
	};


public:
	Punkt();
	~Punkt();

	bool sprawdz();
	void przesun(int);
	void obrot();
	int losuj(int);
	int postaw(int);
	void sprawdz_linie(int &);
	bool koniec_gry();
	int sprawdz_pole(int, int);
	int sprawdz_punkt_x(int);
	int sprawdz_punkt_y(int);
};

