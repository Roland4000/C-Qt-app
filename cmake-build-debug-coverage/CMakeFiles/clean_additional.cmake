# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Qtie_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Qtie_autogen.dir\\ParseCache.txt"
  "Qtie_autogen"
  )
endif()
