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

    // engine.addComponent(ent, ECS::Position(1116, 340), ECS::POSITION);
    // engine.addComponent(ent, ECS::Velocity(0, 5), ECS::VELOCITY);
    // engine.addComponent(ent, ECS::Dimensions(250, 250), ECS::DIMENSIONS);
    // engine.addComponent(ent, ECS::Life(20), ECS::LIFE);
    // engine.addComponent(ent, ECS::Bomb(), ECS::BOMB);
    engine.addComponent(ent, ECS::entityDetails(entityType::SPACESHIP, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    std::cout << "spaceship" << std::endl;
}

void spaceship::update(const float dt, ECS::ECSEngine& engine)
{
    static int time = 0;
    static bool way = true;//mettre un random pour changer si on commence par partir vers le haut ou le bas ?
    static bool firstBuf = false;
    static bool secondBuf = false;


    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::SPACESHIP) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
            auto& hp = engine.getComponent<ECS::Life>(ent, ECS::LIFE);


            //SA VITESSE MONTE QUAND IL A PEU DE PV
            if (hp._hp < 10 && firstBuf == false) {
                vel._vy *= 2;
                firstBuf = true;
            }
            if (hp._hp < 3 && secondBuf == false) {
                vel._vy *= 2;
                secondBuf = true;
            }
            //SA VITESSE MONTE QUAND IL A PEU DE PV

            if (time % (100 / (static_cast<int>(vel._vy))) == 0) {// plus la velocité monte, plus ca ira souvent dans le if

                //SE PLACER CORRECTEMENT EN X
                if (pos._x >= 800)
                    pos._x -= 1;
                //SE PLACER CORRECTEMENT EN X
                else {
                    //BOUGER VERS LE HAUT OU LE BAS
                    if (way == true) {//VERS LE BAS
                        if (pos._y < 600)
                            pos._y += 1;
                        else
                            way = false;
                    } else {//VERS LE HAUT
                        if (pos._y > 250)
                            pos._y -= 1;
                        else
                            way = true;
                    }
                    //BOUGER VERS LE HAUT OU LE BAS
                }

                

                if (time % (1000 / (static_cast<int>(vel._vy))) == 0) {//plus la velocité monte, plus ca ira souvent dans le if
                    //shoot?
                }
            }
        }
    }
    time++;
}

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<spaceship>());
}