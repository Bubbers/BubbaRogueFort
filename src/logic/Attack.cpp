#include "Attack.h"
#include "Stats.h"

#include "ParticleGenerator.h"
#include "particleEffects/CircleEffect.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "components/TimedLife.h"

Attack punch() {
    return [](Stats stats) -> AttackResult {
        return AttackResult(stats.strength);
    };
}

AttackResult::AttackResult(int damage) : damage(damage) {
}

void AttackResult::visualEffect(chag::float3 fromPos, chag::float3 toPos, Camera *camera,
                                std::function<void(GameObject*)> putGameObject) {
    GameObject *gob = new GameObject();
    gob->setLocation(toPos);
    gob->update(0.16f);
    Texture *texture = ResourceManager::loadAndFetchTexture("../meshes/bubba.png");

    int particles = 2000;
    CircleEffect *circleEffect = new CircleEffect();
    ParticleGenerator *pgen = new ParticleGenerator(texture, particles, camera,
                                                    gob->getModelMatrix(), circleEffect);

    gob->addComponent(new TimedLife(5));
    gob->addRenderComponent(pgen);
    putGameObject(gob);
}
