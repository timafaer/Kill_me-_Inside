#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<fstream>
class Editor;
class Component
{
public:
	virtual const char* type() { return typeid(Component).name(); }
protected:
	friend Editor;
};

class Draw : public Component,public sf::Drawable,public sf::Transformable 
{
protected:
	sf::Drawable* obj;
	sf::Texture* texture;
	friend Editor;
public:
	virtual const char* type() { return typeid(Draw).name(); }
	void set_obj(sf::Drawable* obj) { this->obj = obj; }
	void set_texture(sf::Texture* texture) { this->texture = texture; }

	void draw(sf::RenderTarget& target, sf::RenderStates states)const {
		if (!Is_NULL()) {
			states.texture = texture;
			target.draw(*obj, states);
		}
	}

	bool Is_NULL()const {
		return obj == nullptr;
	}
};

class Map : public Component 
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