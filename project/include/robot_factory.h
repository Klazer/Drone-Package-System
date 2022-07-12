/**
* @file robot_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "ientity_factory.h"
#include "entity_base.h"
#include "json_helper.h"
#include "robot.h"

#ifndef ROBOT_FACTORY
#define ROBOT_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Robot factory class to create robots from.
*/
class RobotFactory : public IEntityFactory {
public: 
    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    *
    * @returns a pointer to the desired robot entity
    */
    IEntity* CreateEntity(const picojson::object& obj);
private:

}; // RobotFactory

} // namespace csci3081

#endif // ROBOT_FACTORY