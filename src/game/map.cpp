/*
** EPITECH PROJECT, 2022
** map
** File description:
** map
*/

#include <iostream>
#include<cmath>
#include "const.hpp"
#include "map.hpp"
#include "pause.hpp"
#include "raylib.h"

using namespace WallObj;

static bool is_spawn(const float &i, const float &t)
{
    if (i == -6 || i == 6)
        if (t == -6 || t == -5 || t == 6 || t == 5)
            return true;
    if (i == -5 || i == 5)
        if (t == -6 || t == 6)
            return true;
    return false;
}

void Map::RandomBreakableWall(void)
{
    bool has_found = false;

    for (float i = -6; i < 7; ++i) {
        for (float t = -6; t < 7; ++t) {
            has_found = false;
            if (is_spawn(i, t))
                continue;
            Vector3 pos = { i, 0, t };
            for (int k = 0; k < UNBREAKABLE_WALL_NB; ++k)
                if (pos == WallPositions[k])
                    has_found = true;
            if (!has_found && (std::rand() % 10) >= 3) // (10 - 3 = 7, so 70% luck)
                PutWallBreakable({ i, 0, t });
        }
    }
}

Map::Map()
{
    background = LoadTexture("../resources/map/background.png");
    PlayerCreate();
    BombCreate();

    for (size_t i = 0; i < UNBREAKABLE_WALL_NB; ++i) {
        wallUnbreakable[i].setBreakable(false);
        wallUnbreakable[i].setPosition(WallPositions[i]);
    }
    //RandomBreakableWall();
}

bool Map::CheckPlayerCollision(const Vector3 &pos, const KeyboardKey &inp, const KeyboardKey key[5])
{
    Vector3 tmp = pos;

    if (inp == key[0]) {
        tmp.x += 1.0f;
    } else if (inp == key[1]) {
        tmp.x -= 1.0f;
    } else if (inp == key[2]) {
        tmp.z += 1.0f;
    } else if (inp == key[3]) {
        tmp.z -= 1.0f;
    }
    for (size_t i = 0; i < UNBREAKABLE_WALL_NB; ++i) {
        if (wallUnbreakable[i].getPosition() == tmp)
            return false;
    }
    for (size_t i = 0; i < AllBomb.size(); ++i) {
        if (AllBomb[i].get()->positions == tmp)
            return false;
    }
    for (size_t i = 0; i < wallBreakable.size(); ++i) {
        if (wallBreakable[i].get()->getPosition() == tmp)
            return false;
    }
    return true;
}

KeyboardKey Map::GetInput(KeyboardKey &input, const KeyboardKey key[5], const int &i)
{
    input = KEY_NULL;
    if (IsKeyDown(key[0]) && CheckPlayerCollision(AllPlayer[i].get()->position, key[0], key)) {
        input = key[0];
    } else if (IsKeyDown(key[1]) && CheckPlayerCollision(AllPlayer[i].get()->position, key[1], key)) {
        input = key[1];
    } else if (IsKeyDown(key[2]) && CheckPlayerCollision(AllPlayer[i].get()->position, key[2], key)) {
        input = key[2];
    } else if (IsKeyDown(key[3]) && CheckPlayerCollision(AllPlayer[i].get()->position, key[3], key)) {
        input = key[3];
    } else if (IsKeyReleased(key[4]))
        input = key[4];
    return input;
}

bool Map::CheckExplosion(const Vector3 &pos1, const Vector3 &pos2)
{
    if ((pos2.x < pos1.x + 1.25f && pos2.x > pos1.x - 1.25f && pos1.z == pos2.z)
        || (pos2.z < pos1.z + 1.25f && pos2.z > pos1.z - 1.25f && pos1.x == pos2.x))
        return false;
    return true;
}

KeyboardKey Map::GetAIkey(const size_t &id, std::vector<KeyboardKey> &aikey)
{
    // bomb handling
    auto player = AllPlayer[id].get();
    if (player->dead)
        return KEY_NULL;
    bool find = false;
    auto tmpPosition = player->position;

    //algo for dodge bombs
    for (size_t i = 0; i < AllBomb.size(); ++i) {
        auto bomb = AllBomb[i].get()->positions;
        auto posX = player->position.x - bomb.x;
        auto posZ = player->position.z - bomb.z;
        //negative is bomb at rigth the AI
        if ((posX >=0.75 || posX <= -0.75) && posZ == 0) {
            if (CheckPlayerCollision(tmpPosition, KEY_UP, allKeyP1)) {
                aikey.emplace_back(KEY_UP);
                break;
            } else if (CheckPlayerCollision(tmpPosition, KEY_DOWN, allKeyP1)) {
                aikey.emplace_back(KEY_DOWN);
                break;
            } else if (posX <= -0.75) {
                if (CheckPlayerCollision(tmpPosition, KEY_LEFT, allKeyP1)) {
                    tmpPosition.x -= 1.0f;
                    aikey.emplace_back(KEY_LEFT);
                }
            } else if (posX >= 0.75f) {
                if (CheckPlayerCollision(tmpPosition, KEY_RIGHT, allKeyP1)) {
                    tmpPosition.x += 1.0f;
                    aikey.emplace_back(KEY_RIGHT);
                }
            }

        } else if ((posZ >=0.75 || posZ <= -0.75) && posX == 0) {
            if (CheckPlayerCollision(tmpPosition, KEY_LEFT, allKeyP1)) {
                aikey.emplace_back(KEY_LEFT);
                break;
            } else if (CheckPlayerCollision(tmpPosition, KEY_RIGHT, allKeyP1)) {
                aikey.emplace_back(KEY_RIGHT);
                break;
            } else if (posZ <= -0.75) {
                if (CheckPlayerCollision(tmpPosition, KEY_UP, allKeyP1)) {
                    tmpPosition.z -= 1.0f;
                    aikey.emplace_back(KEY_UP);
                }
            } else if (posZ >= 0.75f) {
                if (CheckPlayerCollision(tmpPosition, KEY_DOWN, allKeyP1)) {
                    tmpPosition.z += 1.0f;
                    aikey.emplace_back(KEY_DOWN);
                }
            }

        }
    }

    if (aikey.size() == 0)
        return KEY_NULL;
    KeyboardKey tmp = aikey[0];
    aikey.erase(aikey.begin());
    return tmp;
}

void Map::Update(SceneProcess &scene)
{
    KeyboardKey inputList[4] = {};

    // get input and send to player
    inputList[0] = GetInput(inputList[0], allKeyP1, 0);
    inputList[1] = GetInput(inputList[1], allKeyP2, 1);
    inputList[2] = GetAIkey(2, aikey1);
    //inputList[4] = GetAIkey(4);

    // check the bomb explotion, if player touch explotion set player->dead = true
    for (size_t i = 0; i < AllBomb.size(); ++i) {
        // for all player , if touch bomb fire , set player dead
        for (size_t j = 0; j < AllPlayer.size(); j++) {
            if (AllPlayer[j].get()->dead)
                continue;
            if (AllBomb[i].get()->Active &&
            !CheckExplosion(AllBomb[i].get()->positions, AllPlayer[j].get()->position)) {
                AllPlayer[j].get()->dead = true;
                break;
            }
        }
        // for all wall breakable, if touch bomb fire, delete wall
        for (size_t j = 0; j < wallBreakable.size(); j++) {
            if (AllBomb[i].get()->Active && !CheckExplosion(AllBomb[i].get()->positions, wallBreakable[j].get()->getPosition())) {
                wallBreakable.erase(wallBreakable.begin() + j);
            }
        }
    }

    // update animation player if player not dead
    for (size_t i = 0; i < AllPlayer.size(); ++i) {
        if (AllPlayer[i].get()->dead == true)
            continue;
        AllPlayer[i]->UpdataAnimation(inputList[i]);
        // set bomb for all player
        if (AllPlayer[i]->CanSetBomb && i < 2) {
            for (size_t j = 3 * i; j < 3 + 3 * i; ++j) {
                if (!(AllBomb[j].get()->positions != NULL_Position)) {
                    AllBomb[j]->putBomb(AllPlayer[i]->position, AllPlayer[i]->Id, 2.0f);
                    break;
                }
            }
        }
    }
    // update scene
    /*for (size_t i = 0; i < AllPlayer.size(); ++i) {
        if (AllPlayer[i].get()->dead == true) {
            this->reset();
            scene = MENU_SCENE;
        }
    }*/
}

void Map::reset()
{
    std::vector<std::unique_ptr<BombObj::Bomb>>().swap(AllBomb);
    std::vector<std::unique_ptr<Player>>().swap(AllPlayer);
    std::vector<std::unique_ptr<Wall>>().swap(wallBreakable);

    PlayerCreate();
    BombCreate();
    RandomBreakableWall();
}

void Map::DrawMap()
{

    for (size_t i = 0; i < AllPlayer.size(); ++i) {
        AllPlayer[i]->DrawAnimation();
    }
    for (size_t j = 0; j < AllBomb.size(); ++j) {
        AllBomb[j]->DrawBomb();
    }
    for (size_t i = 0; i < UNBREAKABLE_WALL_NB; ++i) {
        wallUnbreakable[i].DrawWall();
    }
    for (size_t i = 0; i < wallBreakable.size(); ++i) {
        wallBreakable[i]->DrawWall();
    }
}

void Map::BombCreate()
{
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::CYAN_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::CYAN_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::CYAN_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
}

void Map::PutWallBreakable(const Vector3 &pos)
{
    std::unique_ptr<Wall> wall(new Wall(true));
    wall->setPosition(pos);
    wallBreakable.emplace_back(std::move(wall));
}

void Map::PlayerCreate()
{
    AllPlayer.emplace_back(new Player(IdPlayer::BLUE_P, { 6.0, 0.0, 6.0 }, allKeyP1));
    AllPlayer.emplace_back(new Player(IdPlayer::CYAN_P, { -6.0, 0.0, 6.0 }, allKeyP2));
    AllPlayer.emplace_back(new Player(IdPlayer::PURPLE_P, { 3.0, 0.0, 6.0 }, allKeyP1));
    //AllPlayer.emplace_back(new Player(IdPlayer::GREEN_P, { -6.0, 0.0, -6.0 }, allKeyP1));
}

void Map::DrawBackground(void) const
{
    DrawTextureEx(background, (Vector2) { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
}

Map::~Map()
{
    UnloadTexture(background);
}