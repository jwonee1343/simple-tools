#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <malloc.h>

#define FILE_SIZE(fd) \
	({ struct stat s; fstat(fd, &s) < 0 ? -1 : s.st_size; })

void
file_copy(int src, int cp, long offset)
{
	void *buf;
	size_t leftover;

	buf = malloc(offset);
	for (leftover = FILE_SIZE(src);
	     leftover >= offset; 
		 leftover = leftover - offset)
	{
		read(src, buf, offset);
		write(cp, buf, offset);
	}

	read(src, buf, leftover);
	write(cp, buf, leftover);

	free(buf);
}
