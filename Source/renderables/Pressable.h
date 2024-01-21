/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#include <Systems.h>

class Pressable
{
private:
    bool hovering;
    bool pressed;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Pressable();
    ~Pressable();

    /*
    SECTION 2A: SETTERS
    */
    void setPressed(bool pressed);
    void setHovering(bool hovering);
    /*
    SECTION 2B: GETTERS
    */
    bool isPressed();
    bool isHovering();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Pressable::Pressable()
{
    /*
    NOTE:
        - Initially set to `false` for both.
    */
    this->setPressed(false);
    this->setHovering(false);
}

Pressable::~Pressable()
{
    /*
    NOTE:
        - Empty, for now.
    */
}

/*
SECTION 2A: SETTERS
*/
void Pressable::setPressed(bool pressed) { this->pressed = pressed; }
void Pressable::setHovering(bool hovering) { this->hovering = hovering; }
/*
SECTION 2B: GETTERS
*/
bool Pressable::isPressed() { return pressed; }
bool Pressable::isHovering() { return hovering; }