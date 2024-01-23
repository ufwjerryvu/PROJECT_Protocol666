/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

#include <Button.h>
#include <FileHandler.h>

#include <Navigation.h>
#include <Settings.h>
#include <About.h>
#include <Instructions.h>

#include <Creator.h>

class Master;

class Menu : public Navigation
{
private:
    Button play;
    Button settings;
    Button about;
    Button instructions;
    Button quit;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Menu();
    Menu(Master *context);
    ~Menu();
    void loadButtons();

    /*
    SECTION 2: OTHER METHODS
    */
    void switchState();
    void update();
    void render();
};