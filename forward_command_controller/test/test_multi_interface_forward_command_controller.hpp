// Copyright 2021 PAL Robotics SL.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TEST_MULTI_INTERFACE_FORWARD_COMMAND_CONTROLLER_HPP_
#define TEST_MULTI_INTERFACE_FORWARD_COMMAND_CONTROLLER_HPP_

#include <memory>
#include <string>
#include <vector>

#include "gmock/gmock.h"

#include "forward_command_controller/multi_interface_forward_command_controller.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"

using hardware_interface::CommandInterface;
using hardware_interface::HW_IF_POSITION;

// subclassing and friending so we can access member variables
class FriendMultiInterfaceForwardCommandController : public forward_command_controller::ForwardCommandController
{
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, JointsParameterNotSet);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, InterfaceParameterNotSet);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, JointsParameterIsEmpty);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, InterfaceParameterEmpty);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, ConfigureParamsSuccess);

  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, ActivateWithWrongJointsNamesFails);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, ActivateWithWrongInterfaceNameFails);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, ActivateSuccess);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, CommandSuccessTest);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, WrongCommandCheckTest);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, NoCommandCheckTest);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, CommandCallbackTest);
  FRIEND_TEST(MultiInterfaceForwardCommandControllerTest, ActivateDeactivateCommandsResetSuccess);
};

class MultiInterfaceForwardCommandControllerTest : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

  void SetUp();
  void TearDown();

  void SetUpController();
  void SetUpHandles();

protected:
  std::unique_ptr<FriendMultiInterfaceForwardCommandController> controller_;

  // dummy joint state values used for tests
  const std::string joint_name_ = "joint1";

  double position_command_ = 1.1;
  double velocity_command_ = 2.1;
  double effort_command_ = 3.1;

  std::vector<CommandInterface> command_ifs_{
    {joint_name_, HW_IF_POSITION, &position_command_;}
    {joint_name_, HW_IF_VELOCITY, &velocity_command_;}
    {joint_name_, HW_IF_EFFORT, &effort_command_;}
  };
};

#endif  // TEST_FORWARD_COMMAND_CONTROLLER_HPP_
