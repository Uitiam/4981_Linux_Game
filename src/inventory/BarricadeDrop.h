#ifndef BARRICADEDROP_H
#define BARRICADEDROP_H
#include "../collision/HitBox.h"
#include "../basic/Entity.h"
#include "../collision/CollisionHandler.h"
#include "weapons/Weapon.h"
#include "Drop.h"
#include <SDL2/SDL.h>

class BarricadeDrop: public Drop{
public:
    BarricadeDrop(int32_t id, const SDL_Rect &dest, const SDL_Rect &pickupSize, int32_t cId);

    ~BarricadeDrop();
private:
    int32_t barricadeId;
};



#endif
