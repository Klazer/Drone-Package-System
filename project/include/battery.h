/**
* @file battery.h
*/

#ifndef BATTERY
#define BATTERY

/************************************************************
* Includes
************************************************************/

namespace csci3081 {

/************************************************************
* Class definitions
************************************************************/
/**
* @brief Class to instantiate battery objects from.
*/
class Battery {
    // TODO: Add documentation to these functions
    public:
    /**
    * @brief the constructor for creating battery objects
    *
    * @param[in] charge The amount of charge the battery holds
    */
    Battery(int charge = 10000);

    /**
    * @brief function to update the battery charge when being used
    *
    * @param[in] dt rate to decrease battery charge level by
    */
    void UseBattery(float dt);

    /**
    * @brief function to charge the battery with
    *
    * @param[in] charge amount to charge battery by
    */
    void ChargeBattery(float charge);

    /**
    * @brief getter function to return the battery's current charge
    *
    * @returns the battery's charge level
    */
    float GetCharge() const;

    /**
    * @brief setter function to set the charge of the battery
    *
    * @param[in] charge the amount to set the charge
    */
    void SetCharge(float charge) ;

    /**
    * @brief function to return whether the battery is dead or not
    * 
    * @returns bool
    */
    bool IsDead();

    /**
    * @brief function to return whether the battery is at its max charge or not
    *
    * @returns bool
    */
    bool IsMaxCharge();

    private:
    float charge_lvl_;
    float max_charge_;
    bool is_max_charge_ = true; //starts off with a charge of 10,000 (full)
    
};

}  // namespace csci3081

#endif // PACKAGE

