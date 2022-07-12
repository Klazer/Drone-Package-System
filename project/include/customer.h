/**
* @file customer.h
*/

#ifndef CUSTOMER
#define CUSTOMER

/************************************************************
* Includes
************************************************************/
#include "json_helper.h"
#include "entity_base.h"
#include <vector>
#include <string>

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate Customer objects from.
*/
class Customer : public csci3081::EntityBase {
 public:
  /**
  * @brief Constructor for the Customer class.
  *
  * @param[in] pos position of the customer
  * @param[in] direction direction of the customer
  * @param[in] obj the picojson object describing the customer
  *
  */
  Customer(std::vector<float> pos, std::vector<float> direction, const picojson::object& obj);
  
  /**
  * @brief function to update the entity depending on its "state"
  *         A customer doesn't need to do more than stay in one position.
  *         Unless that changes, this function does nothing. 
  */
  void UpdateEntity(float dt) ;

  virtual picojson::value createEvent(std::string value) {}

  private: 
    //int id_ = 0;
};

}  // namespace csci3081

#endif // CUSTOMER
