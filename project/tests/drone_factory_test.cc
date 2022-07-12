#include "gtest/gtest.h"
#include "json_helper.h"
#include "entity_base.h"
#include "ientity_factory.h"
#include "drone_factory.h"
#include <iostream>

namespace csci3081 {

class DroneFactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
      //factory = dynamic_cast<IENTITY_FACTORY*>(dfact);
      factory = new DroneFactory();

  }
  virtual void TearDown() {}

  //IEntity_Factory* factory;
  DroneFactory* factory;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(DroneFactoryTest, DroneCreated) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");
  JsonHelper::AddStringToJsonObject(obj, "name", "drone");
  JsonHelper::AddFloatToJsonObject(obj, "speed", 30.0);
  std::vector<float> position_to_add{498.292,253.883,-228.623};
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  std::vector<float> direction_to_add{1,0,0};
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  IEntity* entity = factory->CreateEntity(obj);

  // Checks that the returned entity is not NULL
  ASSERT_NE(entity, nullptr) << "The entity created";
  //system->AddEntity(entity);
  //ASSERT_EQ(1, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity->GetDirection()[2], direction_to_add[2]);

  // Checks that when GetDetails() is called, the entity returns 
  //  the picojson object that was used to initialize it
  ASSERT_EQ(picojson::value(entity->GetDetails()).serialize(), picojson::value(obj).serialize());

}

}  // namespace csci3081
