#pragma once
#include<any>
#include"base_comps.h"
class Entity : public sf::Drawable, public sf::Transformable
{
private:
	std::vector<Component*> comps;
	Soul* soul;
	
	friend Editor;
public:
	sf::Vector2f pos;
	int deep = 0;
	Entity() {
		pos = sf::Vector2f(0, 0);
	}

	template<class T>
	void add() {
		comps.push_back(new T());
	}

	template<class T>
	T& comp() const {
		for (auto& com : comps)
			if ((*com).type() == typeid(T).name())
				return static_cast<T&>(*com);
	}
	

	void draw(sf::RenderTarget& target, sf::RenderStates states)const {
		states.transform.translate(pos);
		target.draw(comp<Draw>(), states);
	}

	void logic() { soul->logic(); }
};