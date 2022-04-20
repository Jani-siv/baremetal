add_executable(tests tests.cpp ../core/cpu.cpp ../core/memory.cpp)
include_directories(${CMAKE_SOURCE_DIR}/core)


install(TARGETS tests RUNTIME DESTINATION bin)

