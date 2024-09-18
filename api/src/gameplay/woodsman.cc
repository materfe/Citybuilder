#include <random>

#include "gameplay/woodsman.h"
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
WoodsMan::WoodsMan(const sf::Vector2f& pos, const float speed, Tilemap& map, EconomyManager& economy) : Walker(pos, speed), map_(map), economy_(economy)
{
	home_destination_ = pos;
	stamina_ = 15;
	DefineTexture();

	SetBehaviorTreeNode();
}

//copy constructor for problems when you add another character
WoodsMan::WoodsMan(const WoodsMan& w): Walker(w), map_(w.map_), economy_(w.economy_)
{
	stamina_ = w.stamina_;
	home_destination_ = w.home_destination_;
	SetBehaviorTreeNode();
}

//set behavior tree
void WoodsMan::SetBehaviorTreeNode()
{
	stamina_ = 15;

	Leaf* seek_wood = new Leaf([this]()
		{
			return SeekWood();
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

	Leaf* gather_wood = new Leaf([this]()
		{
			return GatherWood();
		}
	);

	Leaf* back_home = new Leaf([this]()
		{
			return GoBackHome();
		}
	);

	auto main_sequence = std::make_unique<Sequence>();

	main_sequence->AddAChildren(seek_wood);
	main_sequence->AddAChildren(gather_wood);
	main_sequence->AddAChildren(back_home);

	tree_.AttachNode(main_sequence);

	seek_wood = nullptr;
	gather_wood = nullptr;
	back_home = nullptr;
	check_stamina = nullptr;
}

//go to closest tree
Status WoodsMan::SeekWood()
{
	sf::Vector2f closest_tree;
	if (map_.is_map_generated())
	{
		closest_tree = map_.nature().GetATreeTilePosition(getPosition());

	}

	if (squaredMagnitude(closest_tree - path_.final_destination()) > std::numeric_limits<float>::epsilon())
	{
		if(map_.is_map_generated())
		{
			constexpr int offset = 16;
			const Path p = pathfinder::CalculatePath(map_.GetWalkables(), LastDestination(), closest_tree, offset);
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
Status WoodsMan::GoBackHome()
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
		const int wood_value = RandomNumber();
		economy_.IncreaseWoodEconomyBy(wood_value);
		return Status::kSuccess;
	}
	else
	{
		return Status::kRunning;
	}
}

//collect it
Status WoodsMan::GatherWood() const
{
	if (map_.nature().GatherTree(getPosition()))
	{
		return Status::kSuccess;
	}
	return Status::kFailure;
}

//woodman tick -> what happens every frame
void WoodsMan::Tick()
{
	tree_.Tick();
	////walker.Tick() to make sure that the npc still moves
	Walker::Tick();
}

//override
void WoodsMan::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kWoodsMan));
}
