/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** pause
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "IScene.hpp"
#include <string>
#include "raylib.h"

class PauseMenu : public IScene {
    private:
        Texture2D background;
        int currentProcess;
        int NUM_PROCESSES = 3;
        Rectangle toggleRecs[3];
        int mouseHoverRec = -1;
        bool changeScene = false;
        SceneProcess CurrentScene = GAME_SCENE;
        const std::string processText[3] = {
            "RESUME",
            "RESTART",
            "RETURN TO SCREEN",
        };
    public:
        PauseMenu();
        ~PauseMenu() {};
        SceneProcess getScene();
        void Loop(SceneProcess &CurrentScene);
        void init();
        void draw();
        void free();
};

#endif /* !PAUSE_HPP_ */
