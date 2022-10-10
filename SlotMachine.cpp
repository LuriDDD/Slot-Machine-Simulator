#include "SlotMachine.h"

#include "WaitSlotMachine.h"

SlotMachine::SlotMachine()
    : window(sf::VideoMode(1250, 800), "Slot Machine"),
      slots(3), textures(6), currentState(&WaitSlotMachine::getInstance()), prizes({1, 1, 1}), speed({0, 0, 0})
{

    std::srand(std::time(nullptr));
    window.setFramerateLimit(maxFPS);
    textures[0].loadFromFile("resources/apple.png");
    textures[1].loadFromFile("resources/cherry.png");
    textures[2].loadFromFile("resources/lemon.png");
    textures[3].loadFromFile("resources/watermelon.png");
    textures[4].loadFromFile("resources/diamond.png");
    textures[5].loadFromFile("resources/casino.png");

    background_texture.loadFromFile("resources/vector.png");
    start_texture.loadFromFile("resources/start.png");
    stop_texture.loadFromFile("resources/stop.png");

    slot_shader.loadFromFile("resources/wave.vert", "resources/blur.frag");
    button_shader.loadFromFile("resources/edge.frag", sf::Shader::Fragment);

    slot_states.shader = &slot_shader;
    button_states.shader = &button_shader;

    background.setTexture(background_texture);
    background.setPosition(0, 0);
    background.setScale(0.32f, 0.29f);

    start.setTexture(start_texture);
    start.setPosition(880, 150);
    start.setScale(0.7f, 0.7f);

    stop.setTexture(stop_texture);
    stop.setPosition(880, 450);
    stop.setScale(0.7f, 0.7f);

    for (int i = 0; i < slots.size(); i++)
    {
        slots[i] = std::vector<std::pair<sf::Sprite, int>>(4);
        int y = blockHeight * 3;
        for (auto &sprite : slots[i])
        {
            sprite.first.setTexture(textures[std::rand() % textures.size()]);
            sprite.first.setPosition((i + 1) * blockWidth, y);
            sprite.first.setScale(0.25f, 0.25f);
            y -= blockHeight;
        }
    }
}

// Reset the vector that stores slot sprites
void SlotMachine::updateSlots()
{
    std::vector<std::vector<std::pair<sf::Sprite, int>>> tmp(slots.size());

    for (int i = 0; i < tmp.size(); i++)
    {
        for (int j = prizes[i] - 1; j < prizes[i] + 3; j++)
        {
            tmp[i].push_back(slots[i][j]);
        }
    }
    prizes = {1, 1, 1};
    slots = tmp;
}

// Return indexes of slot sprites which are in the middle of slot machine
std::vector<int> SlotMachine::getPrizes()
{
    return prizes;
}

// Set the movement speed of slot sprites
void SlotMachine::setSpeed(std::vector<double> spd)
{
    speed = spd;
}

// Move all slot sprites
void SlotMachine::moveSlots()
{
    for (int i = 0; i < slots.size(); i++)
    {
        for (auto &sprite : slots[i])
        {
            sprite.first.move(0, speed[i]);
        }
        // Add the new slot sprite if if the movement continues
        if (slots[i][prizes[i]].first.getPosition().y > blockHeight * 2 && prizes[i] + 3 == slots[i].size())
        {
            int random = std::rand() % textures.size();
            slots[i].push_back({sf::Sprite(), (random + 1) * blockHeight * 2});
            slots[i].back().first.setTexture(textures[random]);
            slots[i].back().first.setPosition((i + 1) * blockWidth, slots[i][prizes[i]].first.getPosition().y - blockHeight * 3);
            slots[i].back().first.setScale(0.25f, 0.25f);
        }
        // Increase the index of the winning slot sprite if if the movement continues
        if (slots[i][prizes[i] + 1].first.getPosition().y >= blockHeight * 2)
        {
            prizes[i]++;
        }
    }
}

void SlotMachine::run()
{
    currentState->run(this);
}

// Draw all Drawable objects
void SlotMachine::draw(bool start_pressed, bool stop_pressed)
{
    for (int i = 0; i < slots.size(); i++)
    {
        for (auto &sprite : slots[i])
        {
            // Set the blur radius depending on rotate speed
            slot_shader.setUniform("blur_radius", float(speed[i]) / 2 / 1000);
            window.draw(sprite.first, slot_states);
        }
    }
    window.draw(background);
    if (start_pressed)
        window.draw(start, button_states);
    else
        window.draw(start);

    if (stop_pressed)
        window.draw(stop, button_states);
    else
        window.draw(stop);
}

void SlotMachine::setState(SlotMachineState &newState)
{
    currentState = &newState;
    currentState->run(this);
}

void SlotMachine::toggle()
{
    currentState->toggle(this);
}