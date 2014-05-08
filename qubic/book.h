#ifndef BOOK_H
#define BOOK_H

#include "qstring.h"
#include <QObject>
#include <QbCore/qbpersistable.h>
#include <QbUtilities/qbadvancedqueryhelper.h>

class Book : public QbPersistable
{
	Q_OBJECT

private:
	qint32 book_id;
	QString title;
	static bool isRegistered;
public:
	Q_INVOKABLE Book();
	Q_INVOKABLE Book(qint32 book_id, QString title);
	Q_INVOKABLE Book(qint32 book_id, QString title);
	Q_INVOKABLE qint32 getBook_id()const;
	Q_INVOKABLE QString getTitle()const;
	Q_INVOKABLE void setBook_id(qint32 book_id);
	Q_INVOKABLE void setTitle(QString title);
	static QString CLASSNAME;
	static QString BOOK_ID;
	static QString TITLE;
};

Q_DECLARE_METATYPE(Book)

#endif