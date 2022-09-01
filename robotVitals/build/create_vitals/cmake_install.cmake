# Install script for directory: /home/aniketh/programming/robotVitals/robotVitals/src/create_vitals

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/aniketh/programming/robotVitals/robotVitals/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/create_vitals.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/create_vitals/cmake" TYPE FILE FILES
    "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/create_vitalsConfig.cmake"
    "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/create_vitalsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/create_vitals" TYPE FILE FILES "/home/aniketh/programming/robotVitals/robotVitals/src/create_vitals/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/magDist_odom.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/magDist_odom_differentiator.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/odomPosErr_differentiator.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/linAcc_differentiator.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/magROC_event_detection.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/velocity_from_odomMag_differentiator.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/velocity_from_odom_event_detection.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/odomPosErr_event_detection.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/probabilityOfSuffering.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/create_vitals" TYPE PROGRAM FILES "/home/aniketh/programming/robotVitals/robotVitals/build/create_vitals/catkin_generated/installspace/healthAndSuffering.py")
endif()

