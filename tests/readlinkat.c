#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int
main(void)
{
#ifdef __NR_readlinkat
	static const char fname[] = "readlinkat.link";
	unsigned char buf[31];
	long rc;
	unsigned int i;

	rc = syscall(__NR_readlinkat, -100, fname, buf, sizeof(buf));
	if (rc < 0)
		return 77;

	printf("readlinkat(AT_FDCWD, \"");
	for (i = 0; fname[i]; ++i)
		printf("\\x%02x", (int) (unsigned char) fname[i]);
	printf("\", \"");
	for (i = 0; i < 3; ++i)
		printf("\\x%02x", (int) buf[i]);
	printf("\"..., %zu) = %ld\n", sizeof(buf), rc);

	puts("+++ exited with 0 +++");
	return 0;
#else
	return 77;
#endif
}
