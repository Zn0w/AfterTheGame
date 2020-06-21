#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "game_logic/player.h"


#define WIDTH 1280
#define HEIGHT 720
#define CAMERA_SPEED 1.5f
#define PLAYER_NORMAL_SPEED 0.8f
#define PLAYER_INIT_HEALTH 100.0f
#define UPDATE_RADIUS 500.0f

bool running = false;
std::vector<sf::Texture*> textures;

aft::core::Camera camera;
std::vector<aft::core::Entity*> tilemap_solid;
std::vector<aft::core::Entity*> tilemap_nonsolid;
std::vector<aft::LivingEntity*> npcs;
std::vector<aft::core::Entity*> interactables;
aft::Player player(0.0f, 0.0f);

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

std::string collision_map[20] = {
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10001110000000000001",
	"10001110000000000001",
	"10001110000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000110001",
	"10000000000000110001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000111111110001",
	"10000000111111100001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111"
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
			if (collision_map[i].at(j) == '0')
			{
				if (tilemap[i].at(j) == 'm')
					tilemap_nonsolid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, rock_texture));
				else if (tilemap[i].at(j) == 'g')
					tilemap_nonsolid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, grass_texture));
				else if (tilemap[i].at(j) == 'w')
					tilemap_nonsolid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, water_texture));
				else if (tilemap[i].at(j) == 'c')
					tilemap_nonsolid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, cabbage_texture));
			}
			else
			{
				if (tilemap[i].at(j) == 'm')
					tilemap_solid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, rock_texture));
				else if (tilemap[i].at(j) == 'g')
					tilemap_solid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, grass_texture));
				else if (tilemap[i].at(j) == 'w')
					tilemap_solid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, water_texture));
				else if (tilemap[i].at(j) == 'c')
					tilemap_solid.push_back(new aft::core::Entity(j * 64.0f, i * 64.0f, 64.0f, 64.0f, cabbage_texture));
			}
		}


	player = aft::Player(PLAYER_NORMAL_SPEED, PLAYER_INIT_HEALTH, 64.0f, 64.0f, hero_texture);
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
	for (aft::core::Entity* entity : tilemap_nonsolid)
	{
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
	
	sf::Vector2f player_origin = player.getOrigin();
	
	for (aft::core::Entity* entity : tilemap_solid)
	{
		sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance = entity_origin - player_origin;
		if (fabs(distance.x) <= UPDATE_RADIUS && fabs(distance.y) <= UPDATE_RADIUS)
		{
			float entity_x1 = entity->x;
			float entity_y1 = entity->y;
			float entity_x2 = entity->x + entity->width;
			float entity_y2 = entity->y + entity->height;
			
			for (aft::LivingEntity* npc : npcs)
			{
				if (entity->collides(*npc))
				{
					aft::core::Entity e(npc->x - npc->velocity.x, npc->y, npc->width, npc->height, textures.at(0));
					if (!entity->collides(e))
						npc->x -= npc->velocity.x;
					else
						npc->y -= npc->velocity.y;
				}
			}

			if (entity->collides(player))
			{
				aft::core::Entity e(player.x - player.velocity.x, player.y, player.width, player.height, textures.at(0));
				if (!entity->collides(e))
					player.x -= player.velocity.x;
				else
					player.y -= player.velocity.y;
			}
		}
		
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

	for (aft::LivingEntity* entity : npcs)
	{
		sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance = entity_origin - player_origin;
		if (fabs(distance.x) <= UPDATE_RADIUS && fabs(distance.y) <= UPDATE_RADIUS)
		{
			entity->update(elapsed_time);
		}

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

	for (aft::core::Entity* entity : interactables)
	{
		sf::Vector2f entity_origin = entity->getOrigin();
		sf::Vector2f distance = entity_origin - player_origin;
		if (fabs(distance.x) <= UPDATE_RADIUS && fabs(distance.y) <= UPDATE_RADIUS)
		{
			entity->update(elapsed_time);
		}

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