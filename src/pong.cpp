#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include "player.hpp"
#include "ball.hpp"
#include "game.hpp"
#include "ai.hpp"

player user;
ai bot;
ball target;
int game::height = 400;
int game::width = 800;
int game::lives = 3;
bool game::reset = false;
int game::score = 0;
bool game::over = false; 

int main(){
    sf::RenderWindow window(sf::VideoMode(game::width, game::height), "Pong");
	window.setFramerateLimit(60);

    sf::RectangleShape bat(sf::Vector2f(0, 0));
	sf::RectangleShape oponent(sf::Vector2f(0, 0));
	sf::RectangleShape ball(sf::Vector2f(0, 0));

	ball.setSize(sf::Vector2f(10, 10));
	ball.setPosition(target.getPosition());
	bat.setSize(sf::Vector2f(10, 100));
	bat.setPosition(user.getPosition());
	oponent.setSize(sf::Vector2f(10, 100));
	oponent.setPosition(bot.getPosition());

	int totalFrames = 0;
	auto start = std::chrono::high_resolution_clock::now();
	int averageFrames = 0;
	int fps = 0;
	int prevFramesCount;
	auto lastFrameTime = std::chrono::high_resolution_clock::now();

	sf::Font font;
	if (!font.loadFromFile("./roboto.ttf")){
	    std::cout << "font not found!" << std::endl;
	};
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text gameOverText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	livesText.setFont(font);
	livesText.setCharacterSize(18);
	livesText.setFillColor(sf::Color::White);
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(25);
	gameOverText.setFillColor(sf::Color::White);

	const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()){
		totalFrames++;
		auto now = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - start);
		auto secondCheck = std::chrono::duration_cast<std::chrono::seconds>(now - lastFrameTime);
		if(secondCheck.count() >= 1){
			fps = totalFrames - prevFramesCount;
			prevFramesCount = totalFrames;
			lastFrameTime = now;
		};
		if(elapsedTime.count() > 1){
			averageFrames = totalFrames / elapsedTime.count();
		};
		std::stringstream lives;
		std::stringstream score;
		std::stringstream gameover;
		lives << "Lives: " << game::lives;
		score << "Score: " << game::score;
		gameover << "Game Over!\nScore: "<< game::score;
		livesText.setString(lives.str());
		scoreText.setString(score.str());
		gameOverText.setString(gameover.str());
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S))
				user.up = true;
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::S))
				user.up = false;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W))
				user.down = true;
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::W))
				user.down = false;
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
				if(!game::over){
					target.start();
				}else{
					game::over = false;
					game::reset = true;
					game::score = 0; 
					game::lives = 3;
				}
		};
		sf::Time ClockelapsedTime = clock.restart();
		timeSinceLastUpdate += ClockelapsedTime;
		while (timeSinceLastUpdate > TimePerFrame){
			if(game::reset){
				target.moving = false;
				target.y = (game::height/2)-target.height;
				target.x = (game::width/2)-target.width;
				bot.speed = bot.speed + .1;
				game::reset = false;
			};
			if(game::lives <= 0){
				target.moving = false;
				game::over = true;
			}
	        timeSinceLastUpdate -= TimePerFrame;
			if(user.up){
				user.y += 3;
			};
			if(user.down){
				user.y -= 3;
			};
			sf::FloatRect ballBox = ball.getGlobalBounds();
			sf::FloatRect batBox = bat.getGlobalBounds();
			sf::FloatRect aiBox = oponent.getGlobalBounds();
			float xAmp = abs(target.forceX) + .1;
			float bounceMulti = .2f;
			if(ballBox.intersects(batBox)){
				float yAmp = ((target.y+5)-(user.y+50))*bounceMulti;
				if(yAmp > 0){
					target.forceY = yAmp;
				}else{
					target.forceY = -yAmp;
				};
				target.forceX = -xAmp;
			};
			if(ballBox.intersects(aiBox)){
				float yAmp = ((target.y+5)-(bot.y+50))*bounceMulti;
				if(yAmp > 0){
					target.forceY = -yAmp;
				}else{
					target.forceY = yAmp;
				};
				target.forceX = xAmp;
			};
			target.move();
			bot.move(ball);
			bat.setPosition(user.getPosition());
			ball.setPosition(target.getPosition());
			oponent.setPosition(bot.getPosition());
	    };
		sf::FloatRect livesTextBox = livesText.getGlobalBounds();
		sf::FloatRect scoreTextBox = scoreText.getGlobalBounds();
		sf::FloatRect gameOverBox = gameOverText.getGlobalBounds();
		livesText.setPosition((game::width - livesTextBox.width)/2, 0);
		scoreText.setPosition((game::width - scoreTextBox.width)/2, 20);
		gameOverText.setPosition((game::width - gameOverBox.width)/2, (game::height - gameOverBox.height)/2);

		window.clear();
		if(game::over){
			window.draw(gameOverText);	
		}else{
			window.draw(livesText);
			window.draw(scoreText);
			window.draw(bat);
			window.draw(oponent);
			window.draw(ball);
		};
		window.display();
	};
	return 0;
}
