#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<fstream>
#include"helper.h"
#include<map>
#include<utility>
#include<string>
class Game;
class Editor;
class Component// базовый класс
{
public:
	virtual const char* type() { return typeid(Component).name(); }
protected:
	friend Editor;
};



class Draw : public Component, public sf::Drawable, public sf::Transformable //базовый класс отрисовки
{
protected:
	std::map<std::string, std::pair<sf::Drawable*, sf::Texture*>> objs;

	friend Editor;
public:
	virtual const char* type() { return typeid(Draw).name(); }
	void set_obj(sf::Drawable* obj, std::string name = "null") { this->objs[name].first = obj; }
	void set_texture(sf::Texture* texture, std::string name = "null") { this->objs[name].second = texture; }

	void draw(sf::RenderTarget& target, sf::RenderStates states)const {
		for (const auto& obj : objs) {
			states.texture = obj.second.second;
			target.draw(*obj.second.first, states);
		}
	}
	bool Is_NULL() { return 1; }

};


class Map : public Component //базовый класс тайл карты
{
protected:
	sf::VertexArray m_vertices;
	sf::Vector2u textureSize;
	sf::Vector2f tileSize;
	sf::Vector2u mapSize;
	friend Editor;
public:
	virtual const char* type() { return typeid(Map).name(); }
	void set() {
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(100);
		mapSize = sf::Vector2u(5, 5);
		textureSize = sf::Vector2u(32, 32);
		tileSize = (sf::Vector2f)textureSize;

	}
	void set_mapsize(sf::Vector2u size) { mapSize = size; }
	void set_tilesize(sf::Vector2f size) { tileSize = size; }
	void set_texturesize(sf::Vector2u size) { textureSize = size; }

	void read(std::string file) {
		std::ifstream fin;
		fin.open(file);
		int l = 0;
		for (int i = 0; i < mapSize.x; i++)
			for (int j = 0; j < mapSize.y; j++) {
				sf::Vertex* quad = &m_vertices[(j + i * mapSize.y) * 4];

				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				quad[0].texCoords = sf::Vector2f(l * textureSize.x, l * textureSize.y);
				quad[1].texCoords = sf::Vector2f((l + 1) * textureSize.x, l * textureSize.y);
				quad[2].texCoords = sf::Vector2f((l + 1) * textureSize.x, (l + 1) * textureSize.y);
				quad[3].texCoords = sf::Vector2f(l * textureSize.x, (l + 1) * textureSize.y);
			}
		fin.close();
	}
};

class Scence;
class Entity;

class Soul {//базовый класс души
protected:
	Editor* edit;
	Entity* comps;
	Scence* scence;
	Game* core;
	friend Editor;
public:
	Soul() {}
	Soul(Entity* comps, Scence* scence, Editor* edit, Game* core) :
		comps{ comps }, scence{ scence }, edit{ edit }, core{ core } {}
	virtual void set(Entity* comps, Scence* scence, Editor* edit,Game* core)
	{
		this->comps = comps; this->scence = scence; this->edit = edit; this->core = core;
	}
	virtual void logic() {}
};

class Joker : public Soul//производный класс от души (для анимации)
{
	Animat anim;
	Healbar hpbar;
	float s = 3;
	float hp=100;
	float maxhp = 100;
public:

	void set(Entity* comps, Scence* scence, Editor* edit,Game* core);

	static void ani(Animat& anim,Soul* soul);

	void logic();

};