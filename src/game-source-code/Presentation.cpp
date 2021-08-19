#include "Presentation.h"

Presentation::Presentation(const Coordinates & screenDimentions) :
		direction_(Direction::LEFT), pacDir_(direction_), screenWidth_(screenDimentions.getX()), screenHeight_(screenDimentions.getY()), window_(make_shared<sf::RenderWindow>()),
		splash_(screenDimentions, window_)
{
	window_->create(sf::VideoMode(screenWidth_, screenHeight_), "Super-Pacman");
	window_->setFramerateLimit(60);
	pacMan_.setFillColor(sf::Color::Yellow);
	pacMan_.setSize(sf::Vector2f(20,20));
	pacMan_.setPosition(440, 330);
}

bool Presentation::isWindowOpen() const
{
	return window_->isOpen();
}

Direction Presentation::getKeyInputs()
{
	auto event = sf::Event {};

	while (window_->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window_->close();
			break;
		default:
			break;
		}
	}

	direction_ = Direction::NONE;
	setDirection();

	return direction_;
}

void Presentation::drawSplashScreen(const ScreenStates & state)
{

	switch(state)
	{
	case ScreenStates::SPLASHSCREEN:
		splash_.drawStartSplash();
		break;
	case ScreenStates::GAMEWIN:
		splash_.drawWinSplash();
		break;
	case ScreenStates::GAMEOVER:
		splash_.drawEndSplash();
		break;
	default:
		break;
	}

}

void Presentation::close()
{
	window_->close();
}

void Presentation::draw(const Entity & entity, const EntityKey & key)
{
	drawable_.setPosition(entity.getPosition().getX(), entity.getPosition().getY());
	drawable_.setSize(sf::Vector2f(entity.getDimentions().getX(), entity.getDimentions().getY()));
	drawable_.setTexture(sprites_.getSprite(key));
	window_->draw(drawable_);
}

void Presentation::drawStatic(const Entity & entity, const EntityKey & key)
{
	if (key != EntityKey::WALL && key != EntityKey::GATE)
		return;

	if(key == EntityKey::WALL)
		static_.setFillColor(sf::Color::White);
	else if(key == EntityKey::GATE)
		static_.setFillColor(sf::Color::Blue);

	static_.setPosition(entity.getPosition().getX(), entity.getPosition().getY());
	static_.setSize(sf::Vector2f(entity.getDimentions().getX(), entity.getDimentions().getY()));
	window_->draw(static_);
}

void Presentation::drawPacMan(const Entity & pacMan)
{
	if(direction_ != Direction::SPACE && direction_ != Direction::NONE)
		pacDir_ = direction_;

	auto sprite = sprites_.getAnimatedSprite(pacDir_);
	sprite->setPosition(pacMan.getPosition().getX(), pacMan.getPosition().getY());
	window_->draw(*sprite);
}

void Presentation::render()
{
	window_->display();
	window_->clear(sf::Color::Black);
}

Coordinates Presentation::getScreenDimentions() const
{
	return Coordinates {screenWidth_, screenHeight_};
}

void Presentation::setDirection()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction_ = Direction::UP;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction_ = Direction::DOWN;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = Direction::LEFT;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = Direction::RIGHT;
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		direction_ = Direction::SPACE;
}
