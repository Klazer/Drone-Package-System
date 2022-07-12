/**
* @file ientity_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "entity_base.h"
#include "json_helper.h"

#ifndef IENTITY_FACTORY
#define IENTITY_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief ientity factory interface 
*/
class IEntity_Factory {
public: 
    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    *
    * @returns A pointer to an entity
    */
    virtual IEntity* CreateEntity(const picojson::object& obj) =0;
private:

}; // IEntityFactory

} // namespace csci3081

#endif // IENTITY_FACTORY
