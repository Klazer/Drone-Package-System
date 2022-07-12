#include "delivery_simulation.h"
#include "entity_base.h"
#include "json_helper.h"
#include "drone.h"
#include "robot.h"
#include "package.h"
#include "customer.h"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() {
	//Add DeliverySimulation to observe the entities. This is to reschedule packages at appropriate times.
	observers_.push_back(this);

    composite.AddFactory(new DroneFactory());
    composite.AddFactory(new CustomerFactory());
    composite.AddFactory(new PackageFactory());
    composite.AddFactory(new RobotFactory());

    factory = &composite;

    currentlyScheduling = false;
	
}

DeliverySimulation::~DeliverySimulation() {
	//delete and return any dynamic memory used in  delivery_simulation
}
 
IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
  //TODO for lab10: replace the ?????'s with the appropriate values,
  //  then uncomment the section of code
  /*
  if (JsonHelper::GetString(val, "type") == "drone") {
    std::vector<float> position = JsonHelper::GetStdFloatVector(val, "position");
    std::vector<float> direction = JsonHelper::GetStdFloatVector(val, "direction");
    return new Drone(position, direction, val);
  }
  */
  return factory->CreateEntity(val);
  //return NULL;
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	composite.AddFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
    entities_.push_back(entity);
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	graph_ = graph;
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	Package* a_package = dynamic_cast<Package*>(package);
   picojson::value scheduled_event = a_package->createEvent("scheduled");
   currentlyScheduling = true;
	//bool found = false;

	EntityBase* entityBase;
	for (IEntity* entity : entities_) {
		entityBase = dynamic_cast<EntityBase*>(entity);
		
		//find an idle drone
		if ((entityBase->GetType() == "drone")) {   
			Drone* drone = dynamic_cast<Drone*>(entityBase);
			if(!drone->IsDead() && drone->CanTakePackage(a_package->GetWeight())){
				//give that drone a reference to a package and set that packages destination 
				//the customers location.
				//drone = entity;
				a_package->SetDestination(dest->GetPosition());
				a_package->SetDestinationEntity(dest);
				a_package->SetObservers(observers_);

				drone->SetISDynamic(true);
				drone->SetObservers(observers_);

				//If the drone does not have any packages scheduled to be delivered by it
				//yet, assign the package with paths from the drone to the pacakge to the
				//customer.
				if(drone->IsNothingScheduled()){
					std::cout << "NOTHING WAS SCHEDULED\n" << std::endl;
					drone->SetPackage(a_package);
					
					std::vector<float> origin = drone->GetPosition();
					std::vector<float> destination = a_package->GetPosition();
					pathInterface* strategy = drone->GetPathStrategy();
					std::vector<std::vector<float>> path = strategy->doPath(origin,
	               destination, graph_);
					drone->SetPath(path);
					
					picojson::value moving_event = drone->createEvent("moving");
					drone->Notify(moving_event, (*drone));
					drone->Notify(scheduled_event, (*package));

					origin = a_package->GetPosition();
					destination = dest->GetPosition();
					path = strategy->doPath(origin, destination, graph_);
					drone->SetDeliveryPath(path);
				}else{
					std::cout << "SOMETHING WAS ALREADY SCHEDULED\n" << std::endl;
					//If the drone already has packages scheduled to be delivered by it,
					//then assign this new package with paths from the last package assigned
					//to the drone to this new package to the first package's destination.
					//This will replace the previous path that leads to the first customer.

					//Also, a path must be set from the last package's destination to this
					//new package's destination.

					//This allows the packages to all be picked up at once, then delivered
					//in the order that they were picked up in.

					Package* lastPackage = drone->GetLastPackage();
					drone->SetPackage(a_package);//Add the package to the drone after getting the last package.

					//Set path from the last package assigned to the drone to this new package.
   					std::cout << "\nPATH FROM ONE PACKAGE TO THE NEXT" << std::endl;

					std::vector<float> origin = lastPackage->GetPosition();
					std::vector<float> destination = a_package->GetPosition();
					pathInterface* strategy = drone->GetPathStrategy();
					std::vector<std::vector<float>> path = strategy->doPath(origin,
	               destination, graph_);
					drone->SetPath(path);

					drone->Notify(scheduled_event, (*package));


					//Set path from the last customer to this package's customer.
					std::cout << "\nPATH FROM ONE CUSTOMER TO THE NEXT (double dip)" << std::endl;
					EntityBase* lastPackageDestination = dynamic_cast<EntityBase*>(lastPackage->GetDestinationEntity());
					origin = lastPackageDestination->GetPosition();
					destination = dest->GetPosition();
					path = strategy->doPath(origin, destination, graph_);
					drone->SetDeliveryPath(path);

					//Set path from this package to the first package's customer.
					//This is the path that takes the drone from picking up packages
					//to delivering the packages to the customers.
					std::cout << "\nPATH FROM LAST PACKAGE TO FIRST CUSTOMER" << std::endl;
					Package* firstPackage = drone->GetFirstPackage();
					EntityBase* firstPackageDestination = dynamic_cast<EntityBase*>(firstPackage->GetDestinationEntity());
					origin = a_package->GetPosition();
					destination = firstPackageDestination->GetPosition();//Get first customer's position.
					path = strategy->doPath(origin, destination, graph_);
					drone->SetTransitionPath(path);
				}
				currentlyScheduling = false;
				return;
			}
		}
		else if ((entityBase->GetType() == "robot")) {   
			Robot* robot = dynamic_cast<Robot*>(entityBase);
			if(!robot->IsDead() && robot->CanTakePackage(a_package->GetWeight())){
				//give that robot a reference to a package and set that packages destination 
				//the customers location.
				//robot = entity;
				a_package->SetDestination(dest->GetPosition());
				a_package->SetDestinationEntity(dest);
				a_package->SetObservers(observers_);

				robot->SetISDynamic(true);
				robot->SetObservers(observers_);

				//If the robot does not have any packages scheduled to be delivered by it
				//yet, assign the package with paths from the robot to the pacakge to the
				//customer.
				if(robot->IsNothingScheduled()){
					std::cout << "NOTHING WAS SCHEDULED\n" << std::endl;
					robot->SetPackage(a_package);
					
					std::vector<float> origin = robot->GetPosition();
					std::vector<float> destination = a_package->GetPosition();
					pathInterface* strategy = robot->GetPathStrategy();
					std::vector<std::vector<float>> path = strategy->doPath(origin,
	               destination, graph_);
					robot->SetPath(path);
					
					picojson::value moving_event = robot->createEvent("moving");
					robot->Notify(moving_event, (*robot));
					robot->Notify(scheduled_event, (*package));

					origin = a_package->GetPosition();
					destination = dest->GetPosition();
					path = strategy->doPath(origin, destination, graph_);
					robot->SetDeliveryPath(path);
				}else{
					std::cout << "SOMETHING WAS ALREADY SCHEDULED\n" << std::endl;
					//If the robot already has packages scheduled to be delivered by it,
					//then assign this new package with paths from the last package assigned
					//to the robot to this new package to the first package's destination.
					//This will replace the previous path that leads to the first customer.

					//Also, a path must be set from the last package's destination to this
					//new package's destination.

					//This allows the packages to all be picked up at once, then delivered
					//in the order that they were picked up in.

					Package* lastPackage = robot->GetLastPackage();
					robot->SetPackage(a_package);//Add the package to the robot after getting the last package.

					//Set path from the last package assigned to the robot to this new package.
   					std::cout << "\nPATH FROM ONE PACKAGE TO THE NEXT" << std::endl;

					std::vector<float> origin = lastPackage->GetPosition();
					std::vector<float> destination = a_package->GetPosition();
					pathInterface* strategy = robot->GetPathStrategy();
					std::vector<std::vector<float>> path = strategy->doPath(origin,
	               destination, graph_);
					robot->SetPath(path);

					robot->Notify(scheduled_event, (*package));


					//Set path from the last customer to this package's customer.
					std::cout << "\nPATH FROM ONE CUSTOMER TO THE NEXT (double dip)" << std::endl;
					EntityBase* lastPackageDestination = dynamic_cast<EntityBase*>(lastPackage->GetDestinationEntity());
					origin = lastPackageDestination->GetPosition();
					destination = dest->GetPosition();
					path = strategy->doPath(origin, destination, graph_);
					robot->SetDeliveryPath(path);

					//Set path from this package to the first package's customer.
					//This is the path that takes the robot from picking up packages
					//to delivering the packages to the customers.
					std::cout << "\nPATH FROM LAST PACKAGE TO FIRST CUSTOMER" << std::endl;
					Package* firstPackage = robot->GetFirstPackage();
					EntityBase* firstPackageDestination = dynamic_cast<EntityBase*>(firstPackage->GetDestinationEntity());
					origin = a_package->GetPosition();
					destination = firstPackageDestination->GetPosition();//Get first customer's position.
					path = strategy->doPath(origin, destination, graph_);
					robot->SetTransitionPath(path);
				}
				currentlyScheduling = false;
				return;
			}
		}
	}

	//There were no available deliverer entities.
	//Push the package and customer into the backlog to be scheduled later.
	std::cout << "THE PACKAGE IS BEING PUT BACK INTO THE BACKLOG\n" << std::endl;
	packageBacklog.push_back(package);
	destinationBacklog.push_back(dest);
	currentlyScheduling = false;
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	observers_.push_back(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end()); 
}

std::vector<IEntityObserver*> DeliverySimulation::GetObservers(){
	return observers_;
}

void DeliverySimulation::OnEvent(const picojson::value &event, const IEntity &entity) {
	//Instead of seeing what the notification was specifically, just
	//check if a package needs rescheduling each time a notification
	//is recieved. It's not ideal, but it is better than checking
	//everytime Update() is called.

	//Ignore any notifications recieved from pacakges being scheduled.
	//Since this function calls ScheduleDelivery, not ignoring these
	//notifications will result in recursion, which causes trouble
	//since multiple packages will be scheduled at once.
	if(currentlyScheduling){
		return;
	}

	// //Check if there are any dead deliverers that need their package rescheduled.
	EntityBase* an_entity;
	std::vector<Package*> packagesToReschedule;
	for (IEntity* entity : entities_) {
		an_entity = dynamic_cast<EntityBase*>(entity);
		
		//Check if the entity is s deliverer.
		if(an_entity->GetType() == "robot" || an_entity->GetType() == "drone"){
			if(an_entity->GetType() == "robot"){
				Robot *robot = dynamic_cast<Robot*>(an_entity);
				if(robot->IsDead() && robot->GetPackages().size() != 0){
					//if the deliverer's battery is dead and has packages it needs to deliver,
					//backlog the packages and their destinations to be rescheduled later.
					packagesToReschedule = robot->GetPackages();

					for (Package* package : packagesToReschedule) {
						packageBacklog.push_back(package);
						destinationBacklog.push_back(package->GetDestinationEntity());
					}

					//Also, remove the packages from the robot.
					robot->SetHasPackage(false);
					robot->ClearDeliveries();
				}
			}else if(an_entity->GetType() == "drone"){
				Drone *drone = dynamic_cast<Drone*>(an_entity);
				if(drone->IsDead() && drone->GetPackages().size() != 0){
					//if the deliverer is dead and has a package it needs to deliver,
					//backlog the package and its destination to be rescheduled later.
					packagesToReschedule = drone->GetPackages();

					for (Package* package : packagesToReschedule) {
						packageBacklog.push_back(package);
						destinationBacklog.push_back(package->GetDestinationEntity());
					}

					//Also, remove the packages from the drone.
					drone->SetHasPackage(false);
					drone->ClearDeliveries();
				}
			}

		}
	}

	std::vector<IEntity*> packageBacklogTemp;
    std::vector<IEntity*> destinationBacklogTemp;
	//Check if there are any available deliverers to schedule a backlogged package to.
	for (IEntity* entity : entities_) {
		an_entity = dynamic_cast<EntityBase*>(entity);
		
		//If there are packages in the backlog waiting to be scheduled and the current entity
		//is a deliverer.
		if(packageBacklog.size() != 0 && (an_entity->GetType() == "robot" || an_entity->GetType() == "drone")){
			std::cout << "A robot or drone is checked because there is a backlog.\n" << std::endl;
			if(an_entity->GetType() == "robot"){
				Robot *robot = dynamic_cast<Robot*>(an_entity);
				//if the deliverer is not currently making a delivery (not dynamic) and does not have
				//a dead battery, then assign as many packages as possible to be delivered by it.
				if(!robot->IsDynamic() && !robot->GetHasPackages()){
					while(true){
						int backlogCount = packageBacklog.size();
						//If there are no more backlogged packages, stop scheduling.
						if(backlogCount == 0){
							//move all of the packages back into the backlog
							//from the temporary stack.
							while(packageBacklogTemp.size() != 0){
								packageBacklog.push_back(packageBacklogTemp.back());
								destinationBacklog.push_back(destinationBacklogTemp.back());
								packageBacklogTemp.pop_back();
								destinationBacklogTemp.pop_back();
							}
							return;
						}

						std::cout << "A\nA\nA\nThe package is being rescheduled.\nA\nA\nA\n" << std::endl;
						IEntity* backLogPackage = packageBacklog.back();
						IEntity* backLogDestination = destinationBacklog.back();
						packageBacklog.pop_back();
						destinationBacklog.pop_back();
						this->ScheduleDelivery(backLogPackage, backLogDestination);
						
						//If the package was not assigned to the drone,
						//push it to the temp stack so the next package
						//assignment can be attempted.
						if(backlogCount == packageBacklog.size()){
							packageBacklogTemp.push_back(packageBacklog.back());
							destinationBacklogTemp.push_back(destinationBacklog.back());
							packageBacklog.pop_back();
							destinationBacklog.pop_back();
						}
					}
				}
			}else if(an_entity->GetType() == "drone"){
				Drone *drone = dynamic_cast<Drone*>(an_entity);
				//if the deliverer is not currently making a delivery (not dynamic) and does not have
				//a dead battery, then assign as many packages as possible to be delivered by it.
				if(!drone->IsDead() && !drone->GetHasPackages()){
					while(true){
						int backlogCount = packageBacklog.size();
						//If there are no more backlogged packages, stop scheduling.
						if(backlogCount == 0){
							//move all of the packages back into the backlog
							//from the temporary stack.
							while(packageBacklogTemp.size() != 0){
								packageBacklog.push_back(packageBacklogTemp.back());
								destinationBacklog.push_back(destinationBacklogTemp.back());
								packageBacklogTemp.pop_back();
								destinationBacklogTemp.pop_back();
							}
							return;
						}

						std::cout << "A\nA\nA\nThe package is being rescheduled.\nA\nA\nA\n" << std::endl;
						IEntity* backLogPackage = packageBacklog.back();
						IEntity* backLogDestination = destinationBacklog.back();
						packageBacklog.pop_back();
						destinationBacklog.pop_back();
						this->ScheduleDelivery(backLogPackage, backLogDestination);
						
						//If the package was not assigned to the drone,
						//push it to the temp stack so the next package
						//assignment can be attempted.
						if(backlogCount == packageBacklog.size()){
							packageBacklogTemp.push_back(packageBacklog.back());
							destinationBacklogTemp.push_back(destinationBacklog.back());
							packageBacklog.pop_back();
							destinationBacklog.pop_back();
						}
					}
				}
			}

		}
	}
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	EntityBase* an_entity;
	for (IEntity* entity : entities_) {
		an_entity = dynamic_cast<EntityBase*>(entity);
		an_entity->UpdateEntity(dt);
	}
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {

	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
