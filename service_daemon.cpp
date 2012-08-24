#include <unistd.h>
#include <sys/stat.h>
#include "sockets.h"
#include "diy.h"
#include "service_ipc_server.h"

//FIXME: IMPORTANT: Rewrite affluence sockets to support argument passing for accept_stream_socket.

bool accepting = true;

static int accept_server(const char *socket_path,int socket_backlog,conjuration_diy_tmp *tmp) {
	//FIXME: Fixup affluence sockets's return/error codes.
	int socket = create_local_stream_socket(socket_path,socket_backlog);
	if(socket < 0) {
		return -1;
	}
	
	while(accepting) {
		int connection;
		connection = accept(socket,NULL,NULL);
		if(connection < 0) {
			continue;
		}
		conjuration_service_ipc_server(tmp,connection);
		//FIXME: Check for too small buffer error return code from above?
		close(connection);
		//FIXME: Check for close errors?
	}
	close(socket);
	unlink(socket_path);
	return 0;
}
int main(int argc,char **argv) {
	if(argc != 3) {
		return 2;
	}
	
	char *socket_path;
	struct conjuration_diy_tmp tmp;
	
	socket_path = argv[1];
	tmp.location = open(argv[2],O_RDONLY);
	tmp.counter = 0;
	
	if(tmp.location < 0) {
		return 3;
	}
	
	if(accept_server(socket_path,10,&tmp)) {
		return 1;
	}
}