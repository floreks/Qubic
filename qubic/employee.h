#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "qstring.h"
#include "qdate.h"
#include "company.h"
#include "qdatetime.h"
#include <QObject>
#include <QbCore/qbpersistable.h>
#include <QbUtilities/qbadvancedqueryhelper.h>

class Employee : public QbPersistable
{
	Q_OBJECT

private:
	QString firstname;
	QString lastname;
	QDate birthday;
	QString gender;
	Company* companyptr;
	QDateTime hiredate;
	qreal salary;
	qint32 children;
	static bool isRegistered;
public:
	Q_INVOKABLE Employee();
	Q_INVOKABLE Employee(qint32 id, QString firstname, QString lastname, QDate birthday, QString gender, company company, QDateTime hiredate, qreal salary, qint32 children);
	Q_INVOKABLE Employee(QString firstname, QString lastname, QDate birthday, QString gender, company company, QDateTime hiredate, qreal salary, qint32 children);
	Q_INVOKABLE QString getFirstname()const;
	Q_INVOKABLE QString getLastname()const;
	Q_INVOKABLE QDate getBirthday()const;
	Q_INVOKABLE QString getGender()const;
	Q_INVOKABLE Company* getCompanyptr()const;
	Q_INVOKABLE QDateTime getHiredate()const;
	Q_INVOKABLE qreal getSalary()const;
	Q_INVOKABLE qint32 getChildren()const;
	Q_INVOKABLE void setFirstname(QString firstname);
	Q_INVOKABLE void setLastname(QString lastname);
	Q_INVOKABLE void setBirthday(QDate birthday);
	Q_INVOKABLE void setGender(QString gender);
	Q_INVOKABLE void setCompanyptr(Company* company);
	Q_INVOKABLE void setHiredate(QDateTime hiredate);
	Q_INVOKABLE void setSalary(qreal salary);
	Q_INVOKABLE void setChildren(qint32 children);
	static QString CLASSNAME;
	static QString ID;
	static QString FIRSTNAME;
	static QString LASTNAME;
	static QString BIRTHDAY;
	static QString GENDER;
	static QString COMPANY;
	static QString HIREDATE;
	static QString SALARY;
	static QString CHILDREN;
};

Q_DECLARE_METATYPE(Employee)

#endif