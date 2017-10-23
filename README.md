
# DroidDjinni

[![Android Studio Preview](https://img.shields.io/badge/Android%20Studio-3.0%20Preview-brightgreen.svg?style=flat)](https://developer.android.com/studio/preview/index.html)

Android Djinni Sample using CMake :)

## Getting Started

```
$ git clone --recursive https://github.com/joinAero/DroidDjinni.git
```

## Generate Code

```
$ cd DroidDjinni/

# Build djinni once.
$ cd deps/djinni/src
$ ./build

$ cd DroidDjinni/

# Generate codes.
$ ./djinni/build_djinni.sh
```

## Dependencies

* [Djinni](https://github.com/dropbox/djinni)
* [LevelDB](https://github.com/google/leveldb)
    * [Snappy](https://github.com/google/snappy.git)
