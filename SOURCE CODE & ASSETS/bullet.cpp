#include "bullet.h"
#include "asteroid.h"
#include "gamecode.h"

// constructor
Bullet::Bullet()
{
	// initialisation of variables
	position.set(0, 0);
	velocity.set(0, 0);
	lifetime = 2.0f;
}

// initialise method
void Bullet::Initialise(Vector2D startPos, Vector2D startVel)
{
	// initialise pos and vel
	position = startPos;
	velocity = startVel;
	// load bitmap image
	LoadImage(L"plasma.bmp");
	active = true;
	SetImageSize(0.4f);
	lifetime = 2.0f;
}

// update method, called every frame
void Bullet::Update(float frametime)
{
	// accelerate the bullet away from the ship
	Vector2D acceleration;
	acceleration.setBearing(velocity.angle(), 500);
	velocity = velocity + acceleration * frametime;
	
	// update position of bullet
	position = position + velocity * frametime;
	lifetime -= frametime;
	// deactivate bullet after lifetime depletes
	if (lifetime <= 0) {
		Deactivate();
	}

	if (lifetime < 1.0f) {
		// make bullet gradually fade
		transparency = 1.0f - lifetime;

		if (transparency > 1.0f) {
			transparency = 1.0f;
		}
	}

	// find out screen dimensions
	Rectangle2D screen = MyDrawEngine::GetInstance()->GetViewport();

	// screen wrapping
	if (position.YValue > screen.GetTopLeft().YValue + 40) {
		position.YValue = screen.GetBottomRight().YValue - 40;
	}
	if (position.YValue < screen.GetBottomRight().YValue - 40) {
		position.YValue = screen.GetTopLeft().YValue + 40;
	}
	if (position.XValue > screen.GetTopRight().XValue + 40) {
		position.XValue = screen.GetTopLeft().XValue - 40;
	}
	if (position.XValue < screen.GetTopLeft().XValue - 40) {
		position.XValue = screen.GetTopRight().XValue + 40;
	}

	// place hitbox
	collisionShape.PlaceAt(position, 10);
}


// return hitbox
IShape2D& Bullet::GetShape() {
	return collisionShape;
}

// collision handler method
void Bullet::HandleCollision(GameObject& other) {
	// deactivate bullet if it hits asteroid
	if (other.IsActive()) {
		if (typeid(other) == typeid(Asteroid)) {
			Deactivate();
		}
	}
}
