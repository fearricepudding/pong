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

int main()
{
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

	// Load a font
	sf::Font font;
	if (!font.loadFromFile("./roboto.ttf"))
	{
	    std::cout << "font not found!" << std::endl;
	}
	sf::Text text;
	text.setFont(font);

	text.setCharacterSize(18);
	text.setFillColor(sf::Color::White);

	const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
		totalFrames++;
		auto now = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - start);
		auto secondCheck = std::chrono::duration_cast<std::chrono::seconds>(now - lastFrameTime);
		if(secondCheck.count() >= 1){
			fps = totalFrames - prevFramesCount;
			prevFramesCount = totalFrames;
			lastFrameTime = now;
		}
		// Wait 5 seconds for fps to get accurate
		if(elapsedTime.count() > 1){
			averageFrames = totalFrames / elapsedTime.count();
		};

		std::stringstream fpsCounterText;
		fpsCounterText << "FPS: " << fps << " / " << averageFrames << " - Lives: " << game::lives << " Score: " << game::score;
		text.setString(fpsCounterText.str());
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
				target.start();
		}

		sf::Time ClockelapsedTime = clock.restart();
	    timeSinceLastUpdate += ClockelapsedTime;
	    while (timeSinceLastUpdate > TimePerFrame)
	    {
			if(game::reset){
				target.moving = false;
				target.y = (game::height/2)-target.height;
				target.x = (game::width/2)-target.width;
				game::reset = false;
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
			int result = 1 + (rand() % 6);
			if(ballBox.intersects(batBox)){
				if((target.y+5) > (user.y+50)){
					target.forceY = result;
					target.forceX = 3;
				}else{
					target.forceY = -result;
					target.forceX = -3;
				}
				target.forceX = -3;
			}
			if(ballBox.intersects(aiBox)){
				if((bot.y+5) > (bot.y+50)){
					target.forceY = -result;
					target.forceX = -3;
				}else{
					target.forceY = abs(result);
					target.forceX = 3;
				}
				target.forceX = +3;
			}

			target.move();
			bot.move(ball);
			bat.setPosition(user.getPosition());
			ball.setPosition(target.getPosition());
			oponent.setPosition(bot.getPosition());
	    };

        window.clear();
		window.draw(text);
        window.draw(bat);
		window.draw(oponent);
		window.draw(ball);
        window.display();
    }

    return 0;
}
