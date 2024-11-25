/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** InputToGameEvent.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "events/UserCmd.hpp"
#include "GEngine/libdev/systems/driver/input/KeyboardCatcher.hpp"
#include "GEngine/libdev/Events.hpp"


namespace hiop::system {
class InputToGameEvent: public gengine::System<InputToGameEvent>, public gengine::LocalSystem {
public:
    void init(void) override;

    void moveUp(gengine::system::driver::input::KeyUpEvent &e);
    void moveLeft(gengine::system::driver::input::KeyLeftEvent &e);
    void moveDown(gengine::system::driver::input::KeyDownEvent &e);
    void moveRight(gengine::system::driver::input::KeyRightEvent &e);
    void shoot(gengine::system::driver::input::KeyWEvent &e);


    void updateDirectionBitmask(event::UserCmd::MvState state, bool pressed);
    event::UserCmd::MvState getMovementState(void);
    void sendEvents(gengine::system::event::GameLoop &e);


private:
    event::UserCmd::ShootState m_shootState = event::UserCmd::ShootState::SHOOT_NONE;
    char m_directionBitmask = 0;
    static constexpr char UP_MASK = 1 << 0;    // 0b0001
    static constexpr char RIGHT_MASK = 1 << 1; // 0b1000
    static constexpr char DOWN_MASK = 1 << 2;  // 0b0010
    static constexpr char LEFT_MASK = 1 << 3;  // 0b0100
};
}