#include "Camera.h"

Camera::Camera(Rect2D startRect)
{
	mRect = startRect;
}

Camera::~Camera()
{
}

void Camera::SetPosition(Rect2D rect)
{
	mRect.x = (rect.x + rect.w / 2) - SCREEN_WIDTH / 2;
	mRect.y = (rect.y + rect.h / 2) - SCREEN_WIDTH / 2;
}

void Camera::SetLevelDimensions(int w, int h)
{
	levelWidth = w;
	levelHeight = h;
}

void Camera::Update()
{
	if (mRect.x < 0)
	{
		mRect.x = 0;
	}
	if (mRect.y < 0)
	{
		mRect.y = 0;
	}
	if (mRect.x > levelWidth - mRect.w)
	{
		mRect.x = levelWidth - mRect.w;
	}
	if (mRect.y > levelHeight - mRect.h)
	{
		mRect.y = levelHeight - mRect.h;
	}
}
