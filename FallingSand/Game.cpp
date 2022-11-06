#include "Game.h"

Game::Game() :
	WINDOW_SIZE(700, 700),
	DISPLAY_SIZE(300, 300),

	BACKGROUND_COLOUR(30,25,40)
{
	WINDOW = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Falling Sand");

	DISPLAY = new sf::RenderTexture;
	DISPLAY->create(DISPLAY_SIZE.x, DISPLAY_SIZE.y);
}
void Game::start() {

	//defining the element types
	cells.push_back({ true, true, false }); //SAND
	cells.push_back({ true, true, true }); //SAND

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
		if (event.type == sf::Event::Closed)
			WINDOW->close();
	}
}
void Game::update() {

	//iterating every cell
	for (int x = 0; x < DISPLAY_SIZE.x; x++) {
		for (int y = 0; y < DISPLAY_SIZE.x; y++) {

			short i = cell_grid[x][y];
			
			if (x < 0) {

			}



		}
	}
}

Game::~Game() {
	delete WINDOW;
	delete DISPLAY;
}
