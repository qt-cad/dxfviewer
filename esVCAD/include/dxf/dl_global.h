#ifndef DFXLIB_GLOBAL_H
#define DFXLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#       if defined(DXFLIB_LIBRARY)
#           define DXFLIB_EXPORT Q_DECL_EXPORT
#       else
#           define DXFLIB_EXPORT Q_DECL_IMPORT
#       endif

#endif // DFXLIB_GLOBAL_H




