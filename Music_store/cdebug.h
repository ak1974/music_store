#ifndef CDEBUG_H
#define CDEBUG_H

#include <QDebug>

#ifndef __FUNC__
#ifdef _MSC_VER
#define __FUNC__ __FUNCTION__
#else 
#define __FUNC__ __PRETTY_FUNCTION__
#endif
#endif

#ifndef VAR
#define VAR(x) # x << (x)
#endif

#ifndef CDEBUG
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define CDEBUG qInfo() << __FUNC__ << __LINE__
#else
#define CDEBUG qDebug() << __FUNC__ << __LINE__
#endif
#endif

#ifndef CWARNING
#define CWARNING qWarning() << __FUNC__ << __LINE__
#endif


#endif