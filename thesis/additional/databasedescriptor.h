class DatabaseDescriptor
{
    Q_DECLARE_TR_FUNCTIONS(DatabaseDescriptor)

protected:
    QcLogger *logger;
public:
    explicit DatabaseDescriptor();
    virtual ~DatabaseDescriptor() {}

    QStringList getTables();
    QStringList getColumns(const QString &tableName);
    virtual QString getColumnType(const QString &tableName, const QString &columnName) = 0;
    virtual QStringList getColumnTypes(const QString &tableName) = 0;
    virtual QString getTypeSchema() = 0;
    virtual bool isPrimaryKey(const QString &tableName, const QString &columnName) = 0;
    virtual bool isForeignKey(const QString &tableName, const QString &columnName) = 0;
    virtual QString getFKTable(const QString &tableName, const QString &columnName) = 0;
};
