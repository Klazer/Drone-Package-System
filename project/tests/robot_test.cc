#include "gtest/gtest.h"
#include "json_helper.h"
#include "entity_base.h"
#include "robot.h"
#include "battery.h"
#include "package.h"
#include <vector>
#include <iostream>

using std::vector;

namespace csci3081 {

class RobotTest : public ::testing::Test {
 public:
  void SetUp() {
    //Robot setup
    obj2 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj2, "type", "robot");
    JsonHelper::AddStringToJsonObject(obj2, "name", "robot");
    JsonHelper::AddFloatToJsonObject(obj2, "speed", 30.0);
    std::vector<float> position_to_add2 = {498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add2);
    std::vector<float> direction_to_add2 = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add2);

    vector<float> direction2 = {1.5,2.5,3.5};
    vector<float> position2 = {42.1,42.2,42.3};
    robot1 = new Robot(position2, direction2, obj2);

    
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
      delete robot1;
  }
  protected: 
  picojson::object obj;
  picojson::object obj2;
  //IEntity pointers will only use commands/functions from IEntity interface
  //Use package pointer
  Package* package1;
  Robot* robot1;
  
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RobotTest, SetDirectionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    robot1->SetDirection(ascending_vector);
    vector<float> result = robot1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    robot1->SetDirection(origin_vector);
    result = robot1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    robot1->SetDirection(answer_vector);
    result = robot1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(RobotTest, SetPositionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    robot1->SetPosition(ascending_vector);
    vector<float> result = robot1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    robot1->SetPosition(origin_vector);
    result = robot1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    robot1->SetPosition(answer_vector);
    result = robot1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(RobotTest, IsDynamicFunctionTests) {
    EXPECT_EQ(robot1->IsDynamic(), false) << "default is dynamic not set up right";
    robot1->SetISDynamic(true);
    EXPECT_EQ(robot1->IsDynamic(), true) << "default is dynamic not set up right";
}

TEST_F(RobotTest, GetRadiusTest) {
    EXPECT_FLOAT_EQ(robot1->GetRadius(), 1.0f) << "get radius not working properly";
}

TEST_F(RobotTest, GetDirectionTest) {
    vector<float> expected_dir = {1.5,2.5,3.5};
    vector<float> robot_dir = robot1->GetDirection();
    EXPECT_FLOAT_EQ(expected_dir.at(0), robot_dir.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(1), robot_dir.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(2), robot_dir.at(2)) << "get position not working properly";
}

TEST_F(RobotTest, GetPositionTest) {
    vector<float> expected_pos = {42.1,42.2,42.3};
    vector<float> robot_pos = robot1->GetPosition();
    EXPECT_FLOAT_EQ(expected_pos.at(0), robot_pos.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(1), robot_pos.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(2), robot_pos.at(2)) << "get position not working properly";
}

TEST_F(RobotTest, GetIDTest) {
    //this depends on the number of entities created. 
    //when this particular test is compiled robot1 is the 76th
    //entity created.
    EXPECT_EQ(robot1->GetId(), 83) << "default id not set up properly";
}

TEST_F(RobotTest, GetNameFunctionTest) {
    std::string name = robot1->GetName();
    EXPECT_EQ(name, "robot") << "get name not returning correct name";
}

TEST_F(RobotTest, GetTypeFunctionTest) {
    std::string type = robot1->GetType();
    EXPECT_EQ(type, "robot") << "get name not returning correct type";
}

TEST_F(RobotTest, RobotConstructorTest) {
    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};

    ASSERT_NE(robot1, nullptr) << "robot constructor not working properly";
    //check that the robot was initialized correctly
    vector<float> pos = robot1->GetPosition();
    vector<float> dir = robot1->GetDirection();
    EXPECT_EQ(pos, position1) << "robot constructor not initializing position";
    EXPECT_EQ(dir, direction1) << "robot constructor not initializing position";

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    //ASSERT_EQ(picojson::value(robot1.GetDetails()).serialize(), picojson::value(obj).serialize());
}

TEST_F(RobotTest, GetSpeedTest) {
    EXPECT_FLOAT_EQ(robot1->GetSpeed(), 30.0) << "Get speed not working properly";
    robot1->SetSpeed(0);
    EXPECT_FLOAT_EQ(robot1->GetSpeed(), 0.0) << "Get speed not working properly";
}

TEST_F(RobotTest, SetSpeedTest) {
    robot1->SetSpeed(100.0);
    EXPECT_FLOAT_EQ(robot1->GetSpeed(), 100.0) << "Set speed not working properly";
    robot1->SetSpeed(55.55); 
    EXPECT_FLOAT_EQ(robot1->GetSpeed(), 55.55) << "Set speed not working properly";
    robot1->SetSpeed(0.0);
    EXPECT_FLOAT_EQ(robot1->GetSpeed(), 0.0) << "Set speed not working properly";
}

TEST_F(RobotTest, SetPackageTest) {
    robot1->SetPackage(package1);
    std::string name = "package";
    EXPECT_EQ(name, "package");
}

TEST_F(RobotTest, GetHasPackageTest) {
    EXPECT_EQ(robot1->GetHasPackage(), false) << "GetHasPackage not working right";
    robot1->SetHasPackage(true);
    EXPECT_EQ(robot1->GetHasPackage(), true) << "GetHasPackage not working right";
    robot1->SetHasPackage(false);
    EXPECT_EQ(robot1->GetHasPackage(), false) << "GetHasPackage not working right";    
}

TEST_F(RobotTest, SetHasPackageTest) {
    robot1->SetHasPackage(true);
    EXPECT_EQ(robot1->GetHasPackage(), true) << "GetHasPackage not working right";
    robot1->SetHasPackage(false);
    EXPECT_EQ(robot1->GetHasPackage(), false) << "GetHasPackage not working right";
}

TEST_F(RobotTest, SetPathTest) {
    vector<vector<float>> path1;
    vector<float> node = {1,1,1};
    path1.push_back(node);
    robot1->SetPath(path1);

    vector<float> expected_out1 = {1,1,1};

    vector<vector<float>> path_out = robot1->GetPath();
    vector<float> out1 = path_out.at(0);

    EXPECT_FLOAT_EQ(out1.at(0), expected_out1.at(0)) << "set/get path not working properly";
    EXPECT_FLOAT_EQ(out1.at(1), expected_out1.at(1)) << "set/get path not working properly";
    EXPECT_FLOAT_EQ(out1.at(2), expected_out1.at(2)) << "set/get path not working properly";
    
}

TEST_F(RobotTest, SetDeliveryPathTest) {
    vector<vector<float>> path1;
    vector<float> node = {1,1,1};
    path1.push_back(node);
    robot1->SetDeliveryPath(path1);

    vector<float> expected_out1 = {1,1,1};

    vector<vector<float>> path_out = robot1->GetDeliveryPath();
    vector<float> out1 = path_out.at(0);

    EXPECT_FLOAT_EQ(out1.at(0), expected_out1.at(0)) << "set/get deliverypath not working properly";
    EXPECT_FLOAT_EQ(out1.at(1), expected_out1.at(1)) << "set/get deliverypath not working properly";
    EXPECT_FLOAT_EQ(out1.at(2), expected_out1.at(2)) << "set/get deliverypath not working properly";
    
}

TEST_F(RobotTest, ObserverEventTests) {
    picojson::value Revent = robot1->createEvent("idle");

    picojson::object e = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "idle");
    picojson::value event(e);


    EXPECT_EQ(Revent.serialize(), event.serialize());

}
/* not a unit test! integration testing not needed now.
TEST_F(RobotTest, UpdateEntityTest) {
}*/

}  // namespace csci3081
