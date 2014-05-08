#ifndef COMPANY_H
#define COMPANY_H

#include "qstring.h"
#include <QObject>
#include <QbCore/qbpersistable.h>
#include <QbUtilities/qbadvancedqueryhelper.h>

class Company : public QbPersistable
{
	Q_OBJECT

private:
	QString companyname;
	static bool isRegistered;
public:
	Q_INVOKABLE Company();
	Q_INVOKABLE Company(qint32 id, QString companyname);
	Q_INVOKABLE Company(QString companyname);
	Q_INVOKABLE QString getCompanyname()const;
	Q_INVOKABLE void setCompanyname(QString companyname);
	static QString CLASSNAME;
	static QString ID;
	static QString COMPANYNAME;
};

Q_DECLARE_METATYPE(Company)

#endif