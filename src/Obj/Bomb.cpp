/*
** EPITECH PROJECT, 2022
** bomb
** File description:
** bomb
*/

#include <iostream>
#include "Bomb.hpp"
#include "const.hpp"

using namespace BombObj;

Bomb::Bomb(const IdPlayer &id, const BombType_e &type)
{
    positions = NULL_Position;
    Active = false;
    model = LoadModel("../resources/bombs/bomb.obj");
    texture = LoadTexture(PathBombPng[type].c_str());
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    // set explotion
    Explosion = LoadModel("../resources/bombs/explosion/explosion.mtl");
    ExploTexture = LoadTexture("../resources/bombs/explosion/blast.png");
    SetMaterialTexture(&Explosion.materials[0], MATERIAL_MAP_DIFFUSE, ExploTexture);
    this->owner = owner;
}

const IdPlayer &Bomb::getOwner() const
{
    return owner;
}

void Bomb::setOwner(const IdPlayer &id)
{
    this->owner = owner;
}

void Bomb::DrawBomb()
{
    if (Counter <= 0.0f && Active == false)
        Active = true;
    if (Counter <= -1.0f && Active == true) {//after exploration reset all
        Active = false;
        positions = NULL_Position;
    }
    if (positions != NULL_Position)
        Counter -= 0.025f;
    if (!Active)
        DrawModel(model, positions, 1.0f, WHITE);
    if (Active) {
        for (size_t i = 0; i < sizeExplo; i++) {
            DrawModel(Explosion, {positions.x, 0.0f, positions.z - i}, 1.0f, WHITE);
            DrawModel(Explosion, {positions.x, 0.0f, positions.z + i}, 1.0f, WHITE);
            DrawModel(Explosion, {positions.x + i, 0.0f, positions.z}, 1.0f, WHITE);
            DrawModel(Explosion, {positions.x - i, 0.0f, positions.z}, 1.0f, WHITE);
        }
    }
}

void Bomb::operator=(const Vector3 &positions)
{
    this->positions.x = positions.x;
    this->positions.y = positions.y;
    this->positions.z = positions.z;
}

bool Bomb::putBomb(const Vector3 &positions, const IdPlayer &id, float size)
{
    Active = false;
    Counter = 4.0f;
    this->sizeExplo = size;
    this->owner = id;
    operator=(positions);
    return true;
}

Bomb::~Bomb()
{
    UnloadTexture(texture);
    UnloadModel(model);
}