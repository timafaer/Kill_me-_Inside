#pragma once
#include<any>
#include"base_comps.h"
class Entity : public sf::Drawable, public sf::Transformable ,public Component
{
private:
	std::vector<Component*> comps;//система хранения любых компонентов
	Soul* soul;//отдельный компонент - душа (логика)
	
	friend Editor;
public:
	sf::Vector2f pos;
	int deep = 0;
	Entity() {
		pos = sf::Vector2f(0, 0);
	}

	template<class T>
	void add() {
		comps.push_back(new T());//добавление компонента
	}

	template<class T>
	T& comp() const {
		for (auto& com : comps)
			if ((*com).type() == typeid(T).name())
				return static_cast<T&>(*com);// выборка компонента
	}
	

	void draw(sf::RenderTarget& target, sf::RenderStates states)const {
		states.transform.translate(pos);
		target.draw(comp<Draw>(), states);//отрисовка
	}

	void logic() { soul->logic(); }//логика

	const char* type() { return typeid(Entity).name(); }
};