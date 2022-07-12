/**
* @file path_strategy.h
*/

#ifndef PATH_STRATEGY
#define PATH_STRATEGY

/************************************************************
* Includes
************************************************************/
#include <vector> 
#include <string>
#include <EntityProject/facade/delivery_system.h>


namespace csci3081 {

/**
* @brief class to provide an interface for path strategies to inherit from. 
*        This is pure abstract and must be implemented.
*/
class pathInterface{
    public:
        /**
        * @brief pure virtual function to create and return a path using
                 the a pathing strategy.
        *
        * @param[in] origin the starting location.
        * @param[in] destination the ending location.
        * @param[in] praph the Igraph graph object, if needed, else null.
        *
        * @returns the calculated path
        */
        virtual std::vector<std::vector<float>> doPath(std::vector<float> origin,
                                                       std::vector<float> destination,
                                                       const IGraph* graph = NULL) = 0;
        /**
        * @brief pure virtual function to set the speed for path calculations.
        */
        virtual void setSpeed(float speed) = 0;

        /**
        * @brief pure virtual function to return the name of the path strategy.
        */
        virtual const std::string getName() = 0;

};


}

#endif
