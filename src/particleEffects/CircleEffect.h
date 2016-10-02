#pragma once

#include "ParticleConf.h"

class CircleEffect : public ParticleConf {
public:
    CircleEffect();
    ~CircleEffect();

    chag::float3 initialPosition();
    chag::float3 initialVelocity();
    chag::float3 accelerate(chag::float3 velocity);
    chag::float3 calcParticleScale();

    float calcLifetime();
    bool loop(float dt);
private:
    float lifeTime = 3000;

};
