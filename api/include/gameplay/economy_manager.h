#ifndef API_GAMEPLAY_ECONOMY_MANAGER_H_
#define API_GAMEPLAY_ECONOMY_MANAGER_H_


class EconomyManager
{
private:
	size_t wood_economy_;
	size_t stone_economy_;

public:
	//constructor
	EconomyManager();

	//reduce/increase wood_economy by a certain number
	void ReduceWoodEconomyBy(size_t number);
	void IncreaseWoodEconomyBy(size_t number);

	void ReduceStoneEconomyBy(size_t number);
	void IncreaseStoneEconomyBy(size_t number);

	//Get -------------------
	[[nodiscard]] size_t wood_economy() const;
	[[nodiscard]] size_t stone_economy() const;
};


#endif //API_GAMEPLAY_ECONOMY_MANAGER_H_
