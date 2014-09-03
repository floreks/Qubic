class QcMetaField
{
private:
    QString fieldName;
    bool primaryKey;
    bool foreignKey;
protected:
    QString typeName;
public:
    QcMetaField();
    QcMetaField(QString fieldName);
    virtual ~QcMetaField() {}

    void setName(const QString &fieldName);
    void setForeignKey(bool fk);
    void setPrimaryKey(bool pk);
    void setType(const QString &typeName);

    virtual QString getType()const = 0;
    QString getName()const;
    bool isPrimaryKey()const;
    bool isForeignKey()const;
};

#endif // QCMETAFIELD_H
