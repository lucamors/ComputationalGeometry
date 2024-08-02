find_package(GTest REQUIRED)
find_package(GEOS CONFIG REQUIRED)

# Include GEOS headers
include_directories(${GEOS_INCLUDE_DIRS})

add_executable(ConvexHull_test ConvexHull_test.cc)

target_link_libraries(ConvexHull_test
  PRIVATE
  GTest::GTest
  GEOS::geos
  cglib)


add_test(ConvexHullTest ConvexHull_test)
