// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Resource.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Resource.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

void protobuf_ShutdownFile_Resource_2eproto() {
  delete ResourceIndex::default_instance_;
  delete ServerConfig::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_Resource_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_Resource_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ResourceIndex::default_instance_ = new ResourceIndex();
  ServerConfig::default_instance_ = new ServerConfig();
  ResourceIndex::default_instance_->InitAsDefaultInstance();
  ServerConfig::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Resource_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_Resource_2eproto_once_);
void protobuf_AddDesc_Resource_2eproto() {
  ::google::protobuf::::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_Resource_2eproto_once_,
                 &protobuf_AddDesc_Resource_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Resource_2eproto {
  StaticDescriptorInitializer_Resource_2eproto() {
    protobuf_AddDesc_Resource_2eproto();
  }
} static_descriptor_initializer_Resource_2eproto_;
#endif

// ===================================================================

#ifndef _MSC_VER
const int ResourceIndex::kKeyFieldNumber;
const int ResourceIndex::kNameFieldNumber;
const int ResourceIndex::kOffsetFieldNumber;
const int ResourceIndex::kSizeFieldNumber;
const int ResourceIndex::kIsPictureFieldNumber;
#endif  // !_MSC_VER

ResourceIndex::ResourceIndex()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void ResourceIndex::InitAsDefaultInstance() {
}

ResourceIndex::ResourceIndex(const ResourceIndex& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void ResourceIndex::SharedCtor() {
  _cached_size_ = 0;
  key_ = GOOGLE_LONGLONG(0);
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  offset_ = 0;
  size_ = 0;
  ispicture_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ResourceIndex::~ResourceIndex() {
  SharedDtor();
}

void ResourceIndex::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ResourceIndex::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ResourceIndex& ResourceIndex::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Resource_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Resource_2eproto();
#endif
  return *default_instance_;
}

ResourceIndex* ResourceIndex::default_instance_ = NULL;

ResourceIndex* ResourceIndex::New() const {
  return new ResourceIndex;
}

void ResourceIndex::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    key_ = GOOGLE_LONGLONG(0);
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    offset_ = 0;
    size_ = 0;
    ispicture_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool ResourceIndex::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 key = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &key_)));
          set_has_key();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // required string name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_offset;
        break;
      }

      // required int32 offset = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_offset:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &offset_)));
          set_has_offset();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_size;
        break;
      }

      // required int32 size = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &size_)));
          set_has_size();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_IsPicture;
        break;
      }

      // optional int32 IsPicture = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_IsPicture:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ispicture_)));
          set_has_ispicture();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ResourceIndex::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int64 key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->key(), output);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->name(), output);
  }

  // required int32 offset = 3;
  if (has_offset()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->offset(), output);
  }

  // required int32 size = 4;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->size(), output);
  }

  // optional int32 IsPicture = 5;
  if (has_ispicture()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->ispicture(), output);
  }

}

int ResourceIndex::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int64 key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->key());
    }

    // required string name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

    // required int32 offset = 3;
    if (has_offset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->offset());
    }

    // required int32 size = 4;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->size());
    }

    // optional int32 IsPicture = 5;
    if (has_ispicture()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->ispicture());
    }

  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ResourceIndex::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ResourceIndex*>(&from));
}

void ResourceIndex::MergeFrom(const ResourceIndex& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_offset()) {
      set_offset(from.offset());
    }
    if (from.has_size()) {
      set_size(from.size());
    }
    if (from.has_ispicture()) {
      set_ispicture(from.ispicture());
    }
  }
}

void ResourceIndex::CopyFrom(const ResourceIndex& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResourceIndex::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void ResourceIndex::Swap(ResourceIndex* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(name_, other->name_);
    std::swap(offset_, other->offset_);
    std::swap(size_, other->size_);
    std::swap(ispicture_, other->ispicture_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ResourceIndex::GetTypeName() const {
  return "ResourceIndex";
}


// ===================================================================

bool ServerConfig_FILETYPE_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const ServerConfig_FILETYPE ServerConfig::UNZIP;
const ServerConfig_FILETYPE ServerConfig::ZIP;
const ServerConfig_FILETYPE ServerConfig::FILETYPE_MIN;
const ServerConfig_FILETYPE ServerConfig::FILETYPE_MAX;
const int ServerConfig::FILETYPE_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int ServerConfig::kVersionFieldNumber;
const int ServerConfig::kPackagenameFieldNumber;
const int ServerConfig::kUrlFieldNumber;
const int ServerConfig::kFiletypeFieldNumber;
const int ServerConfig::kIndexFieldNumber;
#endif  // !_MSC_VER

ServerConfig::ServerConfig()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
}

void ServerConfig::InitAsDefaultInstance() {
}

ServerConfig::ServerConfig(const ServerConfig& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
}

void ServerConfig::SharedCtor() {
  _cached_size_ = 0;
  version_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  packagename_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  filetype_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ServerConfig::~ServerConfig() {
  SharedDtor();
}

void ServerConfig::SharedDtor() {
  if (version_ != &::google::protobuf::internal::kEmptyString) {
    delete version_;
  }
  if (packagename_ != &::google::protobuf::internal::kEmptyString) {
    delete packagename_;
  }
  if (url_ != &::google::protobuf::internal::kEmptyString) {
    delete url_;
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void ServerConfig::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ServerConfig& ServerConfig::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_Resource_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_Resource_2eproto();
#endif
  return *default_instance_;
}

ServerConfig* ServerConfig::default_instance_ = NULL;

ServerConfig* ServerConfig::New() const {
  return new ServerConfig;
}

void ServerConfig::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_version()) {
      if (version_ != &::google::protobuf::internal::kEmptyString) {
        version_->clear();
      }
    }
    if (has_packagename()) {
      if (packagename_ != &::google::protobuf::internal::kEmptyString) {
        packagename_->clear();
      }
    }
    if (has_url()) {
      if (url_ != &::google::protobuf::internal::kEmptyString) {
        url_->clear();
      }
    }
    filetype_ = 0;
  }
  index_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

bool ServerConfig::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string version = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_version()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_packagename;
        break;
      }

      // required string packagename = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_packagename:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_packagename()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_url;
        break;
      }

      // required string url = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_url:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_url()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_filetype;
        break;
      }

      // optional .ServerConfig.FILETYPE filetype = 4 [default = UNZIP];
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_filetype:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::ServerConfig_FILETYPE_IsValid(value)) {
            set_filetype(static_cast< ::ServerConfig_FILETYPE >(value));
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_index;
        break;
      }

      // repeated .ResourceIndex index = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_index:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_index()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_index;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void ServerConfig::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string version = 1;
  if (has_version()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->version(), output);
  }

  // required string packagename = 2;
  if (has_packagename()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->packagename(), output);
  }

  // required string url = 3;
  if (has_url()) {
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->url(), output);
  }

  // optional .ServerConfig.FILETYPE filetype = 4 [default = UNZIP];
  if (has_filetype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      4, this->filetype(), output);
  }

  // repeated .ResourceIndex index = 5;
  for (int i = 0; i < this->index_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      5, this->index(i), output);
  }

}

int ServerConfig::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string version = 1;
    if (has_version()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->version());
    }

    // required string packagename = 2;
    if (has_packagename()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->packagename());
    }

    // required string url = 3;
    if (has_url()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->url());
    }

    // optional .ServerConfig.FILETYPE filetype = 4 [default = UNZIP];
    if (has_filetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->filetype());
    }

  }
  // repeated .ResourceIndex index = 5;
  total_size += 1 * this->index_size();
  for (int i = 0; i < this->index_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->index(i));
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ServerConfig::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ServerConfig*>(&from));
}

void ServerConfig::MergeFrom(const ServerConfig& from) {
  GOOGLE_CHECK_NE(&from, this);
  index_.MergeFrom(from.index_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_version()) {
      set_version(from.version());
    }
    if (from.has_packagename()) {
      set_packagename(from.packagename());
    }
    if (from.has_url()) {
      set_url(from.url());
    }
    if (from.has_filetype()) {
      set_filetype(from.filetype());
    }
  }
}

void ServerConfig::CopyFrom(const ServerConfig& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServerConfig::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  for (int i = 0; i < index_size(); i++) {
    if (!this->index(i).IsInitialized()) return false;
  }
  return true;
}

void ServerConfig::Swap(ServerConfig* other) {
  if (other != this) {
    std::swap(version_, other->version_);
    std::swap(packagename_, other->packagename_);
    std::swap(url_, other->url_);
    std::swap(filetype_, other->filetype_);
    index_.Swap(&other->index_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string ServerConfig::GetTypeName() const {
  return "ServerConfig";
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
