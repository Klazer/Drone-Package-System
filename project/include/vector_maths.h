/**
* @file vector_maths.h
*/

/************************************************************
* includes
************************************************************/
#include <vector>
using std::vector;

#ifndef VECTOR_MATHS
#define VECTOR_MATHS

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief vector math interface for vector math objects to inherit from
*/
class VectorMaths {
public: 
    /**
    * @brief function to add two vecors
    *
    * @param[in] v1 a vector to add to the second
    * @param[in] v2 the vector to add to the first
    *
    * @returns a resulting vector after the addition
    */
    virtual vector<float> Add(const vector<float>& v1, const vector<float>& v2) =0;

    /**
    *
    * @brief function  to subtract to vectors
    *
    * @param[in] v1 a vector to be subtracted from
    * @param[in] v2 the vector to subtract by
    * 
    * @returns a resulting vector after the subtraction
    */
    virtual vector<float> Subtract(const vector<float>& v1, const vector<float>& v2) =0;

    /**
    *
    * @brief function to return the magnitude of a given vector
    *
    * @param[in] v the vector to calculate the magnitude of
    *
    * @returns the magnitude of the given vector
    */
    virtual float CalcMagnitude(const vector<float>& v) =0;

    /**
    * @brief function to normalize a vector
    *
    * @param[in] v the vector to normalize
    * 
    * @returns a vector that is the normalized form of the input vector
    */
    virtual vector<float> Normalize(const vector<float>& v) =0;


    /**
    * @brief funtion to return the direction of a vector
    * 
    * @param[in] ptA the posiiton to go from
    * @param[in] ptB the position to go to
    *
    * @returns the direction from one point to the given point
    */
    virtual vector<float> CalcDirection(const vector<float>& ptA, const vector<float>& ptB) =0;

    /**
    * @brief function to return the velocity given a direction and a speed
    *
    * @param[in] v a vector giving direction
    * @param[in] speed the speed
    *
    * @returns the velocity 
    */
    virtual vector<float> CalcVelocity(const vector<float>& v, float speed) =0;

    /**
    * @brief function to return the distance traveled given a velocity vector and a time step
    *
    * @param[in] velocity the vector giving the velocity
    * @param[in] dt the time step
    *
    * @returns the distance traveled
    */
    virtual vector<float> CalcDistance(const vector<float>& velocity, float dt) =0;

    /**
    * @brief function to determine a new position using eulerian integration given a point and a distance
    *
    * @param[in] point the starting point of the integration
    * @param[in] distance the distance to move away from the point
    * 
    * @returns the new destination point
    */
    virtual vector<float> EulerianIntegration(const vector<float>& point, const vector<float>& distance) =0;
private:

}; // VectorMaths

} // namespace csci3081

#endif // VECTOR_MATHS