#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "vector2D.h"

class Explosion : public GameObject
{
private:
	float currentImage;
	Circle2D collisionShape;
	Vector2D velocity;
	float animationSpeed;
	PictureIndex images[8];
public:
	Explosion();
	void Initialise(Vector2D pos, float size, float time, Vector2D vel = Vector2D(0, 0));
	void Update(float frametime);
	void Render() override;
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};