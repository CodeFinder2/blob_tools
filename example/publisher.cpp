//=================================================================================================
// Copyright (c) 2013, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================


#include <ros/ros.h>
#include <blob_tools/Blob.h>

#include <sensor_msgs/Imu.h>

ros::Publisher pub;

void publish(const ros::TimerEvent& event)
{
#ifdef SENSOR_MSGS_MESSAGE_IMU_H
  sensor_msgs::Imu message;
  blob_tools::BlobPtr blob(new blob_tools::Blob());
  blob->serialize(message);
#else
  const char buffer[] = "This is a test blob on the stack.\nThis is a test blob on the stack.\nThis is a test blob on the stack.\nThis is a test blob on the stack.\nThis is a test blob on the stack.\n";
  blob_tools::BlobPtr blob(new blob_tools::Blob(buffer, sizeof(buffer), true));
#endif

  blob->setCompressed(true);

  ROS_INFO("Publishing a blob of size %u at address %p", blob->size(), blob->data());
  pub.publish(blob);
  ROS_INFO("Destroying blob at address %p", blob->data());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "blob_tools_example_publisher");
  ros::NodeHandle nh;
  pub = nh.advertise<blob_tools::Blob>("blob", 10);
  ros::Timer timer = nh.createTimer(ros::Duration(1.0), &publish);
  ros::spin();
  return 0;
}
