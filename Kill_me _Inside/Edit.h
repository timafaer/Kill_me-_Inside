#pragma once
#include"Core.h"

class Editor
{
private:
	
public:
	Game* core;

	std::map<std::string, sf::Texture> textures;
	Editor(Game* core) : core{ core } {}

	void map() {
		int x = 100, y = 100;
		std::string texturname = "texture.jpg";
		std::string mapfile = "map.txt";
		core->redact->add_obj("map");
		auto& ent = core->redact->get_one("map");
		ent.pos = sf::Vector2f(x, y);
		ent.add<Draw>();
		ent.add<Map>();
		ent.comp<Map>().set();
		ent.comp<Map>().read(mapfile);
		textures[texturname].loadFromFile(texturname);
		ent.comp<Draw>().set_texture(&textures[texturname]);
		ent.comp<Draw>().set_obj(&ent.comp<Map>().m_vertices);
	}
	void joke() {
		int x = 100, y = 100;
		std::string texturname = "joke.png";
		core->redact->add_obj("joke");
		auto& j = core->redact->get_one("joke");
		j.add<Draw>();
		j.soul = new Joker;

		if (!textures[texturname].loadFromFile(texturname))
			throw;
		j.soul->set(&j, core->redact,this,core);
		j.comp<Draw>().set_texture(&textures[texturname]);
	}

	

};