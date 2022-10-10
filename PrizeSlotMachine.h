#include "SlotMachineState.h"

#include <SFML/Graphics.hpp>

class PrizeSlotMachine : public SlotMachineState
{
public:
	void run(SlotMachine *light) override;
	void toggle(SlotMachine *light) override;
	static PrizeSlotMachine &getInstance();

private:
	PrizeSlotMachine();
	PrizeSlotMachine(const PrizeSlotMachine &other);
	PrizeSlotMachine &operator=(const PrizeSlotMachine &other);

	sf::Font font;
	sf::Text text;

	sf::Sprite background, back;
	sf::Texture background_texture, back_texture;

	sf::Shader button_shader;
	sf::RenderStates button_states;
};