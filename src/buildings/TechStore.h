#ifndef TECHSTORE_H
#define TECHSTORE_H

#include <utility>
#include <SDL2/SDL.h>
#include <memory>
#include "Store.h"


class TechStore: public Store{
public:
    TechStore(const int32_t id, const SDL_Rect dest, const SDL_Rect pickupSize);

    ~TechStore();

    int32_t purchase(int num);//creates Tech and Tech drop for user
    int selectTech();//selected what Tech the user wants
    int32_t createTech(int num, float x, float y);
    int32_t createTurret(float x, float y);
    int32_t createBarricadeDrop(float x, float y);

private:

};

#endif
