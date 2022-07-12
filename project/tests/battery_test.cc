#include "gtest/gtest.h"
#include "battery.h"
#include <iostream>

namespace csci3081 {

class BatteryTest : public ::testing::Test {
 public:
  void SetUp() {  
      battery1 = Battery();
      battery2 = Battery(42);
      battery3 = Battery(42000);
      battery4 = Battery(-5);
      battery5 = Battery(1234);
  }
  void TearDown() {  }
  protected: 
  Battery battery1;
  Battery battery2;
  Battery battery3;
  Battery battery4;
  Battery battery5;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BatteryTest, IsDeadFunctiontests) {
    //Battery battery1;
    //Battery battery2(42);

    EXPECT_EQ(battery1.IsDead(), false) << "IsDead not working properly";
    EXPECT_EQ(battery2.IsDead(), false) << "IsDead not working properly";
    
    battery1.UseBattery(12000);
    battery2.UseBattery(42);

    EXPECT_EQ(battery1.IsDead(), true) << "IsDead not working properly";
    EXPECT_EQ(battery2.IsDead(), true) << "IsDead not working properly";
}

TEST_F(BatteryTest, UseBatteryFunctionTests) {
    //Battery battery1;
    
    battery1.UseBattery(1.5);

    EXPECT_FLOAT_EQ(battery1.GetCharge(), 9998.5) << "UseBattery not working properly";
    EXPECT_EQ(battery1.IsMaxCharge(), false) << "UseBattery not working properly";

    battery1.UseBattery(1.5);

    EXPECT_FLOAT_EQ(battery1.GetCharge(), 9997.0) << "UseBattery not working properly";
}

TEST_F(BatteryTest, ChargeBatteryFunctionTests) {
    //Battery battery1;

    battery1.UseBattery(100);

    battery1.ChargeBattery(50);

    EXPECT_FLOAT_EQ(battery1.GetCharge(), 9950.0) << "ChargeBattery not working properly";

    battery1.ChargeBattery(60);

    EXPECT_FLOAT_EQ(battery1.GetCharge(), 10000.0) << "ChargeBattery not working properly";
    EXPECT_EQ(battery1.IsMaxCharge(), true) << "ChargeBattery nor working properly";
}

TEST_F(BatteryTest, SetChargeFunctionTests) {
    Battery crazy_battery(0);

    crazy_battery.SetCharge(42);
    EXPECT_EQ(crazy_battery.GetCharge(), 42) << "SetCharge function not working properly";
    crazy_battery.SetCharge(10000);
    EXPECT_EQ(crazy_battery.GetCharge(), 10000) << "SetCharge function not working properly";
    crazy_battery.SetCharge(12345);
    EXPECT_EQ(crazy_battery.GetCharge(), 12345) << "SetCharge function not working properly";
}

TEST_F(BatteryTest, GetChargeFunctionTests) {
    //Battery battery5(1234);
    //Battery battery1;
    //Battery battery2(42);

    EXPECT_EQ(battery1.GetCharge(), 10000) << "GetCharge function not working properly";
    EXPECT_EQ(battery2.GetCharge(), 42) << "GetCharge function not working properly";
    EXPECT_EQ(battery5.GetCharge(), 1234) << "GetCharge function not working properly";
}

TEST_F(BatteryTest, ConstructorTest) {
    //Battery battery1;
    //Battery battery2(42);
    //Battery battery3(42000);
    //Battery battery4(-5);
    
    EXPECT_EQ(battery1.GetCharge(), 10000) << "constructor not initializing properly";
    EXPECT_EQ(battery2.GetCharge(), 42) << "constructor not initializing properly";
    EXPECT_EQ(battery3.GetCharge(), 42000) << "constructor not initializing properly";
    EXPECT_EQ(battery4.GetCharge(), 10000) << "constructor not initializing properly";

    EXPECT_EQ(battery1.IsMaxCharge(), true) << "constructor not initializing properly";
    EXPECT_EQ(battery3.IsMaxCharge(), true) << "constructor not initializing properly";
}

TEST_F(BatteryTest, IsMaxChargeFunctionTests) {
    //Battery battery1;
    //Battery battery2(42);

    EXPECT_EQ(battery1.IsMaxCharge(), true) << "constructor not initializing properly";
    EXPECT_EQ(battery2.IsMaxCharge(), true) << "constructor not initializing properly";
    
    battery1.UseBattery(1);
    battery2.UseBattery(1);

    EXPECT_EQ(battery1.IsMaxCharge(), false) << "constructor not initializing properly";
    EXPECT_EQ(battery2.IsMaxCharge(), false) << "constructor not initializing properly";
}



}  // namespace csci3081
