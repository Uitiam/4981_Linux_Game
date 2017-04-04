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
TechStore::TechStore(int32_t id, const SDL_Rect dest): Store(id, dest){

}


/*maitiu March 16*/
TechStore::~TechStore(){
    logv("Destoryed Store");
}

/* Creadt By Maitiu Morton April 4 2017
 * Creates
 */
int32_t TechStore::purchase(int num){
    /*GameManager *gm = GameManager::instance();
    if(gm->checkFreeDropPoints()){
        const int32_t dropPId = gm->getFreeDropPointId();
        const int32_t weaponId = createWeapon(num);

        DropPoint dp = gm->getDropPoint(dropPId);
        const float x = dp.getCoord().first;
        const float y = dp.getCoord().second;

        const int32_t wDropId = gm->createWeaponDrop(x, y, weaponId);

        logv("Purchased From WeaponStore\n");

        if(gm->weaponDropExists(wDropId)){
            gm->getWeaponDrop(wDropId).setDropPoint(dropPId);
        }
        return weaponId;
    }
    logv("NO OPEN DROP POINTS!!!\n");*/
    return -1;
}
