#pragma once

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_WIN,
	SCREEN_HIGHSCORES
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	} 	
	
	Vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct Rect2D
{
	float x;
	float y;
	float w;
	float h;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		w = 0.0f;
		h = 0.0f;

	}

	Rect2D(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};

struct Circle2D
{
	double radius;
	Vector2D position;

	Circle2D()
	{
		radius = 0.0f;
		position.x = 0.0f;
		position.y = 0.0f;
	}

	Circle2D(double _radius, Vector2D pos)
	{
		radius = _radius;
		position.x = pos.x;
		position.y = pos.y;
	}
};


