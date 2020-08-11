
#include <iostream>
#include "ball.hpp"
#include "game.hpp"

ball::ball(){
	width = 10;
	height = 10;
	speed = 3;
	forceX = 0;
	forceY = 0;
	x = (game::width/2)-(width/2);
	y = (game::height/2)-(height/2);
}

void ball::start(){
	if(!moving){
		moving = true;
		forceX = 3;
		forceY = 3;
	};
};

sf::Vector2f ball::getPosition(){
	return sf::Vector2f(x, y);
}

void ball::move(){
	if(moving){
			if((x+width) >= game::width){
				forceX = -forceX;
				game::lives --;
				game::reset = true;
			};
			if(x <= 0){
				forceX = abs(forceX);
				game::score += 300;
				game::reset = true;
			}
			if((y+height*2) >= game::height){
				forceY = -forceY;
			}
			if(y <= 0){
				forceY = abs(forceY);
			}
			x += forceX;
			y += forceY;
	}
}
