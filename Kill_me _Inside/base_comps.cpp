#include"Edit.h"

void Joker::set(Entity* comps, Scence* scence, Editor* edit,Game* core){
	int xd = 45,  yd = 47;
	this->comps = comps; this->scence = scence;
	this->edit = edit; this->core = core;
	sf::Texture& text = edit->textures["joke.png"];
	for (int i = 0; i < 4; i++) {
		anim[i].obj = new sf::Drawable*[3];
		anim[i].count = 3;
		anim[i].func = (Joker::ani);
		for (int j = 0; j < 3; j++) {
			anim[i].obj[j] = new sf::Sprite;
			auto sp = static_cast<sf::Sprite*>(&anim[i].obj[j][0]);
			sp->setTextureRect(sf::IntRect(j * xd, i * yd,  xd,  yd));
			//sp->setOrigin(sf::Vector2f(xd / 2, yd / 2));
			sp->setTexture(text);
		}
	}

}

void Joker::ani(Animat& anim,Soul* soul) {//анимация
	int t = anim.time.getElapsedTime().asMilliseconds();
	int m = 500;
	if (t >= m - 10) {
		
		if (anim.now == anim.count - 1)
			anim.now = 0;
		else
			anim.now++;

		auto joke = static_cast<Joker*>(soul);
		joke->comps->comp<Draw>().set_obj(&anim.obj[anim.now][0]);
		anim.time.restart();
	}
	
}

void Joker::logic() {//пример логики
	using key = sf::Keyboard::Key;
	using k = sf::Keyboard;
	
	if (k::isKeyPressed(key::W)) {
		anim[3].func(anim[3], this);
		comps->pos += sf::Vector2f(0, -s);
	}
	 if (k::isKeyPressed(key::A)) {
		anim[1].func(anim[1], this);
		comps->pos += sf::Vector2f(-s, 0);
	}
	if (k::isKeyPressed(key::S)) {
		anim[0].func(anim[0], this);
		comps->pos += sf::Vector2f(0, s);
	}
	if (k::isKeyPressed(key::D)) {
		anim[2].func(anim[2], this);
		comps->pos += sf::Vector2f(s, 0);
	}
}