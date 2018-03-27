#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "common.h"

int main(int argc, char * argv) {
    uid_t euid, tuid = DEFAULT_TARGET_UID, xuid = DEFAULT_REAPER_UID;
    int rc;

    /* Check to make sure we have enough permissions */
    euid = geteuid();

    if ( euid != 0 ) {
        fprintf(stderr, "Must run as euid 0 to set uid\n");
        return -1;
    }

    /* 
     * Set euid to TARGET_UID so that we can kill the 'runner'; but
     * set ruid to REAPER_UID so that the runner can't kill us.
     */
    if ( setresuid(xuid, tuid, 0) ) {
        perror("Setting uid to target");
        return -1;
    }

    printf("Sleeping for 1 second to get the runner a chance to kill me...\n");
    usleep(1000000);
    
    rc = kill(-1, 9);
    if ( rc )
        perror("No processes killed");
    else
        printf("At least one process killed successfully!\n");

    return 0;
}
