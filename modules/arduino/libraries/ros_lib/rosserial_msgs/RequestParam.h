#ifndef ros_SERVICE_RequestParam_h
#define ros_SERVICE_RequestParam_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace rosserial_msgs
{

static const char REQUESTPARAM[] = "rosserial_msgs/RequestParam";

  class RequestParamRequest : public ros::Msg
  {
    public:
      char * name;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      long * length_name = (long *)(outbuffer + offset);
      *length_name = strlen( (const char*) this->name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, *length_name);
      offset += *length_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
           }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
     return offset;
    }

    const char * getType(){ return REQUESTPARAM; };

  };

  class RequestParamResponse : public ros::Msg
  {
    public:
      unsigned char ints_length;
      long st_ints;
      long * ints;
      unsigned char floats_length;
      float st_floats;
      float * floats;
      unsigned char strings_length;
      char* st_strings;
      char* * strings;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      *(outbuffer + offset++) = ints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < ints_length; i++){
      union {
        long real;
        unsigned long base;
      } u_intsi;
      u_intsi.real = this->ints[i];
      *(outbuffer + offset + 0) = (u_intsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_intsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_intsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_intsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ints[i]);
      }
      *(outbuffer + offset++) = floats_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < floats_length; i++){
      union {
        float real;
        unsigned long base;
      } u_floatsi;
      u_floatsi.real = this->floats[i];
      *(outbuffer + offset + 0) = (u_floatsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_floatsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_floatsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_floatsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->floats[i]);
      }
      *(outbuffer + offset++) = strings_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < strings_length; i++){
      long * length_stringsi = (long *)(outbuffer + offset);
      *length_stringsi = strlen( (const char*) this->strings[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->strings[i], *length_stringsi);
      offset += *length_stringsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      unsigned char ints_lengthT = *(inbuffer + offset++);
      if(ints_lengthT > ints_length)
        this->ints = (long*)realloc(this->ints, ints_lengthT * sizeof(long));
      offset += 3;
      ints_length = ints_lengthT;
      for( unsigned char i = 0; i < ints_length; i++){
      union {
        long real;
        unsigned long base;
      } u_st_ints;
      u_st_ints.base = 0;
      u_st_ints.base |= ((typeof(u_st_ints.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_ints.base |= ((typeof(u_st_ints.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_ints.base |= ((typeof(u_st_ints.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_ints.base |= ((typeof(u_st_ints.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_ints = u_st_ints.real;
      offset += sizeof(this->st_ints);
        memcpy( &(this->ints[i]), &(this->st_ints), sizeof(long));
      }
      unsigned char floats_lengthT = *(inbuffer + offset++);
      if(floats_lengthT > floats_length)
        this->floats = (float*)realloc(this->floats, floats_lengthT * sizeof(float));
      offset += 3;
      floats_length = floats_lengthT;
      for( unsigned char i = 0; i < floats_length; i++){
      union {
        float real;
        unsigned long base;
      } u_st_floats;
      u_st_floats.base = 0;
      u_st_floats.base |= ((typeof(u_st_floats.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_floats.base |= ((typeof(u_st_floats.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_floats.base |= ((typeof(u_st_floats.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_floats.base |= ((typeof(u_st_floats.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_floats = u_st_floats.real;
      offset += sizeof(this->st_floats);
        memcpy( &(this->floats[i]), &(this->st_floats), sizeof(float));
      }
      unsigned char strings_lengthT = *(inbuffer + offset++);
      if(strings_lengthT > strings_length)
        this->strings = (char**)realloc(this->strings, strings_lengthT * sizeof(char*));
      offset += 3;
      strings_length = strings_lengthT;
      for( unsigned char i = 0; i < strings_length; i++){
      uint32_t length_st_strings = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_strings; ++k){
          inbuffer[k-1]=inbuffer[k];
           }
      inbuffer[offset+length_st_strings-1]=0;
      this->st_strings = (char *)(inbuffer + offset-1);
      offset += length_st_strings;
        memcpy( &(this->strings[i]), &(this->st_strings), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return REQUESTPARAM; };

  };

}
#endif