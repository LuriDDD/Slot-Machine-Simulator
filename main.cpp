#include "SlotMachine.h"
#include <vector>
#include <iostream>

using namespace std;

typedef void (*ptr)(int x, int y);

int main()
{
    // SlotMachine slot;
    // slot.run();

    ptr p;
    p(1, 1);

    int *a = new int(1);
    std::vector<int *> v(1);
    v[0] = a;

    cout << *v[0] << " " << *a;
    *a = 2;
    cout << *v[0] << " " << *a;

    return 0;
}