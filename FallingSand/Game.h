#pragma once
#include <SFML/Graphics.hpp>

//#include <imgui.h>
//#include <imgui-SFML.h>

#include <iostream>

#include "CellGrid.h"

struct Inputs {
	bool left_mouse;
	bool right_mouse;
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
		sf::RectangleShape mouse_graphic;

		short current_index; //what are we drawing with?
		CellGrid cell_grid;



	public:
		float DELTA_TIME;

		Game();
		~Game();

		void start();
		void run();
		void poll_events();
		void update();

		void set_cell(int x, int y, short cell);
};