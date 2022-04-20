add_executable(core main.cpp cpu.cpp memory.cpp)
install(TARGETS core
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

