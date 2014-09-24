#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "qstring.h"
#include <ORM/Qubic.h>

class Department : public QbPersistable
{
	Q_OBJECT

private:
	QString departmentname;
	static bool isRegistered;
public:
	Q_INVOKABLE Department();
	Q_INVOKABLE Department(qint32 id, QString departmentname);
	Q_INVOKABLE Department(QString departmentname);
	Q_INVOKABLE Department(const Department& other);
	Q_INVOKABLE QString getDepartmentname()const;
	Q_INVOKABLE void setDepartmentname(QString departmentname);
	QList<QbPersistable*> getPointers();
	QList<QbPersistable*> getEmployees();
	static QString CLASSNAME;
	static QString ID;
	static QString DEPARTMENTNAME;
};

Q_DECLARE_METATYPE(Department)

#endif