#include <stdio.h>
#include <malloc.h>

size_t fstream_size(FILE *fp)
{
	size_t size;
	long back;

	back = ftell(fp);

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, back);

   	return size;
}

void fstream_copy(FILE *src, FILE *cp, long offset)
{
	void *buf;
	size_t leftover;

	buf = malloc(offset);
	for (leftover = fstream_size(src);
	     leftover >= offset;
	     leftover = leftover - offset) {
		fread(buf, offset, 1, src);
		fwrite(buf, offset, 1, cp);
	}
	fread(buf, leftover, 1, src);
	fwrite(buf, leftover, 1, cp);

	free(buf);
}
