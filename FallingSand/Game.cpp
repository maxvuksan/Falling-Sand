#include "Game.h"

Game::Game() :
	WINDOW_SIZE(700, 700),
	DISPLAY_SIZE(300, 300),

	BACKGROUND_COLOUR(30,25,40),
	cell_grid(DISPLAY_SIZE)
{
	WINDOW = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Falling Sand");
	WINDOW->setFramerateLimit(140);

	DISPLAY = new sf::RenderTexture;
	DISPLAY->create(DISPLAY_SIZE.x, DISPLAY_SIZE.y);
	
	//ImGui::SFML::Init(*WINDOW);
}
void Game::start() {

	mouse_graphic.setFillColor(sf::Color::Transparent);
	mouse_graphic.setOutlineColor(sf::Color::White);
	mouse_graphic.setOutlineThickness(1);
}
void Game::run() {

	start();
	
	while (WINDOW->isOpen()) {
		
		DISPLAY->clear(BACKGROUND_COLOUR);
		
		auto delta = CLOCK.restart();
		//ImGui::SFML::Update(*WINDOW, delta);
		DELTA_TIME = delta.asSeconds();


		mouse_pos = sf::Mouse::getPosition(*WINDOW);
		mouse_pos = sf::Vector2i(round(mouse_pos.x * (DISPLAY_SIZE.x / (float)WINDOW_SIZE.x)), round(mouse_pos.y * (DISPLAY_SIZE.y / (float)WINDOW_SIZE.y)));

		update();
		poll_events();
		DISPLAY->display();

		sf::Sprite display_sprite(DISPLAY->getTexture());
		display_sprite.setScale(sf::Vector2f(WINDOW_SIZE.x / (float)DISPLAY_SIZE.x, WINDOW_SIZE.y / (float)DISPLAY_SIZE.y));
		WINDOW->draw(display_sprite);

		//ImGui::Begin("t");


		//ImGui::End();


		//ImGui::SFML::Render();
		WINDOW->display();
	}
	//ImGui::SFML::Shutdown();
}
void Game::poll_events() {

	sf::Event event;
	while (WINDOW->pollEvent(event))
	{
		//ImGui::SFML::ProcessEvent(event);

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
				case sf::Keyboard::Num4:
					current_index = 3;
					break;
			}
		}


		if (event.type == sf::Event::Closed)
			WINDOW->close();
	}
}

void Game::update() {

	short size = 10;
	mouse_graphic.setSize(sf::Vector2f(size * 2, size * 2));
	mouse_graphic.setPosition(sf::Vector2f(mouse_pos.x - size, mouse_pos.y - size));

	if (INPUTS.left_mouse || INPUTS.right_mouse) {
		short index = -1;

		if (INPUTS.left_mouse) { index = current_index; }
		else if (INPUTS.right_mouse) { index = -1; }

		cell_grid.set_area(mouse_pos, index, size);
	}

	cell_grid.update(*DISPLAY);
	DISPLAY->draw(mouse_graphic);
}

Game::~Game() {
	delete WINDOW;
	delete DISPLAY;
}
