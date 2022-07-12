#/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */
class EntityBase : public IEntity {
 public:
  /**
  * @brief constructor for the entity base class
  */
  EntityBase();
  
  /**
  * @brief destructor for the entity base class
  */
  virtual ~EntityBase() {}
  
  /**
  * @brief Get details function to return the picojson object of every entity
  *
  * @returns the picojson object used to initialize the object
  */
  const picojson::object& GetDetails() { return details_; }

   /**
   * @brief A getter function to return the id of an entity
   *
   * @returns The id of an entity
   * */
   int GetId() const { return id_; }

   /**
    * @brief A function to return an entity's name
    *
    * @returns An entity's name
    * */
   const std::string& GetName() { return name_; } 

   /**
    * @brief A function to return an entity's type
    *
    * @return The type of an entity
    **/
   const std::string& GetType() { return type_; }

   /**
    * @brief A function to return an entity's position
    *
    * @returns The position of an entity
    **/
   const std::vector<float>& GetPosition() const { return position_; }

   /**
    * @brief A function to set the position of an entity
    *
    * @param[in] position The new position
    **/
   void SetPosition(std::vector<float> position) { position_ = position; }

   /**
    * @brief A function to get the direction of an entity
    *
    * @returns The direction of an entity
    **/
   const std::vector<float>& GetDirection() const { return direction_; }

   /**
    * @brief A function to set the direction of an entity
    *
    * @param[in] direction The new direction
    **/
   void SetDirection(std::vector<float> direction) { direction_ = direction;}

   /**
    * @brief A function to return the radius of an entity
    *
    * @returns The radius of an entity
    **/
   float GetRadius() const { return radius_; }

   /**
    * @brief A function to return the version of an entity
    *
    * @returns The version of an entity
    **/
   int GetVersion() const { return version_; }

   /**
    * @brief A function that checks if an entity is dynamic
    *
    * @returns True if dynamic, false if not
    **/
   bool IsDynamic() const { return is_dynamic_; }

   /**
    * @brief A function to set the dynamic state of an entity
    *
    * @param[in] state True if dynamic, false if not
    **/
   void SetISDynamic(bool state) { is_dynamic_ = state; }

   /**
   * @brief function to update the entity based on the data/settings it has
   * it is through this function that the simulation moves and progresses 
   * 
   * @param[in] dt the time step to update entities by
   */
   virtual void UpdateEntity(float dt) =0;

   /**
    * @brief A function to set the observers of an entity
    *
    * @param[in] observers The observers to be set
    **/
   void SetObservers(std::vector<IEntityObserver*> observers){ observers_ = observers;}

   /**
    * @brief A function to return the observers of an  entity
    *
    * @returns An entity's observers
    **/
   std::vector<IEntityObserver*> GetObservers(){ return observers_; }

  /**
   * @brief A function to notify observers of events that occur in the simulation
   *
   * @param[in] event A json representation of an event
   * @param[in] entity The entity that the event concerns
   */
   void Notify(const picojson::value& event, const IEntity& entity) const {
      for (int i = 0; i < observers_.size(); i++) {
         observers_.at(i)->OnEvent(event, entity);
      }
   }

   /**
    * @brief A function to create a json representation of an event
    *
    * @param[in] value The type of event to create
    *
    * @returns A json representation of an event
    **/
   virtual picojson::value createEvent(std::string value) = 0;

  protected:
  std::vector<float> direction_;
  std::vector<float> position_;
  std::string name_;
  std::string type_;
  int id_;
  static int super_id_;
  float radius_;
  int version_;
  bool is_dynamic_;
  picojson::object details_;
  std::vector<IEntityObserver*> observers_;
};



}  // namespace csci3081


#endif  // ENTITY_BASE_H_
