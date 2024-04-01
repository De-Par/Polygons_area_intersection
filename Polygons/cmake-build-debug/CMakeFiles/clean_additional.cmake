# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Polygons_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Polygons_autogen.dir/ParseCache.txt"
  "Polygons_autogen"
  )
endif()
