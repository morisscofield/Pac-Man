#include "SplashScreen.h"

SplashScreen::SplashScreen(const Coordinates & screenDimentions, shared_ptr<sf::RenderWindow> & window): width_(screenDimentions.getX()),
		height_(screenDimentions.getY()), window_(window)
{
	if (!font_.loadFromFile("resources/sansation.ttf"))
		throw EXIT_FAILURE;

	message_.setFont(font_);
	message_.setCharacterSize(40);
	message_.setFillColor(sf::Color::White);
}

void SplashScreen::drawStartSplash()
{
	drawMessage({float(width_/4.2), float(height_/4)}, "Welcome to Super-Pacman");
	drawMessage({float(width_/3.2), float(height_/3)}, "Press Space to Start");
	drawMessage({float(width_/2.5), float(height_/2)}, "Instructions");
	drawMessage({float(width_/4.2), float(height_/1.5)}, "Move Up: Up Arrow");
	drawMessage({float(width_/4.2), float(height_/1.39)}, "Move Down: Down Arrow");
	drawMessage({float(width_/4.2), float(height_/1.3)}, "Move Left: Left Arrow");
	drawMessage({float(width_/4.2), float(height_/1.22)}, "Move Right: Right Arrow");
}

void SplashScreen::drawEndSplash()
{
	drawMessage({float(width_/2.5), float(height_/4)}, "Game Over");
	drawMessage({float(width_/3.2), float(height_/3)}, "Press Space to Close");
}

void SplashScreen::drawWinSplash()
{
	drawMessage({float(width_/2.5), float(height_/4)}, "You Win");
	drawMessage({float(width_/3.2), float(height_/3)}, "Press Space to Close");
}

void SplashScreen::drawMessage(const Coordinates & position, const string & message)
{
	message_.setPosition(position.getX(), position.getY());
	message_.setString(message);
	window_->draw(message_);
}
