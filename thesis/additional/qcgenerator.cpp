void QcGenerator::loadDBProperty() {
    QFileInfo propertyFile(QC_PROPERTIES_DIR + QDir::separator() + QC_PROPERTIES_FILE);
    if(!propertyFile.exists()) {
        QMessageBox::critical(this,"Property load error","Could not find " + QString(QC_PROPERTIES_FILE) + " in resources folder.");
        ui->actionConnect->setEnabled(false);
        return;
    }

    properties = new QcProperties();

    if(!QcPropertiesValidator::validate(properties)) {
        QMessageBox::critical(this,"Property validation error", "Validation of " + QString(QC_PROPERTIES_FILE) + " failed.");
        ui->actionConnect->setEnabled(false);
        return;
    }

...

}

void QcGenerator::loadMappingProperty() {
    QFileInfo mappingFile(QC_PROPERTIES_DIR + QDir::separator() + QC_MAPPING_FILE);
    if(!mappingFile.exists()) {
        QMessageBox::critical(this,"Property load error","Could not find " + QString(QC_MAPPING_FILE) + " in resources folder.");
        ui->actionGenerate->setEnabled(false);
        return;
    }

    mapping = new QcMappingProperties();

    if(!QcPropertiesValidator::validate(mapping)) {
        QMessageBox::critical(this,"Mapping validation error", "Validation of " + QString(QC_PROPERTIES_FILE) + " failed.");
        ui->actionGenerate->setEnabled(false);
        return;
    }

    QMessageBox::information(this,"Validation successfull", "Mapping and schema validated successfully.");
    ui->actionGenerate->setEnabled(true);
}

void QcGenerator::connectToDB() {
    db = QcDatabase::getInstance(properties);
    if(!db->open()) {
        QMessageBox::critical(this,"Database error","Could not connect to database.");
        return;
    }

    QMessageBox::information(this,"Database","Successfully connected to database.");
    ui->actionSetRelations->setEnabled(true);
}

void QcGenerator::generate() {
    if(schema == NULL) {
        schema = new QcSchema(QcSchemaGenerator::getSchema(mapping));
        for(QcMetaTable &table : schema->getSchema()) {
            if(table.getRelationType() == RelationType::ManyToMany) {
                table.setRelationType(RelationType::None);
            }
        }
    }

    if(!QcSchemaValidator::hasErrors()) {

        if(QcSchemaValidator::hasWarnings()) {
            QMessageBox::warning(this, "Warning", QcSchemaValidator::getWarnings());
        }

        QString dir = QFileDialog::getExistingDirectory(this,tr("Open directory"),"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(dir == NULL) {
            QMessageBox::critical(this,"Error", "Cancel clicked. Aborting.");
            return;
        }

        QcFileGenerator::generateProject(dir, *schema);

        QMessageBox::information(this,"Generation","Generating completed.");
    } else {
        QMessageBox::critical(this,"Error",QcSchemaValidator::getErrors());
    }

}
