add_library(conjuration SHARED service.cpp service_ipc_client.cpp sockets.cpp)

add_executable(conjuration_daemon service_daemon.cpp service_ipc_server.cpp diy.cpp sockets.cpp)

add_executable(conjuration_test test.cpp)
target_link_libraries(conjuration_test
	conjuration
)

install(TARGETS conjuration DESTINATION lib)
install(FILES conjuration.h DESTINATION include)

install(TARGETS conjuration_daemon DESTINATION sbin)

##FIXME: Clean this up. Should it exist at all? As a different package?
install(TARGETS conjuration_test DESTINATION bin)