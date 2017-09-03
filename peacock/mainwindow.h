#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "peacock.h"
#include "testsfactory.h"
#include "teststree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    TestsTree       *m_tests_tree;
    TestNode        *m_tests_root;
    TestsFactory    *m_tests_factory;
};

#endif // MAINWINDOW_H
