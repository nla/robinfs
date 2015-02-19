robinfs
=======

A round-robin FUSE passthrough filesystem.  Based on [https://github.com/jrk/passfs][passfs]
but tweaked to support multiple roots.

Use case
--------

Imagine you have 4 NFS servers sharing out the same clustered filesystem.  Due
to CPU limitations each NFS server can only serve out content at 2.5 Gbit/s.

There's a multi-threaded client application which wants to read from the NFS
filesystem at 10 Gbit/s.  You can mount up each NFS server under four different
mount points but then how do you get the application to read from all of them
at once without modifying it?

Usage
-----

    $ ./make.sh
    $ mkdir /robin /nfs1 /nfs2 /nfs3 /nfs4
    $ mount -o ro nfs-server-1:/shared /nfs1
    $ mount -o ro nfs-server-2:/shared /nfs2
    $ mount -o ro nfs-server-3:/shared /nfs3
    $ mount -o ro nfs-server-4:/shared /nfs4
    $ ./robinfs /robin /nfs1 /nfs2 /nfs3 /nfs4

Limitations
-----------

* Filesystems should have identical content
* Will not improve single-stream performance, each file handle is only associated with a single backend
* Writing might work but is untested, my use case is read-only
