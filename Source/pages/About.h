#pragma once

#include <Systems.h>

#include <Button.h>
#include <Navigation.h>
#include <Menu.h>
#include <Creator.h>

class Master;

class About : public Navigation
{
private:
    vector<pair<string, Button>> buttons;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    About();
    About(Master *context);
    ~About();
    void loadButtons();

    /*
    SECTION 2: OTHER METHODS
    */
    void switchState();
    void update();
    void render();
};