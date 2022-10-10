#include "SlotMachineState.h"

class WaitSlotMachine : public SlotMachineState
{
public:
	void run(SlotMachine *light) override;
	void toggle(SlotMachine *light) override;
	static SlotMachineState &getInstance();

private:
	WaitSlotMachine() {}
	WaitSlotMachine(const WaitSlotMachine &other);
	WaitSlotMachine &operator=(const WaitSlotMachine &other);
};