prefix=@prefix@
exec_prefix=${prefix}
libdir=${prefix}/@LIBRARY_INSTALL_PATH@
includedir=${prefix}/@INCLUDE_INSTALL_PATH@

Name: maxflow
Description: A library implementing the max-flow/min-cut algorithm 
Version: @PACKAGE_VERSION@
Conflicts:
Libs: -lmaxflow  -L${prefix}/@LIBRARY_INSTALL_PATH@
Cflags: -I${prefix}/@INCLUDE_INSTALL_PATH@
