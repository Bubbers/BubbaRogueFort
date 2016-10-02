#pragma once

#include <functional>
#include "linmath/float3.h"

struct Stats;
class Camera;
class GameObject;

class AttackResult {
public:
    AttackResult(int damage);
    ~AttackResult() = default;

    void visualEffect(chag::float3 fromPos, chag::float3 toPos, Camera *camera, std::function<void (GameObject*)> putGameObject);

    int damage;
};

typedef std::function<AttackResult (Stats stats)> Attack;

//Sample attacks
/**
 * Does the strength as damage
 */
Attack punch();
