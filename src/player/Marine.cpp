#include "Marine.h"
#include <cstdlib>
#include "../game/GameManager.h"
#include "../log/log.h"

Marine::Marine(const int32_t id, const SDL_Rect& dest, const SDL_Rect& movementSize,
        const SDL_Rect& projectileSize, const SDL_Rect& damageSize)
: Entity(id, dest, movementSize, projectileSize, damageSize),
        Movable(id, dest, movementSize, projectileSize, damageSize, MARINE_VELOCITY) {
    logv("Create Marine\n");
}

Marine::~Marine() {
    logv("Destroy Marine\n");
}

void Marine::onCollision() {
    // Do nothing for now
}

void Marine::collidingProjectile(const int damage) {
    health -= damage;
    if (health <= 0){
        GameManager::instance()->deleteMarine(getId());
    }
}

// Created by DericM 3/8/2017
void Marine::fireWeapon() {
    Weapon *w = inventory.getCurrent();
    if(w) {
        w->fire(*this);
    } else {
        logv("Slot Empty\n");
    }
}


/*
 * Created By Maitiu
 * Modified: Mar. 15 2017 - Mark Tattrie
 * Description: Checks The pick up Hitboxes of the Weapon Drops and Turrets to see if the player's
 * Marine is touching them IF Touching a Weapon Drop it Calls the Inventory Pick up method.
 */
int32_t Marine::checkForPickUp() {
    int32_t pickId = -1;
    GameManager *gm = GameManager::instance();
    CollisionHandler& ch = gm->getCollisionHandler();

    Entity *ep = ch.detectPickUpCollision(ch.getQuadTreeEntities(ch.quadtreeStore,this),this);
    if(ep){
        activateStore(ep);
        return -1;
    }
    ep = ch.detectPickUpCollision(ch.getQuadTreeEntities(ch.quadtreePickUp,this),this);
    if(ep) {
        //get Entity drop Id
        pickId = ep->getId();
        logv("Searching for id:%d in weaponDropManager\n", pickId);
        // checks if Id matches any turret Ids in turretManager, if yes, then return with the Id
        if (gm->getTurretManager().count(pickId)) {
            return pickId;
        }
        //Checks if WeaponDrop exists
        if(gm->weaponDropExists(pickId)) {
            const WeaponDrop& wd = gm->getWeaponDrop(pickId);
            //Get Weaopn id from weapon drop
            pickId = wd.getWeaponId();
            //Picks up Weapon
            if(inventory.pickUp(pickId, wd.getX(), wd.getY())) {
                int32_t DropPoint = wd.getDropPoint();
                if(DropPoint != -1){
                    gm->freeDropPoint(DropPoint);
                }
                gm->deleteWeaponDrop(wd.getId());
            }
        } else {
            logv("unable to find id:%d in weaponDropManager\n", pickId);
        }
    } else {
        loge("Pick id was nullptr\n");
    }
    return -1;
}

/**
* Date: Mar 27
* Author: Aing Ragunathan
*
* Interface: void Marine::updateImageDirection()
*
* Description:
*       This function changes the direction that the character is facing.
*       It is called from GameStateMatch::handle after every frame and
*       updates the direction of the sprite according to the angle of the
*       mouse from the center of the screen.
*/
void Marine::updateImageDirection() {
    const double radians = (getAngle() -90) * M_PI/180;

    //order: start from ~0 rad, counter clockwise
    if (radians > SPRITE_ANGLE2 && radians < SPRITE_ANGLE1) {
        setSrcRect(getSrcRect().x, SPRITE_RIGHT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE3 && radians < SPRITE_ANGLE2) {
        setSrcRect(getSrcRect().x, SPRITE_BACK_RIGHT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE4 && radians < SPRITE_ANGLE3) {
        setSrcRect(getSrcRect().x, SPRITE_BACK, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE5 && radians < SPRITE_ANGLE4) {
        setSrcRect(getSrcRect().x, SPRITE_BACK_LEFT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE6 && radians < SPRITE_ANGLE5) {
        setSrcRect(getSrcRect().x, SPRITE_LEFT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE7 && radians < SPRITE_ANGLE6) {
        setSrcRect(getSrcRect().x, SPRITE_FRONT_LEFT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians < SPRITE_ANGLE7) {
        setSrcRect(getSrcRect().x, SPRITE_FRONT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    } else if (radians > SPRITE_ANGLE1 && radians < SPRITE_ANGLE8) {
        setSrcRect(getSrcRect().x, SPRITE_FRONT_RIGHT, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    }
}

/**
* Date: Mar 30
* Author: Aing Ragunathan
*
* Function Interface: void Marine::updateImageWalk(double frameCount)
*       double frameCount - counted frames while walking
*
* Description:
*       This function repeatedly updates the image of the marine in order to animate
*       walking. It is called from GameStateMatch::handle after every frame and updates
*       the feet placement of the marine.
*/
void Marine::updateImageWalk(const Uint8 *state) {
    static unsigned long frameCount = 0;
    ++frameCount;
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        //stops lag when taking first step
        if (getSrcRect().x == SPRITE_FRONT) {
            setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
        } else if (frameCount % FRAME_COUNT_WALK == 0) {
            //cycle throught the walking images
            if (getSrcRect().x < SPRITE_NEXT_STEP) {
                setSrcRect(getSrcRect().x + SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            } else {
                setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            }
        }
    } else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        if (getSrcRect().x == SPRITE_FRONT) {
            setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
        } else if (frameCount % FRAME_COUNT_WALK == 0) {
            if (getSrcRect().x < SPRITE_NEXT_STEP) {
                setSrcRect(getSrcRect().x + SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            } else {
                setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            }
        }
    } else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        if (getSrcRect().x == SPRITE_FRONT) {
            setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
        } else if (frameCount % FRAME_COUNT_WALK == 0) {
            if (getSrcRect().x < SPRITE_NEXT_STEP) {
                setSrcRect(getSrcRect().x + SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            } else {
                setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            }
        }
    } else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        if (getSrcRect().x == SPRITE_FRONT) {
            setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
        } else if (frameCount % FRAME_COUNT_WALK == 0) {
            if (getSrcRect().x < SPRITE_NEXT_STEP) {
                setSrcRect(getSrcRect().x +SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            } else {
                setSrcRect(SPRITE_SIZE_X, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
            }
        }
    } else {
        setSrcRect(SPRITE_FRONT, getSrcRect().y, SPRITE_SIZE_X, SPRITE_SIZE_Y);
    }
}

/*
 *Create by Maitiu March 30
 * Takes in an Entity that is a store and attempts a purchase
 */
void Marine::activateStore(const Entity *ep){
    GameManager *gm = GameManager::instance();
    if(gm->storeExists(ep->getId())){
        int r = rand()% 2 + 1;//random number temp for testing

        gm->getStore(ep->getId())->purchase(r);
    }
}
