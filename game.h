
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

#include "view.h"
#include <windows.h>
#include <vector>
using namespace std;

class Player {
public:
    int percentX;
    int percentY;
    bool isJumping;
    int jumpEnergy;
    bool isDead;

    Player() {
        this->percentX = 20;
        this->percentY = 50;
        this->isJumping = false;
        this->jumpEnergy = 0;
        this->isDead = false;
    }

    bool hasTouchedGround()
    {
        return this->percentY >= 88;
    }

    bool hasTouchedCeiling()
    {
        return this->percentY <= 12;
    }

    void fall() {
        this->percentY++;
        if (this->hasTouchedGround())
        {
            this->isDead = true;
        }
    }

    void startJump()
    {
        this->isJumping = true;
        this->jumpEnergy = 20;
    }

    void rise()
    {
        if (this->isJumping && this->jumpEnergy > 0)
        {
            this->jumpEnergy--;
            this->percentY--;

            if (this->hasTouchedCeiling())
            {
                this->isDead = true;
            }
            if (this->jumpEnergy == 0)
            {
                this->isJumping = false;
            }
        }
    }
};

#define OBSTACLE_WIDTH 30
#define OBSTACLE_HEIGHT 100

class Obstacle
{
public:
    int percentX;
    bool isAtBottom;
    int colorR, colorG, colorB;

    Obstacle()
    {
        this->isAtBottom = (bool)(rand() % 2);
        this->percentX = 100;
        this->colorR = rand() % 255;
        this->colorG = rand() % 255;
        this->colorB = rand() % 255;
    }

    void moveLeft()
    {
        this->percentX--;
    }

    bool hasReachedLeft()
    {
        return OBSTACLE_WIDTH >= ((this->percentX * GAME_VIEW_WIDTH) / 100);
    }
};

struct GameState {
    bool hasStarted;
    bool hasFinished;
    bool isPaused;

    int score;

    Player* player;
    vector<Obstacle*>obstacles;
};

DWORD WINAPI jettThread(void* _renderer);

DWORD WINAPI obstacleCreatorThread(void* _renderer);

DWORD WINAPI obstacleMoverThread(void* _renderer);

void initGame();

void startGame(SDL_Renderer* renderer);

void stopGame();

bool hasGameEnded();

bool isGameRunning();

bool hasGameStarted();

Player* getPlayer();

void generateObstacle();

#endif //JJGAME_GAME_H
