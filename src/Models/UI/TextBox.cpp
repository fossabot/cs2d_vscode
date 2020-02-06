#include "TextBox.h"
#include <iostream>

TextBox::TextBox() = default;

TextBox::TextBox(glm::vec2 position, TextRenderer &renderer, glm::vec2 size, bool isBackGround, float scale /*= 1.0F*/, glm::vec3 color /*= glm::vec3(1.0F)*/) : Label(position, renderer, scale, color, UIObjectType::TEXTBOX)
{
	this->editable = true;
	this->editMode = false;
	//this->mouseEvents = true;
	this->isBackGround = isBackGround;
	cursor = Sprite(ResourceManager::GetTexture("textcursor"));
	this->size = size;
	labelClickColor = glm::vec3(1.0F);
	clickBorderColor = glm::vec3(1.0F);
	borderColor = glm::vec3(0.6F);
	hoverBorderColor = glm::vec3(0.78F);
	currentBorderColor = borderColor;
	square = Square(true);
}

void TextBox::Update(const float dt)
{
	InputText(dt);
}

void TextBox::Draw(SquareRenderer &squareRenderer, SpriteRenderer &spriteRenderer)
{
	if (isVisible() && isEnable())
	{
		if (isBackGround)
			squareRenderer.RenderSquare(this->square, glm::vec2(getPosition().x, getPosition().y), size, glm::vec3(0.15F), currentBorderColor, 1.0F);
		if (editMode)
		{
			if (time <= 0.5F)
			{
				spriteRenderer.DrawSprite(cursor, glm::vec2(getPosition().x + tempTextSize.x, getPosition().y + 2.0F), glm::vec2(8.0F, 16.0F));
			}
			else
			{
				if (time >= 1.0F)
					time = 0.0F;
			}
			if (!tempText.empty())
				this->rend->RenderText(tempText, getPosition().x, getPosition().y + 2.0F, scale, labelCurrentColor);
		}
		else
		{
			if (!text.empty())
				this->rend->RenderText(tempText, getPosition().x, getPosition().y + 2.0F, scale, labelCurrentColor);
		}
	}
}

bool TextBox::isMouseHover()
{
	return isMouseHoverM();
	//return isHover;
}

bool TextBox::isMouseDown(const int key)
{
	return isMouseDownM(key);
	//return isDown;
}

bool TextBox::isMouseUp(const int key) //refactor: neden beraber degiller
{
	return isMouseUpM(key);
	//return isUp;
}

bool TextBox::isMousePress(const int key)
{
	return isMousePressM(key);
	//return isPress;
}

bool TextBox::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->size.x);
	const int sizeY = static_cast<int>(this->size.y);

	for (int i = posX; i <= posX + sizeX; i++)
	{
		for (int j = posY; j <= posY + sizeY; j++)
		{
			if (InputManager::mouseX == i && InputManager::mouseY == j)
			{
				if (editable && !editMode)
					currentBorderColor = hoverBorderColor; //0.78F
				return true;
			}
		}
	}
	if (editable && !editMode)
		currentBorderColor = borderColor; //0.6F
	return false;
}

bool TextBox::isMouseDownM(const int key)
{
	if (!isDown)
	{
		if (InputManager::isButtonDown(key))
		{
			if (isMouseHover())
			{
				isDown = true;
				isDownForClick = true;
				//isUp = false;
				//SetMouseState(isDown, true);
				//SetMouseState(isUp, false);
				//InputManager::mouseDownTrigger[key] = GL_TRUE;
				return true;
			}

			isDown = true;
			isDownForClick = false;
			InputManager::mouseDownTrigger[key] = GL_TRUE;
		}
	}
	//InputManager::mouseDownTrigger[key] = GL_TRUE;
	return false;
}

bool TextBox::isMouseUpM(const int key)
{
	if (isDown && isDownForClick)
	{
		if (InputManager::isButtonUp(key))
		{
			isDown = false;
			isDownForClick = false;
			//isUp = true;
			//isPress = false;
			//SetMouseState(isDown, false);
			//SetMouseState(isUp, true);
			//SetMouseState(isPress, false);
			//labelCurrentColor = labelColor;
			return true;
		}
	}

	else if (InputManager::isButtonUp(key))
	{
		if (isDown && !isDownForClick)
		{
			isDown = false;
			//isUp = true;
			//isPress = false;
			//SetMouseState(isDown, false);
			//SetMouseState(isUp, true);
			//SetMouseState(isPress, false);
			//labelCurrentColor = labelColor;
		}
		InputManager::mouseUpTrigger[key] = GL_TRUE;
	}
	//InputManager::mouseUpTrigger[key] = GL_TRUE;
	return false;
}

bool TextBox::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		return true;
	}
	return false;
}

void TextBox::InputText(const float dt)
{
	if (editable)
	{
		if (isEnable() && isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
		{
			editMode = true;
			time = 0.0F;
			labelCurrentColor = labelClickColor;
			currentBorderColor = clickBorderColor; //1.0F
		}

		if (editMode && isEnable())
		{
			time += dt;
			if (InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !isMouseHover())
			{
				this->labelCurrentColor = labelColor;
				this->text = tempText;
				this->labelSize = rend->CalculateSize(text, scale);
				this->tempTextSize = labelSize;
				this->currentBorderColor = borderColor; //0.6F
				editMode = false;
			}

			if (InputManager::isKeyDown(GLFW_KEY_BACKSPACE))
			{
				if (!tempText.empty())
				{
					tempText.pop_back();
					this->tempTextSize = rend->CalculateSize(tempText, scale);
				}
			}

			if (InputManager::keycode != L'\0')
			{
				if (InputManager::keycode >= 0 && InputManager::keycode <= 255)
				{
					const wchar_t keycode = InputManager::keycode;
					const wchar_t *c = &keycode;
					std::wstring tempString = &c[0];
					std::string afsaf;
					afsaf = tempString[0];
					this->tempText += afsaf;
					if (rend->CalculateSize(tempText, scale).x >= size.x)
					{
						tempText.pop_back();
					}
					else
					{
						this->tempTextSize = rend->CalculateSize(tempText, scale);
					}
				}
				InputManager::keycode = L'\0';
			}
		}
		else if (isMouseHover())
		{
			currentBorderColor = hoverBorderColor; //0.78F
		}

		else
		{
			currentBorderColor = borderColor; //0.6F
		}
	}

	isMouseUp(GLFW_MOUSE_BUTTON_LEFT);
}