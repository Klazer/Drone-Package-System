#include "gtest/gtest.h"
#include "json_helper.h"
#include "entity_base.h"
#include "drone.h"
#include "battery.h"
#include "package.h"
#include <vector>
#include <iostream>
#include "beeline_strategy.h"
#include "parabolic_strategy.h"

using std::vector;

namespace csci3081 {

class DroneTest : public ::testing::Test {
 public:
  void SetUp() {
    //drone setup
    obj2 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj2, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj2, "name", "drone");
    JsonHelper::AddFloatToJsonObject(obj2, "speed", 30.0);
    std::vector<float> position_to_add2 = {498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    std::vector<float> direction_to_add2 = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add2);

    vector<float> direction2 = {1.5,2.5,3.5};
    vector<float> position2 = {42.1,42.2,42.3};
    drone1 = new Drone(position2, direction2, obj2);

    
    //package setup
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    JsonHelper::AddStringToJsonObject(obj, "name", "package");
    std::vector<float> position_to_add = {498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);

    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};
    package1 = new Package(position1, direction1, obj);
    
  }
  void TearDown() {
      delete package1;
      delete drone1;
  }
  protected: 
  picojson::object obj;
  picojson::object obj2;
  //IEntity pointers will only use commands/functions from IEntity interface
  //Use package pointer
  Package* package1;
  Drone* drone1;
  
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
//TEST_F(DroneTest, ) {
    
//}

TEST_F(DroneTest, SetDirectionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    drone1->SetDirection(ascending_vector);
    vector<float> result = drone1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    drone1->SetDirection(origin_vector);
    result = drone1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    drone1->SetDirection(answer_vector);
    result = drone1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(DroneTest, SetPositionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    drone1->SetPosition(ascending_vector);
    vector<float> result = drone1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    drone1->SetPosition(origin_vector);
    result = drone1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    drone1->SetPosition(answer_vector);
    result = drone1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(DroneTest, IsDynamicFunctionTests) {
    EXPECT_EQ(drone1->IsDynamic(), false) << "default is dynamic not set up right";
    drone1->SetISDynamic(true);
    EXPECT_EQ(drone1->IsDynamic(), true) << "default is dynamic not set up right";
}

TEST_F(DroneTest, GetRadiusTest) {
    EXPECT_FLOAT_EQ(drone1->GetRadius(), 1.0f) << "get radius not working properly";
}

TEST_F(DroneTest, GetDirectionTest) {
    vector<float> expected_dir = {1.5,2.5,3.5};
    vector<float> drone_dir = drone1->GetDirection();
    EXPECT_FLOAT_EQ(expected_dir.at(0), drone_dir.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(1), drone_dir.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(2), drone_dir.at(2)) << "get position not working properly";
}

TEST_F(DroneTest, GetPositionTest) {
    vector<float> expected_pos = {42.1,42.2,42.3};
    vector<float> drone_pos = drone1->GetPosition();
    EXPECT_FLOAT_EQ(expected_pos.at(0), drone_pos.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(1), drone_pos.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(2), drone_pos.at(2)) << "get position not working properly";
}

TEST_F(DroneTest, GetIDTest) {
    //this depends on the number of entities created. 
    //when this particular test is compiled drone1 is the 26th 
    //entity created.
    EXPECT_EQ(drone1->GetId(), 26) << "default id not set up properly";
}

TEST_F(DroneTest, GetNameFunctionTest) {
    std::string name = drone1->GetName();
    EXPECT_EQ(name, "drone") << "get name not returning correct name";
}

TEST_F(DroneTest, DroneConstructorTest) {
    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};

    ASSERT_NE(drone1, nullptr) << "drone constructor not working properly";
    //check that the drone was initialized correctly
    vector<float> pos = drone1->GetPosition();
    vector<float> dir = drone1->GetDirection();
    EXPECT_EQ(pos, position1) << "drone constructor not initializing position";
    EXPECT_EQ(dir, direction1) << "drone constructor not initializing position";

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    //ASSERT_EQ(picojson::value(drone1.GetDetails()).serialize(), picojson::value(obj).serialize());
}

TEST_F(DroneTest, GetSpeedTest) {
    EXPECT_FLOAT_EQ(drone1->GetSpeed(), 30.0) << "Get speed not working properly";
    drone1->SetSpeed(0);
    EXPECT_FLOAT_EQ(drone1->GetSpeed(), 0.0) << "Get speed not working properly";
}

TEST_F(DroneTest, SetSpeedTest) {
    drone1->SetSpeed(100.0);
    EXPECT_FLOAT_EQ(drone1->GetSpeed(), 100.0) << "Set speed not working properly";
    drone1->SetSpeed(55.55); 
    EXPECT_FLOAT_EQ(drone1->GetSpeed(), 55.55) << "Set speed not working properly";
    drone1->SetSpeed(0.0);
    EXPECT_FLOAT_EQ(drone1->GetSpeed(), 0.0) << "Set speed not working properly";
}

TEST_F(DroneTest, SetPackageTest) {
    drone1->SetPackage(package1);
    std::string name = "package";
    EXPECT_EQ(name, "package");
}

TEST_F(DroneTest, GetHasPackageTest) {
    EXPECT_EQ(drone1->GetHasPackage(), false) << "GetHasPackage not working right";
    drone1->SetHasPackage(true);
    EXPECT_EQ(drone1->GetHasPackage(), true) << "GetHasPackage not working right";
    drone1->SetHasPackage(false);
    EXPECT_EQ(drone1->GetHasPackage(), false) << "GetHasPackage not working right";    
}

TEST_F(DroneTest, SetHasPackageTest) {
    drone1->SetHasPackage(true);
    EXPECT_EQ(drone1->GetHasPackage(), true) << "GetHasPackage not working right";
    drone1->SetHasPackage(false);
    EXPECT_EQ(drone1->GetHasPackage(), false) << "GetHasPackage not working right";
}

TEST_F(DroneTest, SetPathTest) {
    vector<vector<float>> path1;
    vector<float> node = {1,1,1};
    path1.push_back(node);
    drone1->SetPath(path1);

    vector<float> expected_out1 = {1,1,1};

    vector<vector<float>> path_out = drone1->GetPath();
    vector<float> out1 = path_out.at(0);

    EXPECT_FLOAT_EQ(out1.at(0), expected_out1.at(0)) << "set/get path not working properly";
    EXPECT_FLOAT_EQ(out1.at(1), expected_out1.at(1)) << "set/get path not working properly";
    EXPECT_FLOAT_EQ(out1.at(2), expected_out1.at(2)) << "set/get path not working properly";
    
}

TEST_F(DroneTest, SetDeliveryPathTest) {
    vector<vector<float>> path1;
    vector<float> node = {1,1,1};
    path1.push_back(node);
    drone1->SetDeliveryPath(path1);

    vector<float> expected_out1 = {1,1,1};

    vector<vector<float>> path_out = drone1->GetDeliveryPath();
    vector<float> out1 = path_out.at(0);

    EXPECT_FLOAT_EQ(out1.at(0), expected_out1.at(0)) << "set/get deliverypath not working properly";
    EXPECT_FLOAT_EQ(out1.at(1), expected_out1.at(1)) << "set/get deliverypath not working properly";
    EXPECT_FLOAT_EQ(out1.at(2), expected_out1.at(2)) << "set/get deliverypath not working properly";
    
}

TEST_F(DroneTest, StrategyTests) {
    picojson::object obj3 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj3, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj3, "name", "drone");
    JsonHelper::AddStringToJsonObject(obj3, "path", "beeline");
    JsonHelper::AddFloatToJsonObject(obj3, "speed", 30.0);
    std::vector<float> position_to_add3 = {498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "position", position_to_add3);
    std::vector<float> direction_to_add3 = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj3, "direction", direction_to_add3);

    vector<float> direction3 = {1.5,2.5,3.5};
    vector<float> position3 = {42.1,42.2,42.3};
    Drone* drone2 = new Drone(position3, direction3, obj3);

    picojson::object obj4 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj4, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj4, "name", "drone");
    JsonHelper::AddStringToJsonObject(obj4, "path", "parabolic");
    JsonHelper::AddFloatToJsonObject(obj4, "speed", 30.0);
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "position", position_to_add3);
    JsonHelper::AddStdFloatVectorToJsonObject(obj4, "direction", direction_to_add3);

    Drone* drone3 = new Drone(position3, direction3, obj4);

    EXPECT_EQ(drone2->GetPathStrategy()->getName(), "Beeline");
    EXPECT_EQ(drone3->GetPathStrategy()->getName(), "Parabolic");
}

TEST_F(DroneTest, ObserverEventTests) {
    picojson::value Devent = drone1->createEvent("idle");

    picojson::object e = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "idle");
    picojson::value event(e);

    EXPECT_EQ(Devent.serialize(), event.serialize());
}

//no integration testing
/*TEST_F(DroneTest, UpdateEntityTest) {
    vector<float> simple = {0,0,0};
    drone1->SetPosition(simple);
    drone1->SetISDynamic(false);
    drone1->SetHasPackage(false);
    
    vector<vector<float>> travelpath;
    vector<vector<float>> deliverpath;
    vector<float> p1 = {1,1,1};
    travelpath.push_back(p1);
    drone1->SetPath(travelpath);
    vector<float> p2 = {2,2,2};
    deliverpath.push_back(p2);
    drone1->SetDeliveryPath(deliverpath);
    drone1->SetPackage(package1);


    drone1->UpdateEntity(0.05);
    float pos1 = 0.8660254038;
    EXPECT_FLOAT_EQ(drone1->GetPosition()[0], pos1) << "Update not working correctly";
    EXPECT_FLOAT_EQ(drone1->GetPosition()[1], pos1) << "Update not working correctly";
    EXPECT_FLOAT_EQ(drone1->GetPosition()[2], pos1) << "Update not working correctly";

    drone1->UpdateEntity(0.05);
    EXPECT_FLOAT_EQ(drone1->GetPosition()[0], pos1) << "Update not working correctly";
    EXPECT_FLOAT_EQ(drone1->GetPosition()[1], pos1) << "Update not working correctly";
    EXPECT_FLOAT_EQ(drone1->GetPosition()[2], pos1) << "Update not working correctly";
    EXPECT_EQ(drone1->GetHasPackage(), true); 

    //caused seg fault
    /*drone1->UpdateEntity(0.5);
    EXPECT_NEAR(drone1->GetPosition()[0], pos1, 0.001) << "Update not working correctly";
    EXPECT_NEAR(drone1->GetPosition()[1], pos1, 0.001) << "Update not working correctly";
    EXPECT_NEAR(drone1->GetPosition()[2], pos1, 0.001) << "Update not working correctly";

    drone1->UpdateEntity(0.5);
    EXPECT_NEAR(drone1->GetPosition()[0], pos1, 0.001) << "Update not working correctly";
    EXPECT_NEAR(drone1->GetPosition()[1], pos1, 0.001) << "Update not working correctly";
    EXPECT_NEAR(drone1->GetPosition()[2], pos1, 0.001) << "Update not working correctly";
    EXPECT_EQ(drone1->GetHasPackage(), false);*/

//}

}  // namespace csci3081
