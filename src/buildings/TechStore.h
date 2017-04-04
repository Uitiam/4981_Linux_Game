#ifndef TECHSTORE_H
#define TECHSTORE_H

#include <utility>
#include <SDL2/SDL.h>
#include <memory>
#include "Store.h"


class TechStore: public Store{
public:
    TechStore(int32_t id, const SDL_Rect dest);

    ~TechStore();

    int32_t purchase(int num);//creates Tech and Tech drop for user
    int selectTech();//selected what Tech the user wants

private:

};

#endif
