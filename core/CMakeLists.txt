file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(core ${SRC_FILES} ${HEADER_FILES})
target_include_directories(core PUBLIC include/)

add_executable(core_test 
test/test_vec2i.cc 
test/test_vec2f.cc 
test/test_queue.cc 
test/test_stack.cc 
test/test_fixed_queue.cc 
test/test_fixed_stack.cc
test/test_small_vector.cc
test/test_basic_vector.cc
test/test_fixed_vector.cc)

if(ENABLE_PROFILING)
    target_link_libraries(core PUBLIC Tracy::TracyClient)
    target_compile_definitions(core PUBLIC TRACY_ENABLE=1)
endif(ENABLE_PROFILING)

target_link_libraries(core_test PRIVATE core GTest::gtest GTest::gtest_main)