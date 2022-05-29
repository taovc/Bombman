/*
** EPITECH PROJECT, 2022
** player
** File description:
** player
*/

#pragma once
#include <cstddef>
#include "raylib.h"
#include "Bomb.hpp"

class Player {
public:
    Player(const IdPlayer &Id, const Vector3 &pos, const KeyboardKey key[5]);
    ~Player();
    void UpdataAnimation(KeyboardKey &inp);
    void DrawAnimation();
    bool CheckPlayerCollision() const;
    bool CanSetBomb;
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    IdPlayer Id;
    bool dead;

private:
    Vector3 animaitonposition = { 0.0f, 0.0f, 0.0f };
    float CdBomb = 6.0f;
    size_t CurrentBomb;//for marking the number of the bomb on the map
    size_t MaxBomb;//for marking the number of the max bomb
    KeyboardKey allKey[5];
    const std::string PathPlayer[6] = {
        "../resources/player/textures/blue.png",
        "../resources/player/textures/cyan.png",
        "../resources/player/textures/green.png",
        "../resources/player/textures/purple.png",
        "../resources/player/textures/red.png",
        "../resources/player/textures/yellow.png",
    };
    KeyboardKey input = KEY_NULL;
    bool IsbuttonPressed = false;
    float moveCounter = 0.0f;
    ModelAnimation *anims;
    Model model;
    Texture2D texture;
    size_t animFrameCounter = 0;
    unsigned int animsCount = 0;
    bool PlayerAction = true; // the animation when player not move
    float rotationAngle = 0.0f;
};
