#ifndef API_GAMEPLAY_PATHFINDER_A_STAR_H_
#define API_GAMEPLAY_PATHFINDER_A_STAR_H_
#include "path.h"
#include <array>


class PathPoint
{
private:

	//g -> distance from start to end
	float g_;
	//h -> (heuristic function) which is an estimated cost to goal
	float h_;

	sf::Vector2f position_;

	int parent_ = -1;

	float f() const { return g_ + h_; }

public:

	//constructor and operator
	PathPoint(float g, float h, int parent, sf::Vector2f pos) : g_(g), h_(h), position_(pos), parent_(parent) {}
	bool operator>(const PathPoint& other) const
	{
		return f() > other.f();
	}

	//Get --------------------
	[[nodiscard]] sf::Vector2f position() const;
	[[nodiscard]] int parent_index() const;
	[[nodiscard]] float g() const;
};

//coords of tile neughbours compared to current tile
const std::array<sf::Vector2f, 4> kNeighbours =
{
	sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(1.0f, 0.0f),
	sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(-1.0f, 0.0f)
};


namespace pathfinder
{
	Path CalculatePath(std::vector<sf::Vector2f> walkables_positions, sf::Vector2f start, sf::Vector2f end, int offset);
};

#endif //API_GAMEPLAY_PATHFINDER_A_STAR_H_