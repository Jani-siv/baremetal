add_executable(core main.cpp cpu.cpp)
install(TARGETS core
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

