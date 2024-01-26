#include "Animator.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
template <typename Type>
Animator<Type>::Animator(map<Type, Animation> animations)
{
    /*
    NOTE:
        - Just an initializing constructor.
    */
    this->animations = animations;
}

template <typename Type>
Animator<Type>::~Animator()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTER AND GETTER METHODS
*/
template <typename Type>
void Animator<Type>::setKey(Type key)
{
    /*
    NOTE:
        - Checking for `NULL` and throwing an exception and
        halting the entire program.
    */
    if (this->animations[key] == NULL)
    {
        cerr << "Error: invalid key to animator." << endl;
        assert(false);
    }
    else
    {
        /*
        NOTE:
            - If we've switched keys, we've gotta reset the
            animation index of the current animation sequence
            before assigning the new key.
        */
        this->animations[this->key].reset();
        this->key = key;
    }
}

template <typename Type>
Type Animator<Type>::getKey()
{
    /*
    NOTE:
        - Gets the current key that maps to the animation
        sequence.
    */
    return this->key;
}

template <typename Type>
vector<Type> Animator<Type>::getKeys()
{
    /*
    NOTE:
        - Retrieves the key of a map and stores it into a
        generic vector. Code modified from StackOverflow.
    */
    map<Type, Animation> mapped = this->animations;
    vector<Type> keys;
    
    for (auto it = mapped.begin(); it != mapped.end(); ++it)
    {
        keys.push_back(it->first);
    }

    return keys;
}

template <typename Type>
SDL_Texture *Animator<Type>::getCurrentFrame(){
    /*
    NOTE:
        - Gets the current frame of the current animation
        sequence mapped by the key.
    */
   return this->animations[this->key].getCurrentFrame();
}

/*
SECTION 3: OTHER METHODS
*/
template <typename Type>
void Animator<Type>::increment(){
    /*
    NOTE:
        - Increments the index of the current frame in the
        current animation sequence.
    */
    this->animations[this->key].increment();
}