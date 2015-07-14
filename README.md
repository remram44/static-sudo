sudo replacement as a static binary

What is this
------------

This is a simple C program that changes uid and gid to the ones provided on the
command-line before executing a command. It is meant to replace sudo where it
is overkill, and can be compiled to a very small static binary that will work
everywhere.

It accepts numeric uid and gid (like sudo, but unlike su).

Note that it doesn't do any authentication and is not meant to be set-uid; it
is only a wrapper intended to be run by root.

Why is this needed?
-------------------

This is needed by the [ReproZip](https://github.com/ViDA-NYU/reprozip) project.
The reprounzip component builds virtual machines and unpacks the files needed
to reproduce an experiment, which might mean overwriting system libraries; a
dynamically linked binary cannot be guaranteed to work after that. A static
build of Busybox can be used as the shell, but a helper to get the uid/gid
right is needed; this is it.

Reprounzip downloads the static binaries from this project's releases page:

    https://github.com/remram44/static-sudo/releases/download/current/rpzsudo-{arch}

where `{arch}` is one of: `i686`, `x86_64` (`uname -m`).
