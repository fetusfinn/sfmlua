//
//	bezier.cpp
//
#include "bezier.h"

//
//
//
CBezier::CBezier(const vec2& _rAnchorA, const vec2& _rControlA, const vec2& _rControlB, const vec2& _rAnchorB) : m_rAnchorA(_rAnchorA), m_rControlA(_rControlA), m_rControlB(_rControlB), m_rAnchorB(_rAnchorB)
{
	
}

//
// Linear interpolation
//
vec2 CBezier::Lerp(const vec2& _rPointA, const vec2& _rPointB, float _fAlpha)
{
	//return { _rPointA.x + ((_rPointB.x - _rPointA.x) * _fAlpha) , _rPointA.y + ((_rPointB.y - _rPointA.y) * _fAlpha) };

	return _rPointA + ((_rPointB - _rPointA) * _fAlpha);
}

//
//
//
vec2 CBezier::Quadratic(const vec2& _rPointA, const vec2& _rPointB, const vec2& _rPointC, float _fAlpha)
{
	vec2 rLerpA = Lerp(_rPointA, _rPointB, _fAlpha);
	vec2 rLerpB = Lerp(_rPointB, _rPointC, _fAlpha);

	return Lerp(rLerpA, rLerpB, _fAlpha);
}

//
//
//
vec2 CBezier::Cubic(const vec2& _rPointA, const vec2& _rPointB, const vec2& _rPointC, const vec2& _rPointD, float _fAlpha)
{
	vec2 rQuadA = Quadratic(_rPointA, _rPointB, _rPointC, _fAlpha);
	vec2 rQuadB = Quadratic(_rPointB, _rPointC, _rPointD, _fAlpha);

	return Lerp(rQuadA, rQuadB, _fAlpha);
}

//
//
//
void CBezier::Update()
{
	// Tick
	m_fTime += 1.f / 60.f;

	for (int i = 0; i < NUM_POINTS; i++)
	{
		float fAlpha = static_cast<float>(i) / static_cast<float>(NUM_POINTS - 1);

		m_rPoints[i] = Cubic(m_rAnchorA, m_rControlA, m_rControlB, m_rAnchorB, fAlpha);
	}
}

//
//
//
void CBezier::Draw(sf::RenderWindow& _rWindow, sf::CircleShape& _rCircle)
{
	_rWindow.draw(m_rPoints, NUM_POINTS, sf::LineStrip);

	// Draw our control points
	_rCircle.setPosition(m_rControlA);
	_rWindow.draw(_rCircle);

	_rCircle.setPosition(m_rControlB);
	_rWindow.draw(_rCircle);

	float fDistAlong = fmod(m_fTime / 5.f, 1.f);

	_rCircle.setPosition(Cubic(m_rAnchorA, m_rControlA, m_rControlB, m_rAnchorB, fDistAlong));
	_rWindow.draw(_rCircle);
}

