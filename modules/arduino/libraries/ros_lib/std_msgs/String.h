#ifndef ros_std_msgs_String_h
#define ros_std_msgs_String_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace std_msgs
{

  class String : public ros::Msg
  {
    public:
      char * data;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      long * length_data = (long *)(outbuffer + offset);
      *length_data = strlen( (const char*) this->data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, *length_data);
      offset += *length_data;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_data = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
           }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
     return offset;
    }

    const char * getType(){ return "std_msgs/String"; };

  };

}
#endif