#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamAttribute>
#include <QXmlStreamReader>
#include <QByteArray>

#include "task.h"
#include <QCheckBox>

#include "tzn.h"
#include "dba.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readXml();
    void storeBD();

    QVector<Task*> tasks;

public slots:
    void submit();
    void change();

private:
    Ui::MainWindow *ui;
    QList<QCheckBox*> checkboxes;



};
#endif // MAINWINDOW_H
