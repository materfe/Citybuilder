#ifndef API_GAMEPLAY_PATH_H_
#define API_GAMEPLAY_PATH_H_
#include <queue>
#include <SFML/System/Vector2.hpp>


class Path
{
public:
	//GET ----------
	[[nodiscard]] bool is_ended() const;
	[[nodiscard]] bool is_available() const;
	[[nodiscard]] bool is_ready() const;
	[[nodiscard]] sf::Vector2f final_destination() const;

	sf::Vector2f GetNextStep();
	void SetSteps(std::vector<sf::Vector2f> steps);
	// steps getter
	const std::queue<sf::Vector2f>& GetSteps();

private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;
	sf::Vector2f final_destination_;

	bool is_available_ = false;
	bool is_ready_ = true;
};





#endif //API_GAMEPLAY_PATH_H_