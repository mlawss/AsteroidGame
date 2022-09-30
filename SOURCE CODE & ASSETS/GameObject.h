#pragma once
#include "mydrawengine.h"

class GameObject {
private:
	PictureIndex image;
	float imageSize;
protected:
	Vector2D position;
	double angle;
	bool active;
	float transparency;

public:
	GameObject(); // constructor
	virtual ~GameObject(); // virtual destructor
	void LoadImage(const wchar_t* filename);
	virtual void Render();
	virtual void Update(float frametime) = 0;
	void SetImageSize(float size);
	float GetImageSize();
	virtual IShape2D& GetShape() = 0;
	virtual void HandleCollision(GameObject& other) = 0;
	bool IsActive() const;
	void Deactivate();
};