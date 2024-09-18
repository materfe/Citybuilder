#include "gameplay/pathfinder_a_star.h"
#include <unordered_set>
#include "maths/vec2f.h"

static std::vector<sf::Vector2f> ConstructPath(const PathPoint& exit_point, const PathPoint* visited_points) //in this senario static means private to this file
{
	std::vector<sf::Vector2f> path;
	PathPoint point = exit_point;

	path.emplace_back(exit_point.position());
	while (point.parent_index() != 0)
	{
		point = visited_points[point.parent_index()];
		path.push_back(point.position());
	}
	std::reverse(path.begin(), path.end());
	visited_points = nullptr;
	return path;
}

struct SfmlHash
{
	std::size_t operator()(const sf::Vector2f& v) const noexcept
	{
		std::size_t h1 = std::hash<float>{}(v.x);
		std::size_t h2 = std::hash<float>{}(v.y);
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

//calculate path
Path pathfinder::CalculatePath(std::vector<sf::Vector2f> walkables_positions, sf::Vector2f start, const sf::Vector2f end,
	const int offset)
{
	// - prepare the setup
	Path path;
	sf::Vector2f rounded_end;
	rounded_end.x = end.x - fmod(end.x, static_cast<float>(offset));
	rounded_end.y = end.y - fmod(end.y, static_cast<float>(offset));

	sf::Vector2f rounded_start;
	rounded_start.x = start.x - fmod(end.x, static_cast<float>(offset));
	rounded_start.y = start.y - fmod(end.y, static_cast<float>(offset));

	// -- Prepare the list with --
	walkables_positions.emplace_back(start);
	walkables_positions.emplace_back(rounded_end);

	// --
	std::priority_queue<PathPoint, std::vector<PathPoint>, std::greater<PathPoint>> open_queue;

	std::unordered_set<sf::Vector2f, SfmlHash> open_list;
	std::unordered_set <sf::Vector2f, SfmlHash> closed_list;
	std::vector<PathPoint> visited_points;

	open_queue.emplace(0, Magnitude(rounded_end - rounded_start), 0, start);
	open_list.emplace(rounded_start);

	while (!open_queue.empty())
	{
		// Find the lowest score point
		auto current = open_queue.top();
		closed_list.emplace(current.position());

		open_queue.pop();
		std::erase_if(open_list, [&current](const sf::Vector2f p) {return current.position() == p; });

		// Did we find the exit of the maze ?
		if (Magnitude(rounded_end - current.position()) <= std::numeric_limits<float>::epsilon())
		{
			path.SetSteps(ConstructPath(current, visited_points.data()));
			return path;
		}

		for (auto neighbour : kNeighbours)
		{
			// ReSharper disable once CppCStyleCast
			sf::Vector2f neighbour_pos = current.position() + neighbour * static_cast<float>(offset);

			// Tous les voisins
			auto found_position = std::find_if(walkables_positions.begin(), walkables_positions.end(), [&neighbour_pos](sf::Vector2f& pos)
				{
					return pos == neighbour_pos;
				});

			// Didn't found a valid neighbour
			// Possible cases : outside of the map, empty lists, etc.
			if (found_position != walkables_positions.end())
			{
				bool is_in_closed = closed_list.contains(*found_position);
				bool is_in_open = open_list.contains(*found_position);


				if (!is_in_closed && !is_in_open)
				{
					auto index = visited_points.size();
					visited_points.push_back(current);




					open_queue.emplace(PathPoint(current.g() + offset, Magnitude(rounded_end - current.position()), static_cast<int>(index), *found_position));
					open_list.emplace(*found_position);
				}

			}

		}

	}

	return path;

}

//GET

sf::Vector2f PathPoint::position() const
{
	return position_;
}
int PathPoint::parent_index() const
{
	return parent_;
}
float PathPoint::g() const
{
	return g_;
}