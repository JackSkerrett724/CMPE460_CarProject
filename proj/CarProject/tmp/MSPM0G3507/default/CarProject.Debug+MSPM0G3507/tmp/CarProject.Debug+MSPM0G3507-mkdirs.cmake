# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507")
  file(MAKE_DIRECTORY "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507")
endif()
file(MAKE_DIRECTORY
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/1"
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507"
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/tmp"
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/src/CarProject.Debug+MSPM0G3507-stamp"
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/src"
  "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/src/CarProject.Debug+MSPM0G3507-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/src/CarProject.Debug+MSPM0G3507-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jackp/OneDrive/Documents/04_Fourth Year 2026-2027/Fall 2026/CMPE460 - Interface & Digital Electronics/Car Project/proj/CarProject/tmp/MSPM0G3507/default/CarProject.Debug+MSPM0G3507/src/CarProject.Debug+MSPM0G3507-stamp${cfgdir}") # cfgdir has leading slash
endif()
