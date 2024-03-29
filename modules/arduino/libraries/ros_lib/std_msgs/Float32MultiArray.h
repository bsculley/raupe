#ifndef ros_std_msgs_Float32MultiArray_h
#define ros_std_msgs_Float32MultiArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"
#include "std_msgs/MultiArrayLayout.h"

namespace std_msgs
{

  class Float32MultiArray : public ros::Msg
  {
    public:
      std_msgs::MultiArrayLayout layout;
      unsigned char data_length;
      float st_data;
      float * data;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      offset += this->layout.serialize(outbuffer + offset);
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < data_length; i++){
      union {
        float real;
        unsigned long base;
      } u_datai;
      u_datai.real = this->data[i];
      *(outbuffer + offset + 0) = (u_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_datai.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->layout.deserialize(inbuffer + offset);
      unsigned char data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (float*)realloc(this->data, data_lengthT * sizeof(float));
      offset += 3;
      data_length = data_lengthT;
      for( unsigned char i = 0; i < data_length; i++){
      union {
        float real;
        unsigned long base;
      } u_st_data;
      u_st_data.base = 0;
      u_st_data.base |= ((typeof(u_st_data.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_data.base |= ((typeof(u_st_data.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_data.base |= ((typeof(u_st_data.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_data.base |= ((typeof(u_st_data.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_data = u_st_data.real;
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "std_msgs/Float32MultiArray"; };

  };

}
#endif