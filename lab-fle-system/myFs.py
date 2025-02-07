#!/usr/bin/env python3
 
# 2110352 Operating System
# FUSE/Filesystem exercise
# By Krerk Piromsopa, Ph.D. <Krerk.P@chula.ac.th>
#    Department of Computer Engineering
#    Chulalongkorn University.

import os, stat, errno
from fuse import FUSE, Operations, FuseOSError

containers={ \
               '/subject':b"2021S2 - Operating Systems\nCP ENG CU\n" ,
               '/instructors':b"0:CP ENG CU OS 2018S1 - Instructors\n" \
b"1:      Krerk Piromsopa, Ph. D.\n" \
b"2:      Veera Muangsin, Ph.D.\n" \
b"3:      Thongchai Rojkangsadan\n"
       }

class MyStat(dict):
    def __init__(self):
        self.update(dict(st_mode=0, st_ino=0, st_dev=0, st_nlink=0,
                        st_uid=0, st_gid=0, st_size=0, st_atime=0,
                        st_mtime=0, st_ctime=0))

class MyFS(Operations):
    def getattr(self, path, fh=None):
        st = MyStat()
        if path == '/':
            st['st_mode'] = stat.S_IFDIR | 0o777
            st['st_nlink'] = 2
        elif path in containers:
            st['st_mode'] = stat.S_IFREG | 0o444
            st['st_nlink'] = 1
            content=containers[path]
            st['st_size'] = len(content)
        else:
            raise FuseOSError(errno.ENOENT)
        return st

    def readdir(self, path, fh):
        dirents = ['.', '..']
        if path == '/':
            dirents.extend(name[1:] for name in containers.keys())
        return dirents

    def open(self, path, flags):
        if path not in containers:
            raise FuseOSError(errno.ENOENT)
        accmode = os.O_RDONLY | os.O_WRONLY | os.O_RDWR
        if (flags & accmode) != os.O_RDONLY:
            raise FuseOSError(errno.EACCES)
        return 0

    def read(self, path, size, offset, fh):
        if path not in containers:
            raise FuseOSError(errno.ENOENT)

        content = containers[path]
        slen = len(content)
        if offset < slen:
            if offset + size > slen:
                size = slen - offset
            buf = content[offset:offset+size]
        else:
            buf = b''
        return buf

def main():
    FUSE(MyFS(), "mnt", nothreads=True, foreground=True)

if __name__ == '__main__':
    main()