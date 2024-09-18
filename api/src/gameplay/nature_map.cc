#include <random>
#include <SFML/System/Time.hpp>

#include "gameplay/nature_map.h"
#include "maths/vec2f.h"

static int& RandomNumberInCutTrees(const Nature& nature)
{
	std::random_device r;
	std::default_random_engine e1(r());

	std::uniform_int_distribution uniform_dist(0, static_cast<int>(nature.all_cut_trees().size() - 1));
	int rnd = uniform_dist(e1);
	return rnd;
}
static int& RandomNumberInCutStones(const Nature& nature)
{
	std::random_device r;
	std::default_random_engine e1(r());

	std::uniform_int_distribution uniform_dist(0, static_cast<int>(nature.all_cut_rocks().size() - 1));
	int rnd = uniform_dist(e1);
	return rnd;
}

//setup vector 
Nature::Nature() : interval_(sf::seconds(0.2f))
{
	constexpr size_t size_x = 150;
	constexpr size_t size_y = 150;

	all_trees_.clear();
	all_trees_.reserve(size_x * size_y);

	all_cut_trees_.clear();
	all_cut_trees_.reserve(size_x * size_y);

	all_stones_.clear();
	all_stones_.reserve(size_x * size_y);
}

//add a tree tile
void Nature::AddATreeAt(const sf::Vector2f position)
{
	Tree new_tree(position);
	all_trees_.emplace_back(new_tree);
}
void Nature::AddAStoneAt(const sf::Vector2f position)
{
	Stone new_stone(position);
	all_stones_.emplace_back(new_stone);
}
void Nature::AddACutTree(const sf::Vector2f position)
{
	CutTree new_tree(position);
	all_cut_trees_.emplace_back(new_tree);
}
void Nature::AddACutStone(const sf::Vector2f position)
{
	MinedStone new_stone(position);
	all_cut_stones_.emplace_back(new_stone);
}

//cut tree and return if tree is here or not
bool Nature::GatherTree(sf::Vector2f pos)
{
	const auto tree = std::find_if(all_trees_.begin(), all_trees_.end(), [pos](const Tree& t) { return pos == t.position(); });

	if (tree != all_trees_.end())
	{
		const sf::Vector2f position = tree->position();
		AddACutTree(position);
		all_trees_.erase(tree);
		return true;
	}
	else
	{
		return false;
	}
}
bool Nature::GatherStone(sf::Vector2f pos)
{
	const auto stone = std::find_if(all_stones_.begin(), all_stones_.end(),
		[pos](const Stone& t) { return pos == t.position(); });

	if (stone != all_stones_.end())
	{
		const sf::Vector2f position = stone->position();
		AddACutStone(position);
		all_stones_.erase(stone);
		return true;
	}
	else
	{
		return false;
	}
}

//repop an entity based on CD
void Nature::RepopTree()
{
	if (wood_clock_.getElapsedTime() >= interval_)
	{
		GrowTree();

		wood_clock_.restart();
	}
}
void Nature::RepopStone()
{
	if (stone_clock_.getElapsedTime() >= interval_)
	{
		GrowStone();

		stone_clock_.restart();
	}
}

//update
void Nature::UpdateRepopCd(const float woodsman_size)
{
	interval_ = sf::seconds(interval_.asSeconds() - woodsman_size/8);
}

//repop an entity
void Nature::GrowTree()
{
	if (!all_cut_trees_.empty())
	{
		auto ref = this;

		const int random = RandomNumberInCutTrees(*ref);

		const auto tree_selected = all_cut_trees_[random].position();

		const auto tree_found = std::find_if(all_cut_trees_.begin(), all_cut_trees_.end(), [&tree_selected](const CutTree& cut)
			{
				return cut.position() == tree_selected;
			});
		AddATreeAt(tree_found->position());
		all_cut_trees_.erase(tree_found);
		ref = nullptr;
	}
}
void Nature::GrowStone()
{
	if (!all_cut_stones_.empty())
	{
		auto ref = this;

		const int random = RandomNumberInCutStones(*ref);

		const auto tree_selected = all_cut_stones_[random].position();

		const auto tree_found = std::find_if(all_cut_stones_.begin(), all_cut_stones_.end(), [&tree_selected](const MinedStone& cut)
			{
				return cut.position() == tree_selected;
			});
		AddAStoneAt(tree_found->position());
		all_cut_stones_.erase(tree_found);
		ref = nullptr;
	}
}

//return a tree position
sf::Vector2f Nature::GetATreeTilePosition(const sf::Vector2f starting_pos)
{
	sf::Vector2f selected_tree;
	float closest_tree_distance = std::numeric_limits<float>::infinity();

	std::for_each(all_trees_.begin(), all_trees_.end(), [&selected_tree, &starting_pos, &closest_tree_distance](const Tree& t)
		{
			const auto new_pos_square_m = squaredMagnitude(starting_pos - t.position());

			if (new_pos_square_m < closest_tree_distance)
			{
				selected_tree = t.position();
				closest_tree_distance = new_pos_square_m;
			}

		});

	return selected_tree;
}
sf::Vector2f Nature::GetAStoneTilePosition(sf::Vector2f starting_pos)
{
	sf::Vector2f selected_stone;
	float closest_stone_distance = std::numeric_limits<float>::infinity();

	std::for_each(all_stones_.begin(), all_stones_.end(), [&selected_stone, &starting_pos, &closest_stone_distance](const Stone& t)
		{
			const auto new_pos_square_m = squaredMagnitude(starting_pos - t.position());

			if (new_pos_square_m < closest_stone_distance)
			{
				selected_stone = t.position();
				closest_stone_distance = new_pos_square_m;
			}

		});

	return selected_stone;
}


//GET
std::vector<CutTree> Nature::all_cut_trees() const
{
	return all_cut_trees_;
}
std::vector<MinedStone> Nature::all_cut_rocks() const
{
	return all_cut_stones_;
}


void Nature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& t : all_trees_)
	{
		target.draw(t, states);
	}

	for (auto& s : all_stones_)
	{
		target.draw(s, states);
	}

	for (auto& t : all_cut_trees_)
	{
		target.draw(t, states);
	}

	for (auto& t : all_cut_stones_)
	{
		target.draw(t, states);
	}
}
