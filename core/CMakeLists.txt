add_executable(core main.cpp decoder.cpp cpu.cpp memory.cpp cpuRegister.cpp)
install(TARGETS core
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

