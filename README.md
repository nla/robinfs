robinfs
=======

A round-robin FUSE passthrough filesystem.  Based on [passfs](https://github.com/jrk/passfs)
but tweaked to support multiple roots.

Motivation
----------

Imagine you have 4 NFS servers sharing out the same clustered filesystem.  Due
to CPU or other resource limitations each NFS server can only serve out content at 2.5 Gbit/s.

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
    
    $ cd /robin; ls -l
    lrwxrwxrwx 1 root bin   64 Dec 16  2003 file1 -> /nfs4/file1
    lrwxrwxrwx 1 root bin   63 Dec 16  2003 file2 -> /nfs2/file2
    lrwxrwxrwx 1 root bin   64 Dec 16  2003 file3 -> /nfs3/file3
    lrwxrwxrwx 1 root bin   63 Dec 16  2003 file4 -> /nfs1/file4


If you want to expose the contents as regular files rather than symlinks use the -p flag.  This
will incur a significant CPU cost as all data must be copied back and forth to userspace.

Limitations
-----------

* Filesystems should have identical content
* Will not improve single-stream performance, each file handle is only associated with a single backend
* Writing might work but is untested, my use case is read-only
* Only tested under FUSE 2.9.2
* Mapping is not persistent (open a file multiple times and you'll get different backends), not great for caching
