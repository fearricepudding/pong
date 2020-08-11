#include <SFML/Graphics.hpp>

class ai{
	public:
		int lives;
		int score;

		float x;
		float y;
		float speed;
		float boundLeft;
		float boundRight;
		float boundTop;
		float boundBottom;

		float width;
		float height;

		bool up = false;
		bool down = false;
		ai();
		sf::Vector2f getPosition();
		void move(sf::RectangleShape target);

};
