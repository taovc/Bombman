/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** pause
*/

#include "pause.hpp"
#include "raylib.h"
#include "const.hpp"
#include <iostream>

PauseMenu::PauseMenu()
{
    background = LoadTexture("../resources/pause_bg.png");
    currentProcess = RESUME;
    mouseHoverRec = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i)
        toggleRecs[i] = (Rectangle) {120.0f, (float) (200 + 102 * i), 300.0f, 80.0f};
}

void PauseMenu::draw()
{
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTextureEx(background, (Vector2) { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        DrawRectangleLines((int)toggleRecs[i].x, (int)toggleRecs[i].y, (int)toggleRecs[i].width, (int)toggleRecs[i].height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        DrawText(processText[i].c_str(), (int)(toggleRecs[i].x + toggleRecs[i].width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, (int)toggleRecs[i].y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
    EndDrawing();
}

void PauseMenu::Loop(SceneProcess &CurrentScene)
{
    changeScene = false;
    mouseHoverRec = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
            mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                currentProcess = i;
                changeScene = true;
            }
            break;
        } else
            mouseHoverRec = -1;
    }
    // Keyboard toggle group logic
    if (IsKeyPressed(KEY_DOWN)) {
        currentProcess++;
        if (currentProcess > (NUM_PROCESSES - 1))
            currentProcess = 0;
    } else if (IsKeyPressed(KEY_UP)) {
        currentProcess--;
        if (currentProcess < 0)
            currentProcess = 2;
    }
    if (changeScene) {
        switch (currentProcess) {
        case RESUME:
            CurrentScene = GAME_SCENE;
            break;
        case PAUSE_HELP:
            CurrentScene = HELP_SCENE;
            break;
        case SCREEN:
            CurrentScene = MENU_SCENE;
            break;
        default:
            break;
        }
    }
}

void PauseMenu::free()
{
    UnloadTexture(background);
}
