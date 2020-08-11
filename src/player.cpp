#include "player.hpp"
#include "game.hpp"

player::player(){
	height = 100;
	width = 10;
	y = (game::height/2)-height/2;
};

sf::Vector2f player::getPosition(){
	if(y > game::height-height){
		y = game::height-height;
	};
	if(y <= 0){
		y = 0;
	};
	return sf::Vector2f(game::width-10, y);
};
