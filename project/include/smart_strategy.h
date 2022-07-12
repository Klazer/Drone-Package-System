/**
* @file smart_strategy.h
*/

#ifndef SMART_STRATEGY
#define SMART_STRATEGY

/************************************************************
* Includes
************************************************************/
#include "path_strategy.h"
#include <vector> 
#include <string>

namespace csci3081 {
/**
* @brief Class to provide the smart pathing strategy to 
*        deliverer entities.
*/
class Smart : public pathInterface{
    public:
        /**
        * @brief constructor for the smart path strategy object
        */
         Smart(std::string name = "Smart"){
            this->name = name;
        }

        /**
        * @brief function to create and return a path using the smart strategy.
        *
        * @param[in] origin the starting location.
        * @param[in] destination the ending location.
        * @param[in] praph the Igraph graph object, if needed, else null.
        *
        * @returns the calculated path
        */
        std::vector<std::vector<float>> doPath(std::vector<float> origin,
                                              std::vector<float> destination,
                                              const IGraph* graph = NULL) override;
        
        /**
        * @brief setter function to set the speed for the path calculations.
        */
        void setSpeed(float speed) override;  

        /**
        * @brief getter to return the name of this path strategy.
        */
        const std::string getName() override;

    private:
        float speed;
        std::string name;

}; //end smart_strategy.h

} //namespace csci3081

#endif
