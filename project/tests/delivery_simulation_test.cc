#include "gtest/gtest.h"
#include "delivery_simulation.h"
#include <iostream>
#include <vector>
#include <EntityProject/entity_console_logger.h>
#include <EntityProject/facade/delivery_system.h>
#include <EntityProject/project_settings.h>

namespace csci3081 {
   class DeliverySimulationTest : public ::testing::Test {
      public:
         void SetUp() {
            entitySystem = GetEntitySystem("default");
            deliverySimulation = dynamic_cast<DeliverySimulation*>(entitySystem);
         }

         void TearDown() {
            delete entitySystem;
         }

      protected:
         entity_project::EntityConsoleLogger logger;
         IEntitySystem* entitySystem;
         DeliverySimulation* deliverySimulation;
   };

   TEST_F(DeliverySimulationTest, AddObserverTest) {
      deliverySimulation->AddObserver(&logger);
      EXPECT_EQ((deliverySimulation->GetObservers()).size(), 2) << "AddObserver() not working";
   }

   TEST_F(DeliverySimulationTest, RemoveObserverTest) {
      deliverySimulation->RemoveObserver(&logger);
      EXPECT_EQ((deliverySimulation->GetObservers()).size(), 1) << "RemoveObserver() not working";
   }

}
