#include <stdio.h>
#include <stdlib.h>

void assembly(void)
{
    __asm__ ( "msg db \"Hello, World\", 0x0a"
               "len equ $ - msg"
               "mov eax, 4"
               "mov ebx, 1"
               "mov ecx, msg"
               "mov edx, len"
               "int 0x80"
    );
}


int main(void)
{
    assembly();
}