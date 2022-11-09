#include "Element.h"

Element::Element()
{
	name = "";

	desired_spread = 1;
	gravity_direction = 1;
	is_static = false;
	density = 2;
	durability = 30;
}
void Element::link_game(Game* game) {
	this->game = game;
}
void Element::acid_contact(CellGrid& grid, sf::Vector2i position, Cell& cell) {
	cell.durability--;

	if (cell.durability < 0) {
		grid.remove_cell(position);
	}
}
void Element::lava_contact(CellGrid& grid, sf::Vector2i position, Cell& cell) {}

///////////////////////////////
MovingSolid::MovingSolid() {
	travel_down = true;
	travel_down_diagonal = true;
	travel_sideways = false;
	density = 3;
	durability = 7;
}
Sand::Sand() {
	name = "SAND";
	colour = sf::Color(242, 205, 136);
	desired_spread = 2;
}

///////////////////////////////
StaticSolid::StaticSolid() {
	travel_down = false;
	travel_down_diagonal = false;
	travel_sideways = false;
	density = 10;
	durability = 20;
}
Stone::Stone() {
	name = "STONE";
	colour = sf::Color(121, 127, 138);
}
Wood::Wood() {
	name = "WOOD";
	colour = sf::Color(133, 102, 80);
	durability = 8;
}
Metal::Metal() {
	name = "METAL";
	colour = sf::Color(193, 203, 219);
}


///////////////////////////////
Liquid::Liquid() {
	travel_down = true;
	travel_down_diagonal = true;
	travel_sideways = true;

	density = 2;
	desired_spread = 4;
	durability = 4;
}
Water::Water() {
	name = "WATER";
	colour = sf::Color(162, 209, 224);
}
void Water::lava_contact(CellGrid& grid, sf::Vector2i position, Cell& cell) {
	grid.set_cell(position, 2); //set to STONE (index 2)
}

Lava::Lava() {
	name = "LAVA";
	colour = sf::Color(255, 111, 59);
}
Acid::Acid() {
	name = "ACID";
	colour = sf::Color(150, 255, 140);
	density = 0;
}

///////////////////////////////
Gas::Gas() {
	gravity_direction = -1;

	travel_down = true;
	travel_down_diagonal = true;
	travel_sideways = true;

	density = 1;
}
Smoke::Smoke() {
	name = "SMOKE";
	colour = sf::Color(52, 53, 54);
}