#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(HunapuSim)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
#include(${ROOT_USE_FILE})
#include($ENV{ROOTSYS}/share/root/cmake/modules/RootNewMacros.cmake)

cmake_policy(SET CMP0042 NEW)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include/WCDtank
                    ${PROJECT_SOURCE_DIR}/include/electronics
                    ${PROJECT_SOURCE_DIR}/include/cla
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR}
                   )
file(GLOB W_sources ${PROJECT_SOURCE_DIR}/src/WCDtank/*.cc)
file(GLOB W_headers ${PROJECT_SOURCE_DIR}/include/WCDtank/*.hh)
file(GLOB e_sources ${PROJECT_SOURCE_DIR}/src/electronics/*.cc)
file(GLOB e_headers ${PROJECT_SOURCE_DIR}/include/electronics/*.hh)
file(GLOB c_sources ${PROJECT_SOURCE_DIR}/src/cla/*.cc)
file(GLOB c_headers ${PROJECT_SOURCE_DIR}/include/cla/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_library( cla SHARED ${c_sources} ${c_headers} )
target_compile_options(cla PRIVATE -std=c++11)

add_executable(WCDtankSim WCDtank.cc ${W_sources} ${W_headers})
target_link_libraries(WCDtankSim ${Geant4_LIBRARIES} )

add_executable(ElecSim electronics.cc ${e_sources} ${e_headers})
target_link_libraries(ElecSim cla ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build RE02. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(WCDtank_SCRIPTS
    vis.mac
    muon.mac
    muon-vert.mac
    muon-nonvert.mac
    pulses.C
  )

foreach(_script ${WCDtank_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
