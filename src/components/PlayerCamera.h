#pragma once

#include <Camera.h>
#include "linmath/float3x3.h"

class PlayerCamera : public Camera {
public:
    PlayerCamera(chag::float3 offset, chag::float3 lookAt, chag::float3 up,
                 float fov, float ratio, float nearPlane, float farPlane);

    ~PlayerCamera();

    chag::float4x4 getViewMatrix();
    chag::float4x4 getProjectionMatrix();

    void update(float dt);
    void setPosition(chag::float3 position);
    void setLookAt(chag::float3 lookAt);
    void setUpVector(chag::float3 up);
    void setOffset(chag::float3 offset);
private:
    chag::float3   offset;
    chag::float4x4 lookAt(const chag::float3 &eye, const chag::float3 &center, const chag::float3 &up);
    chag::float4x4 perspectiveMatrix(float fov, float aspectRatio, float n, float f);

};
