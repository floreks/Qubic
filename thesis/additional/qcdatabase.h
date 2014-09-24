class QcDatabase
{
    Q_DECLARE_TR_FUNCTIONS(QcDatabase)

public:

    static QcDatabase* getInstance(Properties *properties);
    static QcDatabase* getInstance();
    bool open();
    void close();
private:

    static QSharedPointer<QcDatabase> instance;
    QcDatabase(Properties *properties);
    QcDatabase();
};
