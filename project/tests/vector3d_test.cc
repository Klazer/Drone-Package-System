/**************************************************
* includes
**************************************************/
#include "gtest/gtest.h"
//#include "vector_maths.h"
#include "vector3d.h"
#include <vector>

using std::vector;

namespace csci3081 {

class VectorTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    //object for vector3D math operations. m for maths.
    m = Vector3D();
    // code here will execute just before the test ensues 
    origin_vector = vector<float>{0.0,0.0,0.0};
    simple_vector = vector<float>{1.0,1.0,1.0};
    small_vector = vector<float>{0.1,0.1,0.1};
    answer_vector = vector<float>{42.42,42.42,42.42};
    better_than_24_vector = vector<float>{25.5,25.5,25.5};
    simple_unit_vector = vector<float>{1.0,0.0,0.0};
    negative_vector = vector<float>{-1.0,-1.0,-1.0};
    negative_one_two_three = vector<float>{-1.0,-2.0,-3.0};
  }
  void TearDown () {}
 protected:
  vector<float> origin_vector;
  vector<float> simple_vector;
  vector<float> small_vector;
  vector<float> answer_vector;
  vector<float> simple_unit_vector;
  vector<float> better_than_24_vector;
  vector<float> negative_vector;
  vector<float> negative_one_two_three;
  Vector3D m;
};

TEST_F(VectorTest, derp) {
  EXPECT_FLOAT_EQ(0.0,0.0) << "a derp";
}

TEST_F(VectorTest, EulerianIntegrationFunctionTests) {
  //Vector3D m;
  vector<float> expected_vector1 = {1.0,1.0,1.0};
    vector<float> expected_vector2 = {43.42,43.42,43.42};
    vector<float> expected_vector3 = {-2.0,-3.0,-4.0};

    EXPECT_EQ(m.EulerianIntegration(origin_vector, simple_vector), expected_vector1) << "Add function not adding properly";
    EXPECT_EQ(m.EulerianIntegration(simple_vector, answer_vector), expected_vector2) << "Add function not adding properly";
    EXPECT_EQ(m.EulerianIntegration(origin_vector, origin_vector), origin_vector) << "Add function not adding properly";
    EXPECT_EQ(m.EulerianIntegration(negative_vector, negative_one_two_three), expected_vector3) << "Add function not adding properly";
}

TEST_F(VectorTest, CalcDistanceFunctionTests) { 
  vector<float> expected_vec1 = {42.0,42.0,42.0}; 
  vector<float> expected_vec2 = {21.21,21.21,21.21}; 
  vector<float> expected_vec3 = {11.1111,11.1111,11.1111};

  EXPECT_EQ(m.CalcVelocity(simple_vector, 1.0) , simple_vector) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(simple_vector, 42.0), expected_vec1) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(origin_vector, 0.0), origin_vector) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(answer_vector, 0.5), expected_vec2) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(answer_vector, 0.2619306931), expected_vec3) << "CalcVelocity not working properly";
}

TEST_F(VectorTest, CalcVelocityFunctionTests) {
  vector<float> expected_vec1 = {42.0,42.0,42.0}; 
  vector<float> expected_vec2 = {21.21,21.21,21.21}; 
  vector<float> expected_vec3 = {11.1111,11.1111,11.1111};

  EXPECT_EQ(m.CalcVelocity(simple_vector, 1.0) , simple_vector) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(simple_vector, 42.0), expected_vec1) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(origin_vector, 0.0), origin_vector) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(answer_vector, 0.5), expected_vec2) << "CalcVelocity not working properly";
  EXPECT_EQ(m.CalcVelocity(answer_vector, 0.2619306931), expected_vec3) << "CalcVelocity not working properly";
}

TEST_F(VectorTest, CalcDirectionFunctionTests) {
  vector<float> expected_vector1 = {-1.0,-1.0,-1.0};
  vector<float> expected_vector2 = {25.4,25.4,25.4};

  EXPECT_EQ(m.CalcDirection(origin_vector, origin_vector), origin_vector) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(origin_vector, simple_vector), expected_vector1) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(better_than_24_vector, small_vector), expected_vector2) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(answer_vector, answer_vector), origin_vector) << "CalcDirection not working properly";
} 

TEST_F(VectorTest, NormalizeFunctionTests) {
    vector<float> one_two_three_vector = {1.0,2.0,3.0};

    float num1 = 0.5773502692;
    //float num2 = 3.741657387;

    vector<float> expected_vec1 = {0.0,0.0,0.0};
    vector<float> expected_vec2 = {num1,num1,num1};
    vector<float> expected_vec3 = {num1,num1,num1};
    vector<float> expected_vec4 = {0.2672612419,0.5345224838,0.8017837257};

    EXPECT_EQ(m.Normalize(origin_vector), expected_vec1) << "Normalize not functioning properly";
    EXPECT_EQ(m.Normalize(simple_vector), expected_vec2) << "Normalize not functioning properly";
    EXPECT_EQ(m.Normalize(answer_vector), expected_vec3) << "Normalize not functioning properly";
    //EXPECT_EQ(m.Normalize(one_two_three_vector), expected_vec4) << "Normalize not functioning properly";

    vector<float> test_v = m.Normalize(one_two_three_vector);
    for (int i = 0; i < 3; i++) {
      EXPECT_FLOAT_EQ(test_v.at(i), expected_vec4.at(i));
    }

}

TEST_F(VectorTest, CalcMagnitudeFunctionTests) {
    float expected_out1 = 73.47359526;
    float expected_out2 = 1.732050808;

    EXPECT_EQ(m.CalcMagnitude(simple_unit_vector), 1) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(answer_vector), expected_out1) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(origin_vector), 0) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(simple_vector) , expected_out2) << "CalcMagnitude function not working properly";
}

TEST_F(VectorTest, AddFunctionTests) {
    vector<float> expected_vector1 = {1.0,1.0,1.0};
    vector<float> expected_vector2 = {43.42,43.42,43.42};
    vector<float> expected_vector3 = {-2.0,-3.0,-4.0};

    EXPECT_EQ(m.Add(origin_vector, simple_vector), expected_vector1) << "Add function not adding properly";
    EXPECT_EQ(m.Add(simple_vector, answer_vector), expected_vector2) << "Add function not adding properly";
    EXPECT_EQ(m.Add(origin_vector, origin_vector), origin_vector) << "Add function not adding properly";
    EXPECT_EQ(m.Add(negative_vector, negative_one_two_three), expected_vector3) << "Add function not adding properly";
}

TEST_F(VectorTest, SubtractFunctionTests) {
    vector<float> expected_vector1 = {-1.0,-1.0,-1.0};
    vector<float> expected_vector2 = {25.4,25.4,25.4};
    vector<float> expected_vector3 = {0.0,1.0,2.0};

    EXPECT_EQ(m.Subtract(origin_vector, origin_vector), origin_vector) << "Subtract function not subtracting properly";
    EXPECT_EQ(m.Subtract(origin_vector, simple_vector), expected_vector1) << "Subtract function not subtracting properly";
    EXPECT_EQ(m.Subtract(better_than_24_vector, small_vector), expected_vector2) << "Subtract function not subtracting properly";
    EXPECT_EQ(m.Subtract(answer_vector, answer_vector), origin_vector) << "Subtract function not subtracting properly";
    EXPECT_EQ(m.Subtract(negative_vector, negative_one_two_three), expected_vector3) << "Subtract function not subtracting properly";
}

} // namespace csci3081