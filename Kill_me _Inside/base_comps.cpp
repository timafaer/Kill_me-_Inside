#include"Edit.h"

void Joker::set(Entity* comps, Scence* scence, Editor* edit,Game* core){
	int xd = 100,  yd = 140;
	this->comps = comps; this->scence = scence;
	this->edit = edit; this->core = core;
	sf::Texture& text = edit->textures["hero.png"];
	
	anim.obj = new sf::Drawable*[3];
	anim.count = 3;
	anim.func = (Joker::ani);
	anim.now = 2;
	for (int j = 0; j < 3; j++) {
		anim.obj[j] = new sf::Sprite;
		auto sp = static_cast<sf::Sprite*>(&anim.obj[j][0]);
		sp->setTextureRect(sf::IntRect(j * xd,  0,  xd,  yd));
		//sp->setOrigin(sf::Vector2f(xd / 2, yd / 2));
		sp->setTexture(text);
	}


	comps->add<Draw>();
	comps->comp<Draw>().set_obj(&anim.obj[anim.now][0],"hero");
	comps->comp<Draw>().set_texture(&text,"hero");

	hpbar.bacground.setFillColor(sf::Color::Black);
	hpbar.bacground.setSize(sf::Vector2f(100, 20));
	hpbar.bacground.setPosition(sf::Vector2f(0, 140));

	hpbar.hpbar.setFillColor(sf::Color::Green);
	hpbar.hpbar.setSize(sf::Vector2f(94, 14));
	hpbar.hpbar.setPosition(sf::Vector2f(3, 143));
	comps->comp<Draw>().set_obj(&hpbar.bacground, "hp");
	comps->comp<Draw>().set_obj(&hpbar.hpbar, "hpbar");

}
static int g = 1;
void Joker::ani(Animat& anim,Soul* soul) {//анимация
	int t = anim.time.getElapsedTime().asMilliseconds();
	int m = 300;

	if (t >= m - 10) {
		
		if (anim.now == anim.count - 1||anim.now == 0)
			g=-g;
		anim.now+=g;

		auto joke = static_cast<Joker*>(soul);
		joke->comps->comp<Draw>().set_obj(&anim.obj[anim.now][0],"hero");
		anim.time.restart();
	}
	
}

void Joker::logic() {//пример логики
	using key = sf::Keyboard::Key;
	using k = sf::Keyboard;
	
	if (k::isKeyPressed(key::W)) {
		comps->pos += sf::Vector2f(0, -s);
	}
	 if (k::isKeyPressed(key::A)) {
		comps->pos += sf::Vector2f(-s, 0);
	}
	if (k::isKeyPressed(key::S)) {
		comps->pos += sf::Vector2f(0, s);
	}
	if (k::isKeyPressed(key::D)) {
		comps->pos += sf::Vector2f(s, 0);
	}

	anim.func(anim, this);

	hpbar.hpbar.setSize(sf::Vector2f(94 * hp / maxhp, 14));
	comps->comp<Draw>().set_obj(&hpbar.hpbar, "hpbar");
	if(hp>0)
		hp -= 1;
}