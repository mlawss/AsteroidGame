#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "gamecode.h"
#include "explosion.h"

// constants for easier changing of main values
const float TURN_RATE = 2.0f;
const float SHIP_SPEED = 900.0f;
const float FRICTION = 1.0f;
const float BULLETSPEED = 1000.0f;

// constructor
Spaceship::Spaceship() {
	// initialisation of main variables
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	shootDelay = 0.0f;
}

void Spaceship::Initialise(Vector2D startPosition) {
	// initialisation of other variables
	position = startPosition;
	velocity.set(0, 0);
	angle = 0;
	// load bitmap image
	LoadImage(L"spaceship.bmp");
	SetImageSize(1.0f);
	shootDelay = 0.0f;
}

// update method, called every frame
void Spaceship::Update(float frametime) {
	// set up keyboard for inputs
	MyInputs::GetInstance()->SampleKeyboard();

	// turn ship if A and D are pressed
	if (MyInputs::GetInstance()->KeyPressed(DIK_A)) {
		angle = angle - TURN_RATE * frametime;
	}

	if (MyInputs::GetInstance()->KeyPressed(DIK_D)) {
		angle = angle + TURN_RATE * frametime;
	}

	// propel ship forward if W is pressed
	if (MyInputs::GetInstance()->KeyPressed(DIK_W)) {
		Vector2D acceleration;
		acceleration.setBearing(angle, SHIP_SPEED);
		velocity += acceleration * frametime;
	}

	//bullet firing
	if (MyInputs::GetInstance()->KeyPressed(DIK_SPACE) && shootDelay<=0) {
		// new bullet appears from position and angle of spaceship
		Bullet* pBullet = new Bullet();
		Vector2D vel;
		vel.setBearing(angle, BULLETSPEED);
		pBullet->Initialise(position, vel);

		Game::instance.GetObjectManager().Add(pBullet);
		// shoot delay so bullets don't just come out constantly
		shootDelay = 0.4f;
	}
	// increment the shootdelay
	shootDelay = shootDelay - frametime;

	velocity = velocity - velocity * FRICTION * frametime; // deceleration when W key is released
	position += velocity * frametime; // so ship keeps moving after W is released

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
	collisionShape.PlaceAt(position, 30);
}

// returns hitbox
IShape2D& Spaceship::GetShape() {
	return collisionShape;
}

// collision handler method
void Spaceship::HandleCollision(GameObject& other) {
	if (other.IsActive()) {
		// deactivate and create new explosion if ship collides with asteroid
		if (typeid(other) == typeid(Asteroid)) {
			Deactivate();
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position, 3.0f, 0.75f, Vector2D(0, 0));

			Game::instance.GetObjectManager().Add(pExplosion);
		}
	}
}
