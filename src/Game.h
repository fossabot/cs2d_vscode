#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "Renderers/SpriteRenderer.h"
#include "Models/GameObject.h"
#include "Models/Map.h"
#include "Models/Camera.h"
#include "Models/Player.h"
#include <memory>
#include "Scenes/StartGame.h"
#include "Managers/ResourceManager.h"
#include "Others/Game_Parameters.h"
#include "Scenes/Menu.h"
#include "Scenes/Editor.h"

class Game
{
public:
	Game(GLuint width, GLuint height);
	Game();
	virtual ~Game();

	void Init();
	void Update(const float dt);
	void Render(const float dt);
	void ProcessInput(const float dt);
	void NewGame();

	static void SetGameState(GameState state);
	static GameState GetGameState();

	static GameState state;

private:
	//std::unique_ptr<SpriteRenderer> renderer;

	SpriteRenderer spriteRenderer, menuRenderer;
	//std::shared_ptr<TextRenderer> textRenderer;
	Camera camera;
	//Label *label;
	//std::shared_ptr<std::vector<Map>> maps;

	std::vector<Map> maps;
	std::vector<Weapon> weapons;

	//std::vector<GameObject*> gameobjects;

	//std::shared_ptr<std::vector<Weapon*>> weapons;
	//std::vector<std::shared_ptr<Weapon>> weapons;
	//std::vector<std::shared_ptr<Sprite>> pointers;
	Sprite mouseSprite;
	static StartGame scene;
	static Menu menu;
	static Editor editor;

	Sprite menuSprites[4];

	//Weapon *main1, *main2, *main3, *pistol1, *pistol2, *pistol3, *pistol4, *knife1, *knife2;
	void initTextures() const;
	void initMaps();
	void initRenderers();
	void initShaders() const;
	void initMenuSprites();
};

#endif // GAME_H