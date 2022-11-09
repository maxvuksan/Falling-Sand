#pragma once

struct Cell {
	short index;
	short durability;

	bool updated;

	bool prefer_left;
};
