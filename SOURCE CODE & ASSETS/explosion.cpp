#include "explosion.h"

// (empty) constructor
Explosion::Explosion()
{
	
}

// initialise method
void Explosion::Initialise(Vector2D pos, float size, float time, Vector2D vel)
{
	// set initial values for variables
	position = pos;
	animationSpeed = 8 / time;
	SetImageSize(size);
	active = true;
	velocity = vel;
	currentImage = 0.0f;
	
	// create list of images to create explosion animation
	images[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	images[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	images[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	images[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	images[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	images[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	images[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	images[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
}

// update method, called every frame
void Explosion::Update(float frametime)
{
	// animate explosion then deactivate
	currentImage += frametime * animationSpeed;
	if (currentImage >= 8.0) {
		Deactivate();
	}
}

// render method
void Explosion::Render()
{
	if (active) { // check to make sure object is active before rendering
		MyDrawEngine::GetInstance()->DrawAt(position, images[(int)currentImage], GetImageSize(), angle, transparency);
	}
}

// return hitbox
IShape2D& Explosion::GetShape()
{
	return collisionShape;
}

// (empty) collision handler method (since nothing needs to collide with the explosion itself)
// but still need method since it is in the superclass (GameObject)
void Explosion::HandleCollision(GameObject& other)
{
}
