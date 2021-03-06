// Generated by gencpp from file swj_socket/heartrecvflag.msg
// DO NOT EDIT!


#ifndef SWJ_SOCKET_MESSAGE_HEARTRECVFLAG_H
#define SWJ_SOCKET_MESSAGE_HEARTRECVFLAG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace swj_socket
{
template <class ContainerAllocator>
struct heartrecvflag_
{
  typedef heartrecvflag_<ContainerAllocator> Type;

  heartrecvflag_()
    : heartrecvflag(0)
    , recv_flag(0)  {
    }
  heartrecvflag_(const ContainerAllocator& _alloc)
    : heartrecvflag(0)
    , recv_flag(0)  {
  (void)_alloc;
    }



   typedef int8_t _heartrecvflag_type;
  _heartrecvflag_type heartrecvflag;

   typedef int8_t _recv_flag_type;
  _recv_flag_type recv_flag;




  typedef boost::shared_ptr< ::swj_socket::heartrecvflag_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::swj_socket::heartrecvflag_<ContainerAllocator> const> ConstPtr;

}; // struct heartrecvflag_

typedef ::swj_socket::heartrecvflag_<std::allocator<void> > heartrecvflag;

typedef boost::shared_ptr< ::swj_socket::heartrecvflag > heartrecvflagPtr;
typedef boost::shared_ptr< ::swj_socket::heartrecvflag const> heartrecvflagConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::swj_socket::heartrecvflag_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::swj_socket::heartrecvflag_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace swj_socket

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'swj_socket': ['/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::swj_socket::heartrecvflag_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::swj_socket::heartrecvflag_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::swj_socket::heartrecvflag_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::swj_socket::heartrecvflag_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::swj_socket::heartrecvflag_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::swj_socket::heartrecvflag_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::swj_socket::heartrecvflag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b4a4cc1afa7750f8ddbae253c9ba88fd";
  }

  static const char* value(const ::swj_socket::heartrecvflag_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb4a4cc1afa7750f8ULL;
  static const uint64_t static_value2 = 0xddbae253c9ba88fdULL;
};

template<class ContainerAllocator>
struct DataType< ::swj_socket::heartrecvflag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "swj_socket/heartrecvflag";
  }

  static const char* value(const ::swj_socket::heartrecvflag_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::swj_socket::heartrecvflag_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 heartrecvflag\n\
int8 recv_flag\n\
";
  }

  static const char* value(const ::swj_socket::heartrecvflag_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::swj_socket::heartrecvflag_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.heartrecvflag);
      stream.next(m.recv_flag);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct heartrecvflag_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::swj_socket::heartrecvflag_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::swj_socket::heartrecvflag_<ContainerAllocator>& v)
  {
    s << indent << "heartrecvflag: ";
    Printer<int8_t>::stream(s, indent + "  ", v.heartrecvflag);
    s << indent << "recv_flag: ";
    Printer<int8_t>::stream(s, indent + "  ", v.recv_flag);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SWJ_SOCKET_MESSAGE_HEARTRECVFLAG_H
