//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_IDENTITYCAMERA_H
#define BUBBAROGUEFORT_IDENTITYCAMERA_H

#include <Camera.h>

class IdentityCamera : public Camera {

public:
    IdentityCamera();


    virtual void update(float dt);

    virtual float4x4 getViewMatrix();

    virtual float4x4 getProjectionMatrix();
};


#endif //BUBBAROGUEFORT_IDENTITYCAMERA_H
