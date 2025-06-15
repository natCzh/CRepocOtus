#ifndef LOGGER_GLOBAL_H
#define LOGGER_GLOBAL_H

#include <QtCore/qglobal.h>

//#ifdef WIN32
# ifdef LOGGER_BUILD_SHARED
#if defined(LOGGER_LIBRARY)
#  define LOGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LOGGERSHARED_EXPORT Q_DECL_IMPORT
#endif
# else
# define LOGGERSHARED_EXPORT
# endif
/*#else
# if __GNUC__ >= 4
# define LOGGERSHARED_EXPORT __attribute__ ((visibility ("default")))
# else
# define LOGGERSHARED_EXPORT
# endif
#endif*/

#endif // LOGGER_GLOBAL_H
