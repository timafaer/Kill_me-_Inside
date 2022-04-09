#pragma once
#include"Scence.h"

class Game//главный класс 
{
private:
	Scence n_scence;//В ДАННЫЙ МОМЕНТ 1 СЦЕНА (ПОКА ЧТО)
	Scence* redact;//при редактировании - указатель на текущую сцену
	friend Editor;
public:
	sf::Event event;
	sf::RenderWindow window;
	Game() {
		window.create(sf::VideoMode(800, 600), "Kill_Me_Inside");
		window.setFramerateLimit(60);
		redact = &n_scence;
	}

	void main_loop() {
		while (window.isOpen()){
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
			window.clear(sf::Color(255,255,255));
			n_scence.logic();//логика объектов
			window.draw(n_scence);//отрисовка
			window.display();
		}
	}
};