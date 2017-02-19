# - Find Edi-ide
# Find the Edi includes and library
# This module defines
#  EDI_INCLUDE_DIRS, where to find Edi.h, etc.
#  EDI_LIBRARIES, the libraries needed to use Edi.
#  EDI_FOUND, If false, do not try to use Edi.
# also defined, but not for general use are
#  EDI_LIBRARY, where to find the Edi library.

find_path(EDI_INCLUDE_DIRS Edi.h
  /opt/efler/include/edi-0/
  /opt/efler/include
  /usr/local/include/edi-0/
  /usr/local/include
  )

set(EDI_NAMES ${EDI_NAMES} edi)
find_library(EDI_LIBRARY
  NAMES ${EDI_NAMES}
  PATHS /opt/efler/lib /usr/local/lib
  )

if(EDI_LIBRARY AND EDI_INCLUDE_DIRS)
   set(EDI_LIBRARIES ${EDI_LIBRARY})
   set(EDI_FOUND "YES")
else(EDI_LIBRARY AND EDI_INCLUDE_DIRS)
   set(EDI_FOUND "NO")
endif(EDI_LIBRARY AND EDI_INCLUDE_DIRS)

if(EDI_FOUND)
   if(NOT EDI_FIND_QUIETLY)
      MESSAGE(STATUS "Found edi: ${EDI_LIBRARIES}")
   endif(NOT EDI_FIND_QUIETLY)
else(EDI_FOUND)
   if(EDI_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find edi library.")
   endif(EDI_FIND_REQUIRED)
endif(EDI_FOUND)
