#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int get_host_bits(int n) {
    int host_bits = 0;
    
    for (int b = 0; b < 8; b++) {
        if ((n & (1 << (7 - b))) == 0)
            host_bits++;
    }
  
    return host_bits;
}

uint32_t hosts_in_subnet(const char* netmask) {    
    char* copy = strdup(netmask);
    char* tok = strtok(copy, ".");
    
    int n, i = 0, host_bits = 0;
  
    while (tok != NULL && i < 4) {
        n = atoi(tok); 
        host_bits += get_host_bits(n);    
        tok = strtok(NULL, ".");
        i++;
    }
  
    free(copy);
    if (host_bits == 1) {
        // /31 networks have 2 usable hosts
        return 2;
    }
    if (host_bits <= 0) return 1;
  return (1U << host_bits) - 2;
}

int main() {
    char* netmask = "128.69.200.0";
    uint32_t hosts = hosts_in_subnet(netmask);
    printf("%d\n", hosts);
}