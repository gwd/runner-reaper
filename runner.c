#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "common.h"

int main(int argc, char * argv) {
    uid_t euid, tuid = DEFAULT_TARGET_UID;

    /* Check to make sure we have enough permissions */
    euid = geteuid();

    if ( euid != 0 ) {
        fprintf(stderr, "Must run as euid 0 to set uid\n");
        return -1;
    }

    if(setuid(tuid)) {
        perror("Setting uid to target");
        return -1;
    }

    while(1) {
        if(!fork())
            kill(-1, 9);
        else
            _exit(0);
    }
}
