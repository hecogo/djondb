#!/bin/sh

## find packages
## dpkg -S 

# ldd ./djondb

# dpkg -S /bin/djondbd
# apt-cache showpkg libxss1
find debian -type d | xargs chmod 755

fakeroot dpkg-deb --build debian djondb.deb
lintian djondb.deb

