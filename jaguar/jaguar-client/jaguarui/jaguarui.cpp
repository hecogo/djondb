#include "jaguarui.h"
#include "ui/MenuItem.h"
#include <map>
#include <vector>

using namespace std;

map<int, screenFunction> screenFunctions;
int screenCount;
vector<MenuItem*> items;

vector<MenuItem*> getMenuItems() {
    return items;
}

void addMenu(MenuItem* item) {
    items.push_back(item);
}

void addScreen(screenFunction function, char* menu) {
    MenuItem* item = new MenuItem(menu, screenCount);
    screenFunctions.insert(pair<int, screenFunction>(screenCount, function));
    screenCount++;
    addMenu(item);
}

ScreenBase* callScreenFunction(int id) {
    map<int, screenFunction>::iterator iter = screenFunctions.find(id);
    screenFunction function = iter->second;
    ScreenBase* screen = (*function)();
    return screen;
}