#pragma once
#include <SFML/Graphics.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <iostream>

#include "CellGrid.h"
class Element;

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

		int brush_size;
		int brush_MAX;

		short current_index; //what are we drawing with?
		CellGrid cell_grid;


	public:
		
		std::vector<Element*> ELEMENTS;
		float DELTA_TIME;
		bool SHOW_CHUNKS;

		Game();
		~Game();

		void start();
		void run();
		void poll_events();
		void render_ui();
		void update();
};