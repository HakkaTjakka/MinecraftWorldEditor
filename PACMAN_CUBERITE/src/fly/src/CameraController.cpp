#include "CameraController.h"
#include "Log.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace fly
{

CameraController::CameraController(sf::RenderWindow& window, Camera& camera) :
    m_window(window),
    m_camera(camera),
    m_previousMouse(sf::Mouse::getPosition(window)),
    m_mouseDown(false)
{
}

void CameraController::update(float dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto new_mouse = sf::Mouse::getPosition(m_window);
        if (  new_mouse.x < 0 || new_mouse.x > m_window.getSize().x
           || new_mouse.y < 0 || new_mouse.y > m_window.getSize().y)
            return;

        if (m_mouseDown)
        {
            auto diff = new_mouse - m_previousMouse;
            m_camera.rotate(diff.x * dt, diff.y * dt);
        }
        m_mouseDown = true;
        m_previousMouse = new_mouse;
    }
    else
        m_mouseDown = false;
}


void CameraController::update2(float dt, sf::Vector2i new_mouse)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (new_mouse.x>=0) {
//            if (new_mouse != m_previousMouse) printf("External window left mouse button pressed\n");
        } else {
//            printf("External window left mouse button pressed outside external window\n");
            return;
        }
//        if (new_mouse != m_previousMouse) printf("Received mouse: X=%d Y=%d\n",new_mouse.x,new_mouse.y);
        if (m_mouseDown)
        {
            auto diff = new_mouse - m_previousMouse;
            m_camera.rotate(diff.x * dt, diff.y * dt);
        } else m_mouseDown = true;
        m_previousMouse = new_mouse;
    }
    else {
//        if (m_mouseDown) printf("External window left mouse button released\n");
        m_mouseDown = false;

    }
}


void CameraController::passEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        m_camera.zoom(event.mouseWheelScroll.delta * -0.05f);
        printf("Delta1=%f\n",event.mouseWheelScroll.delta);
    }
}

void CameraController::passEvent2(float delta)
{
    m_camera.zoom(delta * -0.05f);
    printf("Delta2=%f\n",delta);
}

}
