#pragma once
#include "vector2D.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Asteroid : public GameObject
{
private:
	Vector2D velocity;
	float spinSpeed;
	Circle2D collisionShape;
public:
	Asteroid();
	void Initialise(Vector2D startPos, Vector2D startVel);
	void Update(float frametime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};