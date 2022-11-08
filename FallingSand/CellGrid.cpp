#include "CellGrid.h"
#include "Game.h"

CellGrid::CellGrid(Game* game, sf::Vector2i dimensions) {
	this->game = game;
	this->dimensions = dimensions;

	world_graphic.create(dimensions.x, dimensions.y);

	reset();


	chunk_awake_hold_time = 4;
	chunk_division = 15;
	chunk_width = round(dimensions.x / chunk_division);
	chunk_height = round(dimensions.y / chunk_division);

	sf::RectangleShape chunk_rect;
	chunk_rect.setSize(sf::Vector2f(chunk_width, chunk_height));
	chunk_rect.setFillColor(sf::Color::Transparent);
	chunk_rect.setOutlineColor(sf::Color(255,150,150,150));
	chunk_rect.setOutlineThickness(1);
	
	chunks.resize(chunk_division);
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i].resize(chunk_division);
	}

	for (int x = 0; x < chunk_division; x++) {
		for (int y = 0; y < chunk_division; y++) {
			chunk_rect.setPosition(sf::Vector2f(x * chunk_width, y * chunk_height));
			chunks[x][y] = { chunk_rect };
		}
	}

}

void CellGrid::reset() {
	grid.clear();
	//resizing grid to fit screen size
	grid.resize(dimensions.x);
	for (int i = 0; i < grid.size(); i++) {
		grid[i].resize(dimensions.y, { -1, false });
	}
}

void CellGrid::set_cell(sf::Vector2i position, short index) {
	if (position.x >= 0 && position.x < dimensions.x) {
		if (position.y >= 0 && position.y < dimensions.y) {
			grid[position.x][position.y] = { index, false };

			awake_chunk_at(position);
		}
	}
}

void CellGrid::set_area(sf::Vector2i position, short index, short size) {
	for (int x = -size; x < size; x++) {
		for (int y = -size; y < size; y++) {
			set_cell(position + sf::Vector2i(x,y), index);
		}
	}
}

void CellGrid::swap_cells(sf::Vector2i position1, sf::Vector2i position2) {
	Cell cell_temp = grid[position1.x][position1.y];

	grid[position1.x][position1.y] = grid[position2.x][position2.y];
	grid[position2.x][position2.y] = cell_temp;

	awake_chunk_at(position1);
	awake_chunk_at(position2);
}

void CellGrid::cell_logic(int x, int y) {

	short i = grid[x][y].index;
	grid[x][y].updated = true;

	bool bounded_y = false;
	bool bounded_x = false;

	if (y > 0 && y < dimensions.y - 1) {
		bounded_y = true;
	}
	if (x > 0 && x < dimensions.x - 1) {
		bounded_x = true;
	}

	//vertical travel
	short vt = game->ELEMENTS[i]->gravity_direction;
	short desired_spread = game->ELEMENTS[i]->desired_spread;

	if (bounded_y && game->ELEMENTS[i]->travel_down) {

		if (grid[x][y + vt].index == -1 || game->ELEMENTS[grid[x][y + vt].index]->density < game->ELEMENTS[i]->density) { //DOWN
			//move to empty place
			swap_cells(sf::Vector2i(x, y), sf::Vector2i(x, y + vt));
			return;
		}
	}
	if (bounded_y && bounded_x && game->ELEMENTS[i]->travel_down_diagonal) { //DIAGONAL
		if (grid[x][y].prefer_left) {
			if (grid[x + 1][y + vt].index == -1 || game->ELEMENTS[grid[x + 1][y + vt].index]->density < game->ELEMENTS[i]->density) {
				grid[x][y].prefer_left = false;
				swap_cells(sf::Vector2i(x, y), sf::Vector2i(x + 1, y + vt));
				return;
			}
			else if (grid[x - 1][y + vt].index == -1 || game->ELEMENTS[grid[x - 1][y + vt].index]->density < game->ELEMENTS[i]->density) {
				grid[x][y].prefer_left = true;
				swap_cells(sf::Vector2i(x, y), sf::Vector2i(x - 1, y + vt));
				return;
			}
		}
		if (grid[x - 1][y + vt].index == -1 || game->ELEMENTS[grid[x - 1][y + vt].index]->density < game->ELEMENTS[i]->density) {
			grid[x][y].prefer_left = true;
			swap_cells(sf::Vector2i(x, y), sf::Vector2i(x + 1, y - vt));
			return;
		}
		else if (grid[x + 1][y + vt].index == -1 || game->ELEMENTS[grid[x + 1][y + vt].index]->density < game->ELEMENTS[i]->density) {
			grid[x][y].prefer_left = false;
			swap_cells(sf::Vector2i(x, y), sf::Vector2i(x + 1, y + vt));
			return;
		}
	}
	if (bounded_x && game->ELEMENTS[i]->travel_sideways) { //SIDEWAYS
		if (grid[x][y].prefer_left) {
			if (grid[x - 1][y].index == -1) {
				grid[x][y].prefer_left = true;
				swap_cells(sf::Vector2i(x, y), sf::Vector2i(x - 1, y));
				return;
			}
			else if (grid[x + 1][y].index == -1) {
				grid[x][y].prefer_left = false;
				swap_cells(sf::Vector2i(x, y), sf::Vector2i(x + 1, y));
				return;
			}
		}
		if (grid[x + 1][y].index == -1) {
			swap_cells(sf::Vector2i(x, y), sf::Vector2i(x + 1, y));
			return;
		}
		else if (grid[x - 1][y].index == -1) {
			swap_cells(sf::Vector2i(x, y), sf::Vector2i(x - 1, y));
			return;
		}
	}

}

void CellGrid::awake_chunk_at(sf::Vector2i position) {
	sf::Vector2i offsets[5] = { sf::Vector2i(0,0), sf::Vector2i(0,1),sf::Vector2i(0,-1),sf::Vector2i(-1,0),sf::Vector2i(1,0) };

	for (int i = 0; i < 5; i++) {
		int x = round((position.x + offsets[i].x )/ chunk_width);
		int y = round((position.y + offsets[i].y )/ chunk_height);
		
		if (x < 0 || x >= chunk_division) {
			continue;
		}
		if (y < 0 || y >= chunk_division) {
			continue;
		}

		chunks[x][y].time_since_awake = chunk_awake_hold_time;
		chunks[x][y].awake = true;
	}
}
void CellGrid::update_chunk(Chunk& chunk, sf::RenderTexture& surface) {
	sf::Vector2i offset = sf::Vector2i(chunk.rect.getPosition().x, chunk.rect.getPosition().y);
	//iterating every cell
	for (int x = 0; x < chunk.rect.getSize().x; x++) {
		for (int y = 0; y < chunk.rect.getSize().y; y++) {

			int _x = x + offset.x;
			int _y = y + offset.y;

			if (grid[_x][_y].index != -1 && !grid[_x][_y].updated) {

				Cell caught_cell = grid[_x][_y];
				if (chunk.awake) {
					cell_logic(_x, _y);
				}

				world_graphic.setPixel(_x, _y, game->ELEMENTS[caught_cell.index]->colour);
			}
		}
	}	
}

void CellGrid::sleep_all_chunks() {
	for (int x = 0; x < chunk_division; x++) {
		for (int y = 0; y < chunk_division; y++) {
			
			if (chunks[x][y].time_since_awake <= 0) {
				chunks[x][y].awake = false;
			}
			chunks[x][y].time_since_awake--;
		}
	}
}

void CellGrid::update(sf::RenderTexture& surface) {

	for (int x = 0; x < chunk_division; x++) {
		for (int y = 0; y < chunk_division; y++) {
			auto chunk = chunks[x][y];

			update_chunk(chunk, surface);
		}
	}

	sf::Texture texture;
	texture.loadFromImage(world_graphic);
	surface.draw(sf::Sprite(texture));

	//reseting updated state
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = dimensions.y - 1; y >= 0; y--) {
			grid[x][y].updated = false;
			world_graphic.setPixel(x, y, sf::Color::Transparent);
		}
	}

	if (game->SHOW_CHUNKS) {
		for (int x = 0; x < chunk_division; x++) {
			for (int y = 0; y < chunk_division; y++) {
				if (chunks[x][y].awake) {
					surface.draw(chunks[x][y].rect);
				}
			}
		}
	}

	sleep_all_chunks();
}