/*
** EPITECH PROJECT, 2022
** gameloop
** File description:
** gameloop
*/

#pragma once

#include "pause.hpp"
#include "IScene.hpp"
#include "raylib.h"
#include "map.hpp"

class GameLoop : public IScene {

private:
    Camera camera;
    std::unique_ptr<PauseMenu> pause;
    // class player
    std::unique_ptr<Map> map;

public:
    GameLoop();
    SceneProcess getScene();
    void Loop(SceneProcess &scene);
    void draw();
    ~GameLoop();
};
