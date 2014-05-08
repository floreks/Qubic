#ifndef AUTHOR_H
#define AUTHOR_H

#include "qstring.h"
#include <QObject>
#include <QbCore/qbpersistable.h>
#include <QbUtilities/qbadvancedqueryhelper.h>

class Author : public QbPersistable
{
	Q_OBJECT

private:
	qint32 author_id;
	QString name;
	static bool isRegistered;
public:
	Q_INVOKABLE Author();
	Q_INVOKABLE Author(qint32 author_id, QString name);
	Q_INVOKABLE Author(qint32 author_id, QString name);
	Q_INVOKABLE qint32 getAuthor_id()const;
	Q_INVOKABLE QString getName()const;
	Q_INVOKABLE void setAuthor_id(qint32 author_id);
	Q_INVOKABLE void setName(QString name);
	static QString CLASSNAME;
	static QString AUTHOR_ID;
	static QString NAME;
};

Q_DECLARE_METATYPE(Author)

#endif