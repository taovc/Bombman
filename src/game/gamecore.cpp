/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#include <stdlib.h>
#include <iostream>
#include "gameCore.hpp"
#include "indielib.hpp"

void game_loop(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Bomberman");
    Core gamecore;
    SceneProcess CurrentScene = MENU_SCENE;

    SetTargetFPS(60);
    auto scene = gamecore.current[CurrentScene].get();
    while (!WindowShouldClose()) {
        scene->Loop(CurrentScene);
        scene = gamecore.current[CurrentScene].get();
        scene->draw();
    }
    gamecore.~Core();
    CloseWindow();
}
