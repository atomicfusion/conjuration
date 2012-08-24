#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include "sockets.h"
#include "diy.h"
#include "service_ipc_server.h"

int conjuration_service_ipc_server(conjuration_diy_tmp *tmp,int socket) {
	int fd;
	int err = 0;
	int flags;
	mode_t mode;
	ucred creds;
	
	get_local_socket_credentials(socket,&creds);
	
	if(read(socket,&flags,sizeof(flags)) != sizeof(flags) && !err) {
		err = errno;
	}
	if(read(socket,&mode,sizeof(mode)) != sizeof(mode) && !err) {
		err = errno;
	}
	
	fd = conjuration_diy(flags,mode,creds.uid,creds.gid,tmp);
	if(fd < 0) {
		err = errno;
	}
	
	if(send_fd(socket,fd) < 0 && !err) {
		err = errno;
	}
	if(write(socket,&err,sizeof(err)) != sizeof(err) && !err) {
		err = errno;
	}
	if(fd > 0) {
		close(fd);
	}
	return err;
}