/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** const
*/

#pragma once
#include <string>
#include "raylib.h"

#define PUT_ERROR(msg)                                     \
    std::cerr << "\033[1;31m/******************/\033[0m\n" \
              << "\033[1;31mERROR :\033[0m\n"              \
              << "File : "                                 \
              << __FILE__ << "\n"                          \
              << "Line : "                                 \
              << __LINE__ << "\n"                          \
              << "Function : "                             \
              << __FUNCTION__ << "\n"                      \
              << "Message : "                              \
              << msg << "\n"                               \
              << "\033[1;31m/******************/\033[0m" << std::endl;

static const unsigned char GOOD = 0;
static const unsigned char ERROR = 84;
static const char FAIL = -1;
static const unsigned short SCREEN_WIDTH = 1600;
static const unsigned short SCREEN_HEIGHT = 900;
static const unsigned short SCENE_LENGTH = 4;

typedef enum SceneProcess_e {
    NULL_SCENE = -1,
    MENU_SCENE = 0,
    HELP_SCENE,
    GAME_SCENE,
} SceneProcess;

typedef enum PauseProcess_e {
    RESUME = 0,
    PAUSE_HELP,
    SCREEN,
} PauseProcess;

typedef enum ImageProcess_e {
    START = 0,
    HELP,
} ImageProcess;

typedef enum HelpProcess_e {
    BACK = 0,
    NEXT,
    PREVIOUS,
} HelpProcess;

typedef enum HelpPage_e {
    ABOUT,
    COMMANDS,
    HELP_PAGE_NB
} HelpPage;

typedef enum Bonus_e {
    BombUp,
    SpeedUp,
    FireUp,
    WallPass,
} Bonus;

static const Vector3 NULL_Position = {-999.0f, -999.0f, -999.0f};

static const bool operator==(Vector3 v1, Vector3 v2)
{
    if ((v1.x < v2.x - 0.25f || v1.x > v2.x + 0.25f)
    || (v1.z < v2.z - 0.25f || v1.z > v2.z + 0.25f))
        return false;
    return true;
}

static const bool operator!=(Vector3 v1, Vector3 v2)
{
    return !operator==(v1, v2);
}
