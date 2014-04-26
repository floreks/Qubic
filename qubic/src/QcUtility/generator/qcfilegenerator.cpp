#include "qcfilegenerator.h"

#include <QDir>
#include "qcheaderfile.h"
#include "qcsourcefile.h"

QcLogger* QcFileGenerator::logger;

void QcFileGenerator::generateHeaders(QString dirPath, QcSchema schema) {
    logger = QcLogger::getInstance();
    for(QcMetaTable table : schema.getSchema()) {
        QFile file(dirPath + QDir::separator() + table.getName().toLower() + ".h");
        if(file.open(QFile::ReadWrite)) {
            QTextStream in(&file);
            QcHeaderFile header(table.getName());
            header.setInherits("QbPersistable");
            header.addFunction(getConstructor(table,ConstructorType::Empty));
            header.addFunction(getConstructor(table,ConstructorType::WithID));
            header.addFunction(getConstructor(table,ConstructorType::WithoutID));
            header.addFunctions(getGetters(table));
            header.addFunctions(getSetters(table));

            header.addVariables(getVariables(table));
            header.addVariable(QcVariable("static bool","isRegistered",true));
            header.addVariable(QcVariable("static QString","CLASSNAME",true),false);
            header.addVariables(getQueryVariables(table),false);
            in << header;
        } else {
            logger->error("File named " + table.getName().toLower() + " could not be created.");
            return;
        }
        file.close();
    }
}

void QcFileGenerator::generateCPPs(QString dirPath, QcSchema schema) {
    logger = QcLogger::getInstance();
    for(QcMetaTable table : schema.getSchema()) {
        QFile file(dirPath + QDir::separator() + table.getName().toLower() + ".cpp");
        if(file.open(QFile::ReadWrite)) {
            QTextStream in(&file);
            QcSourceFile src(table.getName());
            src.addFunction(getConstructor(table,ConstructorType::Empty));
            src.addFunctions(getGetters(table));
            src.addFunctions(getSetters(table));

            in << src;
        } else {
            logger->error("File named " + table.getName().toLower() + " could not be created.");
            return;
        }
        file.close();
    }
}

// ========================== PRIVATE ========================== //

QcFunction QcFileGenerator::getConstructor(QcMetaTable &table, ConstructorType type) {
    QcFunction result(table.getName(),table.getName(),FunctionType::Constructor);
    result.setInvokable(true);
    for(QcMetaField *field : table.getFields()) {
        if(type == ConstructorType::Empty) {
            break;
        } else if(type == ConstructorType::WithoutID && (field->getName().compare("id",Qt::CaseInsensitive) == 0)) {
            continue;
        }

        result.addParameter(field->getType(),field->getName());
    }
    return result;
}

QList<QcFunction> QcFileGenerator::getGetters(QcMetaTable &table) {
    QList<QcFunction> result;
    for(QcMetaField *field : table.getFields()) {
        if(field->getName().compare("id",Qt::CaseInsensitive) == 0) {
            continue;
        }

        QcFunction func(field->getName(),table.getName(),FunctionType::Getter);
        func.setInvokable(true);

        if(field->isForeignKey()) {
            func.setName(field->getName()+"Ptr");
            func.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName());
        } else {
            func.addParameter(field->getType(),field->getName());
        }

        result.push_back(QcFunction(func));
    }
    return result;
}

QList<QcFunction> QcFileGenerator::getSetters(QcMetaTable &table) {
    QList<QcFunction> result;
    for(QcMetaField *field : table.getFields()) {
        if(field->getName().compare("id",Qt::CaseInsensitive) == 0) {
            continue;
        }

        QcFunction func(field->getName(),table.getName(),FunctionType::Setter);
        func.setInvokable(true);

        if(field->isForeignKey()) {
            func.setName(field->getName()+"Ptr");
            func.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName());
        } else {
            func.addParameter(field->getType(),field->getName());
        }

        result.push_back(QcFunction(func));
    }
    return result;
}

QList<QcVariable> QcFileGenerator::getVariables(QcMetaTable &table) {
    QList<QcVariable> result;
    for(QcMetaField *field : table.getFields()) {
        if(field->getName().compare("id",Qt::CaseInsensitive) == 0) {
            continue;
        }
        if(field->isForeignKey()) {
            result.push_back(QcVariable(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName()+"Ptr"));
        } else {
            result.push_back(QcVariable(field->getType(),field->getName()));
        }
    }
    return result;
}

QList<QcVariable> QcFileGenerator::getQueryVariables(QcMetaTable &table) {
    QList<QcVariable> result;
    for(QcMetaField *field : table.getFields()) {
        result.push_back(QcVariable("static QString", field->getName(),true));
    }
    return result;
}
