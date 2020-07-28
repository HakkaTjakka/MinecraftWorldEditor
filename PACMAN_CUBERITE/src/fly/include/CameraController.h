#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Camera.h"

namespace fly
{


class CameraController
{
public:
    CameraController(sf::RenderWindow& window, Camera& camera);
    void update(float dt);
    void update2(float dt, sf::Vector2i new_mouse);
    void passEvent(const sf::Event& event);
    void passEvent2(float delta);
private:
    sf::RenderWindow&       m_window;
    Camera&                 m_camera;
    sf::Vector2i            m_previousMouse;
    bool                    m_mouseDown;
};


}


#endif
