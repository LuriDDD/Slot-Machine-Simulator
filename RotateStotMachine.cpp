#include "RotateSlotMachine.h"

#include <chrono>

#include "StopSlotMachine.h"
#include "SlotMachine.h"

using namespace std::chrono;

void RotateSlotMachine::toggle(SlotMachine *slot)
{
    slot->setState(StopSlotMachine::getInstance());
}

void RotateSlotMachine::run(SlotMachine *slot)
{
    sf::RenderWindow *window = slot->getWindow();

    // Set the maximum speed
    std::vector<double> acceleration(3);
    for (auto &x : acceleration)
        x = 15 + double(std::rand() % 6) * 3;

    auto speed = slot->getSpeed();

    high_resolution_clock::time_point start_pressed, stop_pressed,
        timer = high_resolution_clock::now();
    bool toggle = false;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window->close();
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    if (slot->getStartButton()->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,
                                                                           sf::Mouse::getPosition(*window).y))
                        start_pressed = high_resolution_clock::now();

                    if (slot->getStopButton()->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,
                                                                          sf::Mouse::getPosition(*window).y))
                    {
                        stop_pressed = high_resolution_clock::now();
                        toggle = true;
                    }

                    break;
                default:
                    break;
                }
            }
        }

        // Increase the speed until the necessary one is not reached
        for (int i = 0; i < speed.size(); i++)
        {
            if (speed[i] < acceleration[i])
                speed[i] += acceleration[i] / (maxFPS * 2);
        }

        slot->setSpeed(speed);

        window->clear();
        slot->moveSlots();
        auto now = high_resolution_clock::now();
        slot->draw(duration_cast<duration<double>>(now - start_pressed).count() < pressedTime,
                   duration_cast<duration<double>>(now - stop_pressed).count() < pressedTime);
        window->display();

        // Toggle to the next state if start button is pressed or the timer has run out
        if ((duration_cast<duration<double>>(now - stop_pressed).count() >= pressedTime && toggle) ||
            duration_cast<duration<double>>(now - timer).count() >= rotateTime)
            slot->toggle();
    }
}

SlotMachineState &RotateSlotMachine::getInstance()
{
    static RotateSlotMachine singleton;
    return singleton;
}