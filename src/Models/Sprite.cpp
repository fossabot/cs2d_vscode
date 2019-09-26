#include "Sprite.h"
#include "../Others/Logger.h"

Sprite::Sprite(Texture2D texture, GLuint x, GLuint y, GLuint width, GLuint height)
{
	this->texture = texture;
	if (width == 0)
	{
		size = glm::vec2(texture.Width, texture.Height);
		initData();
	}
	else
	{
		size = glm::vec2(width, height);
		initData(x, y, width, height);
	}
	Logger::WriteLog("Sprite->Sprite(texture, " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(width) + ", " + std::to_string(height) + ")");
}

Sprite::Sprite() = default;

Sprite::~Sprite() = default;

void Sprite::initData(GLuint x, GLuint y, GLuint width, GLuint height)
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[24];

	if (width == 0)
	{
		vertices[0] = 0.0f;
		vertices[1] = 1.0f;
		vertices[2] = 0.0f;
		vertices[3] = 1.0f;
		vertices[4] = 1.0f;
		vertices[5] = 0.0f;
		vertices[6] = 1.0f;
		vertices[7] = 0.0f;
		vertices[8] = 0.0f;
		vertices[9] = 0.0f;
		vertices[10] = 0.0f;
		vertices[11] = 0.0f;

		vertices[12] = 0.0f;
		vertices[13] = 1.0f;
		vertices[14] = 0.0f;
		vertices[15] = 1.0f;
		vertices[16] = 1.0f;
		vertices[17] = 1.0f;
		vertices[18] = 1.0f;
		vertices[19] = 1.0f;
		vertices[20] = 1.0f;
		vertices[21] = 0.0f;
		vertices[22] = 1.0f;
		vertices[23] = 0.0f;
	}

	else
	{
		const GLfloat xNorm = static_cast<GLfloat>(x) / static_cast<GLfloat>(texture.Width);
		const GLfloat yNorm = static_cast<GLfloat>(y) / static_cast<GLfloat>(texture.Height);

		const GLfloat wNorm = static_cast<GLfloat>(width) / static_cast<GLfloat>(texture.Width);
		const GLfloat hNorm = static_cast<GLfloat>(height) / static_cast<GLfloat>(texture.Height);

		vertices[0] = 0.0f;
		vertices[1] = 1.0f;
		vertices[2] = xNorm;
		vertices[3] = yNorm + hNorm; //sol alt
		vertices[4] = 1.0f;
		vertices[5] = 0.0f;
		vertices[6] = xNorm + wNorm;
		vertices[7] = yNorm; //sa� �st
		vertices[8] = 0.0f;
		vertices[9] = 0.0f;
		vertices[10] = xNorm;
		vertices[11] = yNorm; //sol �st

		vertices[12] = 0.0f;
		vertices[13] = 1.0f;
		vertices[14] = xNorm;
		vertices[15] = yNorm + hNorm;
		; //sol alt
		vertices[16] = 1.0f;
		vertices[17] = 1.0f;
		vertices[18] = xNorm + wNorm;
		vertices[19] = yNorm + hNorm; //sa� alt
		vertices[20] = 1.0f;
		vertices[21] = 0.0f;
		vertices[22] = xNorm + wNorm;
		vertices[23] = yNorm; //sa� �st
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}