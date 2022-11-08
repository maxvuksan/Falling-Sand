#include "Element.h"

Element::Element()
{
	desired_spread = 1;
	gravity_direction = 1;
	is_static = false;
	density = 2;
}

///////////////////////////////
MovingSolid::MovingSolid() {
	travel_down = true;
	travel_down_diagonal = true;
	travel_sideways = false;
	density = 3;
}
Sand::Sand() {
	colour = sf::Color(242, 205, 136);
	desired_spread = 2;
}

///////////////////////////////
StaticSolid::StaticSolid() {
	travel_down = false;
	travel_down_diagonal = false;
	travel_sideways = false;
	density = 10;
}
Stone::Stone() {
	colour = sf::Color(121, 127, 138);
}

///////////////////////////////
Liquid::Liquid() {
	travel_down = true;
	travel_down_diagonal = true;
	travel_sideways = true;

	density = 2;
	desired_spread = 4;
}
Water::Water() {
	colour = sf::Color(162, 209, 224);
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
	colour = sf::Color(52, 53, 54);
}