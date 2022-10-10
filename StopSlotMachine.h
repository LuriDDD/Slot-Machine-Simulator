#include "SlotMachineState.h"

class StopSlotMachine : public SlotMachineState
{
public:
	void run(SlotMachine *light) override;
	void toggle(SlotMachine *light) override;
	static SlotMachineState &getInstance();

private:
	StopSlotMachine() {}
	StopSlotMachine(const StopSlotMachine &other);
	StopSlotMachine &operator=(const StopSlotMachine &other);
};