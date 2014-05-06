#ifndef QCGENERATOR_H
#define QCGENERATOR_H

#include <QMainWindow>

#include "properties/properties.h"
#include "database/qcdatabase.h"

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

    Properties *properties, *mapping;
    QcDatabase *db;
private slots:
    void loadDBProperty();
    void loadMappingProperty();

    void connectToDB();

    void generate();

    void setLoggingLevel(QString);
};

#endif // QCGENERATOR_H
