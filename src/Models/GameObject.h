#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Renderers/SpriteRenderer.h"

enum class ObjectType
{
	PLAYER,
	WEAPON,
	GAMEOBJECT
};

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 pos, Sprite sprite, glm::vec2 size, int objType = 2);
	virtual ~GameObject();

	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	virtual void DrawModel(SpriteRenderer &renderer);

	virtual void SetParent(GameObject *go);
	virtual void RemoveParent();

	void SetTransform(glm::mat4 transform);

	void SetTransform(glm::vec2 pos, glm::vec2 size, GLfloat rot = 0.0f);
	void SetPosition(glm::vec2 pos);
	void SetPosition(const float x, const float y);
	void SetSize(glm::vec2 size);
	void SetRotation(GLfloat rot);
	void setCellPosition(int x, int y);
	void setCellPosition(glm::vec2 pos);

	virtual void Destroy();
	virtual void OnDestroy();

	
	GameObject GetParentObject() const;
	int GetObjectType() const;
	glm::mat4 GetTransform();
	glm::vec2 GetPosition() const;

	void BuildTransform();

	GLboolean IsCollision() const;
	GLboolean IsDestroyed() const;
	GLboolean IsParent() const;

	Sprite sprite;

protected:
	// Object state
	glm::vec2 localPosition, localSize, velocity;
	GLfloat localRotation;

	glm::vec2 cellPos;

	glm::mat4 localTranform = glm::mat4(1.0f);

	GameObject *parent = nullptr;

	GLboolean isCollision;
	GLboolean isDestroyed;

	ObjectType objType;
};



#endif