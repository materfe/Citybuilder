#ifndef API_GRAPHICS_VIEW_H_
#define API_GRAPHICS_VIEW_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

#include "graphics/tilemap.h"

class ViewPoint
{
private:

    sf::View view_;

    Tilemap& tile_map_;

    sf::Vector2f dead_zone_;
    sf::Vector2f camera_speed_;

    sf::Vector2f pos_;

    float max_zoom_;
    float min_zoom_;

    float zoom_;

    bool camera_modification_;

    void InitVariables();

public:
    explicit ViewPoint(Tilemap& tilemap);

    bool IsWithinBounds(const sf::Vector2f& center) const;
    sf::Vector2f ClampCenterToBounds(const sf::Vector2f& center) const;

    sf::View getView() const
    {
        return view_;
    }
    sf::Vector2f pos() const
    {
        return pos_;
    }

    void Move(const sf::Event& event);

    void Zoom(const sf::Event& event, const sf::RenderWindow& window);

    void MoveViewByMouse(const sf::RenderWindow& window);

    //void ClampView();
};


#endif //API_GRAPHICS_VIEW_H_