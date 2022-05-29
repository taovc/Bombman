/*
** EPITECH PROJECT, 2022
** wall
** File description:
** wall
*/

#include "raylib.h"
#include "wall.hpp"
#include "const.hpp"

using namespace WallObj;

Wall::Wall(const bool &isBreakable)
{
    this->isBreakable = isBreakable;
    textureWall = LoadTexture(
        this->isBreakable ? "../resources/map/breakable_wall.png"
                          : "../resources/map/unbreakable_wall.png");
    Awall = LoadModel("../resources/map/breakable_wall.mtl");
    SetMaterialTexture(&Awall.materials[0], MATERIAL_MAP_DIFFUSE, textureWall);
}

Wall::Wall()
{
    textureWall = LoadTexture("../resources/map/unbreakable_wall.png");
    Awall = LoadModel("../resources/map/breakable_wall.mtl");
    SetMaterialTexture(&Awall.materials[0], MATERIAL_MAP_DIFFUSE, textureWall);
}

Wall::~Wall()
{
    UnloadTexture(textureWall);
    UnloadModel(Awall);
}

const Vector3 &Wall::getPosition() const
{
    return positionWall;
}

void Wall::DrawWall(void) const
{
    DrawModel(Awall, positionWall, 1.0f, WHITE);
}

void Wall::setPosition(const Vector3 &pos)
{
    positionWall = pos;
}

void Wall::setBreakable(const bool &breakable)
{
    isBreakable = breakable;
}

bool Wall::getBreakable(void) const
{
    return isBreakable;
}
