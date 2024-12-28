//
//	math.h
//
#pragma once

#include <SFML/Graphics.hpp>

//
// Constants 
//
namespace Physics
{
	// How many frames we're displaying per second
	const inline float fTimeStep = 60.f;

	// How strong our gravity is
	const inline float fGravity = 9.81f;

	// Gravity as a vector
	const inline sf::Vector2f rGravity = { 0.f, fGravity };

	//
	const inline float fMoveScale = 50.f;

	//
	const inline float fMassSizeScale = 20.f;

	// Our friction coefficient
	inline float fFriction = 2.f;

	//
	// Calculates the magnitude for the given vector
	//
	inline float CalcMagnitude(const sf::Vector2f& _rVec)
	{
		return std::sqrt(std::pow(_rVec.x, 2) + std::pow(_rVec.y, 2));
	}

	//
	// Normalizes the given vector
	//
	inline sf::Vector2f Normalize(const sf::Vector2f& _rVec)
	{
		float fMag = CalcMagnitude(_rVec);

		if (fMag != 0)
			return _rVec / fMag;

		// If magnitude is 0 then return a zero vec
		return sf::Vector2f(0, 0);
	}

	//
	// Calculates the friction given the velocity and mass
	//
	inline sf::Vector2f CalcFriction(float _fFriction, const sf::Vector2f& _rVel, float _fMass)
	{
		return Normalize(-_rVel) * _fFriction * (fGravity * _fMass);
	}
}
