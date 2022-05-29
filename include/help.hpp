/*
** EPITECH PROJECT, 2022
** help
** File description:
** help
*/

#pragma once
#include "IScene.hpp"
#include "raylib.h"

class help : public IScene {
private:
    Texture2D background[HELP_PAGE_NB];
    int currentProcess;
    int NUM_PROCESSES = 3;
    Rectangle toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    SceneProcess CurrentScene = HELP_SCENE;
    const std::string processText[3] = { "BACK", "NEXT", "PREVIOUS" };
    HelpPage CurrentPage = ABOUT;

public:
    help(/* args */);
    SceneProcess getScene();
    void Loop(SceneProcess &scene);
    void draw();
    ~help();
};
