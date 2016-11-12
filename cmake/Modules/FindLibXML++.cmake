# - Try to find LibXML++ 3.0
# Once done, this will define
#
#  LibXML++_FOUND - system has LibXML++
#  LibXML++_INCLUDE_DIRS - the LibXML++ include directories
#  LibXML++_LIBRARIES - link these to use LibXML++

include(LibFindMacros)

# Dependencies
libfind_package(LibXML++ LibXML2)
libfind_package(LibXML++ Glibmm)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(LibXML++_PKGCONF libxml++-3.0)

# Main include dir
find_path(LibXML++_INCLUDE_DIR
        NAMES libxml++/libxml++.h
        HINTS ${LibXML++_PKGCONF_INCLUDE_DIRS}
        PATH_SUFFIXES libxml++-3.0
        )

# Glib-related libraries also use a separate config header, which is in lib dir
find_path(LibXML++Config_INCLUDE_DIR
        NAMES libxml++config.h
        HINTS ${LibXML++_PKGCONF_INCLUDE_DIRS} /usr
        PATH_SUFFIXES lib/libxml++-3.0/include ../lib/libxml++-3.0/include
        )

# Finally the library itself
find_library(LibXML++_LIBRARY
        NAMES xml++-3.0
        HINTS ${LibXML++_PKGCONF_LIBRARY_DIRS}
        )

set(LibXML++_PROCESS_INCLUDES LibXML++Config_INCLUDE_DIR)
libfind_process(LibXML++)

