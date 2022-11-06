#include "Game.h"

Game::Game() :
	WINDOW_SIZE(700, 700),
	DISPLAY_SIZE(200, 200),

	BACKGROUND_COLOUR(30,25,40)
{
	WINDOW = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Falling Sand");
	WINDOW->setFramerateLimit(140);

	DISPLAY = new sf::RenderTexture;
	DISPLAY->create(DISPLAY_SIZE.x, DISPLAY_SIZE.y);
}
void Game::start() {

	mouse_graphic.setFillColor(sf::Color::Transparent);
	mouse_graphic.setOutlineColor(sf::Color::White);
	mouse_graphic.setOutlineThickness(1);

	cell_graphic.setSize(sf::Vector2f(1, 1));

	//defining the element types
	elements.push_back({ true, true, false, sf::Color(242, 205, 136)}); //SAND
	elements.push_back({ true, true, true, sf::Color(162, 209, 224)}); //WATER
	elements.push_back({ false, false, false, sf::Color(121, 127, 138) }); //STONE

	//resizing grid to fit screen size
	cell_grid.resize(DISPLAY_SIZE.x);
	for (int i = 0; i < cell_grid.size(); i++) {
		cell_grid[i].resize(DISPLAY_SIZE.y, {-1, false});
	}

}
void Game::run() {

	start();
	
	while (WINDOW->isOpen()) {
		
		DISPLAY->clear(BACKGROUND_COLOUR);
		DELTA_TIME = CLOCK.restart().asSeconds();

		mouse_pos = sf::Mouse::getPosition(*WINDOW);
		mouse_pos = sf::Vector2i(round(mouse_pos.x * (DISPLAY_SIZE.x / (float)WINDOW_SIZE.x)), round(mouse_pos.y * (DISPLAY_SIZE.y / (float)WINDOW_SIZE.y)));

		update();
		poll_events();
		DISPLAY->display();

		sf::Sprite display_sprite(DISPLAY->getTexture());
		display_sprite.setScale(sf::Vector2f(WINDOW_SIZE.x / (float)DISPLAY_SIZE.x, WINDOW_SIZE.y / (float)DISPLAY_SIZE.y));
		WINDOW->draw(display_sprite);
		WINDOW->display();
	}
}
void Game::poll_events() {

	sf::Event event;
	while (WINDOW->pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == 0) {
				INPUTS.left_mouse = true;
			}
			if (event.mouseButton.button == 1) {
				INPUTS.right_mouse = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == 0) {
				INPUTS.left_mouse = false;
			}
			if (event.mouseButton.button == 1) {
				INPUTS.right_mouse = false;
			}
		}

		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::Num1:
					current_index = 0;
					break;
				case sf::Keyboard::Num2:
					current_index = 1;
					break;
				case sf::Keyboard::Num3:
					current_index = 2;
					break;
			}
		}


		if (event.type == sf::Event::Closed)
			WINDOW->close();
	}
}

void Game::set_cell(int x, int y, short element_index) {

	if (x >= 0 && x < DISPLAY_SIZE.x) {
		if (y >= 0 && y < DISPLAY_SIZE.y) {
			cell_grid[x][y] = { element_index, false };
		}
	}
}

void Game::update() {

	int size = 4;
	mouse_graphic.setSize(sf::Vector2f(size * 2, size * 2));
	mouse_graphic.setPosition(sf::Vector2f(mouse_pos.x - size, mouse_pos.y - size));

	if (INPUTS.left_mouse || INPUTS.right_mouse) {
		short index = -1;

		if (INPUTS.left_mouse) { index = current_index; }
		else if (INPUTS.right_mouse) { index = -1; }

		for (int x = -size; x < size; x++) {
			for (int y = -size; y < size; y++) {
				set_cell(mouse_pos.x + x, mouse_pos.y + y, index);
			}
		}
	}

	//reseting updated state
	for (int x = 0; x < DISPLAY_SIZE.x; x++) {
		for (int y = 0; y < DISPLAY_SIZE.y; y++) {
			cell_grid[x][y].updated = false;
		}
	}

	//iterating every cell
	for (int x = 0; x < DISPLAY_SIZE.x; x++) {
		for (int y = 0; y < DISPLAY_SIZE.y; y++) {

			short i = cell_grid[x][y].index;
			Cell current_cell = cell_grid[x][y];

			if (i == -1 || cell_grid[x][y].updated) {
				continue; //skip iteration, cell is empty
			}

			current_cell.updated = true;

			bool bounded_y = false;
			bool bounded_x = false;

			if (y > 0 && y < DISPLAY_SIZE.y - 1) {
				bounded_y = true;
			}
			if (x > 0 && x < DISPLAY_SIZE.x - 1) {
				bounded_x = true;
			}

			if (bounded_y && elements[i].travel_down && cell_grid[x][y + 1].index == -1) { //DOWN
				//move to empty place
				cell_grid[x][y].index = -1;
				cell_grid[x][y + 1] = current_cell;
				goto moved_cell;

			}
			if (bounded_y && bounded_x && elements[i].travel_down_diagonal) { //DIAGONAL
				if (cell_grid[x + 1][y + 1].index == -1) {
					cell_grid[x][y].index = -1;
					cell_grid[x + 1][y + 1] = current_cell;
					goto moved_cell;
				}
				else if (cell_grid[x - 1][y + 1].index == -1) {
					cell_grid[x][y].index = -1;
					cell_grid[x - 1][y + 1] = current_cell;
					goto moved_cell;
				}
			}
			if (bounded_x && elements[i].travel_sideways) { //SIDEWAYS
				if (cell_grid[x + 1][y].index == -1) {
					cell_grid[x][y].index = -1;
					cell_grid[x + 1][y] = current_cell;
					goto moved_cell;
				}
				else if (cell_grid[x - 1][y].index == -1) {
					cell_grid[x][y].index = -1;
					cell_grid[x - 1][y] = current_cell;
					goto moved_cell;
				}
			}


			moved_cell:

				cell_graphic.setPosition(sf::Vector2f(x, y));
				cell_graphic.setFillColor(elements[i].colour);

				DISPLAY->draw(cell_graphic);
		}
	}
	DISPLAY->draw(mouse_graphic);
}

Game::~Game() {
	delete WINDOW;
	delete DISPLAY;
}
