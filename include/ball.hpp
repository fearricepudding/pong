#include <SFML/Graphics.hpp>

class ball{
	public:
		int moving = false;
		float x;
		float y;
		int width;
		int height;
		int forceX;
		int forceY;
		int speed;

		ball();
		void start();
		sf::Vector2f getPosition();
		void move();

};
