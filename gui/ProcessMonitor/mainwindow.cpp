#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "TEST debug:";
    qRegisterMetaType<ProcessInfo>("ProcessInfo");
    qDBusRegisterMetaType<ProcessInfo>();

    /*bool ok = QDBusConnection::sessionBus().connect(
        "com.example.MyService",  // service
        "/com/example/MyObject",  // path
        "com.example.Interface",  // interface
        "ProcessUpdated",         // signal
        "((isddtyts))",           // D-Bus signature of the struct
        this,
        SLOT(onProcessUpdated(QDBusArgument))
        );*/


    bool ok = QDBusConnection::sessionBus().connect(
        QStringLiteral("com.example.MyService"),    // service
        QStringLiteral("/com/example/MyObject"),   // path
        QStringLiteral("com.example.Interface"),   // interface
        QStringLiteral("ProcessUpdated"),          // signal
        this,
        SLOT(onProcessUpdatedMessage(QDBusMessage))
        );

    qDebug() << "DBus signal connection ok:" << ok;
    qDebug() << "TEST debug2:";

}

void MainWindow::onProcessUpdatedMessage(const QDBusMessage &msg)
{
    if (msg.arguments().isEmpty()) return;

    QDBusArgument arg = msg.arguments().at(0).value<QDBusArgument>();
    ProcessInfo p;
    arg >> p;  // use your operator>>

    qDebug() << "Signal received via QDBusMessage!";
    qDebug() << "PID:" << p.pid
             << "USER:" << p.user
             << "CPU:" << p.cpu_percent
             << "CMD:" << p.command;
}

void MainWindow::onProcessUpdated(const QDBusArgument &arg)
{
    qDebug() << "onProcessUpdated";
    ProcessInfo p;
    arg >> p;  // deserialize
    qDebug() << "Signal received!";
    qDebug() << "PID:" << p.pid
             << "USER:" << p.user
             << "CPU:" << p.cpu_percent
             << "CMD:" << p.command;
}

MainWindow::~MainWindow()
{
    delete ui;
}
