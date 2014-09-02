#ifndef QCGENERATOR_H
#define QCGENERATOR_H

#include <QMainWindow>

#include "properties/properties.h"
#include "database/qcdatabase.h"
#include "relationwidget.h"

namespace Ui {
class QcGenerator;
}

class QcGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit QcGenerator(QWidget *parent = 0);
    ~QcGenerator();

private:
    Ui::QcGenerator *ui;

    Properties *properties = NULL, *mapping = NULL;
    QcDatabase *db = NULL;
    RelationWidget *relationWidget = NULL;
    QcSchema *schema = NULL;
private slots:
    void loadDBProperty();
    void loadMappingProperty();

    void connectToDB();

    void generate();

    void setLoggingLevel(QString);

    void setUpRelations();
};

#endif // QCGENERATOR_H
