#include "relationwidget.h"
#include "ui_relationwidget.h"

#include <QGroupBox>

RelationWidget::RelationWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelationWidget)
{
    ui->setupUi(this);
}

RelationWidget::RelationWidget(QWidget *parent, QcSchema *schema) :
    QDialog(parent),
    ui(new Ui::RelationWidget)
{
    ui->setupUi(this);

    connect(ui->actionSave,SIGNAL(clicked()),this,SLOT(saveClicked()));
    connect(ui->actionCancel,SIGNAL(clicked()),this,SLOT(cancelClicked()));

    this->schema = schema;
    setRelations();
}

RelationWidget::~RelationWidget()
{
    delete ui;
}

void RelationWidget::addRelation(QString leftSide, QString center, QString rightSide) {
    QGroupBox *groupBox = new QGroupBox(ui->widget);
    QHBoxLayout *vbox = new QHBoxLayout();

    QComboBox *leftBox = new QComboBox(groupBox);
    QComboBox *centerBox = new QComboBox(groupBox);
    QComboBox *rightBox = new QComboBox(groupBox);

    connect(leftBox,SIGNAL(currentIndexChanged(int)),centerBox,SLOT(setCurrentIndex(int)));
    connect(leftBox,SIGNAL(currentIndexChanged(int)),rightBox,SLOT(setCurrentIndex(int)));
    connect(centerBox,SIGNAL(currentIndexChanged(int)),leftBox,SLOT(setCurrentIndex(int)));
    connect(centerBox,SIGNAL(currentIndexChanged(int)),rightBox,SLOT(setCurrentIndex(int)));
    connect(rightBox,SIGNAL(currentIndexChanged(int)),leftBox,SLOT(setCurrentIndex(int)));
    connect(rightBox,SIGNAL(currentIndexChanged(int)),centerBox,SLOT(setCurrentIndex(int)));

    leftBox->addItem("");
    leftBox->addItem(leftSide);
    centerBox->addItem("");
    centerBox->addItem(center);
    rightBox->addItem("");
    rightBox->addItem(rightSide);

    int rows = ui->widget->findChildren<QGroupBox*>().size();
    vbox->addWidget(leftBox,12);
    vbox->addWidget(centerBox,12);
    vbox->addWidget(rightBox,12);
    groupBox->setLayout(vbox);
    ui->gridLayout_2->addWidget(groupBox,rows,0);

    groupBox->show();

    this->setGeometry(600,300,this->width(),this->height()+40);
    this->show();
}

void RelationWidget::setRelations() {
    for(QcMetaTable table : schema->getSchema()) {
        if(table.getRelationType() == RelationType::ManyToMany) {
            addRelation(table.getName(),table.getJointTable()->getName(),table.getRelatedTable()->getName());
        }
    }
}

void RelationWidget::removeRelationFromSchema(QcSchema *schema, QString tableName) {
    for(QcMetaTable &table : schema->getSchema()) {
        if(table.getName().compare(tableName) == 0) {
            qDebug() << "Removing relation from " + table.getName();
            table.setRelationType(RelationType::None);
        }
    }
}

// ============= SIGNALS ============== //

void RelationWidget::saveClicked() {
    QList<QGroupBox*> groupBoxes = ui->widget->findChildren<QGroupBox*>();

    for(QGroupBox* box : groupBoxes) {
        QList<QComboBox*> comboBoxes = box->findChildren<QComboBox*>();
        if(comboBoxes.size() == 3) {
            if(comboBoxes.at(0)->currentText().isEmpty()) {
                removeRelationFromSchema(schema, comboBoxes.at(0)->itemText(1));
            }
        }
    }

    this->setResult(QDialog::Accepted);
    this->hide();
}

void RelationWidget::cancelClicked() {
    for(QcMetaTable &table : schema->getSchema()) {
        if(table.getRelationType() == RelationType::ManyToMany) {
            table.setRelationType(RelationType::None);
        }
    }

    this->setResult(QDialog::Rejected);
    this->hide();
}
