#include "robot.h"
#include "parabolic_strategy.h"
#include "beeline_strategy.h"
#include "smart_strategy.h"
#include <vector>
#include <iostream>


namespace csci3081 {

Robot::Robot(std::vector<float> position, std::vector<float> direction,
                                        const picojson::object& details) {
  // TODO for lab10: store the position and direction vectors.
  name_ = JsonHelper::GetString(details, "name");
  type_ = JsonHelper::GetString(details, "type");
  position_ = position;
  direction_ = direction;
  radius_ = 1.0;
  speed_ = 30.0;
  is_dynamic_ = false;
  has_packages_ = false;
  packages_delivered_ = false;

  if(JsonHelper::ContainsKey(details, "capacity")){
    carrying_capacity = JsonHelper::GetDouble(details, "capacity");
  }else{
    carrying_capacity = 100.0;
  }
  current_weight = 0.0;

  // The following line saves the json object in the details_ member variable
  // from the EntityBase class, in order to return it later in GetDetails()
  details_ = details;

  //the battery is given a default value if the json does not include one
  float charge = 10000.0;
  bool contains = JsonHelper::ContainsKey(details, "battery_capacity");
  if (contains) {
    charge = JsonHelper::GetDouble(details, "battery_capacity");
  }
  battery_ = new Battery(charge);

  m =  new Vector2D();
  speed_ = JsonHelper::GetDouble(details, "speed");
  //id_ = GenerateId();
  id_ = super_id_;
  if (JsonHelper::ContainsKey(details, "path")) {
     std::string path_type = JsonHelper::GetString(details, "path");
     if (path_type == "smart") {
        path_strategy = new Smart();
     }
     else if (path_type == "beeline") {
        path_strategy = new Beeline();
     }
     else {
        std::cout << "Path type does not exist." << std::endl;
        path_strategy = new Smart();
     }
  }
  else {
     path_strategy = new Smart();
  }
}

Robot::~Robot() {
  //deallocate all dynamic memory
  delete battery_;
  battery_ = nullptr;
  delete m;
  delete path_strategy;
  m = nullptr;
  //delete package_;
}

void Robot::UpdateEntity(float dt) {
  //implementing the "smart path" traversing the vertices of a path in travel_path_ and 
  //deliver_path_ until it reaches the end of those two paths. 

  //ONLY do the following if the robot is "dynamic" otherwise will throw exceptions
  //from the following vector operations
  //the robot does not have the package so it must get it
  if (has_packages_ == false && is_dynamic_ == true) { 
    curr_dest_ = all_travel_paths_.at(0).at(0);
    direction_ = m->CalcDirection(curr_dest_, position_);
    //if the robot hasn't reached a node in the path then move towards it
    if (m->CalcMagnitude(direction_) > radius_) {
      direction_ = m->Normalize(direction_);
      std::vector<float> velocity = m->CalcVelocity(direction_, speed_);
      std::vector<float> distance = m->CalcDistance(velocity, dt);
      position_ = m->EulerianIntegration(position_, distance);

      //Update the positions of all of the packages that have been picked up so far.
      for (Package* package : pickedUpPackages_) {
        package->SetPosition(position_);
      }

      battery_->UseBattery(dt);
      //if the robots battery is dead it cannot move
      if (battery_->IsDead()) {
        is_dynamic_ = false;
        picojson::value idle_event = createEvent("idle");
        Notify(idle_event, (*this));
        return;
      }
    }
    else {    //if the robot has reached a node then get the next node
      all_travel_paths_.at(0).erase(all_travel_paths_.at(0).begin());
    }

    //the robot has reached the package and must pick it up
    if (all_travel_paths_.at(0).size() == 0) {
      packages_.at(0)->SetISDynamic(true);

      picojson::value event = packages_.at(0)->createEvent("en route");
      packages_.at(0)->Notify(event, (*packages_.at(0)));

      picojson::value event2 = createEvent("moving");
      Notify(event2, (*this));

      //The package has been picked up, so it will be moved to 
      //the vector of picked up packages.
      pickedUpPackages_.push_back(packages_.front());
      packages_.erase(packages_.begin());

      //We are done with this route. Notify() needs an empty path
      //to function properly, so this route is being erased after
      //the Notify() calls.
      all_travel_paths_.erase(all_travel_paths_.begin());
      if(all_travel_paths_.size() == 0){
        //all assigned packages have been picked up.
        has_packages_ = true;
      }
    }
  } 
  //now the robot has the package and must deliver to the customer
  else if (has_packages_ == true && is_dynamic_ == true) {
    curr_dest_ = all_delivery_paths_.at(0)[0];
    direction_ = m->CalcDirection(curr_dest_, position_);
    // picojson::value Pevent = createEvent("moving");
    // Notify(Pevent, (*this));
    //if the robot hasn't reached a node in the path then move towards it
    if (m->CalcMagnitude(direction_) > radius_) {
      direction_ = m->Normalize(direction_);
      std::vector<float> velocity = m->CalcVelocity(direction_, speed_);
      std::vector<float> distance = m->CalcDistance(velocity, dt);
      position_ = m->EulerianIntegration(position_, distance);

      //Update the positions of all of the carried packages.
      for (Package* package : pickedUpPackages_) {
        package->SetPosition(position_);
      }

      battery_->UseBattery(dt);
      //if the robot's battery is dead it cannot move
      if (battery_->IsDead()) {
        is_dynamic_ = false;
        picojson::value idle_event = createEvent("idle");
        Notify(idle_event, (*this));
        return;
      }
    }
    else {    //if the robot has reached a node then get the next node
      all_delivery_paths_.at(0).erase(all_delivery_paths_.at(0).begin());
    }
    //the robot has reached the customer and the package 
    //is removed from the scene
    if (all_delivery_paths_.at(0).size() == 0) {
      picojson::value event = pickedUpPackages_.at(0)->createEvent("delivered");
      pickedUpPackages_.at(0)->Notify(event, (*pickedUpPackages_.at(0)));
      //packages_delivered_ = true;

      std::vector<float> teleport = {1000,1000,1000};
      pickedUpPackages_.at(0)->SetPosition(teleport);

      //remove the delivered package and the path that brought
      //the robot to the customer that was just reached.
      pickedUpPackages_.erase(pickedUpPackages_.begin());
      all_delivery_paths_.erase(all_delivery_paths_.begin());

      if(all_delivery_paths_.size() == 0) {
        //There are no more customers to deliver to.
        
        all_delivery_paths_.clear();
        all_travel_paths_.clear();
        packages_.clear();
        pickedUpPackages_.clear();
        has_packages_ = false;
        is_dynamic_ = false;
        current_weight = 0.0;

        picojson::value Devent = createEvent("idle");
        Notify(Devent, (*this));
      }
    }
  }



} // end UpdateEntity function

}  // namespace csci3081
