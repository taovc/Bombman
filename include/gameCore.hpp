/*
** EPITECH PROJECT, 2022
** gamecore
** File description:
** core
*/

#pragma once
#include <memory>
#include "indielib.hpp"

class Core {
private:

public:
    std::unique_ptr<IScene> current[SCENE_LENGTH] { // all scene
        std::make_unique<menu>(),
        std::make_unique<help>(),
        std::make_unique<GameLoop>(),
    };
    // function
    Core(/* args */) {};
    ~Core() {};
};
