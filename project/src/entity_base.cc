#include "entity_base.h"

namespace csci3081 {

EntityBase::EntityBase() {
    //generates a new unique id for every entity created
    id_ = ++super_id_;
}

int EntityBase::super_id_ = 0;

}
