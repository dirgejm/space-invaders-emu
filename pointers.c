#include <stdio.h>

int main() {
    // 4 bytes, each char is 8 bits
    const char *p = "abc";
    
    assert(*p == 'a');
}