// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: scsid.proto

#ifndef PROTOBUF_scsid_2eproto__INCLUDED
#define PROTOBUF_scsid_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace gproto {
namespace s {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_scsid_2eproto();
void protobuf_AssignDesc_scsid_2eproto();
void protobuf_ShutdownFile_scsid_2eproto();


enum MSGID {
  CSID_L2W_HEART = 1000
};
bool MSGID_IsValid(int value);
const MSGID MSGID_MIN = CSID_L2W_HEART;
const MSGID MSGID_MAX = CSID_L2W_HEART;
const int MSGID_ARRAYSIZE = MSGID_MAX + 1;

const ::google::protobuf::EnumDescriptor* MSGID_descriptor();
inline const ::std::string& MSGID_Name(MSGID value) {
  return ::google::protobuf::internal::NameOfEnum(
    MSGID_descriptor(), value);
}
inline bool MSGID_Parse(
    const ::std::string& name, MSGID* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MSGID>(
    MSGID_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace s
}  // namespace gproto

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gproto::s::MSGID>() {
  return ::gproto::s::MSGID_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_scsid_2eproto__INCLUDED
