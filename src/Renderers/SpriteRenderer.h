#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "../Models/Shader.h"
#include "../Models/Sprite.h"

class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	//SpriteRenderer(Shader shader, Texture2D texture, GLuint x, GLuint y, GLuint width, GLuint height);
	SpriteRenderer(Shader shader);
	SpriteRenderer();
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	//void DrawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f);

	/**
 	* Does stuff
 	* @param {GLfloat} shineFactor : sadece editor'deki tile'larin parlamasi icin
	* @param {bool} isSelected : sadece editor'deki secili tile'larin parlamasi icin
 	*/
	void DrawSprite(const Sprite &sprite, glm::vec2 position, glm::vec2 size, GLfloat rotate = 0.0F, bool drawCenter = false,
	GLfloat shineFactor = 0.0F, bool isSelected = false, GLfloat time = 0.0F);
	
	void DrawSprite(const Sprite &sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color, bool drawCenter = false, 
	GLfloat rotate = 0.0F, GLfloat shineFactor = 0.0F, bool isSelected = false);

	void DrawSprite(const Sprite &sprite, glm::mat4 model);
	void SetProjection(glm::mat4 projection);

private:
	// Render state
	Shader shader;
	//GLuint quadVAO;
	//Texture2D quadTexture;

	//void initData(GLuint x = NULL, GLuint y = NULL, GLuint width = NULL, GLuint height = NULL);
};

#endif
