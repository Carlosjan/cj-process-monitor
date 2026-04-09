#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QDBusArgument>
#include <QMetaType>
#include <QDBusMetaType>
#include <QDBusConnection>
#include <QDBusMessage>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct ProcessInfo
{
    int pid;
    QString user;
    double cpu_percent;
    double mem_percent;
    quint64 rss;
    quint8 state;
    quint64 time;
    QString command;
};



// Deserialize (DBus → Qt)
inline const QDBusArgument& operator>>(const QDBusArgument& arg, ProcessInfo& p)
{
    arg.beginStructure();

    arg >> p.pid
        >> p.user
        >> p.cpu_percent
        >> p.mem_percent
        >> p.rss
        >> p.state
        >> p.time
        >> p.command;

    arg.endStructure();
    return arg;
}

// Serialize (optional, needed if you send back)
inline QDBusArgument& operator<<(QDBusArgument& arg, const ProcessInfo& p)
{
    arg.beginStructure();

    arg << p.pid
        << p.user
        << p.cpu_percent
        << p.mem_percent
        << p.rss
        << p.state
        << p.time
        << p.command;

    arg.endStructure();
    return arg;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:

    void onProcessUpdated(const QDBusArgument &arg);
    void onProcessUpdatedMessage(const QDBusMessage &msg);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
