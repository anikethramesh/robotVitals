<<<<<<< HEAD:robotVitals/build/status_publisher/cmake_install.cmake
# Install script for directory: /home/aniketh/programming/robotVitals/robotVitals/src/status_publisher
=======
# Install script for directory: /home/aniketh/rv_ws/robotVitals/robotVitals/src/support_scripts
>>>>>>> b7c7b0bbf976791929962dda2e3f0ec41580ac0b:robotVitals/build/support_scripts/cmake_install.cmake

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

<<<<<<< HEAD:robotVitals/build/status_publisher/cmake_install.cmake
# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/aniketh/programming/robotVitals/robotVitals/build/status_publisher/catkin_generated/installspace/status_publisher.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/status_publisher/cmake" TYPE FILE FILES
    "/home/aniketh/programming/robotVitals/robotVitals/build/status_publisher/catkin_generated/installspace/status_publisherConfig.cmake"
    "/home/aniketh/programming/robotVitals/robotVitals/build/status_publisher/catkin_generated/installspace/status_publisherConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/status_publisher" TYPE FILE FILES "/home/aniketh/programming/robotVitals/robotVitals/src/status_publisher/package.xml")
=======
if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/aniketh/rv_ws/robotVitals/robotVitals/build/support_scripts/catkin_generated/installspace/support_scripts.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/support_scripts/cmake" TYPE FILE FILES
    "/home/aniketh/rv_ws/robotVitals/robotVitals/build/support_scripts/catkin_generated/installspace/support_scriptsConfig.cmake"
    "/home/aniketh/rv_ws/robotVitals/robotVitals/build/support_scripts/catkin_generated/installspace/support_scriptsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/support_scripts" TYPE FILE FILES "/home/aniketh/rv_ws/robotVitals/robotVitals/src/support_scripts/package.xml")
>>>>>>> b7c7b0bbf976791929962dda2e3f0ec41580ac0b:robotVitals/build/support_scripts/cmake_install.cmake
endif()

