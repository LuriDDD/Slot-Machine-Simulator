#include "WaitSlotMachine.h"

#include "RotateSlotMachine.h"
#include "SlotMachine.h"
#include <chrono>
#include <string>

using namespace std::chrono;

void WaitSlotMachine::toggle(SlotMachine *slot)
{
	slot->setState(RotateSlotMachine::getInstance());
}

// Just waiting for the start button to be pressed
void WaitSlotMachine::run(SlotMachine *slot)
{
	sf::RenderWindow *window = slot->getWindow();
	high_resolution_clock::time_point start_pressed, stop_pressed;
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
				case sf::Keyboard::Left:
					slot->toggle();
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
					{
						start_pressed = high_resolution_clock::now();
						toggle = true;
					}

					if (slot->getStopButton()->getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,
																		  sf::Mouse::getPosition(*window).y))
						stop_pressed = high_resolution_clock::now();

					break;
				default:
					break;
				}
			}
		}

		window->clear();
		auto now = high_resolution_clock::now();
		slot->draw(duration_cast<duration<double>>(now - start_pressed).count() < pressedTime,
				   duration_cast<duration<double>>(now - stop_pressed).count() < pressedTime);
		window->display();
		if (duration_cast<duration<double>>(now - start_pressed).count() >= pressedTime && toggle)
			slot->toggle();
	}
}

SlotMachineState &WaitSlotMachine::getInstance()
{
	static WaitSlotMachine singleton;
	return singleton;
}