/**
* @file deliverer.h
*/

#ifndef DELIVERER
#define DELIVERER

/************************************************************
* Includes
************************************************************/
#include "json_helper.h"
#include "entity_base.h" 
#include "battery.h"
#include "package.h"
#include "vector3d.h"
#include "vector2d.h"
// #include "delivery_simulation.h"
#include "path_strategy.h"
#include <vector> 
#include <string>

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate Deliverer objects from.
*/
class Deliverer : public csci3081::EntityBase {
 public:
  /**
  * @brief Constructor for the Deliverer class.
  *
  */
  Deliverer() {}

  /**
  * @brief deconstructor for deliverers
  */
  ~Deliverer() {}

  /**
  * @brief getter to return the speed
  * @returns the speed of the deliverer
  */
  float GetSpeed() const;

  /**
   * @brief getter to return the path strategy
   * @returns The path strategy
   */
  pathInterface* GetPathStrategy() const;

  /**
  * @brief setter to set the deliverer speed
  * @param[in] speed the speed to set the deliverer at
  */
  void SetSpeed(float speed);

  /**
  * @brief getter function to return the deliveer's packages.
  *
  * @returns A vector of package pointers that the deliverer is carrying.
  */
  std::vector<Package*> GetPackages();


  /**
  * @brief This clears the deliverer's assigned deliveries.
  *
  */
  void ClearDeliveries();

  /**
  * @brief getter function to return the deliverer's last package to pick up.
  *
  * @returns A pointer to the last package that the deliverer will pick up.
  */
  Package* GetLastPackage();

    /**
  * @brief getter function to return the deliverer's first package to pick up.
  *
  * @returns A pointer to the first package that the deliverer will pick up.
  */
  Package* GetFirstPackage();

  /**
  * @brief setter to set the package pointer to a package
  *
  * @param[in] package The package pointer
  */
  void SetPackage(Package* package);

  /**
  * @brief getter function to return if the deliverer is carrying all of its scheduled packages.
  *
  * @returns true if the deliverer has its packages, false if not
  */
  bool GetHasPackages() const;

  /**
  * @brief Setter function to set the deliverer into a "has package" state
  *
  * @param[in] state A value indicating if the deliverer has a package
  */
  void SetHasPackage(bool state);

  /**
  * @brief getter function to return if the deliverer's battery is dead.
  *
  * @return true if the battery is dead, false if not.
  */
  bool IsDead() const;

    /**
  * @brief getter function to return if the deliverer has any assigned pacakges currently.
  *
  * @return true if there are no packages assigned to the deliverer, false if there are.
  */
  bool IsNothingScheduled() const;

  /**
  * @brief getter function to return if the deliverer is able to be assigned a package at the moment.
  *
  * @return true if the deliverer can be assigned the package, false if not.
  */
  bool CanTakePackage(float weight);

  /**
  * @brief Setter function to give the deliverer a path to travel on
  *
  * @param[in] path the path to use
  */
  void SetPath(std::vector<std::vector<float>> path);

  /**
  * @brief getter function to return the deliverer path
  *
  * @returns the deliverer path its traveling along
  */
  std::vector<std::vector<float>> GetPath();

  /**
  * @brief Setter function to give the deliverer a path to travel on for delivering
  *
  * @param[in] path the path to use
  */
  void SetDeliveryPath(std::vector<std::vector<float>> path);

  /**
  * @brief Setter function to give the deliverer a path to travel from the packages to the customers.
  *
  * @param[in] path the path to use
  */
  void SetTransitionPath(std::vector<std::vector<float>> path);

  /**
  * @brief getter function to return the deliverer's delivery path
  *
  * @returns the path from the package to the customer
  */
  std::vector<std::vector<float>> GetDeliveryPath();


  /**
  * @brief function to update the enity based on its "state"
  *
  *@param[in] dt the time step to move things along by
  */
  virtual void UpdateEntity(float dt)=0;

  /**
   * @brief A function to create an event
   *
   * @param[in] value The type of event being created
   */
  picojson::value createEvent(std::string value) override;



  protected: 
    std::vector<float> curr_dest_;
    std::vector<std::vector<float>> travel_path_;
    std::vector<std::vector<std::vector<float>>> all_travel_paths_;
    std::vector<std::vector<float>> delivery_path_;
    std::vector<std::vector<std::vector<float>>> all_delivery_paths_;

    float carrying_capacity;
    float current_weight;
    bool has_packages_;
    bool packages_delivered_;

    float speed_;
    Battery* battery_;
    std::vector<Package*> packages_;
    std::vector<Package*> pickedUpPackages_;
    std::vector<Package*> allPackages_;
    bool notified;
    pathInterface* path_strategy;

};

}  // namespace csci3081

#endif // DELIVERER