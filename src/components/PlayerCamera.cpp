#include "PlayerCamera.h"
#include "GameObject.h"

using namespace chag;

PlayerCamera::PlayerCamera(float3 offset, float3 lookAt, float3 up, float fov, float ratio, float nearPlane, float farPlane)
    : Camera(offset, lookAt, up, fov, ratio, nearPlane, farPlane) {
    this->offset = offset;
}

PlayerCamera::~PlayerCamera() {
}

float4x4 PlayerCamera::getViewMatrix() {
    return lookAt(m_vPosition, m_vLookAt, m_vUp);
}

void PlayerCamera::update(float dt) {
    if (owner != nullptr) {
        this->m_vPosition = owner->getAbsoluteLocation() + this->offset;
        setLookAt(owner->getAbsoluteLocation());
    }
}

float4x4 PlayerCamera::lookAt(const float3 &eye, const float3 &center, const float3 &up) {
    float3 dir = chag::normalize(eye - center);
    float3 right = chag::normalize(cross(up, chag::normalize(dir)));
    float3 newup = chag::normalize(cross(dir, right));
    float3x3 R = make_matrix(right, newup, dir);
    float4x4 invrot = make_matrix(transpose(R), make_vector(0.0f,0.0f,0.0f));
    return invrot * make_translation(-eye);
}

float4x4 PlayerCamera::getProjectionMatrix() {
    return perspectiveMatrix(m_fFov, m_fRatio, m_fNearPlane, m_fFarPlane);
}

float4x4 PlayerCamera::perspectiveMatrix(float fov, float aspectRatio, float n, float f)
{
    return make_perspective(fov, aspectRatio, n, f);
}

void PlayerCamera::setPosition(float3 position) {
}

void PlayerCamera::setOffset(float3 offset) {
    this->offset = offset;
}

void PlayerCamera::setLookAt(float3 lookAt){
    this->m_vLookAt = lookAt;
}

void PlayerCamera::setUpVector(float3 up){
    this->m_vUp = up;
}
