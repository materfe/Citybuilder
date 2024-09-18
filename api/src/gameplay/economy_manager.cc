#include "gameplay/economy_manager.h"

EconomyManager::EconomyManager()
{
	//statring money
	constexpr int starting_economy = 50;
	wood_economy_ = starting_economy;
	stone_economy_ = starting_economy;
}

//increase and reduce
void EconomyManager::ReduceWoodEconomyBy(const size_t number)
{
	wood_economy_ -= number;
}
void EconomyManager::IncreaseWoodEconomyBy(const size_t number)
{
	wood_economy_ += number;
}
void EconomyManager::ReduceStoneEconomyBy(const size_t number)
{
	stone_economy_ -= number;
}
void EconomyManager::IncreaseStoneEconomyBy(const size_t number)
{
	stone_economy_ += number;
}


//GET
size_t EconomyManager::wood_economy() const
{
	return wood_economy_;
}
size_t EconomyManager::stone_economy() const
{
	return stone_economy_;
}