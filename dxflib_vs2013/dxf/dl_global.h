#ifndef DFXLIB_GLOBAL_H
#define DFXLIB_GLOBAL_H

#ifdef DXF_EXPORTS
#define DXF_API __declspec(dllexport)
#else
#define DXF_API __declspec(dllimport)
#endif

#define  DXFLIB_EXPORT  DXF_API
#endif // DFXLIB_GLOBAL_H




