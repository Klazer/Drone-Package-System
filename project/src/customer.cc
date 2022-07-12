/**
* @file customer.cc
*/


/************************************************************
* includes
************************************************************/
#include "customer.h"

namespace csci3081 {

Customer::Customer(std::vector<float> position, std::vector<float> direction,
                                        const picojson::object& details) {
  // TODO for lab10: store the position and direction vectors.
  position_ = position;
  direction_ = direction;
  name_ = JsonHelper::GetString(details, "name");
  type_ = JsonHelper::GetString(details, "type");
  radius_ = 1.0;
  is_dynamic_ = false;

  // The following line saves the json object in the details_ member variable
  // from the EntityBase class, in order to return it later in GetDetails()
  details_ = details;
  id_ = super_id_;
}



void Customer::UpdateEntity(float dt) {}

}  // namespace csci3081
