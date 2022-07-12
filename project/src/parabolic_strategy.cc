/**
* @file parabolic_strategy.cc
*/

/************************************************************
* includes
************************************************************/
#include "parabolic_strategy.h"

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
std::vector<std::vector<float>> Parabolic::doPath(std::vector<float> origin,
                                                  std::vector<float> destination,
                                                  const IGraph* graph){
   std::vector<std::vector<float>> path;
   path.push_back(origin);

   float x_origin = origin.at(0);
   float y_origin = origin.at(1);
   float z_origin = origin.at(2);

   float x_dest = destination.at(0);
   float y_dest = destination.at(1);
   float z_dest = destination.at(2);

   float parabola_height = 500.0;

   for (int i = 1; i < 101; i++) {
      std::vector<float> point;
      float step = (1.0/100) * i;

      float x = x_origin + (x_dest - x_origin) * step;
      float z = z_origin + (z_dest - z_origin) * step;
      float y = ((-4 * parabola_height) + (2 * y_origin) + (2 * y_dest)) * (step * step) +
              ((4 * parabola_height) - (3 * y_origin) - y_dest) * step + y_origin;

      point.push_back(x);
      point.push_back(y);
      point.push_back(z);

      path.push_back(point);
   }

   return path;
}

void Parabolic::setSpeed(float speed){}                                      

const std::string Parabolic::getName(){
   return name;
}
}
