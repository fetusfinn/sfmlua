//
//  Week 2 exercies
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include <sol/sol.hpp>

#include "physics.h"
#include "bezier.h"

//
// Generates a random number within the given range
//
inline int RandomInt(int min, int max)
{
	if (max < min)
		return 0;

	return rand() % (max - min + 1) + min;
}

//
// Fades between the wo given colours, fades from col1 to col2
//
sf::Color FadeBetween(const sf::Color& _rCol1, const sf::Color& _rCol2, float _fPercent)
{
	// Ensure percentage is clamped between 0 and 1
	if (_fPercent > 1.f)
		_fPercent = 1.f;

	if (_fPercent < 0.f)
		_fPercent = 0.f;

	// Lerp each base colour
	sf::Uint8 r = static_cast<sf::Uint8>(_rCol1.r + _fPercent * (_rCol2.r - _rCol1.r));
	sf::Uint8 g = static_cast<sf::Uint8>(_rCol1.g + _fPercent * (_rCol2.g - _rCol1.g));
	sf::Uint8 b = static_cast<sf::Uint8>(_rCol1.b + _fPercent * (_rCol2.b - _rCol1.b));
	sf::Uint8 a = static_cast<sf::Uint8>(_rCol1.a + _fPercent * (_rCol2.a - _rCol1.a));

	return { r, g, b, a };
}

//
// Function to handle the fading between an array of colors
//
sf::Color FadeBetween(const std::vector<sf::Color>& colors, float elapsedTime, float fadeDuration, bool loop)
{
	size_t colorCount = colors.size();

	// If there is only one color, just return it
	if (colorCount < 2)
		return colors[0];

	// Calculate the total time required to fade between each color in sequence
	float totalDuration = fadeDuration * (colorCount - 1);

	// If not looping and the fade is complete, return the last color
	if (!loop && elapsedTime >= totalDuration)
		return colors.back();

	// Calculate the current segment based on elapsed time
	float timeInCycle = fmod(elapsedTime, totalDuration);
	int currentColorIndex = static_cast<int>(timeInCycle / fadeDuration);

	// Get the two colors to interpolate between
	sf::Color startColor = colors[currentColorIndex];
	sf::Color endColor = colors[(currentColorIndex + 1) % colorCount]; // Wrap around if looping

	// Calculate the percentage between the two colors
	float percentage = (timeInCycle - currentColorIndex * fadeDuration) / fadeDuration;

	// Interpolate between the two colors
	return FadeBetween(startColor, endColor, percentage);
}

//
//
//
int main()
{
	// Seed our RNG
	std::srand(std::time(nullptr));

	// Create the window with a set resolution:
	sf::RenderWindow rWindow(sf::VideoMode(1280, 720), "SFML Project");

	// Set the frame rate limit
	rWindow.setFramerateLimit(Physics::fTimeStep);

	// Our circle for our control points
	sf::CircleShape rCircle;
	rCircle.setPointCount(10);
	rCircle.setRadius(10);
	rCircle.setOrigin(10, 10);
	rCircle.setFillColor(sf::Color::Transparent);
	rCircle.setOutlineColor(sf::Color::White);
	rCircle.setOutlineThickness(2);

	// Create our curve
	CBezier rCurve(vec2(0, 360), vec2(300, 150), vec2(800, 500), vec2(1280, 360));

	// Clock to keep track of our fade
	sf::Clock rFadeClock;

	// How many seconds we want to take to fade
	float fFadeDur = 5.f;

	sf::Color rFade[2] = { sf::Color::White, sf::Color::Blue };

	// our lua state
	sol::state lua;


	//
	// For as long as the window's open
	//
	while (rWindow.isOpen())
	{
		//
		// Event handling
		//
		{
			sf::Event rEvent;
			while (rWindow.pollEvent(rEvent))
			{
				switch (rEvent.type)
				{
				case sf::Event::Closed:
					rWindow.close();
					break;



				}
			}
		}

		//
		// Input
		//
		{
			// Left click to move the first control point
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				rCurve.SetControlPos(POINT_A, static_cast<vec2>(sf::Mouse::getPosition(rWindow)));
			}

			// Right click to move the second control point
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				rCurve.SetControlPos(POINT_B, static_cast<vec2>(sf::Mouse::getPosition(rWindow)));
			}
		}

		//
		// Functionality
		//
		{
			rCurve.Update();
		}

		//
		// Colour fade
		//
		{
			// Calculate the percentage of the fade completed based on time
			float fElapsed = rFadeClock .getElapsedTime().asSeconds();
			float fPercent = fElapsed / fFadeDur;

			// Get the current color by interpolating between start colour and end colour
			sf::Color rFadeCol = FadeBetween(rFade[0], rFade[1], fPercent);

			// Apply the color to the rectangle
			rCurve.SetColour(rFadeCol);

			// If the fade is complete, reset the clock to loop
			if (fPercent >= 1.f)
			{
				// Swap our colours so it bounces between the colours
				std::swap(rFade[0], rFade[1]);

				// Restart clock for looping the fade
				rFadeClock.restart();
			}
		}

		//
		// Drawing
		//
		//rWindow.clear(sf::Color::White);
		rWindow.clear(sf::Color::Black);
		{
			rCurve.Draw(rWindow, rCircle);
		}
		rWindow.display();
	}

	return 0;
}