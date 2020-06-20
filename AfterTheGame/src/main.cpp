#include <iostream>

#include <SFML/Graphics.hpp>


int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "After");

	sf::Clock clock;

	// run the program as long as the window is open
	while (window.isOpen())
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
				//destroy();
			}
		}

		// process player input
		//get_input(elapsed_time);


		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		//update_and_render(&window);
		sf::CircleShape circle(50.0f);
		circle.setFillColor(sf::Color::Cyan);
		window.draw(circle);

		// end the current frame
		window.display();
	}
	
	return 0;
}