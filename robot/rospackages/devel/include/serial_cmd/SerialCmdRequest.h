// Generated by gencpp from file serial_cmd/SerialCmdRequest.msg
// DO NOT EDIT!


#ifndef SERIAL_CMD_MESSAGE_SERIALCMDREQUEST_H
#define SERIAL_CMD_MESSAGE_SERIALCMDREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace serial_cmd
{
template <class ContainerAllocator>
struct SerialCmdRequest_
{
  typedef SerialCmdRequest_<ContainerAllocator> Type;

  SerialCmdRequest_()
    : msg()  {
    }
  SerialCmdRequest_(const ContainerAllocator& _alloc)
    : msg(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _msg_type;
  _msg_type msg;





  typedef boost::shared_ptr< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SerialCmdRequest_

typedef ::serial_cmd::SerialCmdRequest_<std::allocator<void> > SerialCmdRequest;

typedef boost::shared_ptr< ::serial_cmd::SerialCmdRequest > SerialCmdRequestPtr;
typedef boost::shared_ptr< ::serial_cmd::SerialCmdRequest const> SerialCmdRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::serial_cmd::SerialCmdRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace serial_cmd

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "7d96ed730776804754140b85e64c862e";
  }

  static const char* value(const ::serial_cmd::SerialCmdRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x7d96ed7307768047ULL;
  static const uint64_t static_value2 = 0x54140b85e64c862eULL;
};

template<class ContainerAllocator>
struct DataType< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "serial_cmd/SerialCmdRequest";
  }

  static const char* value(const ::serial_cmd::SerialCmdRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string msg\n\
";
  }

  static const char* value(const ::serial_cmd::SerialCmdRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.msg);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SerialCmdRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::serial_cmd::SerialCmdRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::serial_cmd::SerialCmdRequest_<ContainerAllocator>& v)
  {
    s << indent << "msg: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.msg);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SERIAL_CMD_MESSAGE_SERIALCMDREQUEST_H
