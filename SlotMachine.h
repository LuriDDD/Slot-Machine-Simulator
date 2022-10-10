#include <SFML/Graphics.hpp>

#include <vector>

#include "SlotMachineState.h"

constexpr int blockWidth = 200;
constexpr int blockHeight = 150;
constexpr int maxFPS = 60;

class SlotMachine
{
public:
	SlotMachine();

	inline SlotMachineState *getCurrentState() const { return currentState; }

	void toggle();

	void setState(SlotMachineState &newState);

	void draw(bool start_pressed, bool stop_pressed);

	void run();

	void moveSlots();

	void updateSlots();

	void setSpeed(std::vector<double> spd);

	std::vector<double> getSpeed() { return speed; }

	std::vector<std::vector<std::pair<sf::Sprite, int>>> *getSlot() { return &slots; }

	std::vector<int> getPrizes();

	sf::Sprite *getStartButton() { return &start; }

	sf::Sprite *getStopButton() { return &stop; }

	sf::RenderWindow *getWindow() { return &window; }

private:
	sf::Sprite background, start, stop;
	sf::Texture background_texture, start_texture, stop_texture;

	sf::Shader slot_shader, button_shader;
	sf::RenderStates slot_states, button_states;

	std::vector<std::vector<std::pair<sf::Sprite, int>>> slots;
	std::vector<sf::Texture> textures;
	std::vector<int> prizes;
	std::vector<double> speed;
	sf::RenderWindow window;

	SlotMachineState *currentState;
};