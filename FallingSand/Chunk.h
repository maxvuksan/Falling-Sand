#pragma once
#include <SFML/Graphics.hpp>

struct Chunk {

	sf::RectangleShape rect;
	
	int time_since_awake;

	bool awake;
};
