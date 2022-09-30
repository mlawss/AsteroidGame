#pragma once
#include "vector2D.h"
#include "mydrawengine.h"
#include "myinputs.h"
#include "mysoundengine.h"
#include "GameObject.h"

class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	float shootDelay;
	Circle2D collisionShape;
public:
	Spaceship();
	void Initialise(Vector2D startPosition);
	void Update(float frametime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};