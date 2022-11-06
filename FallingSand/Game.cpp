#include "Game.h"

Game::Game() :
	WINDOW_SIZE(700, 700),
	DISPLAY_SIZE(300, 300),

	BACKGROUND_COLOUR(30,25,40)
{
	WINDOW = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Falling Sand");
	WINDOW->setFramerateLimit(500);

	DISPLAY = new sf::RenderTexture;
	DISPLAY->create(DISPLAY_SIZE.x, DISPLAY_SIZE.y);
}
void Game::start() {

	cell_graphic.setSize(sf::Vector2f(1, 1));

	//defining the element types
	cells.push_back({ true, true, false }); //SAND
	cells.push_back({ true, true, true }); //WATER

	//resizing grid to fit screen size
	cell_grid.resize(DISPLAY_SIZE.x);
	for (int i = 0; i < cell_grid.size(); i++) {
		cell_grid[i].resize(DISPLAY_SIZE.y, -1);
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
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == 0) {
				INPUTS.left_mouse = false;
			}
		}


		if (event.type == sf::Event::Closed)
			WINDOW->close();
	}
}
void Game::update() {


	if (INPUTS.left_mouse) {
		cell_grid[mouse_pos.x][mouse_pos.y] = 0;
	}


	//iterating every cell
	for (int x = 0; x < DISPLAY_SIZE.x; x++) {
		for (int y = DISPLAY_SIZE.y - 1; y >= 0; y--) {

			short i = cell_grid[x][y];
			
			if (i == -1) {
				continue; //skip iteration, cell is empty
			}

			if (y > 0 && y < DISPLAY_SIZE.y - 1) {
				
				if (cells[i].travel_down && cell_grid[x][y + 1] == -1) { //DOWN
					//move to empty place
					cell_grid[x][y] = -1;
					cell_grid[x][y + 1] = i;
				}
				else if (cells[i].travel_down_diagonal) { //DIAGONAL
					if (cell_grid[x + 1][y + 1] == -1) {
						cell_grid[x][y] = -1;
						cell_grid[x + 1][y + 1] = i;
					}
					else if (cell_grid[x - 1][y + 1] == -1) {
						cell_grid[x][y] = -1;
						cell_grid[x - 1][y + 1] = i;
					}
				}
			}

			cell_graphic.setPosition(sf::Vector2f(x, y));
			cell_graphic.setFillColor(sf::Color::White);

			DISPLAY->draw(cell_graphic);
		}
	}
}

Game::~Game() {
	delete WINDOW;
	delete DISPLAY;
}
