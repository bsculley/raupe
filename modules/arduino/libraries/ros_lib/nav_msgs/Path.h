#ifndef ros_nav_msgs_Path_h
#define ros_nav_msgs_Path_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/PoseStamped.h"

namespace nav_msgs
{

  class Path : public ros::Msg
  {
    public:
      std_msgs::Header header;
      unsigned char poses_length;
      geometry_msgs::PoseStamped st_poses;
      geometry_msgs::PoseStamped * poses;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = poses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      unsigned char poses_lengthT = *(inbuffer + offset++);
      if(poses_lengthT > poses_length)
        this->poses = (geometry_msgs::PoseStamped*)realloc(this->poses, poses_lengthT * sizeof(geometry_msgs::PoseStamped));
      offset += 3;
      poses_length = poses_lengthT;
      for( unsigned char i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(geometry_msgs::PoseStamped));
      }
     return offset;
    }

    const char * getType(){ return "nav_msgs/Path"; };

  };

}
#endif