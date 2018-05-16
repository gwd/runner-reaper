This is a pair of programs to demonstrate how to kill an uncooperative
process.

# Quick-start

1. You probably want to run this in a VM in case something goes terribly wrong

2. Compile:

    make

This will generate two binaries, `runner` (the process trying to avoid
being killed) and `reaper` (the process which is to kill it).

3. Start the runner

    ./runner

This will execute the following loop:

```
    while(1) {
        if(!fork())
            kill(-1, 9);
        else
            _exit(0);
    }
```

4. Try to kill it with the normal tools

`ps`, pipe, `killall` -- all may _probabilistically_ kill it, but
that's not very satisfactory, is it?

5. Kill it with the reaper

    ./reaper

To demonstrate its invulnerability, it waits 1 second before killing
`runner`, giving it every chance to lose a race.
