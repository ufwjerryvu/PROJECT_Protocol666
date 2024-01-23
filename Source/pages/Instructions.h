/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

#include <Button.h>
#include <FileHandler.h>
#include <Navigation.h>

#include <Menu.h>

class Master;

class Instructions : public Navigation
{
private:
    Button back;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Instructions();
    Instructions(Master *context);
    ~Instructions();
    void loadButtons();

    /*
    SECTION 2: OTHER METHODS
    */
    void switchState();
    void update();
    void render();
};