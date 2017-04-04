//created 2/5/17 Maitiu
#include <memory>

#include "Inventory.h"
#include "../game/GameManager.h"
#include "../log/log.h"

Inventory::Inventory(): defaultGun(GameManager::instance()->generateID()),
        tempZombieHand(GameManager::instance()->generateID()) {
    weaponIds[0] = defaultGun.getID();
    weaponIds[1] = -1;
    weaponIds[2] = -1;
    GameManager::instance()->addWeapon(std::dynamic_pointer_cast<Weapon>(std::make_shared<HandGun>(defaultGun)));

}


void Inventory::switchCurrent(const int slot) {
    if (current != slot) {
        logv(3, "Switched to slot: %d\n", slot);
        current = slot;
    }
}

//Created By Maitiu
bool Inventory::pickUp(int32_t weaponId, const float x, const float y) {
    if (current == 0) {
        logv(3, "Can't Swap default gun \n");
        return false;
    }

    //drop Current Weapon

    dropWeapon(x, y);

    logv(3, "Picked up weapon\n");
    logv(3, "Swapped from %d ", weaponIds[current]);
    weaponIds[current] = weaponId;
    logv(3, "to %d\n\n", weaponIds[current]);
    return true;
}

//Created By Maitiu
Weapon* Inventory::getCurrent() {
    if (weaponIds[current] >= 0) {
        return GameManager::instance()->getWeapon(weaponIds[current]).get();
    }
    return nullptr;
}

void Inventory::useItem() {
    if (medkit != nullptr) {
        medkit->OnConsume();
        medkit = nullptr;
    }

}

//Created By Maitiu
void Inventory::scrollCurrent(int direction) {
    int currentTime = SDL_GetTicks();

    if (currentTime > (slotScrollTick + scrollDelay)) {
        slotScrollTick = currentTime;
        direction += current;
        if (direction < 0) {
            current = 2;
        } else if (direction > 2) {
            current = 0;
        } else {
            current = direction;
        }
        logv(3, "Switched to slot:%d\n", current);
    }

}

/**
 * DEVELOPER: Maitiu
 * DESIGNER: Maitiu
 * DATE:      March 29 2017
 * Checks is current CSLot has Weapon then Checks its ammo and creates a weaponDrop and renders it.
 */
 void Inventory::dropWeapon(const float x, const float y) {
     if(current){
         Weapon *w = getCurrent();
         if (w) {
             if (w->getAmmo() > 0) {
                 GameManager::instance()->createWeaponDrop(x,y, weaponIds[current]);

             } else {
                 //delete weapon From Weapon Manager
                 GameManager::instance()->removeWeapon(weaponIds[current]);
             }
             weaponIds[current] = -1;
         }
     }
 }


 /**
  * Date: Mar. 31, 2017
  * Author: Mark Tattrie
  * Function Interface:  void Inventory::initZombie()
  * Description:
  * function to initialize a zombies inventory
  */
 void Inventory::initZombie(){
     weaponIds[0] = tempZombieHand.getID();
     weaponIds[1] = -1;
     weaponIds[2] = -1;
     GameManager::instance()->addWeapon(std::dynamic_pointer_cast<Weapon>
            (std::make_shared<ZombieHand>(tempZombieHand)));
 }
