#include "gtest/gtest.h"

#include "json_helper.h"
#include "entity_base.h"
#include "customer.h"
#include <vector>
#include <iostream>

using std::vector;

namespace csci3081 {

class CustomerTest : public ::testing::Test {
 public:
  void SetUp() {
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj, "name", "customer");
    std::vector<float> position_to_add = {498.292,253.883,-228.623};
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    std::vector<float> direction_to_add = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);

    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};
    //customerB = Customer(position1, direction1, obj);
    //customer1 = Customer(position1, direction1, obj); //: IEntity();
    customer1 = new Customer(position1, direction1, obj);
    //customer1 = &entity;

    /*obj2 = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj2, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj2, "name", "dave");
    std::vector<float> position_to_add2 = {0,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "position", position_to_add);
    std::vector<float> direction_to_add2 = {1,0,0};
    JsonHelper::AddStdFloatVectorToJsonObject(obj2, "direction", direction_to_add);

    customer2 = Customer(position_to_add2, direction_to_add2, obj2);*/
  }
  void TearDown() {
      delete customer1;
  }
  protected: 
  picojson::object obj;
  //picojson::object obj2;
  //Customer customer1;
  //Customer customer2;
  //IEntity pointers will only use commands/functions from IEntity interface
  //Use customer pointer
  Customer* customer1;
  //Customer* customer1;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(CustomerTest, IsDynamicFunctionTests) {
    EXPECT_EQ(customer1->IsDynamic(), false) << "default is dynamic not set up right";
    customer1->SetISDynamic(true);
    EXPECT_EQ(customer1->IsDynamic(), true) << "default is dynamic not set up right";
}

TEST_F(CustomerTest, GetRadiusTest) {
    EXPECT_FLOAT_EQ(customer1->GetRadius(), 1.0f) << "get radius not working properly";
}

TEST_F(CustomerTest, GetDirectionTest) {
    vector<float> expected_dir = {1.5,2.5,3.5};
    vector<float> customer_dir = customer1->GetDirection();
    EXPECT_FLOAT_EQ(expected_dir.at(0), customer_dir.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(1), customer_dir.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(2), customer_dir.at(2)) << "get position not working properly";
}

TEST_F(CustomerTest, GetPositionTest) {
    vector<float> expected_pos = {42.1,42.2,42.3};
    vector<float> customer_pos = customer1->GetPosition();
    EXPECT_FLOAT_EQ(expected_pos.at(0), customer_pos.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(1), customer_pos.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(2), customer_pos.at(2)) << "get position not working properly";
}

TEST_F(CustomerTest, GetIDTest) {
    //this depends on the number of entities created. 
    //when this particular test is compiled customer1 is the 10th 
    //entity created.
    EXPECT_EQ(customer1->GetId(), 10) << "default id not set up properly";
}

TEST_F(CustomerTest, GetNameFunctionTest) {
    std::string name = customer1->GetName();
    EXPECT_EQ(name, "customer") << "get name not returning correct name";
}

TEST_F(CustomerTest, CustomerConstructorTest) {
    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};

    ASSERT_NE(customer1, nullptr) << "customer constructor not working properly";
    //check that the customer was initialized correctly
    vector<float> pos = customer1->GetPosition();
    vector<float> dir = customer1->GetDirection();
    EXPECT_EQ(pos, position1) << "customer constructor not initializing position";
    EXPECT_EQ(dir, direction1) << "customer constructor not initializing position";

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    //ASSERT_EQ(picojson::value(customer1.GetDetails()).serialize(), picojson::value(obj).serialize());
}



}  // namespace csci3081
