/* rpzsudo.c
 *
 * This is a very small binary meant to be statically linked and used in VMs by
 * reprounzip. It allows to switch to any uid/gid by number instead of name,
 * and doesn't require any other dependency (such as libc).
 */

#define _GNU_SOURCE
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

uid_t parse(char *arg)
{
    if(arg[0] == '#')
    {
        char *endptr;
        uid_t ret = strtol(arg + 1, &endptr, 10);
        if(endptr - arg - 1 > 0 && *endptr == '\0')
            return ret;
        else
        {
            fprintf(stderr, "Invalid id\n");
            exit(1);
        }
    }
    else if(arg[0] == '\0')
    {
        fprintf(stderr, "Empty id\n");
        exit(1);
    }
    else
    {
        fprintf(stderr, "Only numeric ids, prefixed with #, are supported\n");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    uid_t user, group;
    if(argc < 5)
    {
        fprintf(stderr,
                "Usage: rpzsudo <user> <group> <cmd> <arg0> [arg1 [...]]\n"
                "Where user and group are numbers preceded with #\n"
                "NOTE that this takes both cmd, the filename to execute, and "
                "arg0 (usually set\nto the same string)\n");
        exit(1);
    }
    else
    {
        user = parse(argv[1]);
        group = parse(argv[2]);
    }

    if(setgroups(0, &group) != 0)
    {
        perror("couldn't set group list");
        exit(1);
    }
    if(setregid(group, group) != 0)
    {
        perror("couldn't set gid");
        exit(1);
    }
    if(setreuid(user, user) != 0)
    {
        perror("couldn't set uid");
        exit(1);
    }

    if(execv(argv[3], argv + 4) == -1)
        perror("Error: exec failed");
    else
        fprintf(stderr, "Error: exec returned\n");

    return 1;
}
