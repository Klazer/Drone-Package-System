/**
* @file parabolic_strategy.h
*/

#ifndef PARABOLIC_STRATEGY
#define PARABOLIC_STRATEGY

/************************************************************
* Includes
************************************************************/
#include <vector> 
#include <string>
#include "path_strategy.h"

namespace csci3081 {

/**
* @brief Class to provide the parabolic pathing strategy to 
*        deliverer entities.
*/
class Parabolic : public pathInterface{
    public:
        /**
        * @brief constructor for the parabolic path strategy object
        */
        Parabolic(std::string name = "Parabolic"){
            this->name = name;
        }

        /**
        * @brief function to create and return a path using the parabolic strategy.
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
                                           
}; //end Parabolic

} // namespace csci3081

#endif
