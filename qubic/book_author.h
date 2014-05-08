#ifndef BOOK_AUTHOR_H
#define BOOK_AUTHOR_H

#include "book.h"
#include "author.h"
#include <QObject>
#include <QbCore/qbpersistable.h>
#include <QbUtilities/qbadvancedqueryhelper.h>

class Book_author : public QbPersistable
{
	Q_OBJECT

private:
	qint32 book_author_id;
	Book* book_idptr;
	Author* author_idptr;
	static bool isRegistered;
public:
	Q_INVOKABLE Book_author();
	Q_INVOKABLE Book_author(qint32 book_author_id, book book_id, author author_id);
	Q_INVOKABLE Book_author(qint32 book_author_id, book book_id, author author_id);
	Q_INVOKABLE qint32 getBook_author_id()const;
	Q_INVOKABLE Book* getBook_idptr()const;
	Q_INVOKABLE Author* getAuthor_idptr()const;
	Q_INVOKABLE void setBook_author_id(qint32 book_author_id);
	Q_INVOKABLE void setBook_idptr(Book* book_id);
	Q_INVOKABLE void setAuthor_idptr(Author* author_id);
	static QString CLASSNAME;
	static QString BOOK_AUTHOR_ID;
	static QString BOOK_ID;
	static QString AUTHOR_ID;
};

Q_DECLARE_METATYPE(Book_author)

#endif