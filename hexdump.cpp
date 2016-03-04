#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
static void hexdump(const void *_data, size_t size) {
    const uint8_t *data = (const uint8_t *)_data;
    size_t offset = 0;
    while (offset < size) {
        printf("%02lX  ", offset);
        size_t n = size - offset;
        if (n > 16) {
            n = 16;
        }

        for (size_t i = 0; i < 16; ++i) {
            if (i == 8) {
                printf(" ");
            }

            if (offset + i < size) {
                printf("%0X ", data[offset + i]);  
            } else {
                printf("   "); 
            }
        }
        printf(" ");

        for (size_t i = 0; i < n; ++i) {
            //if (isprint(data[offset + i])) {
            if (1) {
                printf("%c", data[offset + i]);
            } else {
                printf(".");
            }
        }
        printf("\n");
        offset += 16;
    }
}

int main()
{
	char str[] = "woshiyangzhijia我是羊指甲";
	hexdump(str,strlen(str));
	return 0;	

}
