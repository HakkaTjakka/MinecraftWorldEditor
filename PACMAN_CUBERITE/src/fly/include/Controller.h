#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace fly
{


class Controller
{
public:
    enum Event
    {
        RollLeft,
        RollRight,
        ElevatorUp,         // Technically, elevator is down but we refer to the motion
        ElevatorDown,
        ThrustUp,
        ThrustDown,
        TotalEvents
    };
    Controller(sf::RenderWindow& window);
//    Controller(sf::Window& window);
    template <class Callable>
    void setCallback(Event event, Callable cb) { if (event < TotalEvents) m_callbacks[event] = cb; }

    template <class Callable>
    void registerRotate(Callable cb) { m_rotateCallback = cb; }
    void takeInput(float dt);

    sf::RenderWindow& m_window;

private:

    std::function<void(float, float)> m_rotateCallback;
    std::function<void(void)> m_callbacks[TotalEvents];
//    std::function<void(sf::RenderWindow&)> m_window;
};

}


#endif // CONTROLLER_H
