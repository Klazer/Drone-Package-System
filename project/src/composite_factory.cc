/**
* @file composite_factory.cc
*/

/************************************************************
* includes
************************************************************/
#include "composite_factory.h"

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
CompositeFactory::~CompositeFactory() {
    for (IEntityFactory* factory : factories_)
   {
     delete factory;
   } 
   factories_.clear();
}

IEntity* CompositeFactory::CreateEntity(const picojson::object& obj) {

    // iterates through the entire vector of factories and returns the desired 
    // item when create entity does not give a nullptr. 
    for (IEntityFactory* factory : factories_) {
        IEntity* entity = factory->CreateEntity(obj);
        if (entity != nullptr) {
            return entity;
        }
        //else return nullptr;
    }

}

void CompositeFactory::AddFactory(IEntityFactory* entity_factory) {
    factories_.push_back(entity_factory);
}

} // namespace csci3081