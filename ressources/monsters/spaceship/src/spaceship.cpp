/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** spaceship.cpp
*/

#include "spaceship.hpp"
#include <iostream>
#include <memory>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "Life.hpp"
#include "Bomb.hpp"

spaceship::spaceship() : AMonster()
{

}

void spaceship::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    _id = ent;
    engine.addComponent(ent, ECS::Position(1116, rand() % 400 + 200), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(65, 66), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Life(20), ECS::LIFE);
    engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
    engine.addComponent(ent, ECS::entityDetails(entityType::SPACESHIP, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void spaceship::update(const float dt, ECS::ECSEngine& engine)
{
    static int time = 0;
    static int speed = 5;
    static bool way = rand() % 2;//mettre un random pour changer si on commence par partir vers le haut ou le bas ?
    static bool firstBuf = false;
    static bool secondBuf = false;


    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::SPACESHIP && ent == _id) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
            auto& hp = engine.getComponent<ECS::Life>(ent, ECS::LIFE);


            //SA VITESSE MONTE QUAND IL A PEU DE PV
            if (hp._hp < 10 && firstBuf == false) {
                speed *= 2;
                firstBuf = true;
            }
            if (hp._hp < 3 && secondBuf == false) {
                speed *= 2;
                secondBuf = true;
            }
            //SA VITESSE MONTE QUAND IL A PEU DE PV

            if (time % (100 / speed) == 0) {

                //SE PLACER CORRECTEMENT EN X
                if (pos._x >= 950)
                    vel._vx -= 1;
                //SE PLACER CORRECTEMENT EN X
                else {
                    vel._vx = 0;
                    //BOUGER VERS LE HAUT OU LE BAS
                    if (way == true) {//VERS LE BAS
                        if (pos._y < 700)
                            vel._vy = 1;
                        else {
                            way = false;
                            vel._vy = 0;
                        }
                    } else {//VERS LE HAUT
                        if (pos._y > 30)
                            vel._vy = -1;
                        else {
                            way = true;
                            vel._vy = 0;
                        }
                    }
                    //BOUGER VERS LE HAUT OU LE BAS
                }

                

                if (time % (1000 / speed) == 0) {
                    //shoot?
                }
            }
            if (_animation == 0) {
                details._state = static_cast<animationState>(static_cast<int>(details._state) + 1);
                if (details._state == ANIMATION_5)
                    details._state = ANIMATION_0;
                _animation = 1;
            }
        }
    }
    if (_animation > 0)
        _animation++;
    if (_animation == 5)
        _animation = 0;
    time++;
}

#if defined (_WIN32)

extern "C"  __declspec(dllexport)
void* entryPoint()
{
    return (new std::unique_ptr<spaceship>(new spaceship));
}

#else

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<spaceship>());
}

#endif