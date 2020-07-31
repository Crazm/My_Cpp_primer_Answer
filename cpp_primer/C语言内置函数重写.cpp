#include <stdio.h>
#include <string.h>

void * Memcpy(void *dst, const void *src, unsigned len) {
	if (dst == NULL || src == NULL)
		return NULL;
	unsigned char * pdst = (unsigned char *)dst;
	unsigned char * psrc = (unsigned char *)src;
	if ( pdst >= psrc && psrc + len > pdst ) 
		return NULL;
	if( pdst < psrc && pdst + len > psrc)
		return NULL;
	while (len--)
		*pdst++ = *psrc++;
	return dst;
}

char * Strcpy(char *dst, const char *src) {
	if (dst == NULL || src == NULL)
		return NULL;
	unsigned char * address = (unsigned char *)dst;
	while(*src)
		*dst++ = *src++;
	return dst;
}

int main() {
	char src[10] = "abcdefghi";
	char dst[10] = "ABCDEFGHI";
	//char* res = (char*) Memcpy(dst, src, 10);
	char* res = Strcpy(src, 0);
	printf("res = %p\n", res);
	int i;
	for (i = 0; i < 9; ++i)
		printf("%c ", dst[i]);
	for (i = 0; i < 9; ++i)
		printf("%c ", src[i]);
	return 0;
}