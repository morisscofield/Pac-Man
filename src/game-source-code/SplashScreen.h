#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_
#include "Coordinates.h"
#include <memory>
#include "SFML/Graphics.hpp"
using namespace std;

class SplashScreen {
public:
	SplashScreen(const Coordinates & screenDimentions, shared_ptr<sf::RenderWindow> & window);
	void drawStartSplash();
	void drawEndSplash();
	void drawWinSplash();
private:
	float width_;
	float height_;
	shared_ptr<sf::RenderWindow> window_;
	sf::Font font_;
	sf::Text message_;
	void drawMessage();
	void drawMessage(const Coordinates & position, const string & message);
};

#endif
