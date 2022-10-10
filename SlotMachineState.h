#pragma once

constexpr double pressedTime = 0.1;
constexpr double rotateTime = 5;

class SlotMachine;

class SlotMachineState
{
public:
	virtual void run(SlotMachine *slots) = 0;
	virtual void toggle(SlotMachine *slots) = 0;
	virtual ~SlotMachineState() {}
};