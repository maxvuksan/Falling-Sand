#pragma once

struct Cell {
	short index;
	bool updated;
};

struct Elemenet {
	bool travel_down;
	bool travel_down_diagonal;
	bool travel_sideways;

	short density;

	sf::Color colour;
};


