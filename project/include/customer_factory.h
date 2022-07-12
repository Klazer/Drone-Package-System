/**
* @file customer_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "ientity_factory.h"
#include "entity_base.h"
#include "json_helper.h"
#include "customer.h"

#ifndef CUSTOMER_FACTORY
#define CUSTOMER_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief A factory for producing customers 
*/
class CustomerFactory : public IEntityFactory {
public: 
    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    */
    IEntity* CreateEntity(const picojson::object& obj);
private:

}; // CustomerFactory

} // namespace csci3081

#endif // CUSTOMER_FACTORY
