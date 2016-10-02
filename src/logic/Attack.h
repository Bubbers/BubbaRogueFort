#pragma once

#include <functional>
#include "linmath/float3.h"

struct Stats;
class Camera;
class GameObject;

class AttackResult {
public:
    AttackResult(int damage);
    int damage;
};

typedef std::function<AttackResult (Stats stats)> Attack;

//Sample attacks
/**
 * Does the strength as damage
 */
Attack punch();
