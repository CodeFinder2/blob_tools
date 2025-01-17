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

#include <blob_tools/shape_shifter.h>

namespace blob_tools {

  ShapeShifter::ShapeShifter()
  {
  }

  ShapeShifter::ShapeShifter(const Blob& blob)
    : blob_(blob)
  {
  }

  ShapeShifter::~ShapeShifter()
  {
  }

  // Helpers for inspecting shapeshifter
  std::string const& ShapeShifter::getDataType()          const { return datatype; }
  std::string const& ShapeShifter::getMD5Sum()            const { return md5; }
  std::string const& ShapeShifter::getMessageDefinition() const { return msg_def; }

  ShapeShifter& ShapeShifter::morph(const std::string& _md5sum, const std::string& _datatype, const std::string& _msg_def,
             const std::string& _latching)
  {
    md5 = _md5sum;
    datatype = _datatype;
    msg_def = _msg_def;
    latching = _latching;
    return *this;
  }

  // Helper for advertising
  ros::Publisher ShapeShifter::advertise(ros::NodeHandle& nh, const std::string& topic, uint32_t queue_size_, bool latch,
                           const ros::SubscriberStatusCallback &connect_cb) const
  {
    ros::AdvertiseOptions opts(topic, queue_size_, getMD5Sum(), getDataType(), getMessageDefinition(), connect_cb);
    opts.latch = latch;
    return nh.advertise(opts);
  }

  //! Return the size of the serialized message
  uint32_t ShapeShifter::size() const {
    return blob_.size();
  }

} // namespace blob_tools
