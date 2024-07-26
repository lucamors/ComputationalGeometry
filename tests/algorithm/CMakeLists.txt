find_package(GTest REQUIRED)

add_executable(ConvexHull_test ConvexHull_test.cc)

target_link_libraries(ConvexHull_test
  PRIVATE
  GTest::GTest
  cglib)

add_test(AlgorithmTest ConvexHull_test)
