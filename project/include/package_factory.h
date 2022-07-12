/**
* @file package_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "ientity_factory.h"
#include "entity_base.h"
#include "json_helper.h"
#include "package.h"

#ifndef PACKAGE_FACTORY
#define PACKAGE_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief package factory class to create package entities from
*/
class PackageFactory : public IEntityFactory {
public: 
    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    *
    * @returns a pointer to a created package entity
    */
    IEntity* CreateEntity(const picojson::object& obj);
private:

}; // PackageFactory

} // namespace csci3081

#endif // PACKAGE_FACTORY