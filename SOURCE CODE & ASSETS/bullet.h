#pragma once
#include "vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float lifetime;
	Circle2D collisionShape;
public:
	Bullet();
	void Initialise(Vector2D startPos, Vector2D startVel);
	void Update(float frametime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};