#include "StopSlotMachine.h"

#include <chrono>

#include "PrizeSlotMachine.h"
#include "SlotMachine.h"

using namespace std::chrono;

void StopSlotMachine::toggle(SlotMachine *slot)
{
    slot->setState(PrizeSlotMachine::getInstance());
}

void StopSlotMachine::run(SlotMachine *slot)
{
    sf::RenderWindow *window = slot->getWindow();
    auto sprites = slot->getSlot();
    auto ind_prize = slot->getPrizes();
    auto speed = slot->getSpeed();

    std::vector<double> acceleration(3);
    for (int i = 0; i < acceleration.size(); i++)
        acceleration[i] = speed[i] / maxFPS;

    high_resolution_clock::time_point start_pressed, stop_pressed;

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
                        stop_pressed = high_resolution_clock::now();

                    break;
                default:
                    break;
                }
            }
        }

        std::string str;
        for (int i = 0; i < speed.size(); i++)
        {
            // Move slot sprite until the necessary coordinate is not reached
            if ((*sprites)[i][ind_prize[i]].first.getPosition().y < blockHeight * 10)
            {
                // Decrease speed if sum of an arithmetic progression(with little margin)
                // is enough to reach the necessary coordinate
                if (blockHeight * 10 - (*sprites)[i][ind_prize[i]].first.getPosition().y <
                    (acceleration[i] + acceleration[i] * maxFPS) * (maxFPS / 2 - 1))
                    speed[i] -= acceleration[i];
            }
            else // Set to the exact coordinate
                speed[i] = float(blockHeight * 10) - (*sprites)[i][ind_prize[i]].first.getPosition().y;
        }
        slot->setSpeed(speed);

        window->clear();
        slot->moveSlots();

        auto now = high_resolution_clock::now();
        slot->draw(duration_cast<duration<double>>(now - start_pressed).count() < pressedTime,
                   duration_cast<duration<double>>(now - stop_pressed).count() < pressedTime);
        window->display();

        // Toggle to the next state if rotation is stopped
        if (speed[0] == 0 && speed[1] == 0 && speed[2] == 0)
        {
            slot->setSpeed({0, 0, 0});
            slot->toggle();
        }
    }
}

SlotMachineState &StopSlotMachine::getInstance()
{
    static StopSlotMachine singleton;
    return singleton;
}