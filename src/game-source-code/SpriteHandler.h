#ifndef SPRITEHANDLER_H_
#define SPRITEHANDLER_H_
#include "Direction.h"
#include "Coordinates.h"
#include "EntityKey.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
using namespace std;

class SpriteHandler {
public:
	SpriteHandler();
	const sf::Texture * getSprite(const EntityKey & key);
	sf::Sprite * getAnimatedSprite(const Direction & direction);
	~SpriteHandler();
private:
	sf::Texture spriteFile_;
	sf::Texture * red_;
	sf::Texture * inky_;
	sf::Texture * blinky_;
	sf::Texture * clyde_;
	sf::Texture * fruit_;
	sf::Texture * key_;
	sf::Texture * pellet_;
	sf::Texture * scared_;
	sf::Clock clock_;
	const int pacmanSpriteOffset_;
	const int pacmanAnimationFrames_;
	const int pacmanFrameSize_;
	vector<sf::Sprite*> pacManSprites_;
	void loadPacman();
	void deleteSprites(vector<sf::Sprite*> & sprites);
	sf::IntRect animate(sf::IntRect frame, const int & direction);
};

#endif
