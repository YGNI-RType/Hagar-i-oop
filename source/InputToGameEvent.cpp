/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** InputToGame.hpp
*/

#include "InputToGameEvent.hpp"

namespace hiop::system {
void InputToGameEvent::init(void) {
    subscribeToEvent<gengine::system::event::GameLoop>(&InputToGameEvent::sendEvents);
    subscribeToEvent<gengine::system::driver::input::KeyUpEvent>(&InputToGameEvent::moveUp);
    subscribeToEvent<gengine::system::driver::input::KeyLeftEvent>(&InputToGameEvent::moveLeft);
    subscribeToEvent<gengine::system::driver::input::KeyDownEvent>(&InputToGameEvent::moveDown);
    subscribeToEvent<gengine::system::driver::input::KeyRightEvent>(&InputToGameEvent::moveRight);
    subscribeToEvent<gengine::system::driver::input::KeyWEvent>(&InputToGameEvent::shoot);
}

void InputToGameEvent::shoot(gengine::system::driver::input::KeyWEvent &e) {
    switch (e.state) {
    case geg::event::io::InputState::PRESSED:
        m_shootState = event::UserCmd::ShootState::SHOOT;
        break;
    case geg::event::io::InputState::RELEASE:
        m_shootState = event::UserCmd::ShootState::SHOOT_NONE;
        break;
    default:
        break;
    }
}

void InputToGameEvent::moveUp(gengine::system::driver::input::KeyUpEvent &e) {
    switch (e.state) {
    case geg::event::io::InputState::PRESSED:
        updateDirectionBitmask(event::UserCmd::MvState::UP, true);
        break;
    case geg::event::io::InputState::RELEASE:
        updateDirectionBitmask(event::UserCmd::MvState::UP, false);
        break;
    default:
        break;
    }
}

void InputToGameEvent::moveLeft(gengine::system::driver::input::KeyLeftEvent &e) {
    switch (e.state) {
    case geg::event::io::InputState::PRESSED:
        updateDirectionBitmask(event::UserCmd::MvState::LEFT, true);
        break;
    case geg::event::io::InputState::RELEASE:
        updateDirectionBitmask(event::UserCmd::MvState::LEFT, false);
        break;
    default:
        break;
    }
}

void InputToGameEvent::moveDown(gengine::system::driver::input::KeyDownEvent &e) {
    switch (e.state) {
    case geg::event::io::InputState::PRESSED:
        updateDirectionBitmask(event::UserCmd::MvState::DOWN, true);
        break;
    case geg::event::io::InputState::RELEASE:
        updateDirectionBitmask(event::UserCmd::MvState::DOWN, false);
        break;
    default:
        break;
    }
}

void InputToGameEvent::sendEvents(gengine::system::event::GameLoop &e) {
    publishEvent(event::UserCmd(getMovementState(), m_shootState, event::UserCmd::SplitState::SPLIT_NONE)); // TODO add split
}

void InputToGameEvent::moveRight(gengine::system::driver::input::KeyRightEvent &e) {
    switch (e.state) {
    case geg::event::io::InputState::PRESSED:
        updateDirectionBitmask(event::UserCmd::MvState::RIGHT, true);
        break;
    case geg::event::io::InputState::RELEASE:
        updateDirectionBitmask(event::UserCmd::MvState::RIGHT, false);
        break;
    default:
        break;
    }
}

void InputToGameEvent::updateDirectionBitmask(event::UserCmd::MvState state, bool pressed) {
    char mask = 0;

    switch (state) {
    case event::UserCmd::MvState::UP:
        mask = UP_MASK;
        break;
    case event::UserCmd::MvState::RIGHT:
        mask = RIGHT_MASK;
        break;
    case event::UserCmd::MvState::DOWN:
        mask = DOWN_MASK;
        break;
    case event::UserCmd::MvState::LEFT:
        mask = LEFT_MASK;
        break;
    default:
        return;
    }

    if (pressed)
        m_directionBitmask |= mask;
    else
        m_directionBitmask &= ~mask;
}

event::UserCmd::MvState InputToGameEvent::getMovementState(void) {
    switch (m_directionBitmask) {
    case UP_MASK:
        return event::UserCmd::MvState::UP;
    case DOWN_MASK:
        return event::UserCmd::MvState::DOWN;
    case LEFT_MASK:
        return event::UserCmd::MvState::LEFT;
    case RIGHT_MASK:
        return event::UserCmd::MvState::RIGHT;
    case UP_MASK | LEFT_MASK:
        return event::UserCmd::MvState::UP_LEFT;
    case UP_MASK | RIGHT_MASK:
        return event::UserCmd::MvState::UP_RIGHT;
    case DOWN_MASK | LEFT_MASK:
        return event::UserCmd::MvState::DOWN_LEFT;
    case DOWN_MASK | RIGHT_MASK:
        return event::UserCmd::MvState::DOWN_RIGHT;
    default:
        return event::UserCmd::MvState::STANDING;
    }
}
}