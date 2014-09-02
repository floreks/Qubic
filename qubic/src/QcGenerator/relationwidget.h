#ifndef RELATIONWIDGET_H
#define RELATIONWIDGET_H

#include <QMainWindow>
#include <QDialog>
#include <QComboBox>

#include <schema/qcschema.h>

namespace Ui {
class RelationWidget;
}

class RelationWidget : public QDialog
{
    Q_OBJECT

public:
    RelationWidget(QWidget *parent = 0);
    RelationWidget(QWidget *parent = 0, QcSchema *schema = NULL);
    ~RelationWidget();

private:
    Ui::RelationWidget *ui;
    QcSchema* schema;

    void addRelation(QString leftSide, QString center, QString rightSide);
    void setRelations();
    void removeRelationFromSchema(QcSchema *schema, QString tableName);
public slots:
    void saveClicked();
    void cancelClicked();
};

#endif // RELATIONWIDGET_H
