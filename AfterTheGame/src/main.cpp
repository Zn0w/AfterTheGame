#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "game_logic/player.h"


#define WIDTH 1280
#define HEIGHT 720
#define CAMERA_SPEED 1.5f

bool running = false;
aft::core::Camera camera;
std::vector<aft::core::Entity*> entities;
std::vector<sf::Texture*> textures;
aft::Player player;

sf::Font font;
sf::Text debug_text;

std::string tilemap[20] = {
	"mmmmmmmmmmmmmmmmmmmm",
	"mmmmmmmmmmmmmmmmmmmm",
	"mmmmmmmmmmmmmmmmmmmm",
	"mmmmmmmmmmmmmmmmmmmm",
	"mmggggggggggggggggmm",
	"mmggggggggggggggggmm",
	"mmggwwwgggggggggggmm",
	"mmggwwwgggggggggggmm",
	"mmggwwwgggggggcgggmm",
	"mmggggggggggggggggmm",
	"mmggggcgggggggggggmm",
	"mmggggggggggggwwggmm",
	"mmggggggggggggwwggmm",
	"mmggggggggcgggggggmm",
	"mmggcgggggggggggcgmm",
	"mmggggggwwwwwwwwggmm",
	"mmmmmmmmwwwwwwwmmmmm",
	"mmmmmmmmmmmmmmmmmmmm",
	"mmmmmmmmmmmmmmmmmmmm",
	"mmmmmmmmmmmmmmmmmmmm"
};


void init()
{
	// load textures
	sf::Texture* cabbage_texture = new sf::Texture;
	if (!cabbage_texture->loadFromFile("resources/cabbage.png"))
	{
		// error...
	}
	textures.push_back(cabbage_texture);

	sf::Texture* rock_texture = new sf::Texture;
	if (!rock_texture->loadFromFile("resources/rock.png"))
	{
		// error...
	}
	textures.push_back(rock_texture);

	sf::Texture* grass_texture = new sf::Texture;
	if (!grass_texture->loadFromFile("resources/grass.png"))
	{
		// error...
	}
	textures.push_back(grass_texture);

	sf::Texture* water_texture = new sf::Texture;
	if (!water_texture->loadFromFile("resources/water.png"))
	{
		// error...
	}
	textures.push_back(water_texture);

	sf::Texture* hero_texture = new sf::Texture;
	if (!hero_texture->loadFromFile("resources/hero.png"))
	{
		// error...
	}
	textures.push_back(hero_texture);
	
	// init camera
	camera = aft::core::Camera(0, 0, WIDTH, HEIGHT);
	camera.clip({0, 0});


	// load test tilemap
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			if (tilemap[i].at(j) == 'm')
				entities.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, rock_texture));
			else if (tilemap[i].at(j) == 'g')
				entities.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, grass_texture));
			else if (tilemap[i].at(j) == 'w')
				entities.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, water_texture));
			else if (tilemap[i].at(j) == 'c')
				entities.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, cabbage_texture));
		}


	player = aft::Player(64.0f, 64.0f, hero_texture);
	player.setOrigin({ WIDTH / 2, HEIGHT / 2 });

	running = true;

	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		// error...
	}

	debug_text.setFont(font);
	debug_text.setCharacterSize(16);
	debug_text.setFillColor(sf::Color::Red);
	debug_text.setPosition(0, 0);
}

/*void get_input(float elapsed_time)
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
}*/

void update_and_render(float elapsed_time, sf::RenderWindow* window)
{
	for (aft::core::Entity* entity : entities)
	{
		//entity->update(elapsed_time);
		if (camera.captures(*entity))
		{
			int offset_x = entity->x - camera.x;
			int offset_y = entity->y - camera.y;

			// transfer from game coordinate system to screen coordinate system
			int render_x = WIDTH / 2 + offset_x;
			int render_y = HEIGHT / 2 - offset_y;

			entity->sprite.setPosition(sf::Vector2f(offset_x, offset_y));
			window->draw(entity->sprite);
		}
	}

	// update and render the player
	player.update(elapsed_time);

	int offset_x = player.x - camera.x;
	int offset_y = player.y - camera.y;

	// transfer from game coordinate system to screen coordinate system
	int render_x = WIDTH / 2 + offset_x;
	int render_y = HEIGHT / 2 - offset_y;

	player.sprite.setPosition(sf::Vector2f(offset_x, offset_y));
	window->draw(player.sprite);

	// clip camera to the player
	camera.clip(player);
}

void destroy()
{
	running = false;
}


int main()
{
	init();
	
	// create the window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "After");

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
		//get_input(elapsed_time);


		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		update_and_render(elapsed_time, &window);
		
		// display debug info
		std::string debug_string = "Camera (" + std::to_string(camera.x) + ", " + std::to_string(camera.y) + ")\nFPS: "
			+ std::to_string(1000.0f / elapsed_time);
		debug_text.setString(debug_string);
		window.draw(debug_text);

		// end the current frame
		window.display();
	}
	
	return 0;
}