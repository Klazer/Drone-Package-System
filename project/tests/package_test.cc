#include "gtest/gtest.h"

#include "json_helper.h"
#include "entity_base.h"
#include "package.h"
#include <vector>
#include <iostream>

using std::vector;

namespace csci3081 {

class PackageTest : public ::testing::Test {
 public:
  void SetUp() {
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
  }
  protected: 
  picojson::object obj;
  //IEntity pointers will only use commands/functions from IEntity interface
  //Use package pointer
  Package* package1;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PackageTest, SetDirectionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    package1->SetDirection(ascending_vector);
    vector<float> result = package1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    package1->SetDirection(origin_vector);
    result = package1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    package1->SetDirection(answer_vector);
    result = package1->GetDirection();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(PackageTest, SetPositionTests) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    package1->SetPosition(ascending_vector);
    vector<float> result = package1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), ascending_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), ascending_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), ascending_vector.at(2)) << "set position not working properly";

    package1->SetPosition(origin_vector);
    result = package1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), origin_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), origin_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), origin_vector.at(2)) << "set position not working properly";
    
    package1->SetPosition(answer_vector);
    result = package1->GetPosition();
    EXPECT_FLOAT_EQ(result.at(0), answer_vector.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(1), answer_vector.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(result.at(2), answer_vector.at(2)) << "set position not working properly";
}

TEST_F(PackageTest, IsDynamicFunctionTests) {
    EXPECT_EQ(package1->IsDynamic(), false) << "default is dynamic not set up right";
    package1->SetISDynamic(true);
    EXPECT_EQ(package1->IsDynamic(), true) << "default is dynamic not set up right";
}

TEST_F(PackageTest, GetRadiusTest) {
    EXPECT_FLOAT_EQ(package1->GetRadius(), 1.0f) << "get radius not working properly";
}

TEST_F(PackageTest, GetDirectionTest) {
    vector<float> expected_dir = {1.5,2.5,3.5};
    vector<float> package_dir = package1->GetDirection();
    EXPECT_FLOAT_EQ(expected_dir.at(0), package_dir.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(1), package_dir.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dir.at(2), package_dir.at(2)) << "get position not working properly";
}

TEST_F(PackageTest, GetPositionTest) {
    vector<float> expected_pos = {42.1,42.2,42.3};
    vector<float> package_pos = package1->GetPosition();
    EXPECT_FLOAT_EQ(expected_pos.at(0), package_pos.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(1), package_pos.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_pos.at(2), package_pos.at(2)) << "get position not working properly";
}

TEST_F(PackageTest, GetDestinationTest) {
    vector<float> expected_dest = {0.0,0.0,0.0};
    vector<float> package_dest = package1->GetDestination();
    EXPECT_FLOAT_EQ(expected_dest.at(0), package_dest.at(0)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dest.at(1), package_dest.at(1)) << "get position not working properly";
    EXPECT_FLOAT_EQ(expected_dest.at(2), package_dest.at(2)) << "get position not working properly";
}

TEST_F(PackageTest, SetDestinationTest) {
    vector<float> ascending_vector{1.23,4.56,7.89};
    vector<float> origin_vector{0.0,0.0,0.0};
    vector<float> answer_vector{42.42,42.42,42.42};

    package1->SetDestination(ascending_vector);
    vector<float> package_dest = package1->GetDestination();
    EXPECT_FLOAT_EQ(ascending_vector.at(0), package_dest.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(ascending_vector.at(1), package_dest.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(ascending_vector.at(2), package_dest.at(2)) << "set position not working properly";

    package1->SetDestination(origin_vector);
    package_dest = package1->GetDestination();
    EXPECT_FLOAT_EQ(origin_vector.at(0), package_dest.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(origin_vector.at(1), package_dest.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(origin_vector.at(2), package_dest.at(2)) << "set position not working properly";

    package1->SetDestination(answer_vector);
    package_dest = package1->GetDestination();
    EXPECT_FLOAT_EQ(answer_vector.at(0), package_dest.at(0)) << "set position not working properly";
    EXPECT_FLOAT_EQ(answer_vector.at(1), package_dest.at(1)) << "set position not working properly";
    EXPECT_FLOAT_EQ(answer_vector.at(2), package_dest.at(2)) << "set position not working properly";
}

TEST_F(PackageTest, GetIDTest) {
    //this depends on the number of entities created. 
    //when this particular test is compiled customer1 is the 56th 
    //entity created.
    EXPECT_EQ(package1->GetId(), 62) << "default id not set up properly";
}

TEST_F(PackageTest, GetNameFunctionTest) {
    std::string name = package1->GetName();
    EXPECT_EQ(name, "package") << "get name not returning correct name";
}

TEST_F(PackageTest, PackageConstructorTest) {
    vector<float> direction1 = {1.5,2.5,3.5};
    vector<float> position1 = {42.1,42.2,42.3};

    ASSERT_NE(package1, nullptr) << "package constructor not working properly";
    //check that the package was initialized correctly
    vector<float> pos = package1->GetPosition();
    vector<float> dir = package1->GetDirection();
    EXPECT_EQ(pos, position1) << "package constructor not initializing position";
    EXPECT_EQ(dir, direction1) << "package constructor not initializing position";

    // Checks that when GetDetails() is called, the entity returns 
    //  the picojson object that was used to initialize it
    //ASSERT_EQ(picojson::value(package1.GetDetails()).serialize(), picojson::value(obj).serialize());
}

TEST_F(PackageTest, GetWeightTest) {
    float weight = package1->GetWeight();

    EXPECT_FLOAT_EQ(weight, 0.0) << "get weight not working properly";
}

TEST_F(PackageTest, SetWeightTest) {
    float weight1 = 12.199001;
    float weight2 = -15;

    package1->SetWeight(weight1);
    EXPECT_FLOAT_EQ(package1->GetWeight(), weight1) << "set weight not working properly";
    package1->SetWeight(weight2);
    EXPECT_FLOAT_EQ(package1->GetWeight(), 0.0) << "set weight not working properly";
}

TEST_F(PackageTest, PickupPackageTest) {
    package1->PickupPackage();
    EXPECT_EQ(package1->IsDynamic(), true) << "pickup package not working right";

    package1->DropPackage();
    EXPECT_EQ(package1->IsDynamic(), false) << "pickup package not working right";

    package1->PickupPackage();
    EXPECT_EQ(package1->IsDynamic(), true) << "pickup package not working right";
}

TEST_F(PackageTest, DropPackageTest) {
    package1->PickupPackage();
    EXPECT_EQ(package1->IsDynamic(), true) << "pickup package not working right";

    package1->DropPackage();
    EXPECT_EQ(package1->IsDynamic(), false) << "pickup package not working right";

    package1->PickupPackage();
    EXPECT_EQ(package1->IsDynamic(), true) << "pickup package not working right";
}

TEST_F(PackageTest, ObserverEventTests) {
    picojson::value Pevent = package1->createEvent("scheduled");
    picojson::value Pevent2 = package1->createEvent("en route");
    picojson::value Pevent3 = package1->createEvent("delivered");

    picojson::object e = JsonHelper::CreateJsonObject();
    picojson::object f = JsonHelper::CreateJsonObject();
    picojson::object g = JsonHelper::CreateJsonObject();
    
    JsonHelper::AddStringToJsonObject(e, "type", "notify");
    JsonHelper::AddStringToJsonObject(e, "value", "scheduled");
    picojson::value event(e);

    JsonHelper::AddStringToJsonObject(f, "type", "notify");
    JsonHelper::AddStringToJsonObject(f, "value", "en route");
    picojson::value event2(f);


    JsonHelper::AddStringToJsonObject(g, "type", "notify");
    JsonHelper::AddStringToJsonObject(g, "value", "delivered");
    picojson::value event3(g);


    EXPECT_EQ(Pevent.serialize(), event.serialize());
    EXPECT_EQ(Pevent2.serialize(), event2.serialize());
    EXPECT_EQ(Pevent3.serialize(), event3.serialize());
}


}  // namespace csci3081
