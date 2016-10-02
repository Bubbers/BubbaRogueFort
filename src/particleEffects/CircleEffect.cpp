#include "Utils.h"
#include "CircleEffect.h"
#include "linmath/float3.h"
#include "linmath/float3x3.h"
#include "linmath/Quaternion.h"

using namespace chag;

CircleEffect::CircleEffect() {
}

CircleEffect::~CircleEffect() {
}

float3 CircleEffect::initialPosition() {

    float theta = getRand(- M_PI, M_PI);
    float r = 2.0f;
    return make_vector(r * sinf(theta),
                       3.0f,
                       r * cosf(theta));
}

float3 CircleEffect::initialVelocity() {
    return make_vector(10.0f, 3.0f, 0.0f);
}

float3 CircleEffect::accelerate(float3 velocity) {
    Quaternion quat = make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), (M_PI) / 4.0f );
    float3x3 mat = toMatrix3x3(quat);
    return mat * velocity;
}

float CircleEffect::calcLifetime() {
    return 10000.0f;
}

float3 CircleEffect::calcParticleScale() {
    return make_vector(1.0f, 1.0f, 1.0f);
}

bool CircleEffect::loop(float dt) {
    return false;
}
