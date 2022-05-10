add_executable(tests tests.cpp ../core/cpu.cpp ../core/memory.cpp ../core/decoder.cpp ../core/cpuRegister.cpp)
include_directories(${CMAKE_SOURCE_DIR}/core)


install(TARGETS tests RUNTIME DESTINATION bin)

