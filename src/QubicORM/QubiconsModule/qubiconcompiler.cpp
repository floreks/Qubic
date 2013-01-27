#include "qubiconcompiler.h"
#include <QSharedData>
#include <QHash>
#include "QubeModule/model/qubemodel.h"

void QubiconCompiler::registerQubicon(const QString &entity);

class QubiconCompilerData : public QSharedData {
public:
    QHash<QString,QPointer<QubeModel> > qubes;
};

QubiconCompiler::QubiconCompiler() : data(new QubiconCompilerData){
}

QubiconCompiler::QubiconCompiler(const QubiconCompiler &rhs) : data(rhs.data){
}

QubiconCompiler &QubiconCompiler::operator=(const QubiconCompiler &rhs){
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QubiconCompiler::~QubiconCompiler(){
}

void QubiconCompiler::registerQubicon(const QString &entity){
    this->data.data()->qubes.insert(entity, new SomeModel());
}
