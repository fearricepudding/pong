#include <SFML/Graphics.hpp>

class player{
	public:
		int lives;
		int score;

		float x;
		float y;
		float boundLeft;
		float boundRight;
		float boundTop;
		float boundBottom;

		float width;
		float height;

		bool up = false;
		bool down = false;
		player();
		sf::Vector2f getPosition();

};
