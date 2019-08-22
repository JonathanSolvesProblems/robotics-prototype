// Generated by gencpp from file mcu_control/ScienceRequestResponse.msg
// DO NOT EDIT!


#ifndef MCU_CONTROL_MESSAGE_SCIENCEREQUESTRESPONSE_H
#define MCU_CONTROL_MESSAGE_SCIENCEREQUESTRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mcu_control
{
template <class ContainerAllocator>
struct ScienceRequestResponse_
{
  typedef ScienceRequestResponse_<ContainerAllocator> Type;

  ScienceRequestResponse_()
    : response()
    , success(false)  {
    }
  ScienceRequestResponse_(const ContainerAllocator& _alloc)
    : response(_alloc)
    , success(false)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _response_type;
  _response_type response;

   typedef uint8_t _success_type;
  _success_type success;





  typedef boost::shared_ptr< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> const> ConstPtr;

}; // struct ScienceRequestResponse_

typedef ::mcu_control::ScienceRequestResponse_<std::allocator<void> > ScienceRequestResponse;

typedef boost::shared_ptr< ::mcu_control::ScienceRequestResponse > ScienceRequestResponsePtr;
typedef boost::shared_ptr< ::mcu_control::ScienceRequestResponse const> ScienceRequestResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mcu_control::ScienceRequestResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mcu_control

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'HasHeader': False, 'IsFixedSize': False, 'IsMessage': True}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mcu_control': ['/home/vashmata/Programming/git/robotics-prototype/robot/rospackages/src/mcu_control/msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct HasHeader< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "61c3bd4caa84e668cf48da398a910dc7";
  }

  static const char* value(const ::mcu_control::ScienceRequestResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x61c3bd4caa84e668ULL;
  static const uint64_t static_value2 = 0xcf48da398a910dc7ULL;
};

template<class ContainerAllocator>
struct DataType< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mcu_control/ScienceRequestResponse";
  }

  static const char* value(const ::mcu_control::ScienceRequestResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string response\n\
bool success\n\
\n\
";
  }

  static const char* value(const ::mcu_control::ScienceRequestResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.response);
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ScienceRequestResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mcu_control::ScienceRequestResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mcu_control::ScienceRequestResponse_<ContainerAllocator>& v)
  {
    s << indent << "response: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.response);
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MCU_CONTROL_MESSAGE_SCIENCEREQUESTRESPONSE_H
