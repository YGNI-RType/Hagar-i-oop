/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellCollision.cpp
*/

#include "systems/CellCollision.hpp"
#include "GEngine/libdev/Component.hpp"
#include "ecs/entity/Entity.hpp"
#include <math.h>

namespace hiop::system {
void CellCollision::init(void) {
    subscribeToEvent<geg::event::GameLoop>(&CellCollision::onGameLoop);
}

void CellCollision::onGameLoop(geg::event::GameLoop &) {
    auto &transforms = getComponents<geg::component::Transform2D>();
    auto &hitboxs = getComponents<geg::component::HitBoxCircle2D>();

    for (auto [entity, tranform, hitbox]: gengine::Zip(transforms, hitboxs)) {
        for (auto [entity2, tranform2, hitbox2]: gengine::Zip(transforms, hitboxs)) {
            if (entity == entity2)
                continue;

            double distance = sqrt(pow(tranform.pos.x - tranform2.pos.x, 2) + pow(tranform.pos.y - tranform2.pos.y, 2));

            double r1 = hitbox.radius;
            double r2 = hitbox2.radius;
            double totalRadius = r1 + r2;

            if (distance >= totalRadius)
                continue;

            double d = distance;
            double part1 = r1 * r1 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
            double part2 = r2 * r2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
            double part3 = 0.5 * sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));

            double intersectionArea = part1 + part2 - part3;

            double area1 = M_PI * r1 * r1;
            double area2 = M_PI * r2 * r2;

            double coverage1 = (intersectionArea / area1) * 100.0;
            double coverage2 = (intersectionArea / area2) * 100.0;

            if (r1 > r2)
                publishEvent(event::CellCollision(r1, r2, coverage2));
            else
                publishEvent(event::CellCollision(r2, r1, coverage1));
        }
    }
}
}