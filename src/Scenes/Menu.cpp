#include "Menu.hpp"
#include "../Game.hpp"
#include "../Others/Logger.hpp"

Menu::Menu() = default;

Menu::~Menu() = default;

void Menu::Start()
{
	Logger::WriteLog("Menu::Start()");
	this->menuRenderer = new SpriteRenderer(ResourceManager::GetShader("menu"));
	this->textRenderer = new TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../../resources/fonts/liberationsans.ttf", 16);
	this->squareRenderer = new SquareRenderer(true);

	this->l_console = new Label("Console", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 - 50), *textRenderer, 0.8F, Vector3<float>(0.55F));
	this->l_newgame = new Label("New Game", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 - 20), *textRenderer, 1.0F, Vector3<float>(0.58F));
	this->l_options = new Label("Options", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2), *textRenderer, 1.0F, Vector3<float>(0.58F));
	this->l_editor = new Label("Editor", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 + 20), *textRenderer, 1.0F, Vector3<float>(0.58F));

	this->optionsPanel = new Panel(Vector2<int>(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "Options", Vector2<int>(420, 450), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F));
	this->optionsPanel->setMovable(true);

	this->t_test = new TextBox(Vector2<int>(20, 20), *textRenderer, Vector2<int>(100, 20), true, 1.0F, Vector3<float>(0.58F));
	this->t_test->setParent(optionsPanel);
	this->t_test->setParentCenterPos();

	this->newPanel = new Panel(Vector2<int>(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "New Game", Vector2<int>(420, 450), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F));
	this->newPanel->setMovable(true);

	this->mapsPanel = new Panel(Vector2<int>(100, 100), "Maps", Vector2<int>(120, 200), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F));
	this->mapsPanel->setMovable(false);
	this->mapsPanel->setScrollable(true);
	this->mapsPanel->setOutline(true);
	this->mapsPanel->setVisible(true);
	this->mapsPanel->setOutlineColor(Vector3<float>(0.47F));
	this->mapsPanel->setParent(newPanel, true);
	this->mapNames = new ListItem(mapsPanel);

	this->t_mapName = new TextBox(Vector2<int>(100, 320), *textRenderer, Vector2<int>(120, 20), true, 1.0F, Vector3<float>(0.58F));
	this->t_mapName->setParent(newPanel, true);

	this->b_newGame = new Button("Start", Vector2<int>(240, 320), Vector2<int>(60, 20), *textRenderer, Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	this->b_newGame->setMouseClickColor(Vector3<float>(0.30F));
	this->b_newGame->setMouseHoverColor(Vector3<float>(0.30F));
	this->b_newGame->setLabelMouseHoverColor(Vector3<float>(0.58F));
	this->b_newGame->setLabelClickColor(Vector3<float>(1.0F));
	this->b_newGame->setOutline(true);
	this->b_newGame->setOutlineColor(Vector3<float>(1.0F));
	this->b_newGame->setParent(newPanel, true);

	std::function<void(Button *, Button *)> mapChange = std::bind(&Menu::selectedMapChange, this, std::placeholders::_1, std::placeholders::_2);
	this->mapNames->AddListener(mapChange);
}

void Menu::Initialize(Sprite menuSprites[4])
{
	Logger::WriteLog("Menu::Menu(menuSprites[4], menuRenderer)");
	for (int i = 0; i < 4; i++)
	{
		this->menuSprites[i] = menuSprites[i];
	}

	this->SetEnable(true);
}

void Menu::OnEnable()
{
	this->Start();
	this->optionsPanel->setEnable(false);
	this->mapsPanel->setEnable(false);
}

void Menu::OnDisable()
{
	delete l_console;
	delete l_newgame;
	delete l_options;
	delete l_editor;

	delete t_test;
	delete optionsPanel;

	delete mapNames;

	delete t_mapName;
	delete b_newGame;
	delete mapsPanel;
	delete newPanel;

	delete textRenderer;

	delete menuRenderer;
	delete squareRenderer;
}

void Menu::SetEnable(const bool value)
{
	if (this->enable == value)
		return;
	this->enable = value;
	if (this->enable)
		OnEnable();
	else
		OnDisable();
}

void Menu::Update()
{
	l_options->Update();
	l_console->Update();
	l_editor->Update();
	l_newgame->Update();
	optionsPanel->Update();
	newPanel->Update();
	mapNames->Update();
}

void Menu::ProcessInput()
{
	l_options->ProcessInput();
	l_console->ProcessInput();
	l_editor->ProcessInput();
	l_newgame->ProcessInput();
	optionsPanel->ProcessInput();
	newPanel->ProcessInput();
	mapNames->ProcessInput();

	if (l_editor->isMouseDown())
	{
		Game::SetGameState(GameState::EDITOR);
		return;
	}

	if (l_newgame->isMouseDown())
	{
		mapNames->Clear();
		std::vector<std::string> maps = getMapNames();
		for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
		{
			mapNames->AddItem(maps[i]);
		}
		newPanel->setEnable(true);
	}

	if (b_newGame->isMouseDown())
	{
		std::string mName = "../../resources/levels/" + t_mapName->getText() + ".xml";
		StartGame::instance().Initialize(mName);
		Game::SetGameState(GameState::INGAME);
		return;
	}

	if (l_options->isMouseDown())
	{
		optionsPanel->setEnable(true);
	}
}

void Menu::Render()
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			menuRenderer->DrawSprite(menuSprites[3], Vector2<int>(0), Vector2<int>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
			break;
		}
	}
	//menuRenderer.DrawSprite(menuSprites["mouseSprite"], Vector2<int>(InputManager::mousePos.x, InputManager::mousePos.y), Vector2<int>(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), 0.0F, true);
	l_options->Draw();
	l_editor->Draw();
	l_console->Draw();
	l_newgame->Draw();
	//button->Draw(*squareRenderer);
	optionsPanel->Draw(*menuRenderer, *squareRenderer);
	newPanel->Draw(*menuRenderer, *squareRenderer);
	mapNames->Draw(*menuRenderer, *squareRenderer);
	//t_test->Draw(menuRenderer, squareRenderer);
}

void Menu::selectedMapChange(Button *old, Button *n)
{
	t_mapName->setText(n->getText());
}