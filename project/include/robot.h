/**
* @file robot.h
*/

#ifndef ROBOT
#define ROBOT

/************************************************************
* Includes
************************************************************/
#include "deliverer.h"

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate Robot objects from.
*/
class Robot : public csci3081::Deliverer {
 public:
  /**
  * @brief Constructor for the Robot class.
  *
  * @param[in] pos position of the robot.
  * @param[in] direction direction of the robot.
  * @param[in] obj the picojson object containing addictional details of the robot.
  *
  */
  Robot(std::vector<float> pos, std::vector<float> direction, const picojson::object& obj);

  /**
  * @brief deconstructor for Robots
  */
  ~Robot();

  /**
  * @brief function to update the enity based on its "state"
  * A robot will move, notify observers and deliver packages 
  * through this function.
  *
  *@param[in] dt the time step to move things along by
  */
  void UpdateEntity(float dt) override;



  private: 
    Vector2D* m;

}; //end robot.h

}  // namespace csci3081

#endif // ROBOT
