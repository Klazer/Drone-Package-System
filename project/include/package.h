/**
* @file package.h
*/

#ifndef PACKAGE
#define PACKAGE

/************************************************************
* Includes
************************************************************/
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "entity_base.h"
#include <vector>
#include <string>

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate package objects from.
*/
class Package : public csci3081::EntityBase {
  // TODO: Add documentation to these functions
 public:
  /**
  * @brief Constructor for the Package class.
  *
  * @param[in] pos position of the Package
  * @param[in] direction direction of the Package
  * @param[in] obj the picojson object describing the Package
  *
  */
  Package(std::vector<float> pos, std::vector<float> direction, const picojson::object& obj);
  
  /**
  * @brief function to return the packages destination
  * 
  * @returns the destination
  */
  const std::vector<float>& GetDestination() const;

  /**
  * @brief function to set the destination of the package
  *
  * @param[in] destination where the package is meant to go
  */
  void SetDestination(vector<float> destination);

    /**
  * @brief function to return the packages destination entity. 
  * 
  * @returns the destination entity.
  */
  IEntity* GetDestinationEntity();

  /**
  * @brief function to set the destination entity of the package.
  *
  * @param[in] destination entity where the package is meant to be delivered to.
  */
  void SetDestinationEntity(IEntity* destinationEntity);

  /**
  * @brief getter function to return the weight of the package
  */
  float GetWeight() const;

  /**
  * @brief setter function to set the package weight
  *
  * @param[in] weight the package weight
  */
  void SetWeight(float weight);

  /**
  * @brief function to set the package into a "picked up state"
  */
  void PickupPackage() ;

  /**
  * @brief function to set the package into a "dropped off state"
  */
  void DropPackage() ;

  /**
  * @brief function to update the enity based on its "state"
  *        a package might not even need this, a package cannot 
  *        move itself, a pointer to a package in the drone is used
  *        to "set" the position of the package instead.
  *
  *@param[in] dt the time step to move things along by
  */
  void UpdateEntity(float dt) ;

  /**
   * @brief A function to create an event
   *
   * @param[in] value The type of event that is being created
   */
  picojson::value createEvent(std::string value) override;

  private: 
    std::vector<float> destination_;
    float weight_;
    bool is_picked_up_;
    IEntity* destinationEntity_;

}; //end package.h

}  // namespace csci3081

#endif // PACKAGE
