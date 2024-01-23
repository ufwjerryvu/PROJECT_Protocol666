/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

#include <Button.h>
#include <FileHandler.h>
#include <Navigation.h>

class Master;

class Menu : public Navigation
{
private:
    Button play;
    Button settings;
    Button about;
    Button instructions;
    Button exit;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Menu();
    Menu(Master *context);
    ~Menu();
    void loadButtons();

    /*
    SECTION 2:
    */
    void update();
    void render();
};