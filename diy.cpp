#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "diy.h"

int conjuration_diy(int flags, mode_t mode,uid_t uid,gid_t gid,conjuration_diy_tmp *tmp) {
	int fd;
	char* name;
	/*while(true) {
		asprintf(&name,"%d",tmp->counter);
		tmp->counter++;
		if(mkdirat(tmp->location,name,mode)) {
			free(name);
			switch(errno) {
				case EEXIST:
					continue;
				default:
					return -1;
			}
		}
		break;
	}*/
	asprintf(&name,"%d",tmp->counter);
	tmp->counter++;
	if(mkdirat(tmp->location,name,mode)) {
		free(name);
		return -1;
	}
	fd = openat(tmp->location,name,flags);
	free(name);
	if(fd < 0) {
		return -1;
	}
	if(fchown(fd,uid,gid)) {
		close(fd);
		return -1;
	}
	return fd;
}