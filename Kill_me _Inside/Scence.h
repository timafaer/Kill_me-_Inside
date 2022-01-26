#pragma once
#include"Entity.h"

class Scence : public sf::Drawable ,public sf::Transformable
{
private:
	std::map<std::string, std::vector<Entity>> objects;
	Scence* prev = nullptr;
	std::vector<Entity*> drawing;
	sf::Vector2f pos;
	friend Editor;
public:
	Scence() { pos = sf::Vector2f(0, 0); }
	void add_obj(std::string name) { objects[name].push_back(Entity()); drawing.push_back(&objects[name][objects[name].size() - 1]); }

	Entity& get_one(std::string type, int numb = 0) { return objects[type][numb]; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(pos);
		if (drawing.size() != 0)
			for (auto i : drawing)
				target.draw(*i, states);
	}

};
