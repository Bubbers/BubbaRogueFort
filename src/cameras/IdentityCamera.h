#pragma once

#include <Camera.h>

class IdentityCamera : public Camera {

public:
    IdentityCamera();


    virtual void update(float dt);

    virtual chag::float4x4 getViewMatrix();

    virtual chag::float4x4 getProjectionMatrix();
};
