/**
* @file robot_factory.cc
*/

#include "robot_factory.h"

namespace csci3081 {

    IEntity* RobotFactory::CreateEntity(const picojson::object& obj) {
        //only return a robot if the object passed in is a robot type
        if (JsonHelper::GetString(obj, "type") == "robot") {    
        std::vector<float> position = JsonHelper::GetStdFloatVector(obj, "position");
        std::vector<float> direction = JsonHelper::GetStdFloatVector(obj, "direction");
        return new Robot(position, direction, obj);
        }
        else return nullptr;

    }


} // namespace csci3081