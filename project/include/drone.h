/**
* @file drone.h
*/

#ifndef DRONE
#define DRONE

/************************************************************
* Includes
************************************************************/
#include "deliverer.h"

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate Drone objects from.
*/
class Drone : public csci3081::Deliverer {
 public:
  /**
  * @brief Constructor for the Drone class.
  *
  * @param[in] pos Position of the drone
  * @param[in] direction Direction of the drone
  * @param[in] obj A picojson object containing other details of the drone
  *
  */
  Drone(std::vector<float> pos, std::vector<float> direction, const picojson::object& obj);

  /**
  * @brief deconstructor for drones
  */
  ~Drone();


  /**
  * @brief function to update the enity based on its "state"
  *
  *@param[in] dt the time step to move things along by
  */
  void UpdateEntity(float dt) override;

  Vector3D* m;

};

}  // namespace csci3081

#endif // DRONE
