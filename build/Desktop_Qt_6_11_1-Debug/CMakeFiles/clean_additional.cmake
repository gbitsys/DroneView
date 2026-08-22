# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DroneView_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DroneView_autogen.dir/ParseCache.txt"
  "DroneView_autogen"
  )
endif()
