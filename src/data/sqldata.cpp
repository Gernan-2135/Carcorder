#include "sqldata.h"
#include "allwidget.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>    //提供了数据库执行和操作的方法
#include <QMessageBox>
#include <QDir>

SqlData *SqlData::pSqlData = NULL;

SqlData::SqlData(const QString &filename)
{
    this->open_DB(filename);
}

SqlData *SqlData::get_DB(const QString &filename)
{
    if(NULL == pSqlData)
    {
        pSqlData = new SqlData(filename);
    }
    return pSqlData;
}

void SqlData::open_DB(const QString &filename)
{
    //添加数据库驱动
    pSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    pSqlDatabase.setDatabaseName(filename.toStdString().c_str());
    //使用数据库驱动 去调用DDL语句
    //打开数据库
    if(!pSqlDatabase.open())
    {
        qDebug() << pSqlDatabase.lastError();
    }
    else
    {
        init_usertable();
        init_sourcetable();
        initSettingTable();
    }
}

void SqlData::close_DB()
{
    pSqlDatabase.close();
}

void SqlData::init_usertable()
{
    QSqlQuery pSqlQuery;
    //QString drop_sql = "drop table user;";
    QString create_sql = "create table usr(uId VARCHAR primary key,uName VARCHAR,pwd VARCHAR,state INT);";
    //QString select_sql = "select *from usr;";

    pSqlQuery.prepare(create_sql);
    if(!pSqlQuery.exec()){
        qDebug() << pSqlQuery.lastError();
    }
    else{
        qDebug() << "usr table create";
    }
}

void SqlData::init_sourcetable()
{
    QSqlQuery pSqlQuery;
    //QString drop_sql = "drop table source;";
    QString create_sql = "create table source(id INTEGER primary key AUTOINCREMENT,uId VARCHAR,date TEXT,type VARCHAR,path TEXT);";
    //QString select_sql = "select *from source;";

    pSqlQuery.prepare(create_sql);
    if(!pSqlQuery.exec()){
        qDebug() << pSqlQuery.lastError();
    }
    else{
        qDebug() << "source table create success!";
    }
}

void SqlData::initSettingTable()
{
    QSqlQuery pSqlQuery;
    QString create_sql = "create table setting(uId VARCHAR,imgpath TEXT,videopath TEXT,time TEXT);";

    pSqlQuery.prepare(create_sql);
    if(!pSqlQuery.exec()){
        qDebug() << pSqlQuery.lastError();
    }
    else{
        qDebug() << "setting table create success!";
    }
}

bool SqlData::creatPath(const QString filePath)
{
    QDir dir(filePath);
    if(dir.exists()) {
        return true;
    }
    else {
        bool ok = dir.mkpath(filePath);  //创建多级目录
        return ok;
    }
}

bool SqlData::login_check(QString ID, QString Pwd)
{
    bool ret = search_user(ID);
    if(ret != true)
    {
        QMessageBox::information(NULL,"提示","账号不存在");
        return false;
    }
    else
    {
        QSqlQuery pSqlQuery;
        QString select_sql = QString("select * from usr where uId = '%1' and pwd = '%2';").arg(ID).arg(Pwd);
        qDebug()<<select_sql;
        pSqlQuery.prepare(select_sql);
        if(!pSqlQuery.exec())
        {
            qDebug()<<"登录失败"<<pSqlQuery.lastError();
            return false;
        }
        else
        {
            QString id;
            QString pwd;
            while(pSqlQuery.next())
            {               
                AllWidget::pLoginWidget->CurUser = pSqlQuery.value(0).toString();
                id = pSqlQuery.value(0).toString();
                pwd = pSqlQuery.value(2).toString();
                qDebug()<<QString("id:%1 pwd：%2").arg(id).arg(pwd);//  sprintf("")
            }
            if(id == 0)
            {
                qDebug()<<"登录失败 密码错误";
                QMessageBox::information(NULL,"提示","登录失败 密码错误");
                return false;
            }
            else
            {
                qDebug()<<"登录成功";
                return true;
            }
        }
    }
}

bool SqlData::regist_check(QString ID, QString Name, QString Pwd)
{
    bool ret = search_user(ID);
    if(ret == false)
    {
        QSqlQuery mySqlQuery;
        QString insert_sql = QString("insert into usr values('%1','%2','%3',1);").arg(ID).arg(Name).arg(Pwd);
        mySqlQuery.prepare(insert_sql);
        if(!mySqlQuery.exec())
        {
            qDebug()<<"注册失败"<<mySqlQuery.lastError();
            QMessageBox::information(NULL,"提示","注册失败");
            return false;
        }
        else
        {
            qDebug()<<"注册成功";
            QMessageBox::information(NULL,"提示","注册成功");
            return true;
        }
    }
    else
    {
        qDebug()<<"账号已存在";
        QMessageBox::information(NULL,"提示","账号已存在");
        return false;
    }

}

bool SqlData::search_user(QString ID)
{
    QSqlQuery pSqlQuery;
    QString select_sql = QString("select * from usr where uId = '%1';").arg(ID);
    qDebug()<<select_sql;
    pSqlQuery.prepare(select_sql);
    if(!pSqlQuery.exec()) {
        qDebug()<<"查询失败"<<pSqlQuery.lastError();
        return false;
    }
    else {
        QString id;
        while(pSqlQuery.next())
        {
            id = pSqlQuery.value(0).toString();
        }
        if(id == NULL) {
            qDebug()<<"账号不存在";
            return false;
        }
        else {
            qDebug()<<"账号已注册";
            return true;
        }
    }
}

bool SqlData::insert_sourcetable(QString uId, QString date, QString type, QString path)
{
    if(!uId.isEmpty()) {
        QSqlQuery pSqlQuery;
        QString insert_source = QString("insert into source values(NULL,'%1','%2','%3','%4');").arg(uId).arg(date).arg(type).arg(path);
        pSqlQuery.prepare(insert_source);
        if(!pSqlQuery.exec()){
            qDebug()<<"表格插入失败"<<pSqlQuery.lastError();
            return false;
        }
        else{
            qDebug()<<"表格插入成功";
            return true;
        }
    }
}

int SqlData::checkSettingTable(QString uId)
{
    QSqlQuery pSqlQuery;
    QString checkTable = QString("select * from setting where uId = %1;").arg(uId);
    pSqlQuery.prepare(checkTable);
    if(!pSqlQuery.exec()) {
        qDebug() << pSqlQuery.lastError();
        return 0;
    }
    else {
        while(pSqlQuery.next())
        {
            AllWidget::pSettingWidget->pSettingPath->ImagePath  = pSqlQuery.value(1).toString();
            AllWidget::pSettingWidget->pSettingPath->VideoPath = pSqlQuery.value(2).toString();
            AllWidget::pSettingWidget->pSettingPath->TimeInterval = pSqlQuery.value(3).toString();
        }
        qDebug() << AllWidget::pSettingWidget->pSettingPath->ImagePath << AllWidget::pSettingWidget->pSettingPath->VideoPath << AllWidget::pSettingWidget->pSettingPath->TimeInterval;
        if(AllWidget::pSettingWidget->pSettingPath->ImagePath.isEmpty()){
            qDebug() << "Never Setting Path";
            return 2;
        }
        else {
            bool ret = creatPath(AllWidget::pSettingWidget->pSettingPath->ImagePath);
            bool ret2 = creatPath(AllWidget::pSettingWidget->pSettingPath->VideoPath);
            if(ret == true && ret2 == true) {
                qDebug() << "Allready setting";
                return 1;
            }
            else {
                qDebug() << "Never Setting Path";
                return 2;
            }
        }
    }
}

bool SqlData::insertSettingTable(QString uId, QString imgpath, QString videopath, QString time)
{
    QSqlQuery pSqlQuery;
    QString insert = QString("insert into setting values('%1','%2','%3','%4')").arg(uId).arg(imgpath).arg(videopath).arg(time);
    pSqlQuery.prepare(insert);
    if(!pSqlQuery.exec()) {
        qDebug() << "setting insert failed!";
        return false;
    }
    else {
        qDebug() << "setting insert success!";
        return true;
    }
}

bool SqlData::updateSettingTable(QString uId, QString imgpath, QString videopath, QString time)
{
    QSqlQuery pSqlQuery;
    QString update_table = QString("update setting set imgpath = '%1',videopath = '%2',time = '%3' where uId = '%4';").arg(imgpath).arg(videopath).arg(time).arg(uId);
    pSqlQuery.prepare(update_table);
    if(!pSqlQuery.exec()) {
        qDebug() << "update table failed!";
        return false;
    }
    else {
        qDebug() << "update table success!";
        return true;
    }
}

