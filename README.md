
[Djinni]: https://github.com/dropbox/djinni
[LevelDB]: https://github.com/google/leveldb
[Snappy]: https://github.com/google/snappy

# DroidDjinni

[![Android Studio](https://img.shields.io/badge/Android%20Studio-3.0-brightgreen.svg?style=flat)](https://developer.android.com/studio/index.html)

Android Djinni Sample using CMake.

This sample demonstrates how to implement [LevelDB][] Java interface bindings using [Djinni][].

## Getting Started

```
$ git clone --recursive https://github.com/joinAero/DroidDjinni.git
```

Then, use "Android Studio" to open this sample.

## Generate Code

If you wanna generate codes by [Djinni][],

```
$ cd DroidDjinni/

# Build djinni once.
$ cd deps/djinni/src
$ ./build

$ cd DroidDjinni/

# Generate codes.
$ ./djinni/build_djinni.sh
```

Then, the codes are in "DroidDjinni/djinni/output".

## Directory Structure

```
DroidDjinni/
├─app/                              # Android App
├─deps/                             # Dependencies
│  ├─djinni/
│  ├─leveldb/
│  └─snappy/
├─djinni/                           # Djinni Stuff
│  ├─idls/                          # Djinni IDL Files
│  │  ├─profile/
│  │  │ └─leveldb_profile.yaml      # Djinni Run Options (Change output directory here)
│  │  └─leveldb.idl                 # Djinni IDL File of LevelDB
│  ├─output/                        # Djinni Generate Codes (Ignored)
│  │  ├─cpp/
│  │  ├─java/
│  │  ├─jni/
│  │  └─objc/
│  ├─scripts/
│  └─build_djinni.sh                # Djinni Build Script (Run this to generate codes)
└─libleveldb/                       # Android Library of LevelDB
    ├─libs/
    └─src/
        ├─androidTest/
        ├─main/
        │  ├─cpp/
        │  │  ├─base/
        │  │  ├─cmake/
        │  │  ├─leveldb/
        │  │  │   ├─cpp/            # Copy from djinni/output/cpp
        │  │  │   ├─impl/           # Handwritten codes implement LevelDB bindings
        │  │  │   └─jni/            # Copy from djinni/output/jni
        │  │  └─CMakeLists.txt      # CMake listfile
        │  ├─java/                  # Copy from djinni/output/java
        │  └─res/
        └─test/
```

## Dependencies

* [Djinni][]
* [LevelDB][]
    * [Snappy][]
