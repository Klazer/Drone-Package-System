/**
* @file beeline_strategy.cc
*/

/************************************************************
* includes
************************************************************/
#include "beeline_strategy.h"


namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
   std::vector<std::vector<float>> Beeline::doPath(std::vector<float> origin,
                                                   std::vector<float> destination,
                                                   const IGraph* graph) {
  std::vector<std::vector<float>> path;
  path.push_back(origin);
  origin.at(1) += 50;
  path.push_back(origin);

  std::vector<float> destinationTemp = destination;
  destinationTemp.at(1) += 50;
  path.push_back(destinationTemp);
  path.push_back(destination);


  return path;
 
}

void Beeline::setSpeed(float speed){
   this->speed = speed;
}                                      

const std::string Beeline::getName(){
      return name;
}

}
