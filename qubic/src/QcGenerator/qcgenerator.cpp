#include "qcgenerator.h"
#include "ui_qcgenerator.h"

#include <QMessageBox>
#include <QFileDialog>

#include "properties/qcproperties.h"
#include "properties/qcmappingproperties.h"
#include "properties/qcstaticproperties.h"
#include "properties/qcpropertiesvalidator.h"

#include "schema/qcschemagenerator.h"
#include "schema/qcschema.h"
#include "schema/qcschemavalidator.h"

#include "generator/qcfilegenerator.h"
#include "timer.h"
#include <QDebug>

QcGenerator::QcGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QcGenerator)
{
    ui->setupUi(this);

    // Connect signals & slots
    connect(ui->actionSetDBProperty,SIGNAL(triggered()),this,SLOT(loadDBProperty()));
    connect(ui->actionSetMappingProperty,SIGNAL(triggered()),this,SLOT(loadMappingProperty()));
    connect(ui->actionConnect,SIGNAL(triggered()),this,SLOT(connectToDB()));
    connect(ui->actionGenerate,SIGNAL(triggered()),this,SLOT(generate()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(QString)),SLOT(setLoggingLevel(QString)));
    connect(ui->actionSetRelations, SIGNAL(triggered()), this, SLOT(setUpRelations()));

    ui->actionConnect->setEnabled(false);
    ui->actionGenerate->setEnabled(false);

    QcLogger::addDestination(ui->logBrowser);
}

QcGenerator::~QcGenerator()
{
    if(db != NULL) {
        db->close();
        delete db;
    }
    delete ui;
    if(mapping != NULL)
        delete mapping;
    if(properties != NULL)
        delete properties;

}

// ===================== SLOTS ===================== //

void QcGenerator::setUpRelations() {
    schema = new QcSchema(QcSchemaGenerator::getSchema(mapping));

    relationWidget = new RelationWidget(this, schema);
    relationWidget->exec();
}

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

void QcGenerator::setLoggingLevel(QString level) {
    if(level.contains("info",Qt::CaseInsensitive)) {
        QcLogger::setLoggingLevel(QsLogging::Level::InfoLevel);
    } else if(level.contains("debug", Qt::CaseInsensitive)) {
        QcLogger::setLoggingLevel(QsLogging::Level::DebugLevel);
    }

    ui->logBrowser->clear();
}
