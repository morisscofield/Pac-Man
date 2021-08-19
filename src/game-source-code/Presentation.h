#ifndef PRESENTATION_H_
#define PRESENTATION_H_
#include "SFML/Graphics.hpp"
#include "Direction.h"
#include "Coordinates.h"
#include "Entity.h"
#include "ScreenStates.h"
#include "SplashScreen.h"
#include "SpriteHandler.h"
#include "EntityKey.h"

class Presentation
{
public:
	Presentation(const Coordinates & screenDimentions);
	bool isWindowOpen() const;
	Direction getKeyInputs();
	Coordinates getScreenDimentions() const;
	void drawSplashScreen(const ScreenStates & state);
	void draw(const Entity & entity, const EntityKey & key);
	void drawStatic(const Entity & entity, const EntityKey & key);
	void drawPacMan(const Entity & pacMan);
	void render();
	void close();
private:
	void setDirection();
private:
	Direction direction_;
	Direction pacDir_;
	const float screenWidth_;
	const float screenHeight_;
	shared_ptr<sf::RenderWindow> window_;
	SplashScreen splash_;
	SpriteHandler sprites_;
	sf::RectangleShape drawable_;
	sf::RectangleShape static_;
	sf::RectangleShape pacMan_;
};

#endif
