#pragma once
#include "Commons.h"
#include "Main.h"
#include "GameObject.h"

class Camera
{
public:
	Camera(Rect2D startRect);
	~Camera();

	Vector2D GetPosition() { return Vector2D(mRect.x, mRect.y); }
	Rect2D GetRect() { return mRect; }
	void SetPosition(Rect2D rect);
	void SetLevelDimensions(int w, int h);

	void Update();

private:
	Rect2D mRect;
	int levelWidth;
	int levelHeight;
};

