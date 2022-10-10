#include "PrizeSlotMachine.h"

#include <chrono>
#include <string>

#include "WaitSlotMachine.h"
#include "SlotMachine.h"

using namespace std::chrono;

PrizeSlotMachine::PrizeSlotMachine()
{
    background_texture.loadFromFile("resources/background.png");
    back_texture.loadFromFile("resources/back.png");

    button_shader.loadFromFile("resources/edge.frag", sf::Shader::Fragment);
    button_states.shader = &button_shader;

    font.loadFromFile("resources\\MangabeyRegular.otf");
    text.setFont(font);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(230, 350);

    background.setTexture(background_texture);
    background.setPosition(0, 0);
    background.setScale(0.32f, 0.29f);

    back.setTexture(back_texture);
    back.setPosition(220, 500);
    back.setScale(0.7f, 0.7f);
}

void PrizeSlotMachine::toggle(SlotMachine *slot)
{
    slot->setState(WaitSlotMachine::getInstance());
}

void PrizeSlotMachine::run(SlotMachine *slot)
{
    // Create new window for this state
    sf::RenderWindow new_window(sf::VideoMode(720, 650), "Win!");
    auto sprites = slot->getSlot();
    auto ind_prize = slot->getPrizes();
    std::vector<sf::Sprite> prizes;
    high_resolution_clock::time_point back_pressed;
    bool toggle = false;
    int reward = 0;

    // Copy the sprites from the main window and set positions
    for (int i = 0; i < ind_prize.size(); i++)
    {
        reward += (*sprites)[i][ind_prize[i]].second;
        prizes.push_back((*sprites)[i][ind_prize[i]].first);
        prizes.back().setPosition(i * blockWidth + 90, 75);
    }

    text.setString("Win: " + std::to_string(reward));

    while (new_window.isOpen())
    {
        sf::Event event;
        while (new_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                new_window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    new_window.close();
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
                    if (back.getGlobalBounds().contains(sf::Mouse::getPosition(new_window).x,
                                                        sf::Mouse::getPosition(new_window).y))
                    {
                        toggle = true;
                        back_pressed = high_resolution_clock::now();
                    }

                    break;
                default:
                    break;
                }
            }
        }

        new_window.clear();
        new_window.draw(background);

        auto now = high_resolution_clock::now();
        if (duration_cast<duration<double>>(now - back_pressed).count() < pressedTime)
            new_window.draw(back, button_states);
        else
            new_window.draw(back);

        for (auto &x : prizes)
            new_window.draw(x);

        new_window.draw(text);
        new_window.display();

        if (duration_cast<duration<double>>(now - back_pressed).count() >= pressedTime && toggle)
            new_window.close();
    }
    slot->updateSlots();
    slot->toggle();
}

PrizeSlotMachine &PrizeSlotMachine::getInstance()
{
    static PrizeSlotMachine singleton;
    return singleton;
}