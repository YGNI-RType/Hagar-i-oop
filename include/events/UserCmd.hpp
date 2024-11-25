/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** UserCmd.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"

namespace hiop::event {
struct UserCmd: public gengine::Event {
    enum MvState { STANDING = 0, UP, RIGHT, DOWN, LEFT, UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT} mvState;
    enum ShootState { SHOOT_NONE = 0, SHOOT} shootState;
    enum SplitState { SPLIT_NONE = 0, SPLIT} splitState;

    UserCmd(MvState mvState, ShootState shootState, SplitState splitState)
        : mvState(mvState)
        , shootState(shootState)
        , splitState(splitState) {
    }
};
}