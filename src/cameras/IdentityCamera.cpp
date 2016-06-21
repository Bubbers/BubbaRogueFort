//
// Created by simon on 2016-06-21.
//

#include "IdentityCamera.h"

using namespace chag;

IdentityCamera::IdentityCamera() :
        Camera(make_vector(0.0f,0.0f,0.0f),make_vector(0.0f,0.0f,0.0f), make_vector(0.0f,0.0f,0.0f),
               0.0f, 0.0f, 0.0f, 0.0f) { }

void IdentityCamera::update(float dt) {

}

float4x4 IdentityCamera::getViewMatrix() {
    return chag::make_identity<float4x4>();
}

float4x4 IdentityCamera::getProjectionMatrix() {
    return chag::make_identity<float4x4>();
}
