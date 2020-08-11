#include "ai.hpp"
#include "game.hpp"

ai::ai(){
	height = 100;
	width = 10;
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
		y-= 3;
	}else if(y+height/2 < targetBox.top){
		y+= 3;
	}
}
