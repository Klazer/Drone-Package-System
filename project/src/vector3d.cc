/**
* @file vector3d.cc
*/

#include "vector3d.h"

namespace csci3081 {

vector<float> Vector3D::Add(const vector<float>& v1, const vector<float>& v2) {
    vector<float> temp = {0,0,0};

    if (v1.size() == 3 && v2.size() == 3) {
        for (int i = 0; i < 3; i++) {
            temp.at(i) = v1.at(i) + v2.at(i);
        }
    }
    return temp;
}

vector<float> Vector3D::Subtract(const vector<float>& v1, const vector<float>& v2) {
    vector<float> temp = {0,0,0};

    if (v1.size() == 3 && v2.size() == 3) {
        for (int i = 0; i < 3; i++) {
            temp.at(i) = v1.at(i) - v2.at(i);
        }
    }
    return temp;
}

float Vector3D::CalcMagnitude(const vector<float>& v) {
    float x = v.at(0);
    float y = v.at(1);
    float z = v.at(2);

    //using pythagoreans theorem
    return sqrt((x * x) + (y * y) + (z * z));
}

vector<float> Vector3D::Normalize(const vector<float>& v) {
    vector<float> temp = {0,0,0};

    float magnitude = CalcMagnitude(v);

    //divide each element by the magnitude to create a unit vector
    //aka normalize it!

    if (magnitude != 0) {
        for (int i = 0; i < 3; i++) {
            temp.at(i) = v.at(i) / magnitude;
        }    
    }

    return temp;
}

vector<float> Vector3D::CalcDirection(const vector<float>& ptA, const vector<float>& ptB) {
    return Subtract(ptA, ptB);
}

vector<float> Vector3D::CalcVelocity(const vector<float>& norm_direction, float speed) {
    vector<float> temp = {0,0,0};

    for (int i = 0; i < 3; i++) {
        temp.at(i) = norm_direction.at(i) * speed;
    }  

    return temp;
}

vector<float> Vector3D::CalcDistance(const vector<float>& velocity, float dt) {
    vector<float> temp = {0,0,0};

    for (int i = 0; i < 3; i++) {
        temp.at(i) = velocity.at(i) * dt;
    }

    return temp;
}

vector<float> Vector3D::EulerianIntegration(const vector<float>& point, const vector<float>& distance) {
    return Add(point, distance);
}

} // namespace csci3081