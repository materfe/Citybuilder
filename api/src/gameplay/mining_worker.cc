#include <random>

#include "gameplay/mining_worker.h"
#include "behavior_tree/bt_leaf.h"
#include "gameplay/pathfinder_a_star.h"
#include "maths/vec2f.h"
#include "behavior_tree/bt_sequence.h"

static int& RandomNumber()
{
	std::random_device r;
	std::default_random_engine e1(r());

	std::uniform_int_distribution uniform_dist(1, 5);
	int rnd = uniform_dist(e1);
	return rnd;
}

using namespace behavior_tree;

//constructor
MiningWorker::MiningWorker(const sf::Vector2f& pos, const float speed, Tilemap& map, EconomyManager& economy) : Walker(pos, speed), map_(map), economy_(economy)
{
	home_destination_ = pos;
	stamina_ = 15;
	DefineTexture();

	SetBehaviorTreeNode();
}

//copy constructor for problems when you add another character
MiningWorker::MiningWorker(const MiningWorker& w) : Walker(w), map_(w.map_), economy_(w.economy_)
{
	stamina_ = w.stamina_;
	home_destination_ = w.home_destination_;
	SetBehaviorTreeNode();
}

//set behavior tree
void MiningWorker::SetBehaviorTreeNode()
{
	stamina_ = 15;

	Leaf* seek_stone = new Leaf([this]()
		{
			return SeekStone();
		}
	);


	Leaf* check_stamina = new Leaf([this]()
		{
			if (stamina_ >= 0)
			{
				return Status::kSuccess;
			}
			return Status::kFailure;

		}
	);

	Leaf* gather_stone = new Leaf([this]()
		{
			return GatherStone();
		}
	);

	Leaf* back_home = new Leaf([this]()
		{
			return GoBackHome();
		}
	);

	std::unique_ptr<Sequence> main_sequence = std::make_unique<Sequence>();


	main_sequence->AddAChildren(seek_stone);
	main_sequence->AddAChildren(gather_stone);
	main_sequence->AddAChildren(back_home);

	tree_.AttachNode(main_sequence);

	gather_stone = nullptr;
	seek_stone = nullptr;
	back_home = nullptr;
	check_stamina = nullptr;
}

//go to closest stone
Status MiningWorker::SeekStone()
{
	sf::Vector2f closest_stone;
	if (map_.is_map_generated())
	{
		closest_stone = map_.nature().GetAStoneTilePosition(getPosition());

	}

	if (squaredMagnitude(closest_stone - path_.final_destination()) > std::numeric_limits<float>::epsilon())
	{
		if (map_.is_map_generated())
		{
			constexpr int offset = 16;
			const Path p = pathfinder::CalculatePath(map_.GetWalkables(), LastDestination(), closest_stone, offset);
			set_path(p);
		}
	}

	if (!path_.is_available())
	{
		return Status::kFailure;
	}

	const float sq_mag = squaredMagnitude(getPosition() - path_.final_destination());
	if (sq_mag < std::numeric_limits<float>::epsilon())
	{
		return Status::kSuccess;
	}
	else
	{
		return Status::kRunning;
	}
}

//go back home
Status MiningWorker::GoBackHome()
{
	const sf::Vector2f home_position = home_destination_;

	if (squaredMagnitude(home_position - path_.final_destination()) > std::numeric_limits<float>::epsilon())
	{
		constexpr int offset = 16;
		const Path p = pathfinder::CalculatePath(map_.GetWalkables(), LastDestination(), home_position, offset);
		set_path(p);
	}

	if (!path_.is_available())
	{
		return Status::kFailure;
	}

	const float sq_mag = squaredMagnitude(getPosition() - path_.final_destination());
	if (sq_mag < std::numeric_limits<float>::epsilon())
	{
		const int stone_value = RandomNumber();
		economy_.IncreaseStoneEconomyBy(stone_value);
		return Status::kSuccess;
	}
	else
	{
		return Status::kRunning;
	}
}

//collect it
Status MiningWorker::GatherStone() const
{
	if (map_.nature().GatherStone(getPosition()))
	{
		return Status::kSuccess;
	}
	return Status::kFailure;
}

//woodman tick -> what happens every frame
void MiningWorker::Tick()
{
	tree_.Tick();
	////walker.Tick() to make sure that the npc still moves
	Walker::Tick();
}

//override
void MiningWorker::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kStoneMan));
}