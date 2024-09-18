#ifndef API_GAMEPLAY_WALKER_H_
#define API_GAMEPLAY_WALKER_H_
#include <chrono>
#include <SFML/Graphics/Transformable.hpp>

#include "path.h"
#include "graphics/drawing_the_entity.h"

//class responsible for any entity mouvement 
class Walker : public sf::Transformable, public DrawingEntity
{
private:
	//chrono variable
	float linear_speed_;
	std::chrono::time_point<std::chrono::steady_clock> last_time_;
	sf::Vector2f destination_ = getPosition();

protected:
	Path path_;

public:
	void SetTextureAndDebugShape();

	sf::Vector2f LastDestination() const;

	//constructor
	Walker(const sf::Vector2f& pos, float speed);

	//every second thing -> allow to move in a direction based on coords of a destination
	void Tick();

	//define virtual
	void DefineTexture() override;


	//Set ----------------
	void set_destination(sf::Vector2f pos);
	void set_linear_speed(float speed);
	void set_path(const Path& path);
};
#endif //API_GAMEPLAY_WALKER_H_