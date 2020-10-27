/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** testECSEngine.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ECSEngine.hpp"
#include "movementSystem.hpp"
#include "Error.hpp"

Test(testECSEngineSimpleUsage, ECSEngine)
{
    ECSEngine engine;

    engine.registerComponent<Position>(POSITION);
    engine.registerComponent<Velocity>(VELOCITY);

    engine.registerSystem<movementSystem>();

    auto ent = engine.getNewEntity();
    engine.addComponent(ent, Position(0, 0), POSITION);
    engine.addComponent(ent, Velocity(1, 1), VELOCITY);
    engine.update(1);
    cr_assert_eq(engine.getComponent<Position>(ent, POSITION)._x, 1);
}

Test(testECSEngineSecondSimpleUsage, ECSEngine)
{
    ECSEngine engine;

    engine.registerComponent<Position>(POSITION);
    engine.registerComponent<Velocity>(VELOCITY);

    engine.registerSystem<movementSystem>();

    auto ent = engine.getNewEntity();
    engine.addComponent(ent, Position(0, 0), POSITION);
    engine.addComponent(ent, Velocity(1, 2), VELOCITY);
    engine.update(1);
    cr_assert_eq(engine.getComponent<Position>(ent, POSITION)._y, 2);
}

Test(testECSEngineEntity, ECSEngine)
{
    ECSEngine engine;

    engine.getNewEntity();
    cr_assert_eq(engine.getEntites().front(), 0);
}

Test(testECSRemoveEntity, ECSEngine)
{
    ECSEngine engine;

    engine.getNewEntity();
    engine.removeEntity(engine.getNewEntity());
    cr_assert_eq(engine.getEntites().front(), 0);
}

Test(testECSErrorNbEntities, ECSEngine)
{
    ECSEngine engine;

    try {
        for (int i = 0; i != 505; i++)
            engine.removeEntity(engine.getNewEntity());
    } catch (Error &err) {
        cr_assert_eq(std::strcmp(err.what(), "Error: invalid number of entities has been reached."), 0);
    }
}