#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.h"
#include "Element.h"
#include "Chunk.h"

class Game;

class CellGrid {

	private:
		Game* game;

		sf::Image world_graphic;

		sf::Vector2i dimensions;
		std::vector<std::vector<Cell>> grid;

		std::vector<std::vector<Chunk>> chunks;
		
		int chunk_awake_hold_time;
		float chunk_division;
		int chunk_width;
		int chunk_height;

	public:
		CellGrid(Game*, sf::Vector2i dimensions);

		void set_cell(sf::Vector2i position, short index);
		void set_area(sf::Vector2i position, short index, short size);

		void swap_cells(sf::Vector2i position1, sf::Vector2i position2);

		void update_chunk(Chunk&, sf::RenderTexture&);
		void awake_chunk_at(sf::Vector2i position);
		void sleep_all_chunks();

		void reset();

		void cell_logic(int x, int y);
		void update(sf::RenderTexture&);

		


};