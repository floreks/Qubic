void QcFileGenerator::generateProject(QString dirPath, QcSchema schema) {
    Q_INIT_RESOURCE(qresource);
    QString outPath = dirPath + QDir::separator() + PROJECT_FOLDER_NAME;
    QDir outDir(outPath);
    if(!outDir.exists()) {
        outDir.mkpath(".");
    }

    copyResources(":/files", outPath);

    outDir = QDir(outPath + QDir::separator() + "Generated");
    if(!outDir.exists()) {
        outDir.mkpath(".");
    }

    generateHeaders(outDir.path(), schema);
    generateCPPs(outDir.path(), schema);
    generatePRI(outDir.path(), schema);
}

// ========================== PRIVATE ========================== //

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
            header.addFunction(getConstructor(table,ConstructorType::Copy));
            header.addFunctions(getGetters(table));
            header.addFunctions(getSetters(table));
            header.addFunctions(getFKSetters(table),true);
            header.addFunction(getPointerFunction(table));
            if(table.getRelationType() != RelationType::None) {
                header.addFunction(getRelationFunction(table));
            }

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
            QString className = table.getName().replace(0,1,table.getName()[0].toUpper());
            src.addVariables(getCPPQueryVariables(table));
            src.addVariable(QcVariable("QString " + className + "::", "CLASSNAME = \"" + className + "\"",true));
            src.addVariable(QcVariable("bool " + className + "::", "isRegistered = false",true));

            src.addFunction(getConstructor(table,ConstructorType::Empty));
            src.addFunction(getConstructor(table,ConstructorType::WithID));
            src.addFunction(getConstructor(table,ConstructorType::WithoutID));
            src.addFunction(getConstructor(table,ConstructorType::Copy));
            src.addFunctions(getGetters(table));
            src.addFunctions(getSetters(table));
            src.addFunctions(getFKSetters(table));
            src.addFunction(getPointerFunction(table));
            if(table.getRelationType() != RelationType::None) {
                src.addFunction(getRelationFunction(table));
            }

            in << src;
        } else {
            logger->error("File named " + table.getName().toLower() + " could not be created.");
            return;
        }
        file.close();
    }
}

QcFunction QcFileGenerator::getConstructor(QcMetaTable &table, ConstructorType type) {
    QcFunction result(table.getName(),table.getName(),FunctionType::Constructor);
    result.setInvokable(true);
    for(QcMetaField *field : table.getFields()) {
        if(type == ConstructorType::Empty || type == ConstructorType::Copy) {
            break;
        } else if(type == ConstructorType::WithoutID && (field->getName().compare("id",Qt::CaseInsensitive) == 0)) {
            continue;
        }

        if(field->isForeignKey()) {
            result.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName()+"Ptr");
        } else {
            result.addParameter(field->getType(), field->getName());
        }
    }

    if(type == ConstructorType::Copy) {
        result = QcFunction(table.getName(),table.getName(),FunctionType::CopyConstructor);
        result.setInvokable(true);
        for(QcMetaField *field : table.getFields()) {
            if(field->isForeignKey()) {
                result.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName()+"Ptr");
            } else {
                result.addParameter(field->getType(), field->getName());
            }
        }
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
            func.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName()+"Ptr");
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
            func.addParameter(field->getType().replace(0,1,field->getType()[0].toUpper())+"*",field->getName() + "Ptr");
        } else {
            func.addParameter(field->getType(),field->getName());
        }

        result.push_back(QcFunction(func));
    }
    return result;
}

QList<QcFunction> QcFileGenerator::getFKSetters(QcMetaTable &table) {
    QList<QcFunction> result;
    for(QcMetaField *field : table.getFields()) {
        if(field->isForeignKey()) {
            QcFunction func(field->getName(), table.getName(),FunctionType::Setter);
            func.setInvokable(true);
            func.setName(field->getName()+"Ptr");
            func.addParameter("QbPersistable*",field->getName() + "Ptr");
            QString body = "this->" + field->getName().toLower() + "ptr=(" + field->getType().replace(0,1,field->getType()[0].toUpper())+"*) " + field->getName().toLower() + "ptr;";
            func.setBody(body);
            result.push_back(QcFunction(func));
        }
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
        result.push_back(QcVariable("static QString", field->getName().toUpper(),true));
    }
    return result;
}

QList<QcVariable> QcFileGenerator::getCPPQueryVariables(QcMetaTable &table) {
    QList<QcVariable> result;
    for(QcMetaField *field : table.getFields()) {
        result.push_back(QcVariable("QString " + table.getName().replace(0,1,table.getName()[0].toUpper()) + "::", field->getName().toUpper() + " = \"" + field->getName() + "\"",true));
    }
    return result;
}

QcFunction QcFileGenerator::getPointerFunction(QcMetaTable &table) {
    QcFunction func(table.getName(),table.getName(),FunctionType::Pointer);
    QString body = "\treturn QList<QbPersistable*>()";
    for(QcFunction func : getFKSetters(table)) {
        body.append(" << " + func.getParameterAt(0).getName());
    }
    body.append(";");
    func.setBody(body);
    return func;
}

QcFunction QcFileGenerator::getRelationFunction(QcMetaTable &table) {
    logger = QcLogger::getInstance();
    QcFunction func(table.getRelatedTable()->getName(),table.getName());

    if(table.getRelationType() == RelationType::OneToMany) {
        logger->debug("File generator - building One To Many relation function");
        func.setType(FunctionType::OTM);
    } else {
        logger->debug("File generator - building Many To Many relation function");
        func.setType(FunctionType::MTM);
        func.addParameter("",table.getJointTable()->getName());
    }

    return func;
}
