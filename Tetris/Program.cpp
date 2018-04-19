#include<SFML/Graphics.hpp>
#include<SFML/Audio/Music.hpp>
#include<time.h>
#include"Punkt.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<windows.h>
using namespace sf;

int main()
{
	Punkt pam;
	srand(time(NULL));
	RenderWindow window(VideoMode(320, 480), "Tetris!");
	Texture t1, t2;
	t1.loadFromFile("../Debug/images/klocki.png");
	t2.loadFromFile("../Debug/images/tlo.png");
	Sprite s(t1), tlo(t2);
	std::fstream zapis("../Debug/Najlepszy wynik.txt", std::ios::in);
	sf::Font font;
	font.loadFromFile("../Debug/font/arial.ttf");
	sf::Text text("Aktualny\nwynik: 0", font);
	sf::Text text_2("Najlepszy\nwynik: 0", font);
	sf::Text text_3("Koniec gry!", font);
	text.setCharacterSize(15);
	text.setPosition(250, 98);
	text_2.setCharacterSize(15);
	text_2.setPosition(250, 28);
	text_3.setCharacterSize(30);
	text_3.setPosition(15, 430);
	sf::Music music;
	music.openFromFile("../Debug/sound.ogg");
	music.play();
	music.setLoop(true);

	int dodaj_x = 0;
	bool obrot = 0;
	int kolorNumer = 2;
	float timer = 0, opoznienie = 0.3;
	int wynik = 0;
	int ok;
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Time czas = clock.getElapsedTime();
		float time = czas.asSeconds();
		clock.restart();
		timer += time;
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up)
					obrot = true;
				else if (e.key.code == Keyboard::Left)
					dodaj_x = -1;
				else if (e.key.code == Keyboard::Right)
					dodaj_x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
			opoznienie = 0.05;
		pam.przesun(dodaj_x);
		if (obrot)
			pam.obrot();
		if (timer > opoznienie) {
			ok = pam.postaw(kolorNumer);
			if (ok == 1)
				kolorNumer = pam.losuj(kolorNumer);
			timer = 0;
		}
		pam.sprawdz_linie(wynik);

		int best;
		zapis >> best;

		std::ostringstream oss;
		oss << "Aktualny\nwynik: " << wynik;
		std::string string = oss.str();
		text.setString(string);
		std::ostringstream oss2;
		oss2 << "Najlepszy\nwynik: " << best;
		std::string string_2 = oss2.str();
		text_2.setString(string_2);

		if (!pam.koniec_gry()) {

			if (best < wynik) {
				zapis.close();
				zapis.open("../Debug/Najlepszy wynik.txt", std::ios::out);
				zapis << wynik;
			}
			window.draw(text_3);
			window.display();
			zapis.close();
			Sleep(2000);
			return 0;
		}

		dodaj_x = 0;
		obrot = 0;
		if (wynik >= 10 && wynik < 20)
			opoznienie = 0.25;
		else if (wynik >= 20)
			opoznienie = 0.20;
		else opoznienie = 0.3;

		window.clear(sf::Color::White);
		window.draw(tlo);
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++) {
				if (pam.sprawdz_pole(i, j) == 0)
					continue;
				s.setTextureRect(sf::IntRect(pam.sprawdz_pole(i, j) * 18, 0, 18, 18)); // x, y, szerokosc, wysokosc
				s.setPosition(j * 18, i * 18);
				s.move(29, 31);
				window.draw(s);
			}
		for (int i = 0; i<4; i++) {
			s.setTextureRect(sf::IntRect(kolorNumer * 18, 0, 18, 18));
			s.setPosition(pam.sprawdz_punkt_x(i) * 18, pam.sprawdz_punkt_y(i) * 18);
			s.move(29, 31);
			window.draw(s);
		}
		window.draw(text);
		window.draw(text_2);
		window.display();
	}
	return 0;
}