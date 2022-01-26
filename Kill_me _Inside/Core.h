#pragma once
#include"Scence.h"

class Game
{
private:
	Scence n_scence;
	Scence* redact;
	friend Editor;
public:
	sf::Event event;
	sf::RenderWindow window;
	Game() {
		window.create(sf::VideoMode(800, 600), "Kill_Me_Inside");
		redact = &n_scence;
	}

	void main_loop() {
		while (window.isOpen()){
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();
			window.clear();
			window.draw(n_scence);
			window.display();
		}
	}
};