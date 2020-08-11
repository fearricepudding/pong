#include "ai.hpp"
#include "game.hpp"

ai::ai(){
	height = 100;
	width = 10;
	speed = 3;
	y = (game::height/2)-height/2;
};

sf::Vector2f ai::getPosition(){
	if(y > game::height-height){
		y = game::height-height;
	};
	if(y <= 0){
		y = 0;
	};
	return sf::Vector2f(0, y);
};

void ai::move(sf::RectangleShape target){
	sf::FloatRect targetBox = target.getGlobalBounds();
	if(y+height/2 > targetBox.top){
		y-= speed;
	}else if(y+height/2 < targetBox.top){
		y+= speed;
	}
}
