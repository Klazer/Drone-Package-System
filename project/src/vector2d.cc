/**
* @file vector2d.cc
*/

#include "vector2d.h"

namespace csci3081 {

vector<float> Vector2D::Add(const vector<float>& v1, const vector<float>& v2) {
    vector<float> temp = {0,0,0};

    if (v1.size() == 3 && v2.size() == 3) {
        temp.at(0) = v1.at(0) + v2.at(0);
        temp.at(1) = v1.at(1);
        temp.at(2) = v1.at(2) + v2.at(2);
    }
    return temp;
}

vector<float> Vector2D::Subtract(const vector<float>& v1, const vector<float>& v2) {
    vector<float> temp = {0,0,0};

    if (v1.size() == 3 && v2.size() == 3) {
        temp.at(0) = v1.at(0) - v2.at(0);
        temp.at(1) = v1.at(1);
        temp.at(2) = v1.at(2) - v2.at(2);
    }
    return temp;
}

float Vector2D::CalcMagnitude(const vector<float>& v) {
    float x = v.at(0);
    //float y = v.at(1);  //no y movement y should not be part of this
    float z = v.at(2);

    //using pythagoreans theorem (without y)
    return sqrt((x * x) + (z * z));
}

vector<float> Vector2D::Normalize(const vector<float>& v) {
    vector<float> temp = {0,0,0};

    float magnitude = CalcMagnitude(v);

    //divide each element by the magnitude to create a unit vector
    //aka normalize it! except y!!

    if (magnitude != 0) { 
        temp.at(0) = v.at(0) / magnitude;
        temp.at(1) = v.at(1);    //vector2d does not affect y
        temp.at(2) = v.at(2) / magnitude;
    }

    return temp;
}

vector<float> Vector2D::CalcDirection(const vector<float>& ptA, const vector<float>& ptB) {
    return Subtract(ptA, ptB);
}

vector<float> Vector2D::CalcVelocity(const vector<float>& norm_direction, float speed) {
    vector<float> temp = {0,0,0};

    temp.at(0) = norm_direction.at(0) * speed;
    temp.at(1) = norm_direction.at(1);  //vector2d does not affect y
    temp.at(2) = norm_direction.at(2) * speed;

    return temp;
}

vector<float> Vector2D::CalcDistance(const vector<float>& velocity, float dt) {
    vector<float> temp = {0,0,0};

    temp.at(0) = velocity.at(0) * dt;
    temp.at(1) = velocity.at(1);    //vector2d does not affect y
    temp.at(2) = velocity.at(2) * dt;

    return temp;
}

vector<float> Vector2D::EulerianIntegration(const vector<float>& point, const vector<float>& distance) {
    return Add(point, distance);
}

} // namespace csci3081