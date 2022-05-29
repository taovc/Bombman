/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#pragma once
#include "IScene.hpp"
#include "raylib.h"
#include <string>

class menu : public IScene {
private:
    Texture2D background;
    int currentProcess;
    int NUM_PROCESSES = 3;
    Rectangle toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    SceneProcess CurrentScene = MENU_SCENE;
    const std::string processText[3] = {
        "START",
        "HELP",
        "SHOP",
    };

public:
    menu(/* args */);
    SceneProcess getScene();
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    ~menu() {};
};
