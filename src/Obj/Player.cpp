/*
** EPITECH PROJECT, 2022
** player
** File description:
** player
*/

#include <iostream>
#include "const.hpp"
#include "raylib.h"
#include "Player.hpp"

Player::Player(const IdPlayer &aId, const Vector3 &pos, const KeyboardKey key[5])
{
    rotationAngle = 90.0;
    dead = false;
    animaitonposition = pos;
    position = pos;
    this->Id = aId;
    MaxBomb = 3;
    CanSetBomb = false;
    CurrentBomb = 0;
    animFrameCounter = 65;
    for (size_t i = 0; i < 5; ++i)
        allKey[i] = key[i];
    model = LoadModel("../resources/player/player.iqm");
    texture = LoadTexture(PathPlayer[int(aId)].c_str());
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    anims = LoadModelAnimations("../resources/player/player.iqm", &animsCount);
}

void Player::UpdataAnimation(KeyboardKey &inp)
{
    // move player when no key input(animation)
    if (!IsbuttonPressed) {
        if (animFrameCounter <= 65 || PlayerAction)
            animFrameCounter++, PlayerAction = true;
        if (animFrameCounter >= 68 || !PlayerAction)
            animFrameCounter--, PlayerAction = false;
    } else {
        animFrameCounter++;
        if (animFrameCounter >= anims[0].frameCount)
            animFrameCounter = 0;
    }
    // get direction
    if (input == KEY_NULL) {
        input = inp;
        IsbuttonPressed = inp == KEY_NULL ? false : true;
    }
    // update animaitonposition
    if (input == allKey[0]) {
        animaitonposition.x += 0.05f;
        moveCounter += 0.05f;
        rotationAngle = 180;
    } else if (input == allKey[1]) {
        animaitonposition.x -= 0.05f;
        moveCounter += 0.05f;
        rotationAngle = 0;
    } else if (input == allKey[2]) {
        animaitonposition.z += 0.05f;
        moveCounter += 0.05f;
        rotationAngle = 90;
    } else if (input == allKey[3]) {
        animaitonposition.z -= 0.05f;
        moveCounter += 0.05f;
        rotationAngle = -90;
    }

    if (moveCounter >= 1.0f || input == allKey[4]) {
        if (input == allKey[0])
            position.x += 1.0f;
        else if (input == allKey[1])
            position.x -= 1.0f;
        else if (input == allKey[2])
            position.z += 1.0f;
        else if (input == allKey[3])
            position.z -= 1.0f;
        animaitonposition = position;
        moveCounter = 0.0f;
        input = KEY_NULL;
    }
    //putbomb on the map
    if (inp == (allKey[4]) && CurrentBomb < MaxBomb && input == KEY_NULL) {
        CanSetBomb = true;
        CurrentBomb++;
    } else
        CanSetBomb = false;
    // bomb cd 6.0f seconds
    if (CurrentBomb > 0) {
        CdBomb -= 0.025f * MaxBomb;
        if (CdBomb <= 0.0f) {
            CurrentBomb--;
            CdBomb = 6.0f;
        }
    }
    //reset button
    for (size_t i = 0; i < 5; i++) {
        if (IsKeyReleased(allKey[i]))
            IsbuttonPressed = false;
    }
}

void Player::DrawAnimation()
{
    UpdateModelAnimation(model, anims[0], animFrameCounter);
    if (!dead)
        DrawModelEx(model, animaitonposition, (Vector3) { 0.0f, 1.0f, 0.0f }, rotationAngle, (Vector3) { 0.8f, 0.8f, 0.8f }, WHITE);
    else
        DrawModelEx(model, animaitonposition, (Vector3) { 0.0f, 0.0f, 1.0f }, 90.0f, (Vector3) { 0.8f, 0.8f, 0.8f }, WHITE);
}

Player::~Player()
{
    for (unsigned int i = 0; i < animsCount; i++)
        UnloadModelAnimation(anims[i]);
    UnloadModel(model); // Unload model
}