#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(): pacmanSpriteOffset_(45), pacmanAnimationFrames_(3), pacmanFrameSize_(15)
{
	red_ = new sf::Texture;
	inky_ = new sf::Texture;
	blinky_ = new sf::Texture;
	clyde_ = new sf::Texture;
	fruit_ = new sf::Texture;
	key_ = new sf::Texture;
	pellet_ = new sf::Texture;
	scared_ = new sf::Texture;

	spriteFile_.loadFromFile("resources/Things.png");
	red_->loadFromFile("resources/Red.png");
	inky_->loadFromFile("resources/Inky.png");
	blinky_->loadFromFile("resources/Blinky.png");
	clyde_->loadFromFile("resources/Clyde.png");
	fruit_->loadFromFile("resources/Fruit.png");
	key_->loadFromFile("resources/Key.png");
	pellet_->loadFromFile("resources/Pellet.png");
	scared_->loadFromFile("resources/Scared.png");
	loadPacman();
}

SpriteHandler::~SpriteHandler()
{
	deleteSprites(pacManSprites_);
	delete red_;
	delete inky_;
	delete blinky_;
	delete clyde_;
	delete fruit_;
	delete key_;
	delete pellet_;
	delete scared_;
}

const sf::Texture * SpriteHandler::getSprite(const EntityKey & key)
{
	sf::Texture * texture = NULL;

	switch(key)
	{
	case EntityKey::RED:
		texture = red_;
		break;
	case EntityKey::INKY:
		texture = inky_;
		break;
	case EntityKey::BLINKY:
		texture = blinky_;
		break;
	case EntityKey::CLYDE:
		texture = clyde_;
		break;
	case EntityKey::FRUIT:
		texture = fruit_;
		break;
	case EntityKey::KEY:
		texture = key_;
		break;
	case EntityKey::PELLET:
		texture = pellet_;
		break;
	case EntityKey::SCAREDGHOST:
		texture = scared_;
		break;
	default:
		break;
	}

	return texture;
}

void SpriteHandler::loadPacman()
{
	for(int recStart = 0; recStart <= pacmanSpriteOffset_*3; recStart+=pacmanSpriteOffset_)
	{
		auto rect = new sf::IntRect(recStart, 0, pacmanFrameSize_, pacmanFrameSize_);
		auto sprite = new sf::Sprite(spriteFile_, *rect);
		sprite->setScale(1.0f, 1.0f);
		pacManSprites_.push_back(sprite);
	}
}

void SpriteHandler::deleteSprites(vector<sf::Sprite*> & sprites)
{
	for(auto sprite: sprites)
		delete sprite;
}

sf::Sprite * SpriteHandler::getAnimatedSprite(const Direction & direction)
{
	auto dir = 0;

	switch(direction)
	{
	case Direction::DOWN:
		dir = 1;
		break;
	case Direction::LEFT:
		dir = 2;
		break;
	case Direction::RIGHT:
		dir = 3;
		break;
	default:
		break;
	}

	sf::Sprite * sprite = NULL;
	sprite = pacManSprites_.at(dir);
	sprite->setTextureRect(animate(sprite->getTextureRect(), dir));

	return sprite;
}

sf::IntRect SpriteHandler::animate(sf::IntRect frame, const int & direction)
{
	auto baseFrame = sf::IntRect(direction*pacmanSpriteOffset_, 0, pacmanFrameSize_, pacmanFrameSize_).left;

	if (clock_.getElapsedTime().asSeconds() >= 0.1f)
	{
		if(frame.left >= (baseFrame + pacmanFrameSize_ * (pacmanAnimationFrames_ - 1)))
			frame.left = baseFrame;
		else
			frame.left += pacmanFrameSize_;
		clock_.restart();
	}

	return frame;
}
