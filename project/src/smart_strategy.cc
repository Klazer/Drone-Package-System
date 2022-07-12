/**
* @file smart_strategy.cc
*/

/************************************************************
* includes
************************************************************/
#include "smart_strategy.h"

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
std::vector<std::vector<float>> Smart::doPath(std::vector<float> origin,
                                                 std::vector<float> destination,
                                                 const IGraph* graph){
      return graph->GetPath(origin, destination);

}

void Smart::setSpeed(float speed){}                                      

const std::string Smart::getName(){
      return name;
      }

}
