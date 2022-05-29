/*
** EPITECH PROJECT, 2022
** help
** File description:
** help
*/

#include <iostream>
#include "raylib.h"
#include "help.hpp"
#include "const.hpp"

help::help()
{
    mouseHoverRec = -1;
    background[ABOUT] = LoadTexture("../resources/about.png");
    background[COMMANDS] = LoadTexture("../resources/commands.png");
    currentProcess = BACK;
    toggleRecs[BACK] = (Rectangle) { 80, (20), 300.0f, 80.0f };
    toggleRecs[NEXT] = (Rectangle) { 1200.0f, (800), 300.0f, 80.0f };
    toggleRecs[PREVIOUS] = (Rectangle) { 80, (800), 300.0f, 80.0f };
}

void help::draw()
{
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTextureEx(background[CurrentPage], (Vector2) { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        DrawRectangleLines((int)toggleRecs[i].x, (int)toggleRecs[i].y, (int)toggleRecs[i].width, (int)toggleRecs[i].height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        DrawText(processText[i].c_str(), (int)(toggleRecs[i].x + toggleRecs[i].width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, (int)toggleRecs[i].y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
    EndDrawing();
}

void help::Loop(SceneProcess &CurrentScene)
{
    mouseHoverRec = -1;
    changeScene = false;
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
        case BACK:
            CurrentScene = MENU_SCENE;
            break;
        case NEXT:
            CurrentPage = COMMANDS;
            break;
        case PREVIOUS:
            CurrentPage = ABOUT;
            break;
        default:
            break;
        }
    }
}

help::~help()
{
    for (unsigned short i = 0; i < HELP_PAGE_NB; ++i)
        UnloadTexture(background[i]);
}
