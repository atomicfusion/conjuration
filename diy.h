#ifndef AFFLUENCE_CONJURATION_DIY_H_
#define AFFLUENCE_CONJURATION_DIY_H_

#include <fcntl.h>

struct conjuration_diy_tmp {
	int counter;
	int location;
};

int conjuration_diy(int flags, mode_t mode,uid_t uid,gid_t gid,conjuration_diy_tmp *tmp);

#endif /* AFFLUENCE_CONJURATION_DIY_H_ */