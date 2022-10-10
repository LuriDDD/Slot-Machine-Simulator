#include "SlotMachineState.h"

class RotateSlotMachine : public SlotMachineState
{
public:
	void run(SlotMachine *slot) override;
	void toggle(SlotMachine *slot) override;
	static SlotMachineState &getInstance();

private:
	RotateSlotMachine() {}
	RotateSlotMachine(const RotateSlotMachine &other);
	RotateSlotMachine &operator=(const RotateSlotMachine &other);
};