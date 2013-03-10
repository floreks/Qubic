#ifndef QUBICONS_H
#define QUBICONS_H

#include "qubicon.h"
#include "qubiconcompiler.h"

#ifndef Qubicon
#   define Qubicon(entity) Q_OBJECT \
    QubiconCompiler::registerQubicon(entity);
#endif

#ifndef QCColumn
#   define QCColumn(name, column, flags)
#endif

#ifndef QCId
#   define QCId(type, qcIdGenerator)
#endif

#ifndef QcOneToOne
#   define QcOneToOne
#endif

#ifndef QcOneToMany
#   define QcOneToMany
#endif

#ifndef QcManyToMany
#   define QcManyToMany
#endif

#endif // QUBICONS_H
