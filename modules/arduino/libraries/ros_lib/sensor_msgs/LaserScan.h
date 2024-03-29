#ifndef ros_sensor_msgs_LaserScan_h
#define ros_sensor_msgs_LaserScan_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"
#include "std_msgs/Header.h"

namespace sensor_msgs
{

  class LaserScan : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float angle_min;
      float angle_max;
      float angle_increment;
      float time_increment;
      float scan_time;
      float range_min;
      float range_max;
      unsigned char ranges_length;
      float st_ranges;
      float * ranges;
      unsigned char intensities_length;
      float st_intensities;
      float * intensities;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        unsigned long base;
      } u_angle_min;
      u_angle_min.real = this->angle_min;
      *(outbuffer + offset + 0) = (u_angle_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_min.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_min);
      union {
        float real;
        unsigned long base;
      } u_angle_max;
      u_angle_max.real = this->angle_max;
      *(outbuffer + offset + 0) = (u_angle_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_max.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_max);
      union {
        float real;
        unsigned long base;
      } u_angle_increment;
      u_angle_increment.real = this->angle_increment;
      *(outbuffer + offset + 0) = (u_angle_increment.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle_increment.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle_increment.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle_increment.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_increment);
      union {
        float real;
        unsigned long base;
      } u_time_increment;
      u_time_increment.real = this->time_increment;
      *(outbuffer + offset + 0) = (u_time_increment.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time_increment.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time_increment.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time_increment.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_increment);
      union {
        float real;
        unsigned long base;
      } u_scan_time;
      u_scan_time.real = this->scan_time;
      *(outbuffer + offset + 0) = (u_scan_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_scan_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_scan_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_scan_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->scan_time);
      union {
        float real;
        unsigned long base;
      } u_range_min;
      u_range_min.real = this->range_min;
      *(outbuffer + offset + 0) = (u_range_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_range_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_range_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_range_min.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->range_min);
      union {
        float real;
        unsigned long base;
      } u_range_max;
      u_range_max.real = this->range_max;
      *(outbuffer + offset + 0) = (u_range_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_range_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_range_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_range_max.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->range_max);
      *(outbuffer + offset++) = ranges_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < ranges_length; i++){
      union {
        float real;
        unsigned long base;
      } u_rangesi;
      u_rangesi.real = this->ranges[i];
      *(outbuffer + offset + 0) = (u_rangesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rangesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rangesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rangesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ranges[i]);
      }
      *(outbuffer + offset++) = intensities_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( unsigned char i = 0; i < intensities_length; i++){
      union {
        float real;
        unsigned long base;
      } u_intensitiesi;
      u_intensitiesi.real = this->intensities[i];
      *(outbuffer + offset + 0) = (u_intensitiesi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_intensitiesi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_intensitiesi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_intensitiesi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->intensities[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        unsigned long base;
      } u_angle_min;
      u_angle_min.base = 0;
      u_angle_min.base |= ((typeof(u_angle_min.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_min.base |= ((typeof(u_angle_min.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_min.base |= ((typeof(u_angle_min.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_min.base |= ((typeof(u_angle_min.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_min = u_angle_min.real;
      offset += sizeof(this->angle_min);
      union {
        float real;
        unsigned long base;
      } u_angle_max;
      u_angle_max.base = 0;
      u_angle_max.base |= ((typeof(u_angle_max.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_max.base |= ((typeof(u_angle_max.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_max.base |= ((typeof(u_angle_max.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_max.base |= ((typeof(u_angle_max.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_max = u_angle_max.real;
      offset += sizeof(this->angle_max);
      union {
        float real;
        unsigned long base;
      } u_angle_increment;
      u_angle_increment.base = 0;
      u_angle_increment.base |= ((typeof(u_angle_increment.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle_increment.base |= ((typeof(u_angle_increment.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle_increment.base |= ((typeof(u_angle_increment.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle_increment.base |= ((typeof(u_angle_increment.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle_increment = u_angle_increment.real;
      offset += sizeof(this->angle_increment);
      union {
        float real;
        unsigned long base;
      } u_time_increment;
      u_time_increment.base = 0;
      u_time_increment.base |= ((typeof(u_time_increment.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time_increment.base |= ((typeof(u_time_increment.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time_increment.base |= ((typeof(u_time_increment.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time_increment.base |= ((typeof(u_time_increment.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time_increment = u_time_increment.real;
      offset += sizeof(this->time_increment);
      union {
        float real;
        unsigned long base;
      } u_scan_time;
      u_scan_time.base = 0;
      u_scan_time.base |= ((typeof(u_scan_time.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_scan_time.base |= ((typeof(u_scan_time.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_scan_time.base |= ((typeof(u_scan_time.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_scan_time.base |= ((typeof(u_scan_time.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->scan_time = u_scan_time.real;
      offset += sizeof(this->scan_time);
      union {
        float real;
        unsigned long base;
      } u_range_min;
      u_range_min.base = 0;
      u_range_min.base |= ((typeof(u_range_min.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_range_min.base |= ((typeof(u_range_min.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_range_min.base |= ((typeof(u_range_min.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_range_min.base |= ((typeof(u_range_min.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->range_min = u_range_min.real;
      offset += sizeof(this->range_min);
      union {
        float real;
        unsigned long base;
      } u_range_max;
      u_range_max.base = 0;
      u_range_max.base |= ((typeof(u_range_max.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_range_max.base |= ((typeof(u_range_max.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_range_max.base |= ((typeof(u_range_max.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_range_max.base |= ((typeof(u_range_max.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->range_max = u_range_max.real;
      offset += sizeof(this->range_max);
      unsigned char ranges_lengthT = *(inbuffer + offset++);
      if(ranges_lengthT > ranges_length)
        this->ranges = (float*)realloc(this->ranges, ranges_lengthT * sizeof(float));
      offset += 3;
      ranges_length = ranges_lengthT;
      for( unsigned char i = 0; i < ranges_length; i++){
      union {
        float real;
        unsigned long base;
      } u_st_ranges;
      u_st_ranges.base = 0;
      u_st_ranges.base |= ((typeof(u_st_ranges.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_ranges.base |= ((typeof(u_st_ranges.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_ranges.base |= ((typeof(u_st_ranges.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_ranges.base |= ((typeof(u_st_ranges.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_ranges = u_st_ranges.real;
      offset += sizeof(this->st_ranges);
        memcpy( &(this->ranges[i]), &(this->st_ranges), sizeof(float));
      }
      unsigned char intensities_lengthT = *(inbuffer + offset++);
      if(intensities_lengthT > intensities_length)
        this->intensities = (float*)realloc(this->intensities, intensities_lengthT * sizeof(float));
      offset += 3;
      intensities_length = intensities_lengthT;
      for( unsigned char i = 0; i < intensities_length; i++){
      union {
        float real;
        unsigned long base;
      } u_st_intensities;
      u_st_intensities.base = 0;
      u_st_intensities.base |= ((typeof(u_st_intensities.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_intensities.base |= ((typeof(u_st_intensities.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_intensities.base |= ((typeof(u_st_intensities.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_intensities.base |= ((typeof(u_st_intensities.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_intensities = u_st_intensities.real;
      offset += sizeof(this->st_intensities);
        memcpy( &(this->intensities[i]), &(this->st_intensities), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "sensor_msgs/LaserScan"; };

  };

}
#endif