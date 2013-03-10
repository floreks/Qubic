#ifndef QUBICONCOMPILER_H
#define QUBICONCOMPILER_H

#include <QObject>
#include <QSharedDataPointer>

class QubiconCompilerData;
class QubiconCompiler : public QObject{
public:
    QubiconCompiler();
    QubiconCompiler(const QubiconCompiler &);
    QubiconCompiler &operator=(const QubiconCompiler &);
    ~QubiconCompiler();
    
    static void registerQubicon(const QString &entity);

private:
    QSharedDataPointer<QubiconCompilerData> data;
};
#endif // QUBICONCOMPILER_H
