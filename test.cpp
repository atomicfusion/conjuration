#include <unistd.h>
#include <fcntl.h>
#include "conjuration.h"

int main(int argc,char **argv) {
	if(argc<2) {
		return 1;
	}
	int fd = conjure(O_RDONLY,0700);
	if(fd < 0) {
		return 2;
	}
	if(fchdir(fd)) {
		return 3;
	}
	execvp(argv[1],argv+1);
	return 4;
}