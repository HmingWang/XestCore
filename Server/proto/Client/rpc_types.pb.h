//
// Created by whaim on 16-4-9.
//

#ifndef XESTCORE_RPC_TYPES_PB_H
#define XESTCORE_RPC_TYPES_PB_H

#include <google/protobuf/message.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/repeated_field.h>
#include "Define.h"

class TC_SHARED_API ProcessId : public ::google::protobuf::Message {
public:
    ProcessId();
    virtual ~ProcessId();

    ProcessId(const ProcessId& from);

    inline ProcessId& operator=(const ProcessId& from) {
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
    static const ProcessId& default_instance();

    void Swap(ProcessId* other);

    // implements Message ----------------------------------------------

    ProcessId* New() const;
    void CopyFrom(const ::google::protobuf::Message& from);
    void MergeFrom(const ::google::protobuf::Message& from);
    void CopyFrom(const ProcessId& from);
    void MergeFrom(const ProcessId& from);
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

    // required uint32 label = 1;
    inline bool has_label() const;
    inline void clear_label();
    static const int kLabelFieldNumber = 1;
    inline ::google::protobuf::uint32 label() const;
    inline void set_label(::google::protobuf::uint32 value);

    // required uint32 epoch = 2;
    inline bool has_epoch() const;
    inline void clear_epoch();
    static const int kEpochFieldNumber = 2;
    inline ::google::protobuf::uint32 epoch() const;
    inline void set_epoch(::google::protobuf::uint32 value);

    // @@protoc_insertion_point(class_scope:bgs.protocol.ProcessId)
private:
    inline void set_has_label();
    inline void clear_has_label();
    inline void set_has_epoch();
    inline void clear_has_epoch();

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 _has_bits_[1];
    mutable int _cached_size_;
    ::google::protobuf::uint32 label_;
    ::google::protobuf::uint32 epoch_;
    friend void TC_SHARED_API protobuf_AddDesc_rpc_5ftypes_2eproto();
    friend void protobuf_AssignDesc_rpc_5ftypes_2eproto();
    friend void protobuf_ShutdownFile_rpc_5ftypes_2eproto();

    void InitAsDefaultInstance();
    static ProcessId* default_instance_;
};
class TC_SHARED_API ObjectAddress : public ::google::protobuf::Message {
public:
    ObjectAddress();
    virtual ~ObjectAddress();

    ObjectAddress(const ObjectAddress& from);

    inline ObjectAddress& operator=(const ObjectAddress& from) {
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
    static const ObjectAddress& default_instance();

    void Swap(ObjectAddress* other);

    // implements Message ----------------------------------------------

    ObjectAddress* New() const;
    void CopyFrom(const ::google::protobuf::Message& from);
    void MergeFrom(const ::google::protobuf::Message& from);
    void CopyFrom(const ObjectAddress& from);
    void MergeFrom(const ObjectAddress& from);
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

    // required .bgs.protocol.ProcessId host = 1;
    inline bool has_host() const;
    inline void clear_host();
    static const int kHostFieldNumber = 1;
    inline const ProcessId& host() const;
    inline ProcessId* mutable_host();
    inline ProcessId* release_host();
    inline void set_allocated_host(ProcessId* host);

    // optional uint64 object_id = 2 [default = 0];
    inline bool has_object_id() const;
    inline void clear_object_id();
    static const int kObjectIdFieldNumber = 2;
    inline ::google::protobuf::uint64 object_id() const;
    inline void set_object_id(::google::protobuf::uint64 value);

    // @@protoc_insertion_point(class_scope:bgs.protocol.ObjectAddress)
private:
    inline void set_has_host();
    inline void clear_has_host();
    inline void set_has_object_id();
    inline void clear_has_object_id();

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 _has_bits_[1];
    mutable int _cached_size_;
    ProcessId* host_;
    ::google::protobuf::uint64 object_id_;
    friend void TC_SHARED_API protobuf_AddDesc_rpc_5ftypes_2eproto();
    friend void protobuf_AssignDesc_rpc_5ftypes_2eproto();
    friend void protobuf_ShutdownFile_rpc_5ftypes_2eproto();

    void InitAsDefaultInstance();
    static ObjectAddress* default_instance_;
};
class TC_SHARED_API ErrorInfo : public ::google::protobuf::Message {
public:
    ErrorInfo();
    virtual ~ErrorInfo();

    ErrorInfo(const ErrorInfo& from);

    inline ErrorInfo& operator=(const ErrorInfo& from) {
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
    static const ErrorInfo& default_instance();

    void Swap(ErrorInfo* other);

    // implements Message ----------------------------------------------

    ErrorInfo* New() const;
    void CopyFrom(const ::google::protobuf::Message& from);
    void MergeFrom(const ::google::protobuf::Message& from);
    void CopyFrom(const ErrorInfo& from);
    void MergeFrom(const ErrorInfo& from);
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

    // required .bgs.protocol.ObjectAddress object_address = 1;
    inline bool has_object_address() const;
    inline void clear_object_address();
    static const int kObjectAddressFieldNumber = 1;
    inline const ObjectAddress& object_address() const;
    inline ObjectAddress* mutable_object_address();
    inline ObjectAddress* release_object_address();
    inline void set_allocated_object_address(ObjectAddress* object_address);

    // required uint32 status = 2;
    inline bool has_status() const;
    inline void clear_status();
    static const int kStatusFieldNumber = 2;
    inline ::google::protobuf::uint32 status() const;
    inline void set_status(::google::protobuf::uint32 value);

    // required uint32 service_hash = 3;
    inline bool has_service_hash() const;
    inline void clear_service_hash();
    static const int kServiceHashFieldNumber = 3;
    inline ::google::protobuf::uint32 service_hash() const;
    inline void set_service_hash(::google::protobuf::uint32 value);

    // required uint32 method_id = 4;
    inline bool has_method_id() const;
    inline void clear_method_id();
    static const int kMethodIdFieldNumber = 4;
    inline ::google::protobuf::uint32 method_id() const;
    inline void set_method_id(::google::protobuf::uint32 value);

    // @@protoc_insertion_point(class_scope:bgs.protocol.ErrorInfo)
private:
    inline void set_has_object_address();
    inline void clear_has_object_address();
    inline void set_has_status();
    inline void clear_has_status();
    inline void set_has_service_hash();
    inline void clear_has_service_hash();
    inline void set_has_method_id();
    inline void clear_has_method_id();

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 _has_bits_[1];
    mutable int _cached_size_;
    ObjectAddress* object_address_;
    ::google::protobuf::uint32 status_;
    ::google::protobuf::uint32 service_hash_;
    ::google::protobuf::uint32 method_id_;
    friend void TC_SHARED_API protobuf_AddDesc_rpc_5ftypes_2eproto();
    friend void protobuf_AssignDesc_rpc_5ftypes_2eproto();
    friend void protobuf_ShutdownFile_rpc_5ftypes_2eproto();

    void InitAsDefaultInstance();
    static ErrorInfo* default_instance_;
};
class TC_SHARED_API Header : public ::google::protobuf::Message
{
public:
    Header();
    virtual ~Header();

    Header(const Header& from);

    inline Header& operator=(const Header& from) {
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
    static const Header& default_instance();

    void Swap(Header* other);

    // implements Message ----------------------------------------------

    Header* New() const;
    void CopyFrom(const ::google::protobuf::Message& from);
    void MergeFrom(const ::google::protobuf::Message& from);
    void CopyFrom(const Header& from);
    void MergeFrom(const Header& from);
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

    // required uint32 service_id = 1;
    inline bool has_service_id() const;
    inline void clear_service_id();
    static const int kServiceIdFieldNumber = 1;
    inline ::google::protobuf::uint32 service_id() const;
    inline void set_service_id(::google::protobuf::uint32 value);

    // optional uint32 method_id = 2;
    inline bool has_method_id() const;
    inline void clear_method_id();
    static const int kMethodIdFieldNumber = 2;
    inline ::google::protobuf::uint32 method_id() const;
    inline void set_method_id(::google::protobuf::uint32 value);

    // required uint32 token = 3;
    inline bool has_token() const;
    inline void clear_token();
    static const int kTokenFieldNumber = 3;
    inline ::google::protobuf::uint32 token() const;
    inline void set_token(::google::protobuf::uint32 value);

    // optional uint64 object_id = 4 [default = 0];
    inline bool has_object_id() const;
    inline void clear_object_id();
    static const int kObjectIdFieldNumber = 4;
    inline ::google::protobuf::uint64 object_id() const;
    inline void set_object_id(::google::protobuf::uint64 value);

    // optional uint32 size = 5 [default = 0];
    inline bool has_size() const;
    inline void clear_size();
    static const int kSizeFieldNumber = 5;
    inline ::google::protobuf::uint32 size() const;
    inline void set_size(::google::protobuf::uint32 value);

    // optional uint32 status = 6 [default = 0];
    inline bool has_status() const;
    inline void clear_status();
    static const int kStatusFieldNumber = 6;
    inline ::google::protobuf::uint32 status() const;
    inline void set_status(::google::protobuf::uint32 value);

    // repeated .bgs.protocol.ErrorInfo error = 7;
    inline int error_size() const;
    inline void clear_error();
    static const int kErrorFieldNumber = 7;
    inline const ErrorInfo& error(int index) const;
    inline ErrorInfo* mutable_error(int index);
    inline ErrorInfo* add_error();
    inline const ::google::protobuf::RepeatedPtrField<ErrorInfo >&
            error() const;
    inline ::google::protobuf::RepeatedPtrField<ErrorInfo >*
            mutable_error();

    // optional uint64 timeout = 8;
    inline bool has_timeout() const;
    inline void clear_timeout();
    static const int kTimeoutFieldNumber = 8;
    inline ::google::protobuf::uint64 timeout() const;
    inline void set_timeout(::google::protobuf::uint64 value);

    // optional bool is_response = 9;
    inline bool has_is_response() const;
    inline void clear_is_response();
    static const int kIsResponseFieldNumber = 9;
    inline bool is_response() const;
    inline void set_is_response(bool value);

    // repeated .bgs.protocol.ProcessId forward_targets = 10;
    inline int forward_targets_size() const;
    inline void clear_forward_targets();
    static const int kForwardTargetsFieldNumber = 10;
    inline const ProcessId& forward_targets(int index) const;
    inline ProcessId* mutable_forward_targets(int index);
    inline ProcessId* add_forward_targets();
    inline const ::google::protobuf::RepeatedPtrField<ProcessId >&
            forward_targets() const;
    inline ::google::protobuf::RepeatedPtrField<ProcessId >*
            mutable_forward_targets();

    // optional fixed32 service_hash = 11;
    inline bool has_service_hash() const;
    inline void clear_service_hash();
    static const int kServiceHashFieldNumber = 11;
    inline ::google::protobuf::uint32 service_hash() const;
    inline void set_service_hash(::google::protobuf::uint32 value);

    // @@protoc_insertion_point(class_scope:bgs.protocol.Header)
private:
    inline void set_has_service_id();
    inline void clear_has_service_id();
    inline void set_has_method_id();
    inline void clear_has_method_id();
    inline void set_has_token();
    inline void clear_has_token();
    inline void set_has_object_id();
    inline void clear_has_object_id();
    inline void set_has_size();
    inline void clear_has_size();
    inline void set_has_status();
    inline void clear_has_status();
    inline void set_has_timeout();
    inline void clear_has_timeout();
    inline void set_has_is_response();
    inline void clear_has_is_response();
    inline void set_has_service_hash();
    inline void clear_has_service_hash();

    ::google::protobuf::UnknownFieldSet _unknown_fields_;

    ::google::protobuf::uint32 _has_bits_[1];
    mutable int _cached_size_;
    ::google::protobuf::uint32 service_id_;
    ::google::protobuf::uint32 method_id_;
    ::google::protobuf::uint64 object_id_;
    ::google::protobuf::uint32 token_;
    ::google::protobuf::uint32 size_;
    ::google::protobuf::RepeatedPtrField<ErrorInfo > error_;
    ::google::protobuf::uint32 status_;
    bool is_response_;
    ::google::protobuf::uint64 timeout_;
    ::google::protobuf::RepeatedPtrField<ProcessId > forward_targets_;
    ::google::protobuf::uint32 service_hash_;
    friend void TC_SHARED_API protobuf_AddDesc_rpc_5ftypes_2eproto();
    friend void protobuf_AssignDesc_rpc_5ftypes_2eproto();
    friend void protobuf_ShutdownFile_rpc_5ftypes_2eproto();

    void InitAsDefaultInstance();
    static Header* default_instance_;
};
#endif //XESTCORE_RPC_TYPES_PB_H
