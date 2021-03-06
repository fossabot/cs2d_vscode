#ifndef MENU_H
#define MENU_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include "../Models/Sprite.hpp"
#include "../Renderers/SpriteRenderer.hpp"
#include "../Renderers/TextRenderer.hpp"
#include "../Managers/InputManager.hpp"
#include "../Others/Game_Parameters.hpp"

#include "../Models/UI/Label.hpp"
#include "../Models/UI/TextBox.hpp"
#include "../Models/UI/Panel.hpp"
#include "../Models/UI/ListItem.hpp"

//#include "ButtonRenderer.hpp"

class Menu
{
public:
	Menu();
	~Menu();

	static Menu &instance()
	{
		static Menu INSTANCE;
		return INSTANCE;
	}

	void Initialize(Sprite menuSprites[4]);

	void OnEnable();
	void OnDisable();
	void Start();
	void Update();
	void ProcessInput();
	void Render();

	void SetEnable(const bool value);

	Sprite menuSprites[4];
	TextRenderer *textRenderer;

	SpriteRenderer *menuRenderer;
	SquareRenderer *squareRenderer;

	Label *l_console = nullptr;
	Label *l_quickplay = nullptr;
	Label *l_newgame = nullptr;
	Label *l_options = nullptr;
	Label *l_editor = nullptr;

	TextBox *t_test = nullptr;

	Panel *optionsPanel = nullptr;

	Panel *newPanel = nullptr;
	Panel *mapsPanel = nullptr;
	TextBox *t_mapName = nullptr;
	Button *b_newGame = nullptr;
	ListItem *mapNames = nullptr;

private:
	bool enable = false;

	void selectedMapChange(Button *old, Button *n);

	std::vector<std::string> getMapNames()
	{
		std::vector<std::string> maps;

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir("../../resources/levels")) != NULL)
		{
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL)
			{
				if (ent->d_name[0] == '.')
					continue;
				std::string mapName(ent->d_name);
				if (mapName.substr(mapName.size() - 4) == ".xml")
				{
					std::string a = mapName.substr(0, mapName.size() - 4);
					maps.push_back(a);
				}
			}
			closedir(dir);
		}
		else
		{
			perror("could not open directory");
		}
		return maps;
	}
};

#endif // MENU_H