#ifndef _ROS_demo01_Test_h
#define _ROS_demo01_Test_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace demo01
{

  class Test : public ros::Msg
  {
    public:
      typedef float _radar_x_type;
      _radar_x_type radar_x;
      typedef float _radar_y_type;
      _radar_y_type radar_y;
      typedef float _radar_z_type;
      _radar_z_type radar_z;
      typedef int32_t _flag_type;
      _flag_type flag;
      typedef int32_t _ok_type;
      _ok_type ok;
      typedef int32_t _vision_x_type;
      _vision_x_type vision_x;
      typedef int32_t _vision_y_type;
      _vision_y_type vision_y;
      typedef int32_t _size_type;
      _size_type size;
      typedef int32_t _Distance_type;
      _Distance_type Distance;

    Test():
      radar_x(0),
      radar_y(0),
      radar_z(0),
      flag(0),
      ok(0),
      vision_x(0),
      vision_y(0),
      size(0),
      Distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_radar_x;
      u_radar_x.real = this->radar_x;
      *(outbuffer + offset + 0) = (u_radar_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radar_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radar_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radar_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radar_x);
      union {
        float real;
        uint32_t base;
      } u_radar_y;
      u_radar_y.real = this->radar_y;
      *(outbuffer + offset + 0) = (u_radar_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radar_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radar_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radar_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radar_y);
      union {
        float real;
        uint32_t base;
      } u_radar_z;
      u_radar_z.real = this->radar_z;
      *(outbuffer + offset + 0) = (u_radar_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radar_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radar_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radar_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radar_z);
      union {
        int32_t real;
        uint32_t base;
      } u_flag;
      u_flag.real = this->flag;
      *(outbuffer + offset + 0) = (u_flag.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_flag.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_flag.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_flag.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flag);
      union {
        int32_t real;
        uint32_t base;
      } u_ok;
      u_ok.real = this->ok;
      *(outbuffer + offset + 0) = (u_ok.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ok.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ok.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ok.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ok);
      union {
        int32_t real;
        uint32_t base;
      } u_vision_x;
      u_vision_x.real = this->vision_x;
      *(outbuffer + offset + 0) = (u_vision_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vision_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vision_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vision_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vision_x);
      union {
        int32_t real;
        uint32_t base;
      } u_vision_y;
      u_vision_y.real = this->vision_y;
      *(outbuffer + offset + 0) = (u_vision_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vision_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vision_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vision_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vision_y);
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.real = this->size;
      *(outbuffer + offset + 0) = (u_size.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_size.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_size.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_size.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      union {
        int32_t real;
        uint32_t base;
      } u_Distance;
      u_Distance.real = this->Distance;
      *(outbuffer + offset + 0) = (u_Distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_radar_x;
      u_radar_x.base = 0;
      u_radar_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radar_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radar_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radar_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radar_x = u_radar_x.real;
      offset += sizeof(this->radar_x);
      union {
        float real;
        uint32_t base;
      } u_radar_y;
      u_radar_y.base = 0;
      u_radar_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radar_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radar_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radar_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radar_y = u_radar_y.real;
      offset += sizeof(this->radar_y);
      union {
        float real;
        uint32_t base;
      } u_radar_z;
      u_radar_z.base = 0;
      u_radar_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radar_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radar_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radar_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radar_z = u_radar_z.real;
      offset += sizeof(this->radar_z);
      union {
        int32_t real;
        uint32_t base;
      } u_flag;
      u_flag.base = 0;
      u_flag.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_flag.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_flag.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_flag.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->flag = u_flag.real;
      offset += sizeof(this->flag);
      union {
        int32_t real;
        uint32_t base;
      } u_ok;
      u_ok.base = 0;
      u_ok.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ok.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ok.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ok.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ok = u_ok.real;
      offset += sizeof(this->ok);
      union {
        int32_t real;
        uint32_t base;
      } u_vision_x;
      u_vision_x.base = 0;
      u_vision_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vision_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vision_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vision_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vision_x = u_vision_x.real;
      offset += sizeof(this->vision_x);
      union {
        int32_t real;
        uint32_t base;
      } u_vision_y;
      u_vision_y.base = 0;
      u_vision_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vision_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vision_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vision_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vision_y = u_vision_y.real;
      offset += sizeof(this->vision_y);
      union {
        int32_t real;
        uint32_t base;
      } u_size;
      u_size.base = 0;
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_size.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size = u_size.real;
      offset += sizeof(this->size);
      union {
        int32_t real;
        uint32_t base;
      } u_Distance;
      u_Distance.base = 0;
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Distance = u_Distance.real;
      offset += sizeof(this->Distance);
     return offset;
    }

    virtual const char * getType() override { return "demo01/Test"; };
    virtual const char * getMD5() override { return "33429fd887f8859d0c91115cb897edbe"; };

  };

}
#endif
