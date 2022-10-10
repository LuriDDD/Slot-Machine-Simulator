all: compile

compile: 
	g++ main.cpp PrizeSlotMachine.cpp StopSlotMachine.cpp RotateStotMachine.cpp SlotMachine.cpp WaitSlotMachine.cpp -o main -I"C:\SFML-2.5.1\include" -L"C:\SFML-2.5.1\lib"  -DSFML_STATIC  -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	del -force *.o main.exe
