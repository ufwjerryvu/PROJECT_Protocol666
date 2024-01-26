#pragma once

#include <Systems.h>

#include <Animation.h>

template <typename Type>
class Animator
{
private:
    map<Type, Animation> animations;
    Type key;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Animator(map<Type, Animation> animations);
    ~Animator();

    /*
    SECTION 2: SETTER AND GETTER METHODS
    */
    void setKey(Type key);
    Type getKey();
    vector<Type> getKeys();
    SDL_Texture* getCurrentFrame();

    /*
    SECTION 3: OTHER METHODS
    */
    void increment();
};