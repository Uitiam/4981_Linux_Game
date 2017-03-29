#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <string>

#include "../player/Marine.h"
#include "../turrets/Turret.h"
#include "../inventory/Inventory.h"
#include "../client/NetworkManager.h"
#include "../UDPHeaders.h"
#include "../game/GameManager.h"

constexpr int DOUBLE_COMPARISON_PRECISION = 0.00001;
constexpr int PLAYER_PLACE_DISTANCE = 100;

class Player {
public:


    void handleKeyboardInput(const Uint8 *state); // Handles player input with keyboard state
    void handleMouseUpdate(Window& w, float camX, float camY);

    void setControl(Marine& newControl);

    void handleMouseWheelInput(const SDL_Event *e);

    // Added by Mark.C 02/07/2017
    void handlePlacementClick(SDL_Renderer *renderer);

    void handleTempBarricade(SDL_Renderer *renderer);
    void handleTempTurret(SDL_Renderer *renderer);

    void sendServMoveAction();
    bool hasChangedAngle() const;
    bool hasChangedCourse() const;
    void setId(const int32_t newId) {id = newId;};
    Player();
    ~Player();

    //Stays as pointer cause the player gets a marine object after the ctor is called
    Marine *marine = nullptr;

private:
    int32_t id;
    int tempBarricadeID;
    int tempTurretID;
    bool holdingTurret;
    int pickupTick;
    int pickupDelay;
    ClientMessage moveAction;
};

#endif
