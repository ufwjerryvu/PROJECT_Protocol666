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
    Animator() {}
    ~Animator() {}

    /*
    SECTION 2: SETTER AND GETTER METHODS
    */
    void setAnimations(map<Type, Animation> animations);
    void setKey(Type key);
    void put(Type key, Animation value);
    Type getKey();
    vector<Type> getKeys();
    SDL_Texture *getCurrentFrame();

    /*
    SECTION 3: OTHER METHODS
    */
    bool increment();
    void reset();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/

/*
NOTE:
    - This section has to be defined inline because of the whole
    template-linker ordeal. Good thing is the constructors and
    destructors are empty so we don't need to worry too much about
    code bloating.
*/

/*
SECTION 2: SETTER AND GETTER METHODS
*/
template <typename Type>
void Animator<Type>::setAnimations(map<Type, Animation> animations)
{
    /*
    NOTE:
        - Sets the whole key to animation mapping.
    */
    this->animations = animations;
}

template <typename Type>
void Animator<Type>::setKey(Type key)
{
    /*
    NOTE:
        - Checking for `NULL` and throwing an exception and
        halting the entire program.
    */
    if (!this->animations.count(key))
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
        if (this->key == key)
        {
            /*
            NOTE:
                - Early return due to conciding key values. We
                do not want to reset the animation structure.
            */
            return;
        }
        this->animations[this->key].reset();
        this->key = key;
    }
}

template <typename Type>
void Animator<Type>::put(Type key, Animation value)
{
    /*
    NOTE:
        - Puts a key to animation mapping into the map. If it
        already exists then the standard behavior is the current
        value gets overwritten.
    */
    this->animations[key] = value;
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
SDL_Texture *Animator<Type>::getCurrentFrame()
{
    /*
    NOTE:
        - Gets the current frame of the current animation
        sequence mapped by the key.
    */
    if (!this->animations.count(this->key))
    {
        cerr << "Error: no key was set or invalid key." << endl;
    }
    return this->animations[this->key].getCurrentFrame();
}

/*
SECTION 3: OTHER METHODS
*/
template <typename Type>
bool Animator<Type>::increment()
{
    /*
    NOTE:
        - Increments the index of the current frame in the
        current animation sequence. Returns `true` if a cycle
        has been completed and `false` if otherwise.
    */
    return this->animations[this->key].increment();
}

template <typename Type>
void Animator<Type>::reset()
{
    /*
    NOTE:
        - Just resets the current animation to begin from index
        zero.
    */
    this->animations[this->key].reset();
}