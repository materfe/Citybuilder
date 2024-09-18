#include <tracy/Tracy.hpp>

#include "gameplay/building_manager.h"

//constructor
BuildingManager::BuildingManager(Tilemap& tilemap, EconomyManager& economy) : is_active_(false),
normal_build_cost_(50), tilemap_(tilemap), economy_manager_(economy)
{
	buildings_.clear();
	buildings_.reserve(tilemap_.playground_tile_size_u().x * tilemap_.playground_tile_size_u().y);

	woods_man_.clear();
	woods_man_.reserve(tilemap_.playground_tile_size_u().x * tilemap_.playground_tile_size_u().y);

	is_wood_house_mode_on_ = false;
	is_stone_house_mode_on_ = false;
}

//setup new building
void BuildingManager::SetupNewBuilding(const sf::Vector2i pos, const ResourceManager::Resource resource, Building& new_building) const
{
	new_building.setTexture(resource);

	tilemap_.TileAt(pos).set_is_walkable(true);

	tilemap_.TileAt(pos).set_allow_building(false);
}

//set a building
void BuildingManager::SetBuildingTexture(const ResourceManager::Resource resource, const sf::Vector2f position, const sf::Vector2i second_position)
{
	Building new_building(position);

	SetupNewBuilding(second_position, resource, new_building);

	buildings_.emplace_back(new_building);
}

//add a building
void BuildingManager::AddBuilding(const sf::Vector2i pos)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	if (tilemap_.CheckIfBuildable(pos))
	{
		if (economy_manager_.wood_economy() >= normal_build_cost_)
		{
			//check tile pos
			const auto positon = tilemap_.TileAt(pos).position();

			if (is_wood_house_mode_on_ && economy_manager_.stone_economy() >= normal_build_cost_)
			{
				SetBuildingTexture(ResourceManager::Resource::kWoodHouse, positon, pos);
				PopAWoodMan(positon);
				//cost taken
				economy_manager_.ReduceWoodEconomyBy(normal_build_cost_);
				economy_manager_.ReduceStoneEconomyBy(normal_build_cost_);
			}
			else if (is_stone_house_mode_on_)
			{
				if (economy_manager_.wood_economy() >= normal_build_cost_ * 2)
				{
					SetBuildingTexture(ResourceManager::Resource::kStoneHouse, positon, pos);
					PopAStoneMan(positon);
					//cost taken
					economy_manager_.ReduceWoodEconomyBy(normal_build_cost_ * 2);
				}
			}


		}
	}
}

//clear vector
void BuildingManager::DestroyAllBuildings()
{
	buildings_.clear();
}

//check if tile allow building
bool BuildingManager::CheckIfBuildable(const sf::Vector2i mouse_pos) const
{
	return tilemap_.CheckIfBuildable(mouse_pos);
}

//spawns a walker at house's places
void BuildingManager::PopAWoodMan(const sf::Vector2f& pos)
{
	constexpr int flat_speed = 300;
	WoodsMan new_wood_man(pos, flat_speed, map(), economy_manager_);

	woods_man_.emplace_back(new_wood_man);
}

//spawn a worker guy
void BuildingManager::PopAStoneMan(const sf::Vector2f& pos)
{
	constexpr int flat_speed = 300;
	MiningWorker new_mining_worker(pos, flat_speed, map(), economy_manager_);

	workers_.emplace_back(new_mining_worker);
}

//draw
void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& w : woods_man_)
	{
		target.draw(w, states);
	}
	for (const auto& w : workers_)
	{
		target.draw(w, states);
	}
	for (auto& b : buildings_)
	{
		target.draw(b, states);
	}
}


//do Ticks()
void BuildingManager::DoCharactersTick()
{
	if (!woods_man_.empty())
	{
		for (auto& w : woods_man_)
		{
			w.Tick();
		}
	}
	if (!workers_.empty())
	{
		for (auto& w : workers_)
		{
			w.Tick();
		}
	}
}

//SET
void BuildingManager::set_is_active()
{
	is_active_ = !is_active_;
}
void BuildingManager::set_is_wood_house_mode_on()
{
	is_wood_house_mode_on_ = true;
}
void BuildingManager::set_is_wood_house_mode_off()
{
	is_wood_house_mode_on_ = false;
}
void BuildingManager::set_is_stone_house_mode_on()
{
	is_stone_house_mode_on_ = true;
}
void BuildingManager::set_is_stone_house_mode_off()
{
	is_stone_house_mode_on_ = false;
}
void BuildingManager::DeSetAll()
{
	is_wood_house_mode_on_ = false;
	is_stone_house_mode_on_ = false;
}

//GET
bool BuildingManager::is_active() const
{
	return is_active_;
}
Tilemap& BuildingManager::map() const
{
	Tilemap& map = tilemap_;

	return map;
}
std::vector<WoodsMan> BuildingManager::woodman() const
{
	return woods_man_;
}