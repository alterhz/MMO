// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: game.proto

#ifndef PROTOBUF_game_2eproto__INCLUDED
#define PROTOBUF_game_2eproto__INCLUDED

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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "inc.pb.h"
// @@protoc_insertion_point(includes)

namespace gproto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_game_2eproto();
void protobuf_AssignDesc_game_2eproto();
void protobuf_ShutdownFile_game_2eproto();

class MSG_C2G_PING;
class MSG_G2C_PING;

// ===================================================================

class MSG_C2G_PING : public ::google::protobuf::Message {
 public:
  MSG_C2G_PING();
  virtual ~MSG_C2G_PING();

  MSG_C2G_PING(const MSG_C2G_PING& from);

  inline MSG_C2G_PING& operator=(const MSG_C2G_PING& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MSG_C2G_PING& default_instance();

  void Swap(MSG_C2G_PING* other);

  // implements Message ----------------------------------------------

  MSG_C2G_PING* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_C2G_PING& from);
  void MergeFrom(const MSG_C2G_PING& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 count = 1;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 1;
  inline ::google::protobuf::int32 count() const;
  inline void set_count(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gproto.MSG_C2G_PING)
 private:
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 count_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_game_2eproto();
  friend void protobuf_AssignDesc_game_2eproto();
  friend void protobuf_ShutdownFile_game_2eproto();

  void InitAsDefaultInstance();
  static MSG_C2G_PING* default_instance_;
};
// -------------------------------------------------------------------

class MSG_G2C_PING : public ::google::protobuf::Message {
 public:
  MSG_G2C_PING();
  virtual ~MSG_G2C_PING();

  MSG_G2C_PING(const MSG_G2C_PING& from);

  inline MSG_G2C_PING& operator=(const MSG_G2C_PING& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MSG_G2C_PING& default_instance();

  void Swap(MSG_G2C_PING* other);

  // implements Message ----------------------------------------------

  MSG_G2C_PING* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_G2C_PING& from);
  void MergeFrom(const MSG_G2C_PING& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 count = 1;
  inline bool has_count() const;
  inline void clear_count();
  static const int kCountFieldNumber = 1;
  inline ::google::protobuf::int32 count() const;
  inline void set_count(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:gproto.MSG_G2C_PING)
 private:
  inline void set_has_count();
  inline void clear_has_count();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 count_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_game_2eproto();
  friend void protobuf_AssignDesc_game_2eproto();
  friend void protobuf_ShutdownFile_game_2eproto();

  void InitAsDefaultInstance();
  static MSG_G2C_PING* default_instance_;
};
// ===================================================================


// ===================================================================

// MSG_C2G_PING

// required int32 count = 1;
inline bool MSG_C2G_PING::has_count() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_C2G_PING::set_has_count() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_C2G_PING::clear_has_count() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_C2G_PING::clear_count() {
  count_ = 0;
  clear_has_count();
}
inline ::google::protobuf::int32 MSG_C2G_PING::count() const {
  return count_;
}
inline void MSG_C2G_PING::set_count(::google::protobuf::int32 value) {
  set_has_count();
  count_ = value;
}

// -------------------------------------------------------------------

// MSG_G2C_PING

// required int32 count = 1;
inline bool MSG_G2C_PING::has_count() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_G2C_PING::set_has_count() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_G2C_PING::clear_has_count() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_G2C_PING::clear_count() {
  count_ = 0;
  clear_has_count();
}
inline ::google::protobuf::int32 MSG_G2C_PING::count() const {
  return count_;
}
inline void MSG_G2C_PING::set_count(::google::protobuf::int32 value) {
  set_has_count();
  count_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gproto

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_game_2eproto__INCLUDED
