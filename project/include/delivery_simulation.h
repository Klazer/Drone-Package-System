
/**
 * @file delivery_simulation.h
 */
#ifndef DELIVERY_SIMULATION_H_
#define DELIVERY_SIMULATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/entity_observer.h>
#include <vector>
#include <string>
#include "drone_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include "robot_factory.h"
#include "composite_factory.h"
#include "vector3d.h"
#include <EntityProject/entity_observer.h>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This is the facade for the delivery system
 *
 * This class will delegate operations for the whole drone delivery system.
 * See the documentation for IDeliverySystem for more information.
 */

// DO NOT MODIFY (unless you really know what you are doing)
class DeliverySimulation : public IDeliverySystem, entity_project::IEntityObserver {
 public:
  /**
   * @brief Constructor: this can do any setup your system necessitates.
   */
  DeliverySimulation();

  /// Desconstructor: This should free any memory that your program uses.
  ~DeliverySimulation();

  /**
  Given the picojson::object val, this should create an entity.
  Based on the type of entity, there may be different fields.
  You can see the vals that will be passed in the project/web/scenes
    directory. Some of the fields are for our backend system and you don't
    need to worry about them. (for instance, mesh, rotation, offset, etc.)

  Some fields in val that you will need to create the entity correctly:

    type: string (could be "drone/customer/package")

    name: string

    position: array (contains [x_position, y_position, z_position])

    direction: array (contains [x, y, z])

    speed: float

    battery_capacity: float

  Don't add the entity to the simulation until it is passed in via AddEntity
  */
  IEntity* CreateEntity(const picojson::object& val);

  /**
   *  This function should add a factory to the composite factory pattern
   */
  void AddFactory(IEntityFactory* factory);

  /**
   *  This function should add an entity to the simulation
   */
  void AddEntity(IEntity* entity);

  /**
  This function should simply store a reference to the IGraph* somewhere.
  The IGraph contains useful functions such as the GetPath function which can 
  be used to get a path from one position to another.
  */
  void SetGraph(const IGraph* graph);

  /**
  This function tells the simulation that the IEntity* package should be delivered
  to the IEntity* dest (which is likely a customer). How the delivery takes place
  is entirely dependent on how you design your code, but it should involve a drone
  navigating to the package, picking it up, and then moving to the customer and 
  dropping the package.
  */
  void ScheduleDelivery(IEntity* package, IEntity* dest);

  /**
   * @brief A function to add an observer to the scene
   *
   * @param[in] observer The observer to be added
   * */
  void AddObserver(IEntityObserver* observer);

  /**
   * @brief a function to remove an observer from the scene
   * 
   * @param[in] observer The observer to be removed
   * */
  void RemoveObserver(IEntityObserver* observer);

  /**
   * @brief A function to return all observers in a scene
   *
   * @returns All observers in the scene
   * */
  std::vector<IEntityObserver*> GetObservers();

    /**
   * @brief A function to recieve notificaions of events from the subjects (the entities) that occur in the simulation.
   * This reschedules packages that are not being delivered because no deliverers are available or because the package's deliverer's battery died.
   *
   * @param[in] event A json representation of an event.
   * @param[in] entity The entity that the event concerns.
   */
  void OnEvent (const picojson::value &event, const IEntity &entity);

  /**
   * @brief A function to notify observers of events that occur in the simulation
   *
   * @param[in] event A json representation of an event.
   * @param[in] entity The entity that the event concerns.
   */
   void Notify(const picojson::value& event, const IEntity& entity) const;

  /**
   * @brief A function to return all entities in a scene
   *
   * @returns All entities in the current scene
   * */
  const std::vector<IEntity*>& GetEntities() const;

  /**
  This function is used to advance time in the simulation. float dt refers to the 
  amount of time the update call should advance the simulation by. For instance if a drone
  moves 1 unit of distance per unit of time, and Update is called with dt=.05, then the
  drone should move 1 * .05 = .05 units of distance.

  Some things that should happen in the Update function: move drones, check if
  packages have been delivered to customers, etc.
  */

  /**
   * @brief A function used to advance time in the simulation
   *
   * @param[in] dt The amount of time the simulation should be advanced by
   * */
  void Update(float dt);

  /**
   * @brief You do not need to worry about this function
   * 
   * This function takes care of turning json into function calls of your system.
   * YOU DO NOT NEED TO IMPLEMENT THIS
   *it is already implemented in the delivery_simulation.cc we have provided.
   */
  void RunScript(const picojson::array& script, IEntitySystem* system) const;

 private:
    // You don't strictly need to use the following variable, but it is probably
    // the most straightforward way of storing the entities in the system.
    // Feel free to use it as is or change it.
    std::vector<IEntity*> entities_;
    std::vector<IEntityObserver*> observers_;
    bool currentlyScheduling;

    const IGraph* graph_;

    CompositeFactory composite;
    IEntityFactory* factory;
    std::vector<IEntity*> packageBacklog;
    std::vector<IEntity*> destinationBacklog;

    Vector3D m;
};

}  // namespace csci3081

#endif  // DELIVERY_SIMULATION_H_

