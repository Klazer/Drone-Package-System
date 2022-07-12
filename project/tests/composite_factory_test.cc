#include "gtest/gtest.h"
#include "json_helper.h"
//#include "entity_base.h"
//#include "ientity_factory.h"
#include "drone_factory.h"
#include "robot_factory.h"
#include "customer_factory.h"
#include "package_factory.h"
#include "composite_factory.h"
//#include <iostream>

namespace csci3081 {

class CompositeFactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {

      composite.AddFactory(new DroneFactory());
      composite.AddFactory(new RobotFactory());
      composite.AddFactory(new CustomerFactory());
      composite.AddFactory(new PackageFactory());

      factory = &composite;

  }
  virtual void TearDown() {
  }
  CompositeFactory composite;
  IEntityFactory* factory;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(CompositeFactoryTest, DroneCreated) {
    
    //IEntity entity = factory->CreateEntity(obj)
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj3, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj3, "name", "drone");
    JsonHelper::AddFloatToJsonObject(obj3, "speed", 30.0);
    std::vector<float> position_to_add3{498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add3);
    std::vector<float> direction_to_add3{1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add3);
    IEntity* entity3 = factory->CreateEntity(obj3);

    // Checks that the returned entity is not NULL
    ASSERT_NE(entity3, nullptr) << "The entity created";
    //system->AddEntity(entity);
    //ASSERT_EQ(1, system->GetEntities().size());
    ASSERT_FLOAT_EQ(entity3->GetPosition()[0], position_to_add3[0]);
    ASSERT_FLOAT_EQ(entity3->GetPosition()[1], position_to_add3[1]);
    ASSERT_FLOAT_EQ(entity3->GetPosition()[2], position_to_add3[2]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[0], direction_to_add3[0]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[1], direction_to_add3[1]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[2], direction_to_add3[2]);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(entity3->GetDetails()).serialize(), picojson::value(obj3).serialize());
}

TEST_F(CompositeFactoryTest, PackageCreated) {
    
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    JsonHelper::AddStringToJsonObject(obj, "name", "package");
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

TEST_F(CompositeFactoryTest, CustomerCreated) {
    picojson::object obj2 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj2, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj2, "name", "customer");
    std::vector<float> position_to_add{498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add);
    std::vector<float> direction_to_add{1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add);
    IEntity* entity2 = factory->CreateEntity(obj2);

    // Checks that the returned entity is not NULL
    ASSERT_NE(entity2, nullptr) << "The entity created";
    //system->AddEntity(entity);
    //ASSERT_EQ(1, system->GetEntities().size());
    ASSERT_FLOAT_EQ(entity2->GetPosition()[0], position_to_add[0]);
    ASSERT_FLOAT_EQ(entity2->GetPosition()[1], position_to_add[1]);
    ASSERT_FLOAT_EQ(entity2->GetPosition()[2], position_to_add[2]);
    ASSERT_FLOAT_EQ(entity2->GetDirection()[0], direction_to_add[0]);
    ASSERT_FLOAT_EQ(entity2->GetDirection()[1], direction_to_add[1]);
    ASSERT_FLOAT_EQ(entity2->GetDirection()[2], direction_to_add[2]);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(entity2->GetDetails()).serialize(), picojson::value(obj2).serialize());
}

TEST_F(CompositeFactoryTest, RobotCreated) {
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj3, "type", "robot");
    JsonHelper::AddStringToJsonObject(obj3, "name", "robot");
    JsonHelper::AddFloatToJsonObject(obj3, "speed", 30.0);
    std::vector<float> position_to_add{498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add);
    std::vector<float> direction_to_add{1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add);
    IEntity* entity3 = factory->CreateEntity(obj3);

    // Checks that the returned entity is not NULL
    ASSERT_NE(entity3, nullptr) << "The entity created";
    //system->AddEntity(entity);
    //ASSERT_EQ(1, system->GetEntities().size());
    ASSERT_FLOAT_EQ(entity3->GetPosition()[0], position_to_add[0]);
    ASSERT_FLOAT_EQ(entity3->GetPosition()[1], position_to_add[1]);
    ASSERT_FLOAT_EQ(entity3->GetPosition()[2], position_to_add[2]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[0], direction_to_add[0]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[1], direction_to_add[1]);
    ASSERT_FLOAT_EQ(entity3->GetDirection()[2], direction_to_add[2]);

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    ASSERT_EQ(picojson::value(entity3->GetDetails()).serialize(), picojson::value(obj3).serialize());
}

}  // namespace csci3081
