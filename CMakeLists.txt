cmake_minimum_required(VERSION 3.27)
project(vapev4_detector)

set(CMAKE_CXX_STANDARD 23)

add_library(vapev4_detector SHARED dllmain.cpp
        detector.cpp
        detector.h
        utils.cpp
        utils.h
        class_loader.cpp
        class_loader.h)
