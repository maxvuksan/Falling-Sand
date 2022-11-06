#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.h"

struct Inputs {
	bool left_mouse;
};

class Game {

	protected:

		sf::Vector2i WINDOW_SIZE;
		sf::Vector2i DISPLAY_SIZE;

		sf::RenderWindow* WINDOW;
		sf::RenderTexture* DISPLAY;

		sf::Clock CLOCK;
		sf::Color BACKGROUND_COLOUR;

		Inputs INPUTS;

		//////////////////////////////////////////////////

		sf::Vector2i mouse_pos;

		sf::RectangleShape cell_graphic;
		std::vector<Cell> cells;
		std::vector<std::vector<short>> cell_grid;


	public:
		float DELTA_TIME;

		Game();
		~Game();

		void start();

		void run();

		void poll_events();
		void update();
};