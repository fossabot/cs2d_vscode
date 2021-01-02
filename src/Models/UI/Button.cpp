#include "Button.hpp"
#include "../../Others/Game_Parameters.hpp"

Button::Button() = default;

Button::Button(const std::string &text, Vector2<int> position, Vector2<int> size, TextRenderer &renderer, const Vector3<float> &buttonColor, const Vector3<float> &textColor, float scale, UIObjectType type) : Label(text, position, renderer, scale, textColor, type), difColor(false), haveOutline(false)
{
	this->buttonColor = buttonColor;
	Vector2<int> nSize = renderer.CalculateSize(text, 1.0F);
	this->setSize(Vector2<int>(static_cast<int>(static_cast<float>(nSize.x) * 1.5F), static_cast<int>(static_cast<float>(nSize.y) * 1.5F)));
	this->type = ButtonType::DEFAULT;
}

Button::Button(const Sprite &sprite, Vector2<int> position, Vector2<int> size, bool difColor, float scale, UIObjectType type) : Label(position, size, scale, type), haveOutline(false)
{
	this->sprite = sprite;
	this->difColor = difColor;
	this->type = ButtonType::SPRITE;
}

Button::Button(Tile &tile, float scale) : Label(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::BUTTON), difColor(false), haveOutline(false)
{
	this->tile = tile;
	this->type = ButtonType::TILE;
}

Button::~Button() = default;

void Button::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
	if (isVisible() && isEnable() && isRenderable())
	{
		switch (type)
		{
		case ButtonType::DEFAULT:
			if (haveOutline)
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), currentColor, true, outlineColor, 1.0F, 1.0F, 0.0F);
			}
			else
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), currentColor, false, outlineColor, 1.0F, 1.0F, 0.0F);
			}
			Label::DrawForButton(center);
			break;

		case ButtonType::SPRITE:
			if (difColor)
			{
				spriteRenderer.DrawSprite(this->sprite, this->getPosition(), this->getSize(), currentColor);
			}
			else if (!difColor)
			{
				if (haveOutline)
				{
					squareRenderer.ui_RenderFilledSquare(this->getPosition(), Vector2<int>(this->getSize().x + margin.x, this->getSize().y + margin.y), this->currentColor);
					squareRenderer.ui_RenderEmptySquare(this->getPosition(), Vector2<int>(this->getSize().x + margin.x, this->getSize().y + margin.y), this->outlineColor);
					spriteRenderer.DrawSprite(this->sprite, Vector2<int>(this->getPosition().x + margin.x / 2, this->getPosition().y + margin.y / 2), this->getSize());
				}
				else
				{
					squareRenderer.ui_RenderFilledSquare(this->getPosition(), Vector2<int>(this->getSize().x + margin.x, this->getSize().y + margin.y), this->currentColor);
					spriteRenderer.DrawSprite(this->sprite, Vector2<int>(this->getPosition().x + margin.x / 2, this->getPosition().y + margin.y / 2), this->getSize());
				}
			}
			break;
		case ButtonType::TILE:
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize());
			break;
		case ButtonType::ENV_OBJ:
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition() + Game_Parameters::SIZE_TILE / 4, this->getSize() / Vector2<int>(2));
			break;
		}
	}
}

void Button::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected, float time)
{
	if (isVisible() && isEnable() && isRenderable())
	{
		switch (type)
		{
		case ButtonType::TILE:
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize(), 0.0F, false, shine, selected, time);
		}
	}
}

void Button::Draw()
{
	if (isVisible() && isEnable())
	{
		Label::Draw();
	}
}

void Button::Update()
{
	if (isEnable() && isMouseEvents())
	{
		if (type == ButtonType::DEFAULT && !text.empty())
		{
			if (isMousePress())
			{
				currentColor = mouseclickColor;
				labelCurrentColor = labelClickColor;
			}
			else if (isMouseHover())
			{
				currentColor = mouseHoverColor;
				labelCurrentColor = labelMouseHoverColor;
			}
			else
			{
				currentColor = buttonColor;
				labelCurrentColor = labelColor;
			}
		}
		else if (type == ButtonType::SPRITE)
		{
			if (isMousePress())
			{
				currentColor = mouseclickColor;
			}
			else if (isMouseHover())
			{
				currentColor = mouseHoverColor;
			}
			else
			{
				currentColor = buttonColor;
			}
		}
	}
}

void Button::ProcessInput()
{
	if (isMouseEvents())
	{
		isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
		isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
	}
}

Vector2<int> Button::getPosition()
{
	if (type == ButtonType::TILE || type == ButtonType::ENV_OBJ)
	{
		if (isParent())
		{
			return parent->getPosition() + this->tile.GetPosition();
		}
		return this->tile.GetPosition();
	}
	if (isParent())
	{
		return parent->getPosition() + this->position;
	}
	return this->position;
}

Vector2<int> Button::getLocalPosition()
{
	if (type == ButtonType::TILE)
	{
		if (isParent())
		{
			return this->getPosition() - parent->getPosition();
		}
		return this->tile.GetPosition();
	}
	if (isParent())
	{
		return this->getPosition() - parent->getPosition();
	}
	return this->position;
}

Vector2<int> Button::getSize()
{
	if (type == ButtonType::TILE || type == ButtonType::ENV_OBJ)
	{
		return tile.GetSize();
	}
	return this->size;
}

bool Button::isMouseHover()
{
	if (isEnable() && isMouseEvents())
		return isMouseHoverM();
	return false;
}

bool Button::isMouseDown()
{
	return this->isDown;
}

bool Button::isMouseUp()
{
	return this->isUp;
}

bool Button::isMousePress()
{
	if (isEnable())
		return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
	return false;
}

bool Button::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	int sizeX = static_cast<int>(this->getSize().x);
	int sizeY = static_cast<int>(this->getSize().y);

	if (haveOutline)
	{
		sizeX += margin.x;
		sizeY += margin.y;
	}

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
	{
		return true;
	}
	return false;
}

bool Button::isMouseDownM(const int key)
{
	if (isPressed && isDown)
	{
		isDown = false;
		return false;
	}
	if (InputManager::isButtonDown(key) && isMouseHover())
	{
		isPressed = true;
		isDown = true;
		return true;
	}
	return false;
}

bool Button::isMouseUpM(const int key)
{
	if (InputManager::isButtonUp(key) && isPressed)
	{
		isPressed = false;
		isUp = true;
		return true;
	}
	if (isUp)
		isUp = false;
	return false;
}

bool Button::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		return true;
	}
	return false;
}

void Button::onMouseDown()
{
	if (isEnable() && isMouseHover())
	{
		labelCurrentColor = labelClickColor;
		isPressed = true;
		for (auto &f : listenersDown)
		{
			f();
		}
	}
}

void Button::onMouseUp()
{
	if (isPressed)
	{
		if (isEnable() && isMouseHover())
		{
			labelCurrentColor = labelColor;
			for (auto &f : listenersUp)
			{
				f();
			}
		}
		isPressed = false;
	}
}

void Button::setType(ButtonType type)
{
	this->type = type;
}

void Button::setMouseHoverColor(const Vector3<float> &color)
{
	this->mouseHoverColor = color;
}

void Button::setButtonColor(const Vector3<float> &color)
{
	this->buttonColor = color;
}

void Button::setMouseClickColor(const Vector3<float> &color)
{
	this->mouseclickColor = color;
}

void Button::setOutlineColor(const Vector3<float> &color)
{
	this->outlineColor = color;
}

void Button::setOutline(const bool value)
{
	this->haveOutline = value;
}

void Button::setMargin(const Vector2<int> value)
{
	if (haveOutline)
		this->margin = value;
}

void Button::setPosition(const Vector2<int> position)
{
	if (type == ButtonType::TILE)
	{
		this->tile.SetPosition(position);
	}
	else
		this->position = position;
}

void Button::setPosition(const int x, const int y)
{
	if (type == ButtonType::TILE)
	{
		this->tile.SetPosition(x, y);
	}
	else
	{
		this->position.x = x;
		this->position.y = y;
	}
}

Tile *Button::getTile()
{
	return &this->tile;
}