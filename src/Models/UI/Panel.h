#ifndef PANEL_H
#define PANEL_H

#include "UIObject.h"
#include "../../Renderers/SquareRenderer.h"
#include "../../Renderers/SpriteRenderer.h"
#include <GLFW/glfw3.h>
#include "../../Managers/InputManager.h"
#include "Button.h"

class Panel : public UIObject
{
public:
	Panel(glm::vec2 position, const std::string &title, glm::vec2 size, TextRenderer &renderer, bool isBackGround = false, bool opttitles = true, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F));
	Panel();
	~Panel();

	void Draw(SquareRenderer &squareRenderer, SpriteRenderer &spriteRenderer);
	void Update(const float dt) override;
	void OnEnable() override;
	void OnDisable() override;
	bool isMouseHover();
	bool isMouseDown(int key);
	bool isMouseUp(int key);
	bool isMousePress(int key);
	bool isMouseHoverM();
	bool isMouseDownM(int key);
	bool isMouseUpM(int key);
	bool isMousePressM(int key);

	glm::vec3 getPanelColor() const;
	bool isBackGround() const;
	bool isMovable() const;
	std::string getTitle() const;

	void setPanelColor(const glm::vec3 color);
	void setBackGround(const bool value);
	void setMovable(const bool value);
	void setTitle(const std::string &text);

protected:
	glm::vec3 panelColor;
	glm::vec2 dragSize;
	glm::vec2 dragPos;
	Square square = Square(true);
	Button escapeButton;
	Label title;
	bool opttitles;

	bool backGround;
	bool movable;

private:
	bool isDownForClick = false;
	bool isDown = false;
	float lineOffset = 20.0F;
};

#endif