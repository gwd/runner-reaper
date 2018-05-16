/* 
 * runner.c: Rogue process that's hard to kill
 *
 * Copyright (C) 2018 Citrix Systems UK Ltd
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2 of the
 * License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

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

    /** At this point the process is untrusted **/
    
    while(1) {
        if(!fork())
            kill(-1, 9);
        else
            _exit(0);
    }
}
