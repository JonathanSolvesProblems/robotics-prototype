// Generated by gencpp from file mux_selector/SelectMuxResponse.msg
// DO NOT EDIT!


#ifndef MUX_SELECTOR_MESSAGE_SELECTMUXRESPONSE_H
#define MUX_SELECTOR_MESSAGE_SELECTMUXRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mux_selector
{
template <class ContainerAllocator>
struct SelectMuxResponse_
{
  typedef SelectMuxResponse_<ContainerAllocator> Type;

  SelectMuxResponse_()
    : response()  {
    }
  SelectMuxResponse_(const ContainerAllocator& _alloc)
    : response(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _response_type;
  _response_type response;





  typedef boost::shared_ptr< ::mux_selector::SelectMuxResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mux_selector::SelectMuxResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SelectMuxResponse_

typedef ::mux_selector::SelectMuxResponse_<std::allocator<void> > SelectMuxResponse;

typedef boost::shared_ptr< ::mux_selector::SelectMuxResponse > SelectMuxResponsePtr;
typedef boost::shared_ptr< ::mux_selector::SelectMuxResponse const> SelectMuxResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mux_selector::SelectMuxResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mux_selector

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mux_selector::SelectMuxResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mux_selector::SelectMuxResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mux_selector::SelectMuxResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6de314e2dc76fbff2b6244a6ad70b68d";
  }

  static const char* value(const ::mux_selector::SelectMuxResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6de314e2dc76fbffULL;
  static const uint64_t static_value2 = 0x2b6244a6ad70b68dULL;
};

template<class ContainerAllocator>
struct DataType< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mux_selector/SelectMuxResponse";
  }

  static const char* value(const ::mux_selector::SelectMuxResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string response\n\
\n\
";
  }

  static const char* value(const ::mux_selector::SelectMuxResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.response);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SelectMuxResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mux_selector::SelectMuxResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mux_selector::SelectMuxResponse_<ContainerAllocator>& v)
  {
    s << indent << "response: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.response);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MUX_SELECTOR_MESSAGE_SELECTMUXRESPONSE_H
