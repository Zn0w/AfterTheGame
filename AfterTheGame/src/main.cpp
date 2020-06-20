#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "core/camera.h"


#define WIDTH 1280
#define HEIGHT 720
#define CAMERA_SPEED 1.5f

bool running = false;
Camera camera;
std::vector<Entity*> entities;


void init()
{
	// init camera
	camera = Camera(0, 0, WIDTH, HEIGHT);


	// load test entities
	for (int i = -10; i <= 10; i++)
		for (int j = -10; j <= 10; j++)
		{
			entities.push_back(new Entity(100.0f * j, 100.0f * i, 50.0f, 50.0f));
		}

	running = true;
}

void get_input(float elapsed_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera.x -= CAMERA_SPEED * elapsed_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera.x += CAMERA_SPEED * elapsed_time;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera.y -= CAMERA_SPEED * elapsed_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera.y += CAMERA_SPEED * elapsed_time;
	}
}

void update_and_render(sf::RenderWindow* window)
{
	for (Entity* entity : entities)
	{
		if (camera.captures(*entity))
		{
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

			// transfer from game coordinate system to screen coordinate system
			int render_x = WIDTH / 2 + offset_x;
			int render_y = HEIGHT / 2 - offset_y;

			entity->sprite.setSize(sf::Vector2f(entity->width, entity->height));
			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			entity->sprite.setFillColor(sf::Color::Green);
			window->draw(entity->sprite);
		}
	}
}

void destroy()
{
	running = false;
}


int main()
{
	init();
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "After");

	sf::Clock clock;

	// run the program as long as the window is open
	while (running)
	{
		float elapsed_time = clock.restart().asSeconds() * 1000.0f;
		std::cout << "Elapsed time: " << elapsed_time << "ms" << std::endl;

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
				destroy();
			}
		}

		// process player input
		get_input(elapsed_time);


		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		update_and_render(&window);
		/*sf::CircleShape circle(50.0f);
		circle.setFillColor(sf::Color::Cyan);
		window.draw(circle);*/

		// end the current frame
		window.display();
	}
	
	return 0;
}