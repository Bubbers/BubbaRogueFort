#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include <Camera.h>
#include "linmath/float3x3.h"

class PlayerCamera : public Camera {
public:
    PlayerCamera(float3 offset, float3 lookAt, float3 up,
                      float fov, float ratio, float nearPlane, float farPlane);
    ~PlayerCamera();

    float4x4 getViewMatrix();
    float4x4 getProjectionMatrix();

    void update(float dt);
    void setPosition(float3 position);
    void setLookAt(float3 lookAt);
    void setUpVector(float3 up);
    void setOffset(float3 offset);
 private:
    float3   offset;
    float4x4 lookAt(const float3 &eye, const float3 &center, const float3 &up);
    float4x4 perspectiveMatrix(float fov, float aspectRatio, float n, float f);

};
#endif // PLAYERCAMERA_H
