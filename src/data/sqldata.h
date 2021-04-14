#ifndef SQLDATA_H
#define SQLDATA_H

#include <QString>
#include <QSqlDatabase>

class SqlData
{
public:
    static SqlData *get_DB(const QString &filename);
    void open_DB(const QString &filename);
    void close_DB();
    void init_usertable();
    void init_sourcetable();
    void initSettingTable();

    bool creatPath(const QString filePath);
    bool login_check(QString ID,QString Pwd);
    bool regist_check(QString ID, QString Name, QString Pwd);
    bool search_user(QString ID);
    bool insert_sourcetable(QString uId, QString date, QString type, QString path);
    int checkSettingTable(QString uId);
    bool insertSettingTable(QString uId, QString imgpath, QString videopath, QString time);
    bool updateSettingTable(QString uId, QString imgpath, QString videopath, QString time);

private:
    SqlData(const QString &filename);
    static SqlData *pSqlData;
    QSqlDatabase pSqlDatabase;
};

#endif // SQLDATA_H
