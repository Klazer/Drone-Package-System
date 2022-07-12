#include "deliverer.h"
#include "parabolic_strategy.h"
#include "beeline_strategy.h"
#include "smart_strategy.h"
#include <vector>
#include <iostream>


namespace csci3081 {

float Deliverer::GetSpeed() const {
  return speed_;
}

void Deliverer::SetSpeed(float speed) {
  speed_ = speed;
}

pathInterface* Deliverer::GetPathStrategy() const {
   return path_strategy;
}

void Deliverer::SetPackage(Package* package) {
  packages_.push_back(package);
}

std::vector<Package*> Deliverer::GetPackages(){
  allPackages_.clear();
  allPackages_.insert(allPackages_.end(), packages_.begin(), packages_.end() );
  allPackages_.insert(allPackages_.end(), pickedUpPackages_.begin(), pickedUpPackages_.end() );
  return allPackages_;
}

void Deliverer::ClearDeliveries() {
  all_delivery_paths_.clear();
  all_travel_paths_.clear();
  packages_.clear();
  pickedUpPackages_.clear();
  has_packages_ = false;
  is_dynamic_ = false;
  current_weight = 0.0;
}

Package* Deliverer::GetLastPackage(){
  return packages_.back();
}

Package* Deliverer::GetFirstPackage(){
  return packages_.front();
}

bool Deliverer::GetHasPackages() const {
  return has_packages_;
}

void Deliverer::SetHasPackage(bool state) {
  has_packages_ = state;
}

bool Deliverer::IsDead() const {
  return battery_->IsDead();
}

bool Deliverer::IsNothingScheduled() const {
  if(packages_.size() == 0){
    return true;
  }else{
    return false;
  }
}

bool Deliverer::CanTakePackage(float weight){
  //This checks if the package's weight can be handled
  //and if the deliverer is still picking up packages.
  bool result = ((weight + current_weight) < carrying_capacity) && !has_packages_;
  if(result){
    //If the package can be assigned, add the package's weight.
    current_weight += weight;
  }
  return result;
}

void Deliverer::SetPath(std::vector<std::vector<float>> path) {
  all_travel_paths_.push_back(path);
}

std::vector<std::vector<float>> Deliverer::GetPath() {
  return all_travel_paths_.at(0);
}

void Deliverer::SetDeliveryPath(std::vector<std::vector<float>> path) {
  all_delivery_paths_.push_back(path);
}

void Deliverer::SetTransitionPath(std::vector<std::vector<float>> path) {
  if(all_delivery_paths_.size() == 0){
    return;
  }

  all_delivery_paths_.erase(all_delivery_paths_.begin());
  
  std::vector<std::vector<std::vector<float>>> newPath;
  newPath.push_back(path);

  all_delivery_paths_.insert(all_delivery_paths_.begin(), newPath.begin(), newPath.end());
}

std::vector<std::vector<float>> Deliverer::GetDeliveryPath() {
  return all_delivery_paths_.at(0);
}

picojson::value Deliverer::createEvent(std::string value) {
   static picojson::object e = JsonHelper::CreateJsonObject();
  
  if (value == "idle"){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "idle");
    picojson::value event(e);
    return event;
  }
  else if (value == "moving" && all_travel_paths_.at(0).size() != 0){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "moving");
    JsonHelper::AddStdVectorVectorFloatToJsonObject(e, "path", all_travel_paths_.at(0));
    picojson::value event(e);
    return event;
  }
  else if (value == "moving" && all_delivery_paths_.at(0).size() != 0){
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "moving");
    JsonHelper::AddStdVectorVectorFloatToJsonObject(e, "path", all_delivery_paths_.at(0));
    picojson::value event(e);
    return event;
  }

}

}  // namespace csci3081