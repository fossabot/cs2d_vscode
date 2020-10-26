#include "SquareRenderer.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/InputManager.h"
#include "../Others/Game_Parameters.h"

SquareRenderer::SquareRenderer()
{
}

SquareRenderer::SquareRenderer(bool init)
{
	this->squareShader_world = ResourceManager::LoadShader("../resources/shaders/squareVertex.txt", "../resources/shaders/squareFragment.txt", nullptr, "squareShader");
	this->squareShader_ui = ResourceManager::LoadShader("../resources/shaders/squareVertex.txt", "../resources/shaders/squareFragment.txt", nullptr, "squareShader");
	this->squareShader_ui.Use();
	this->squareShader_ui.SetMatrix4("projection", Projection::ortho(0.0f, static_cast<float>(Game_Parameters::SCREEN_WIDTH), static_cast<float>(Game_Parameters::SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f));
	this->squareShader_ui.UnUse();
	outline.initData();
	square = Square(true);
	emptyCircle = Circle(true);
	filledCircle = Circle(false);
}

SquareRenderer::~SquareRenderer() = default;

void SquareRenderer::ui_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, bool outline, Vector3<float> borderColor, float borderSize, GLfloat transperancy, GLfloat rotate)
{
	// Prepare transformations
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();

	if (outline)
		ui_RenderEmptySquareWithLine(position, size, borderColor, borderSize / 2, transperancy, rotate);
}

void SquareRenderer::ui_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderFilledSquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_world.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glBindVertexArray(square.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	this->squareShader_world.UnUse();
}

void SquareRenderer::world_RenderEmptySquareWithLine(Vector2<float> position, Vector2<float> size, Vector3<float> color, float lineSize, GLfloat transperancy, GLfloat rotate)
{
	//Vector2<float> pos, siz;
	Vector2<float> startPos, endPos;
	//sol kenar
	/*pos = Vector2<float>(position.x - lineSize, position.y);
	siz = Vector2<float>(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = Vector2<float>(position.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//ust kenar
	/*pos = Vector2<float>(position.x, position.y - lineSize);
	siz = Vector2<float>(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = Vector2<float>(position.x + size.x, position.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//sag kenar
	/*pos = Vector2<float>(position.x + size.x - lineSize, position.y);
	siz = Vector2<float>(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = Vector2<float>(position.x + size.x, position.y);
	endPos = Vector2<float>(position.x + size.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//alt kenar
	/*pos = Vector2<float>(position.x, position.y + size.y - lineSize);
	siz = Vector2<float>(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = Vector2<float>(position.x, position.y + size.y);
	endPos = Vector2<float>(position.x + size.x, position.y + size.y);
	this->world_RenderLine(startPos, endPos, color, lineSize, transperancy);
}

void SquareRenderer::ui_RenderEmptySquareWithLine(Vector2<float> position, Vector2<float> size, Vector3<float> color, float lineSize, GLfloat transperancy, GLfloat rotate)
{
	//Vector2<float> pos, siz;
	Vector2<float> startPos, endPos;
	//sol kenar
	/*pos = Vector2<float>(position.x - lineSize, position.y);
	siz = Vector2<float>(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = Vector2<float>(position.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//ust kenar
	/*pos = Vector2<float>(position.x, position.y - lineSize);
	siz = Vector2<float>(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = position;
	endPos = Vector2<float>(position.x + size.x, position.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//sag kenar
	/*pos = Vector2<float>(position.x + size.x - lineSize, position.y);
	siz = Vector2<float>(lineSize * 2, size.y);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = Vector2<float>(position.x + size.x, position.y);
	endPos = Vector2<float>(position.x + size.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);

	//alt kenar
	/*pos = Vector2<float>(position.x, position.y + size.y - lineSize);
	siz = Vector2<float>(size.x, lineSize * 2);
	this->world_RenderFilledSquare(pos, siz, color, transperancy, rotate);*/
	startPos = Vector2<float>(position.x, position.y + size.y);
	endPos = Vector2<float>(position.x + size.x, position.y + size.y);
	this->ui_RenderLine(startPos, endPos, color, lineSize, transperancy);
}

void SquareRenderer::ui_RenderLine(Vector2<float> startPos, Vector2<float> endPos, Vector3<float> color, float lineSize, GLfloat transperancy)
{
	Vector2<float> size;
	int rotate = 0;
	Vector2<float> dif = endPos - startPos;
	if (abs(dif.y) >= abs(dif.x))
	{
		size = Vector2<float>(dif.y, lineSize);
		dif = dif.Normalize();
		rotate = Projection::degrees(atan2(dif.x, dif.y));
		if (dif.y >= 0)
			rotate += 90;
		else
			rotate -= 90;
	}
	else if (abs(dif.x) > abs(dif.y))
	{
		size = Vector2<float>(dif.x, lineSize);
		dif = dif.Normalize();
		rotate = Projection::degrees(atan2(dif.x, dif.y));
		if (dif.x >= 0)
			rotate -= 90;
		else
			rotate += 90;
	}

	// Prepare transformations
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(startPos.x, startPos.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));					   // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(static_cast<float>(rotate)), Vector3(0.0f, 0.0f, 1.0f)); // Then rotate
	//model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));					   // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f)); // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glLineWidth(lineSize);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	glLineWidth(1.0F);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderLine(Vector2<float> startPos, Vector2<float> endPos, Vector3<float> color, float lineSize, GLfloat transperancy)
{
	Vector2<float> size;
	int rotate = 0;
	Vector2<float> dif = endPos - startPos;
	if (abs(dif.y) >= abs(dif.x))
	{
		size = Vector2<float>(dif.y, lineSize);
		dif = dif.Normalize();
		rotate = Projection::degrees(atan2(dif.x, dif.y));
		if (dif.y >= 0)
			rotate += 90;
		else
			rotate -= 90;
	}
	else if (abs(dif.x) > abs(dif.y))
	{
		size = Vector2<float>(dif.x, lineSize);
		dif = dif.Normalize();
		rotate = Projection::degrees(atan2(dif.x, dif.y));
		if (dif.x >= 0)
			rotate -= 90;
		else
			rotate += 90;
	}

	// Prepare transformations
	this->squareShader_world.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(startPos.x, startPos.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));					   // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(static_cast<float>(rotate)), Vector3(0.0f, 0.0f, 1.0f)); // Then rotate
	//model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));					   // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f)); // Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glLineWidth(lineSize);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	glLineWidth(1.0F);
	this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptySquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::world_RenderEmptySquare(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_world.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_world.SetMatrix4("model", model);
	this->squareShader_world.SetVector3f("colorUniform", color);
	this->squareShader_world.SetFloat("trans", transperancy);
	glBindVertexArray(outline.VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
	this->squareShader_world.UnUse();
}

void SquareRenderer::ui_RenderEmptyCircle(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);

	//glLineWidth(2.0F);
	glBindVertexArray(emptyCircle.VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 31);
	glBindVertexArray(0);
	//glLineWidth(1.0F);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::ui_RenderFilledCircle(Vector2<float> position, Vector2<float> size, Vector3<float> color, GLfloat transperancy, GLfloat rotate)
{
	this->squareShader_ui.Use();
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(position.x, position.y, 0.0f)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = Projection::translate(model, Vector3(position.x, position.y, 0.0f));
	model = Projection::translate(model, Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(rotate), Vector3(0.0f, 0.0f, 1.0f));	 // Then rotate
	model = Projection::translate(model, Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
	model = Projection::scale(model, Vector3(size.x, size.y, 1.0f));					 // Last scale
	this->squareShader_ui.SetMatrix4("model", model);
	this->squareShader_ui.SetVector3f("colorUniform", color);
	this->squareShader_ui.SetFloat("trans", transperancy);

	//glLineWidth(2.0F);
	glBindVertexArray(filledCircle.VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 32);
	glBindVertexArray(0);
	//glLineWidth(1.0F);
	this->squareShader_ui.UnUse();
}

void SquareRenderer::SetProjection(Matrix4<float> proj)
{
	this->squareShader_world.Use();
	this->squareShader_world.SetMatrix4("projection", proj);
	this->squareShader_world.UnUse();
}
