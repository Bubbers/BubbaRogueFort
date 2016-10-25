#include "components/TimedLife.h"
#include "GameObject.h"

TimedLife::TimedLife(float lifeTime) : lifeTime(lifeTime) {
}

TimedLife::~TimedLife() {
}

void TimedLife::update(float dt) {
     lifeTime -= dt;
     if (lifeTime <= 0) {
         owner->makeDirty(); 
     }
}
