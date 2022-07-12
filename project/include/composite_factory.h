/**
* @file composite_factory.h
*/

/************************************************************
* includes
************************************************************/
#include "ientity_factory.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"
#include "customer.h"
#include "package.h"
#include <vector>

#ifndef COMPOSITE_FACTORY
#define COMPOSITE_FACTORY

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief A class to facilitate the composite factory pattern, where multiple
*       different ientity factories may be added and objects then instantiated
*       from
*/
class CompositeFactory : public IEntityFactory {
public: 

    /**
    * @brief a destructor to return any memory allocated to the vector of factory pointers
    */
    ~CompositeFactory();

    /**
    * @brief function to be overridden for the creation of entity objects
    *
    * @param[in] obj a picojson object with info attached
    *
    * @returns A pointer to an entity
    */
    IEntity* CreateEntity(const picojson::object& obj) ;
    
    /**
    * @brief function to add ientity factories into the component factories vector
    * 
    * @param[in] entity_factory the IEntityFactory factory to add to the vector of factories
    */
    void AddFactory(IEntityFactory* entity_factory);
private:
    std::vector<IEntityFactory*> factories_;
    
}; // CompositeFactory

} // namespace csci3081

#endif // COMPOSITE_FACTORY
