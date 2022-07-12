/**************************************************
* includes
**************************************************/
#include "gtest/gtest.h"
//#include "vector_maths.h"
#include "vector2d.h"
#include <vector>

using std::vector;

namespace csci3081 {

class Vector2DTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    //object for vector3D math operations. m for maths.
    m = Vector2D();
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
  Vector2D m;
};

TEST_F(Vector2DTest, derp) {
  EXPECT_FLOAT_EQ(0.0,0.0) << "a derp";
}

TEST_F(Vector2DTest, EulerianIntegrationFunctionTests) {
  //Vector3D m;
    vector<float> expected_vector1 = {1.0,0.0,1.0};
    vector<float> expected_vector2 = {43.42,1.0,43.42};
    vector<float> expected_vector3 = {-2.0,-1.0,-4.0};

    vector<float> result1 = m.Add(origin_vector, simple_vector);
    vector<float> result2 = m.Add(simple_vector, answer_vector);
    vector<float> result3 = m.Add(origin_vector, origin_vector);
    vector<float> result4 = m.Add(negative_vector, negative_one_two_three);

    EXPECT_FLOAT_EQ(result1.at(0), expected_vector1.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result1.at(1), expected_vector1.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result1.at(2), expected_vector1.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vector2.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vector2.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vector2.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result3.at(0), origin_vector.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result3.at(1), origin_vector.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result3.at(2), origin_vector.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vector3.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vector3.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vector3.at(2)) << "Add function not adding properly";
    //vector<float> expected_vector1 = {1.0,1.0,1.0};
    //vector<float> expected_vector2 = {43.42,43.42,43.42};
    //vector<float> expected_vector3 = {-2.0,-3.0,-4.0};

    //EXPECT_EQ(m.EulerianIntegration(origin_vector, simple_vector), expected_vector1) << "Add function not adding properly";
    //EXPECT_EQ(m.EulerianIntegration(simple_vector, answer_vector), expected_vector2) << "Add function not adding properly";
    //EXPECT_EQ(m.EulerianIntegration(origin_vector, origin_vector), origin_vector) << "Add function not adding properly";
    //EXPECT_EQ(m.EulerianIntegration(negative_vector, negative_one_two_three), expected_vector3) << "Add function not adding properly";
}

TEST_F(Vector2DTest, CalcDistanceFunctionTests) { 
    vector<float> expected_vec1 = {42.0,1.0,42.0}; 
    vector<float> expected_vec2 = {21.21,42.42,21.21}; 
    vector<float> expected_vec3 = {11.1111,42.42,11.1111};

    vector<float> result1 = m.CalcDistance(simple_vector, 1.0);
    vector<float> result2 = m.CalcDistance(simple_vector, 42.0);
    vector<float> result3 = m.CalcDistance(origin_vector, 0.0);
    vector<float> result4 = m.CalcDistance(answer_vector, 0.5);
    vector<float> result5 = m.CalcDistance(answer_vector, 0.2619306931);

    EXPECT_FLOAT_EQ(result1.at(0), simple_vector.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result1.at(1), simple_vector.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result1.at(2), simple_vector.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vec1.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vec1.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vec1.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result3.at(0), origin_vector.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result3.at(1), origin_vector.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result3.at(2), origin_vector.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vec2.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vec2.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vec2.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result5.at(0), expected_vec3.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result5.at(1), expected_vec3.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result5.at(2), expected_vec3.at(2)) << "ValcDistance not working properly";

    //old tests without expect float
    //EXPECT_EQ(m.CalcDistance(simple_vector, 1.0) , simple_vector) << "CalcVelocity not working properly";
    //EXPECT_EQ(m.CalcDistance(simple_vector, 42.0), expected_vec1) << "CalcVelocity not working properly";
    //EXPECT_EQ(m.CalcDistance(origin_vector, 0.0), origin_vector) << "CalcVelocity not working properly";
    //EXPECT_EQ(m.CalcDistance(answer_vector, 0.5), expected_vec2) << "CalcVelocity not working properly";
    //EXPECT_EQ(m.CalcDistance(answer_vector, 0.2619306931), expected_vec3) << "CalcVelocity not working properly";
}

TEST_F(Vector2DTest, CalcVelocityFunctionTests) {

    vector<float> expected_vec1 = {42.0,1.0,42.0}; 
    vector<float> expected_vec2 = {21.21,42.42,21.21}; 
    vector<float> expected_vec3 = {11.1111,42.42,11.1111};

    vector<float> result1 = m.CalcDistance(simple_vector, 1.0);
    vector<float> result2 = m.CalcDistance(simple_vector, 42.0);
    vector<float> result3 = m.CalcDistance(origin_vector, 0.0);
    vector<float> result4 = m.CalcDistance(answer_vector, 0.5);
    vector<float> result5 = m.CalcDistance(answer_vector, 0.2619306931);

    EXPECT_FLOAT_EQ(result1.at(0), simple_vector.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result1.at(1), simple_vector.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result1.at(2), simple_vector.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vec1.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vec1.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vec1.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result3.at(0), origin_vector.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result3.at(1), origin_vector.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result3.at(2), origin_vector.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vec2.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vec2.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vec2.at(2)) << "ValcDistance not working properly";

    EXPECT_FLOAT_EQ(result5.at(0), expected_vec3.at(0)) << "ValcDistance not working properly";
    EXPECT_FLOAT_EQ(result5.at(1), expected_vec3.at(1)) << "ValcDistance not working properly (y altered)";
    EXPECT_FLOAT_EQ(result5.at(2), expected_vec3.at(2)) << "ValcDistance not working properly";

    /* old tests without expect float
    vector<float> expected_vec1 = {42.0,42.0,42.0}; 
    vector<float> expected_vec2 = {21.21,21.21,21.21}; 
    vector<float> expected_vec3 = {11.1111,11.1111,11.1111};

    EXPECT_EQ(m.CalcVelocity(simple_vector, 1.0) , simple_vector) << "CalcVelocity not working properly";
    EXPECT_EQ(m.CalcVelocity(simple_vector, 42.0), expected_vec1) << "CalcVelocity not working properly";
    EXPECT_EQ(m.CalcVelocity(origin_vector, 0.0), origin_vector) << "CalcVelocity not working properly";
    EXPECT_EQ(m.CalcVelocity(answer_vector, 0.5), expected_vec2) << "CalcVelocity not working properly";
    EXPECT_EQ(m.CalcVelocity(answer_vector, 0.2619306931), expected_vec3) << "CalcVelocity not working properly";*/
}

TEST_F(Vector2DTest, CalcDirectionFunctionTests) {
  vector<float> expected_vector1 = {-1.0,0.0,-1.0};
    vector<float> expected_vector2 = {25.4,25.5,25.4};
    vector<float> expected_vector3 = {0.0,-1.0,2.0};
    vector<float> expected_vector4 = {0.0,42.42,0.0};

    vector<float> result1 = m.CalcDirection(origin_vector, origin_vector);
    vector<float> result2 = m.CalcDirection(origin_vector, simple_vector);
    vector<float> result3 = m.CalcDirection(better_than_24_vector, small_vector);
    vector<float> result4 = m.CalcDirection(answer_vector, answer_vector);
    vector<float> result5 = m.CalcDirection(negative_vector, negative_one_two_three);

    EXPECT_FLOAT_EQ(result1.at(0), origin_vector.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result1.at(1), origin_vector.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result1.at(2), origin_vector.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vector1.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vector1.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vector1.at(2)) << "subtract function not subtracting properly";
    
    EXPECT_FLOAT_EQ(result3.at(0), expected_vector2.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result3.at(1), expected_vector2.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result3.at(2), expected_vector2.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vector4.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vector4.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vector4.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result5.at(0), expected_vector3.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result5.at(1), expected_vector3.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result5.at(2), expected_vector3.at(2)) << "subtract function not subtracting properly";
  
  /*vector<float> expected_vector1 = {-1.0,-1.0,-1.0};
  vector<float> expected_vector2 = {25.4,25.4,25.4};

  EXPECT_EQ(m.CalcDirection(origin_vector, origin_vector), origin_vector) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(origin_vector, simple_vector), expected_vector1) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(better_than_24_vector, small_vector), expected_vector2) << "CalcDirection not working properly";
  EXPECT_EQ(m.CalcDirection(answer_vector, answer_vector), origin_vector) << "CalcDirection not working properly";
    */
} 

TEST_F(Vector2DTest, NormalizeFunctionTests) {
    vector<float> one_two_three_vector = {1.0,2.0,3.0};

    //float num1 = 0.5773502692;
    float num1 = 0.7071067812;
    //float num2 = 3.741657387;

    vector<float> expected_vec1 = {0.0,0.0,0.0};
    vector<float> expected_vec2 = {num1,1.0,num1};
    vector<float> expected_vec3 = {num1,42.42,num1};
    vector<float> expected_vec4 = {0.316227766,2.0,0.9486832981};

    vector<float> result1 = m.Normalize(origin_vector);
    vector<float> result2 = m.Normalize(simple_vector);
    vector<float> result3 = m.Normalize(answer_vector);
    vector<float> result4 = m.Normalize(one_two_three_vector);

    EXPECT_FLOAT_EQ(result1.at(0), expected_vec1.at(0)) << "normalize not functioning properly";
    EXPECT_FLOAT_EQ(result1.at(1), expected_vec1.at(1)) << "normalize not functioning properly (y altered)";
    EXPECT_FLOAT_EQ(result1.at(2), expected_vec1.at(2)) << "normalize not functioning properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vec2.at(0)) << "normalize not functioning properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vec2.at(1)) << "normalize not functioning properly (y altered)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vec2.at(2)) << "normalize not functioning properly";

    EXPECT_FLOAT_EQ(result3.at(0), expected_vec3.at(0)) << "normalize not functioning properly";
    EXPECT_FLOAT_EQ(result3.at(1), expected_vec3.at(1)) << "normalize not functioning properly (y altered)";
    EXPECT_FLOAT_EQ(result3.at(2), expected_vec3.at(2)) << "normalize not functioning properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vec4.at(0)) << "normalize not functioning properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vec4.at(1)) << "normalize not functioning properly (y altered)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vec4.at(2)) << "normalize not functioning properly";


    /* old tests partially withoug expect float 
    EXPECT_EQ(m.Normalize(origin_vector), expected_vec1) << "Normalize not functioning properly";
    EXPECT_EQ(m.Normalize(simple_vector), expected_vec2) << "Normalize not functioning properly";
    EXPECT_EQ(m.Normalize(answer_vector), expected_vec3) << "Normalize not functioning properly";
    //EXPECT_EQ(m.Normalize(one_two_three_vector), expected_vec4) << "Normalize not functioning properly";

    vector<float> test_v = m.Normalize(one_two_three_vector);
    for (int i = 0; i < 3; i++) {
      EXPECT_FLOAT_EQ(test_v.at(i), expected_vec4.at(i));
    }*/

}

TEST_F(Vector2DTest, CalcMagnitudeFunctionTests) {
    float expected_out1 = 59.99093932;
    float expected_out2 = 1.414213562;

    float result1 = m.CalcMagnitude(simple_unit_vector);
    float result2 = m.CalcMagnitude(answer_vector);
    float result3 = m.CalcMagnitude(origin_vector);
    float result4 = m.CalcMagnitude(simple_vector);

    EXPECT_FLOAT_EQ(result1, 1.0) << "CalcMagnitude function not working properly";
    EXPECT_FLOAT_EQ(result2, expected_out1) << "CalcMagnitude function not working properly";
    EXPECT_FLOAT_EQ(result3, 0.0) << "CalcMagnitude function not working properly";
    EXPECT_FLOAT_EQ(result4, expected_out2) << "CalcMagnitude function not working properly";

    /* old tests without expect float
    EXPECT_EQ(m.CalcMagnitude(simple_unit_vector), 1) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(answer_vector), expected_out1) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(origin_vector), 0) << "CalcMagnitude function not working properly";
    EXPECT_EQ(m.CalcMagnitude(simple_vector) , expected_out2) << "CalcMagnitude function not working properly";
    */
}

TEST_F(Vector2DTest, AddFunctionTests) {
    vector<float> expected_vector1 = {1.0,0.0,1.0};
    vector<float> expected_vector2 = {43.42,1.0,43.42};
    vector<float> expected_vector3 = {-2.0,-1.0,-4.0};

    vector<float> result1 = m.Add(origin_vector, simple_vector);
    vector<float> result2 = m.Add(simple_vector, answer_vector);
    vector<float> result3 = m.Add(origin_vector, origin_vector);
    vector<float> result4 = m.Add(negative_vector, negative_one_two_three);

    EXPECT_FLOAT_EQ(result1.at(0), expected_vector1.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result1.at(1), expected_vector1.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result1.at(2), expected_vector1.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vector2.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vector2.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vector2.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result3.at(0), origin_vector.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result3.at(1), origin_vector.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result3.at(2), origin_vector.at(2)) << "Add function not adding properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vector3.at(0)) << "Add function not adding properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vector3.at(1)) << "Add function not adding properly (affected y)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vector3.at(2)) << "Add function not adding properly";
    //old tests without float expect
    //EXPECT_EQ(m.Add(origin_vector, simple_vector), expected_vector1) << "Add function not adding properly";
    //EXPECT_EQ(m.Add(simple_vector, answer_vector), expected_vector2) << "Add function not adding properly";
    //EXPECT_EQ(m.Add(origin_vector, origin_vector), origin_vector) << "Add function not adding properly";
    //EXPECT_EQ(m.Add(negative_vector, negative_one_two_three), expected_vector3) << "Add function not adding properly";
}

TEST_F(Vector2DTest, SubtractFunctionTests) {
    vector<float> expected_vector1 = {-1.0,0.0,-1.0};
    vector<float> expected_vector2 = {25.4,25.5,25.4};
    vector<float> expected_vector3 = {0.0,-1.0,2.0};
    vector<float> expected_vector4 = {0.0,42.42,0.0};

    vector<float> result1 = m.Subtract(origin_vector, origin_vector);
    vector<float> result2 = m.Subtract(origin_vector, simple_vector);
    vector<float> result3 = m.Subtract(better_than_24_vector, small_vector);
    vector<float> result4 = m.Subtract(answer_vector, answer_vector);
    vector<float> result5 = m.Subtract(negative_vector, negative_one_two_three);

    EXPECT_FLOAT_EQ(result1.at(0), origin_vector.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result1.at(1), origin_vector.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result1.at(2), origin_vector.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result2.at(0), expected_vector1.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result2.at(1), expected_vector1.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result2.at(2), expected_vector1.at(2)) << "subtract function not subtracting properly";
    
    EXPECT_FLOAT_EQ(result3.at(0), expected_vector2.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result3.at(1), expected_vector2.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result3.at(2), expected_vector2.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result4.at(0), expected_vector4.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result4.at(1), expected_vector4.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result4.at(2), expected_vector4.at(2)) << "subtract function not subtracting properly";

    EXPECT_FLOAT_EQ(result5.at(0), expected_vector3.at(0)) << "subtract function not subtracting properly";
    EXPECT_FLOAT_EQ(result5.at(1), expected_vector3.at(1)) << "subtract function not subtracting properly (y altered)";
    EXPECT_FLOAT_EQ(result5.at(2), expected_vector3.at(2)) << "subtract function not subtracting properly";
    //old tests before expect float
    //EXPECT_EQ(m.Subtract(origin_vector, origin_vector), origin_vector) << "Subtract function not subtracting properly";
    //EXPECT_EQ(m.Subtract(origin_vector, simple_vector), expected_vector1) << "Subtract function not subtracting properly";
    //EXPECT_EQ(m.Subtract(better_than_24_vector, small_vector), expected_vector2) << "Subtract function not subtracting properly";
    //EXPECT_EQ(m.Subtract(answer_vector, answer_vector), origin_vector) << "Subtract function not subtracting properly";
    //EXPECT_EQ(m.Subtract(negative_vector, negative_one_two_three), expected_vector3) << "Subtract function not subtracting properly";
}

} // namespace csci3081