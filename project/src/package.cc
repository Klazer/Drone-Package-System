/**
* @file package.cc
*/


/************************************************************
* includes
************************************************************/
#include "package.h"

namespace csci3081 {

Package::Package(std::vector<float> position, std::vector<float> direction,
                                        const picojson::object& details) {
  // TODO for lab10: store the position and direction vectors.
  //name_ = "Default";
  position_ = position;
  direction_ = direction;
  name_ = JsonHelper::GetString(details, "name");
  type_ = JsonHelper::GetString(details, "type");
  destination_ = {0,0,0};
  radius_ = 1.0;
  weight_ = 0;
  is_picked_up_ = false;
  is_dynamic_ = false;

  if(JsonHelper::ContainsKey(details, "weight")){
    weight_ = JsonHelper::GetDouble(details, "weight");
  }else{
    weight_ = 40.0;
  }

  // The following line saves the json object in the details_ member variable
  // from the EntityBase class, in order to return it later in GetDetails()
  details_ = details;
  id_ = super_id_;
}

const std::vector<float>& Package::GetDestination() const {
   return destination_;
}

void Package::SetDestination(vector<float> destination) {
   destination_ = destination;
}

IEntity* Package::GetDestinationEntity() {
  return destinationEntity_;
}

void Package::SetDestinationEntity(IEntity* destinationEntity) {
  destinationEntity_ = destinationEntity;
}

float Package::GetWeight() const {
    return weight_;
}

void Package::SetWeight(float weight) {
    if (weight < 0 ) {
        weight = 0;
    }
    weight_ = weight;
}

void Package::PickupPackage() {
    is_picked_up_ = true;
    is_dynamic_ = true;
}

void Package::DropPackage() {
    is_picked_up_ = false;
    is_dynamic_ = false;
}

picojson::value Package::createEvent(std::string value) {
  static picojson::object e = JsonHelper::CreateJsonObject();
  if (value == "scheduled"){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "scheduled");
    picojson::value event(e);
    return event;
  }
  else if (value == "en route"){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "en route");
    picojson::value event(e);
    return event;
  }
  else if (value == "delivered"){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "delivered");
    picojson::value event(e);
    return event;
  }
}

void Package::UpdateEntity(float dt) {}

}  // namespace csci3081
