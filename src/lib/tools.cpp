/*
** EPITECH PROJECT, 2022
** outils
** File description:
** outils
*/

#include "libOutils.hpp"

template <typename T>

bool Libtools<T>::CheckCollision(T v1, T v2)
{
    if ((v1.x < v2.x - 0.25f || v1.x > v2.x + 0.25f)
    || (v1.z < v2.z - 0.25f || v1.z > v2.z + 0.25f))
        return false;
    return true;
}

