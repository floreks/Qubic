// ===================== SLOTS ===================== //

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

    ui->usernameEdit->setText(properties->getProperty("username"));
    ui->passwordEdit->setText(properties->getProperty("password"));

    ui->dbNameEdit->setText(properties->getProperty("database","name"));

    ui->dbHostEdit->setText(properties->getProperty("host","address"));
    ui->dbPortEdit->setText(properties->getProperty("host","port"));

    QMessageBox::information(this,"Validation successfull", "Properties and schema validated successfully.");
    ui->actionConnect->setEnabled(true);
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
}

void QcGenerator::generate() {
    QcSchema schema = QcSchemaGenerator::getSchema(mapping);

    if(!QcSchemaValidator::hasErrors()) {

        if(QcSchemaValidator::hasWarnings()) {
            QMessageBox::warning(this, "Warning", QcSchemaValidator::getWarnings());
        }

        QString dir = QFileDialog::getExistingDirectory(this,tr("Open directory"),"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        QcFileGenerator::generateHeaders(dir,schema);
        QcFileGenerator::generateCPPs(dir,schema);

        QMessageBox::information(this,"Generation","Generating completed.");
    } else {
        QMessageBox::critical(this,"Error",QcSchemaValidator::getErrors());
    }

}
