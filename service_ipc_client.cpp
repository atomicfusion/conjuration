#include <unistd.h>
#include <errno.h>
#include "sockets.h"
#include "service_ipc_client.h"

int conjuration_service_ipc_client(int flags, mode_t mode,int socket) {
	int err;
	int fd;
	
	if (write(socket,&flags,sizeof(flags)) < sizeof(flags)) {
		return -1;
	}
	if (write(socket,&mode,sizeof(mode)) < sizeof(mode)) {
		return -1;
	}
	fd = recv_fd(socket);
	if (fd < 0 && !err) {
		return -1;
	}
	if (read(socket,&err,sizeof(err)) < sizeof(err)) {
		return -1;
	}
	errno = err;
	if(err) {
		return -1;
	}
	return fd;
}