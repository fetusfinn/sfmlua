//
//	bezier.h
//
#pragma once

#include <SFML/Graphics.hpp>

typedef sf::Vector2f vec2;

// const vec2&

// How many points we want for our curve
#define NUM_POINTS 100

//
//
//
enum EPointIndex :  char
{
	POINT_A = 0,
	POINT_B,
};

//
//
//
class CBezier
{
private:

	// Our curves anchor points
	vec2 m_rAnchorA	 = { 0, 0 };
	vec2 m_rAnchorB = { 0, 0 };

	// Our curves control points
	vec2 m_rControlA = { 0, 0 };
	vec2 m_rControlB = { 0, 0 };

	// All of the points in our line
	sf::Vertex m_rPoints[NUM_POINTS];

	float m_fTime = 0;

private:

	vec2 Lerp		(const vec2& _rPointA, const vec2& _rPointB, float _fAlpha);
	vec2 Quadratic	(const vec2& _rPointA, const vec2& _rPointB, const vec2& _rPointC, float _fAlpha);
	vec2 Cubic		(const vec2& _rPointA, const vec2& _rPointB, const vec2& _rPointC, const vec2& _rPointD, float _fAlpha);
	
public:

	CBezier(const vec2& _rAnchorA, const vec2& _rControlA, const vec2& _rControlB, const vec2& _rAnchorB);

	void Update();
	void Draw(sf::RenderWindow& _rWindowm, sf::CircleShape& _rCircle);

	void SetControlPos(char _iIndex, const vec2& _rPos)
	{
		if (_iIndex == 0)
		{
			m_rControlA = _rPos;
		}
		else // if (_iIndex == 1)
		{
			m_rControlB = _rPos;
		}
	}

	void SetColour(const sf::Color& _rCol)
	{
		for (auto& vert : m_rPoints)
			vert.color = _rCol;
	}
};

