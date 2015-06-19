cmake_minimum_required(VERSION 3.0)

project(PONG
  VERSION 0.1.0
  LANGUAGES C CXX
)

include(GNUInstallDirs)

find_package(Threads)
find_package(Boost REQUIRED COMPONENTS filesystem system)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)

add_definitions(-Wall -g -O2)
add_definitions(-std=c++11)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(pong
  pong.cc
  # base
  game/Clock.cc
  game/Event.cc
  game/Log.cc
  # graphics
  game/Action.cc
  game/Camera.cc
  game/Control.cc
  game/Entity.cc
  game/EntityManager.cc
  game/WindowSettings.cc
  # local
  local/Ball.cc
  local/Ground.cc
  local/Paddle.cc
  local/Points.cc
  local/Singletons.cc
)

target_link_libraries(pong
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
)

install(
  TARGETS pong
  RUNTIME DESTINATION games
)
