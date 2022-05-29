/*
** EPITECH PROJECT, 2022
** game
** File description:
** game
*/

#include "const.hpp"
#include "raylib.h"
#include "gameloop.hpp"
#include <iostream>

GameLoop::GameLoop()
{
    camera = { { 0.0f, 20.0f, 10.0f }, { 0.0, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 40.0f, 0 };
    std::unique_ptr<Map> tmp(new Map());
    std::unique_ptr<PauseMenu> pausemenu(new PauseMenu());
    map = std::move(tmp);
    pause = std::move(pausemenu);
}

void GameLoop::Loop(SceneProcess &scene)
{
    // update
    map->Update(scene);
}

void GameLoop::draw()
{
    BeginDrawing();
    map.get()->DrawBackground();
    ClearBackground(BLACK);
    BeginMode3D(camera);
    map->DrawMap();
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

GameLoop::~GameLoop()
{
}
