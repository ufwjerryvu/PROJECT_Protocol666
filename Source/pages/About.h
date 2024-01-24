/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

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
    Button back;

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