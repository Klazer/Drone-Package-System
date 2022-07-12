/**
* @file drone_factory.cc
*/

#include "drone_factory.h"

namespace csci3081 {

    IEntity* DroneFactory::CreateEntity(const picojson::object& obj) {
        //only return a drone if the object passed in is a drone type
        if (JsonHelper::GetString(obj, "type") == "drone") {    
        std::vector<float> position = JsonHelper::GetStdFloatVector(obj, "position");
        std::vector<float> direction = JsonHelper::GetStdFloatVector(obj, "direction");
        return new Drone(position, direction, obj);
        }
        else return nullptr;

    }


} // namespace csci3081