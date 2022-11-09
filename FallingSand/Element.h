#pragma once
#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "CellGrid.h"

class Element { //DERIVED BY : MovingSolid, StaticSolid, Liquid and Gas

	public:
		//which directions will the element move in
		std::string name;
		
		bool travel_down; 
		bool travel_down_diagonal;
		bool travel_sideways; 

		short desired_spread; //how far the element will try to move per update
		short gravity_direction; //falling up or down? (down when =1, up when =-1)
		bool is_static; //is the element stationary

		short durability;
		short density; //determines which objects fall through others, lighter dense elements will rise to top

		sf::Color colour;

		Element();

		virtual void acid_contact(CellGrid&, sf::Vector2i, Cell&);
};
///////////////////////////////
class MovingSolid : public Element { // MINIMAL FLOWING e.g. Sand, Dirt
	public:
		MovingSolid();
};
class Sand : public MovingSolid {
	public:
		Sand();
};

///////////////////////////////
class StaticSolid : public Element { // NO FLOWING e.g. Stone, Metal 
	public:
		StaticSolid();
};
class Stone : public StaticSolid {
	public:
		Stone();
};
class Wood : public StaticSolid {
	public:
		Wood();
};
///////////////////////////////
class Liquid : public Element { // CONSTANT FLOWING e.g. Water, Lava
	public:
		Liquid();
};
class Water : public Liquid {
	public:
		Water();
};
class Acid : public Liquid {
	public:
		Acid();
		void acid_contact(CellGrid&, sf::Vector2i, Cell&) override {}
};
///////////////////////////////

class Gas : public Element { //CONSTANT FLOWING UPWARD e.g. Smoke
	public:
		Gas();
};
class Smoke : public Gas {
	public:
		Smoke();
};


