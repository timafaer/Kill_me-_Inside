#pragma once
#include<functional>
#include<vector>
#include<fstream>
#include<string>
#include<SFML/Graphics.hpp>
//колайдер (пока не используется)
class Colider
{
	std::vector<sf::Vector2f> points;
	sf::Vector2f center;
	int size = 1;
	friend Colider;

	void rotate_one(sf::Vector2f& point,float rotate) {
		float x, y;
		x = point.x - center.x;
		y = point.y - center.y;
		point.x = x * cos(rotate) + y * sin(rotate) + center.x;
		point.y = y * cos(rotate) + x * sin(rotate) + center.y;
	}

	inline float area(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}
	inline bool intersect_1(float a, float b, float c, float d) {
		if (a > b)  std::swap(a, b);
		if (c > d)  std::swap(c, d);
		return std::max(a, c) <= std::min(b, d);
	}
	bool intersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) {
		return intersect_1(a.x, b.x, c.x, d.x)
			&& intersect_1(a.y, b.y, c.y, d.y)
			&& area(a, b, c) * area(a, b, d) <= 0
			&& area(c, d, a) * area(c, d, b) <= 0;
	}
public:
	Colider() {
		points.resize(1);
		center = sf::Vector2f(0, 0);
	}

	void add(sf::Vector2f point) { points[size - 1] = point; points.push_back(points[0]); size++; }
	void loadFromFile(std::string file) {
		std::ifstream fin;
		fin.open(file);
		int a;
		fin >> a;
		size += a;
		float x, y;
		while (!fin.eof()){
			fin >> x >> y;
			add(sf::Vector2f(x, y));
		}
		fin.close();
	}
	void operator+=(const sf::Vector2f move) { for (auto& i : points) { i += move; } }
	void rotate(float rotate) {
		for (auto& i : points)
			rotate_one(i, rotate);
	}
	bool colide(Colider en) {
		for (int i = 0; i < en.size; i++) {
			for (int j = 0; j < size; j++) {
				if (intersect(en.points[i], en.points[i + 1], points[j], points[j + 1]))
					return true;
			}
		}
		return false;
	}
};
class Soul;
struct Animat {//структура для анимации
	int now = 0;
	int count = 0;
	sf::Clock time;
	sf::Drawable** obj;
	sf::Vector2f center;
	void (*func)(Animat&, Soul*);// or std function
};

struct Healbar {
	sf::RectangleShape bacground;
	sf::RectangleShape hpbar;

};
