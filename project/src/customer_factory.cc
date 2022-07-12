/**
* @file customer_factory.cc
*/

#include "customer_factory.h"

namespace csci3081 {

    IEntity* CustomerFactory::CreateEntity(const picojson::object& obj) {
        //only return a drone if the object passed in is a drone type
        if (JsonHelper::GetString(obj, "type") == "customer") {    
        std::vector<float> position = JsonHelper::GetStdFloatVector(obj, "position");
        std::vector<float> direction = JsonHelper::GetStdFloatVector(obj, "direction");
        return new Customer(position, direction, obj);
        }
        else return nullptr;

    }


} // namespace csci3081