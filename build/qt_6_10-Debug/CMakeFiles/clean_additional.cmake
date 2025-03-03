# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WMS-integrator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WMS-integrator_autogen.dir\\ParseCache.txt"
  "WMS-integrator_autogen"
  )
endif()
