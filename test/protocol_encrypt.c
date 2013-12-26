#include <stdio.h>
#include "protocol.h"
#include "testhelper.h"

int main() 
{
    PtlHeader header;
    char *str = "Hello World!";
    Buffer buf;

    header.from = "1";
    header.to = "2";
    protocol_init(&header);
    protocol_set_key(&header, "user", "pwd");
    printf("The key:\n");
    printHex(header.key, 16);
    printf("The dist:\n");
    printHex(header.dist, 20);
    
    buffer_init(&buf);
    buffer_update(&buf, str, strlen(str));
    printf("Before encrypt:\n");
    printHex(buf.buffer, buf.pos);

    protocol_encrypt_string(&buf, &header);

    printf("Encrypted data:\n");
    printHex(buf.buffer, buf.pos);
    buffer_free(&buf);

    return 0;
}
