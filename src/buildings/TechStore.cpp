#include "TechStore.h"
#include "../log/log.h"
#include "../game/GameManager.h"
#include "../inventory/weapons/Rifle.h"
#include "../inventory/weapons/ShotGun.h"
#include "../inventory/weapons/HandGun.h"
#include "DropPoint.h"
#include <memory>

/*
int32_t id of the Store
SDL_RECT dest the rect of the store
maitiu March 16*/
TechStore::TechStore(const int32_t id, const SDL_Rect dest, const SDL_Rect pickupSize): Store(id, dest, pickupSize){

}


/*maitiu March 16*/
TechStore::~TechStore(){
    logv("Destoryed Store");
}

/* Creadt By Maitiu Morton April 4 2017
 * Creates
 */
int32_t TechStore::purchase(int num){
    GameManager *gm = GameManager::instance();
    if(gm->checkFreeDropPoints()){
        const int32_t dropPId = gm->getFreeDropPointId();
        DropPoint dp = gm->getDropPoint(dropPId);
        const std::pair<float, float> coord = dp.getCoord();

        const int32_t id = createTech(num, coord.first, coord.second);

        logv("Purchased From TechStore\n");
        return id;
    }
    logv("NO OPEN DROP POINTS!!!\n");
    return -1;
}

int32_t TechStore::createTech(int num, float x, float y){
    GameManager *gm = GameManager::instance();
    int32_t id = gm->generateID();
    switch(num){
        case 1:
            //create turret
            createTurret(x,y);
            break;
        case 2:
        //make barricade and BArricade Drop
        createBarricadeDrop(x,y);
            break;
        default:
            return -1;//does not exist
    }

    return id;
}

int32_t TechStore::createBarricadeDrop(float x, float y){
    return -1;
}

int32_t TechStore::createTurret(float x, float y){
    return -1;
}
