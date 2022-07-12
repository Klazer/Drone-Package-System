/**
* @file drone_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "ientity_factory.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"

#ifndef DRONE_FACTORY
#define DRONE_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief A factory for producing drones
*/
class DroneFactory : public IEntityFactory {
public: 
    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    *
    * @returns A pointer to a drone object
    */
    IEntity* CreateEntity(const picojson::object& obj);
private:

}; // DroneFactory

} // namespace csci3081

#endif // DRONE_FACTORY
