#include "asteroid.h"
#include "bullet.h"
#include "spaceship.h"
#include "gamecode.h"
#include "explosion.h"

// constructor
Asteroid::Asteroid()
{
	// initialise all variables
	position.set(0, 0);
	velocity.set(0, 0);
	angle = 0;
	spinSpeed = 0;
}

// initialise asteroid object
void Asteroid::Initialise(Vector2D startPos, Vector2D startVel)
{
	// set start position and velocity as parameters
	position.set(startPos);
	velocity.set(startVel);

	// load bitmap image of asteroid
	LoadImage(L"rock3.bmp");

	// random image size and spin speed
	SetImageSize(float(1.0f + rand() % 151/100.0f)); //1.0f - 2.5f
	spinSpeed = float(0.2f + rand() % 81/100.0f); //0.2f - 1.0f
}

// method that calls every frame to update asteroid
void Asteroid::Update(float frametime)
{
	// change angle with spin speed
	angle += spinSpeed * frametime;
	// change position with velocity
	position = position + velocity * frametime;

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

	// place collision shape (hitbox)
	collisionShape.PlaceAt(position, 60);
}

// method that returns the hitbox
IShape2D& Asteroid::GetShape() {
	return collisionShape;
}

// collision handler method for when asteroid collides with something
void Asteroid::HandleCollision(GameObject& other) {
	if (other.IsActive()) {
		if (typeid(other) == typeid(Bullet)) {
			Deactivate();
			// only splits asteroid into 3 IF the size is greater than 0.6f.
			// to prevent infinite splitting
			if (GetImageSize() > 0.6f) {
				for (int i = 0; i < 3; i++) {
					Asteroid* pAst = new Asteroid();
					Vector2D pos = position + Vector2D(rand() % 150 - 75, (rand() % 150 - 75) * GetImageSize());
					Vector2D vel(float(rand() % 200 - 100), float(rand() % 200 - 100));
					pAst->Initialise(pos, vel + velocity);
					pAst->SetImageSize((GetImageSize()) / 2.0);

					Game::instance.GetObjectManager().Add(pAst);

					// explosion effect of asteroid blowing up:
					Explosion* pExplosion = new Explosion();
					pExplosion->Initialise(position, 3.0f, 0.75f, Vector2D(0, 0));

					Game::instance.GetObjectManager().Add(pExplosion);
				}
			}
		}
	}

	// outside of active check because spaceship is deactivated since it has collided
	if (typeid(other) == typeid(Spaceship)) {
		Deactivate();
		// only splits asteroid into 3 IF the size is greater than 0.6f.
		// to prevent infinite splitting
		if (GetImageSize() > 0.6f) {
			for (int i = 0; i < 3; i++) {
				Asteroid* pAst = new Asteroid();
				Vector2D pos = position + Vector2D(rand() % 150 - 75, (rand() % 150 - 75) * GetImageSize());
				Vector2D vel(float(rand() % 200 - 100), float(rand() % 200 - 100));
				pAst->Initialise(pos, vel + velocity);
				pAst->SetImageSize((GetImageSize()) / 2.0);

				Game::instance.GetObjectManager().Add(pAst);
			}
		}
	}
}
