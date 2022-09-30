#include "GameObject.h"

// constructor
GameObject::GameObject() {
	// initialisation of variables
	angle = 0;
	image = -1;
	position.set(0, 0);
	active = true;
	imageSize = 1.0f;
	transparency = 0;
}

GameObject::~GameObject() {
	// virtual destructor, doesn't need code
}

// method to load bitmap image of an object
void GameObject::LoadImage(const wchar_t* filename)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(filename);
}

// render method, draws object onto screen
void GameObject::Render()
{
	if (active) { // check to make sure object is active before rendering
		MyDrawEngine::GetInstance()->DrawAt(position, image, imageSize, angle, transparency);
	}
}

// sets the imageSize variable to the parameter
void GameObject::SetImageSize(float size)
{
	imageSize = size;
}

// returns the imageSize
float GameObject::GetImageSize()
{
	return imageSize;
}

// checks if an object is active
bool GameObject::IsActive() const
{
	return active;
}

// sets an object's active state to false
void GameObject::Deactivate()
{
	active = false;
}