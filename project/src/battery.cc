/**
* @file battery.cc
*/

/************************************************************
* includes
************************************************************/
#include "battery.h"

namespace csci3081 {

Battery::Battery(int charge) {
    //cannot give battery a negative charge
    if (charge < 0) {
        charge = 10000; //default value
    }
    charge_lvl_ = charge;
    max_charge_ = charge;
    is_max_charge_ = true;
}

void Battery::UseBattery(float dt) {
    charge_lvl_ -= dt;
    is_max_charge_ = false;
}

void Battery::ChargeBattery(float charge) {
    //cannot overcharge battery passed its max value
    if (!is_max_charge_) {
        charge_lvl_ += charge;
    }
    //for when the battery is charged fully
    //making sure the charge isnt something like 100.5
    if (charge_lvl_ > max_charge_) {
        charge_lvl_ = max_charge_;
        is_max_charge_ = true;
    }
}

float Battery::GetCharge() const {
    return charge_lvl_;
}

void Battery::SetCharge(float charge) {
    //cannot give it negative charge
    if (charge < 0) {
        charge = 10000;
    }
    charge_lvl_ = charge;
    max_charge_ = charge;
}

bool Battery::IsDead() {
    return (charge_lvl_ <= 0 ? true : false);
}

 bool Battery::IsMaxCharge() {
     return (charge_lvl_ == max_charge_);
 }

}  // namespace csci3081
