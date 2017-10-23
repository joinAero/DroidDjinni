// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from leveldb.idl

#pragma once

#include "djinni_support.hpp"
#include "write_batch.hpp"

namespace djinni_generated {

class NativeWriteBatch final : ::djinni::JniInterface<::dd::WriteBatch, NativeWriteBatch> {
public:
    using CppType = std::shared_ptr<::dd::WriteBatch>;
    using CppOptType = std::shared_ptr<::dd::WriteBatch>;
    using JniType = jobject;

    using Boxed = NativeWriteBatch;

    ~NativeWriteBatch();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeWriteBatch>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeWriteBatch>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeWriteBatch();
    friend ::djinni::JniClass<NativeWriteBatch>;
    friend ::djinni::JniInterface<::dd::WriteBatch, NativeWriteBatch>;

};

}  // namespace djinni_generated