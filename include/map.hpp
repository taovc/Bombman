/*
** EPITECH PROJECT, 2022
** map
** File description:
** map
*/

#pragma once

#include <vector>
#include <memory>
#include "const.hpp"
#include "wall.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

using namespace WallObj;

class Map {
private:
    Texture2D background;
    std::vector<std::unique_ptr<BombObj::Bomb>> AllBomb;
    std::vector<std::unique_ptr<Player>> AllPlayer;
    std::vector<std::unique_ptr<Wall>> wallBreakable;
    std::vector<KeyboardKey> aikey1;
    std::vector<KeyboardKey> aikey2;

    Wall wallUnbreakable[UNBREAKABLE_WALL_NB];
    KeyboardKey allKeyP1[5] = { KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_ENTER };
    KeyboardKey allKeyP2[5] = { KEY_D, KEY_A, KEY_S, KEY_W, KEY_SPACE };
    bool CheckPlayerCollision(const Vector3 &pos, const KeyboardKey &inp, const KeyboardKey key[5]);
    KeyboardKey GetInput(KeyboardKey &input, const KeyboardKey key[5], const int &i);
    bool CheckExplosion(const Vector3 &pos, const Vector3 &pos2);
    void PlayerCreate();
    void BombCreate();
    void PutWallBreakable(const Vector3 &pos);
    void RandomBreakableWall(void);
    void reset();
    KeyboardKey GetAIkey(const size_t &id, std::vector<KeyboardKey> &aikey);

public:
    Map();
    void DrawMap();
    void Update(SceneProcess &scene);
    void DrawBackground(void) const;
    ~Map();
};
