#pragma once

#include <functional>
#include <memory>

#include "linmath/float3.h"

struct Stats;
class Camera;
class GameObject;

class AttackResult {
public:
    AttackResult(int damage);
    ~AttackResult() = default;

    void visualEffect(chag::float3 fromPos, chag::float3 toPos,
                      std::shared_ptr<Camera> camera,
                      std::function<void (std::shared_ptr<GameObject>)> putGameObject);

    int damage;
};

typedef std::function<AttackResult (Stats stats)> Attack;

//Sample attacks
/**
 * Does the strength as damage
 */
Attack punch();
