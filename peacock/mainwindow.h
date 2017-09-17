#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "peacock.h"
#include "testsfactory.h"
#include "teststree.h"
#include "testsview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    TestsTree       *m_tests_tree;
    TestsView       *m_tests_view;
    TestNode        *m_tests_root;
    TestsFactory    *m_tests_factory;
private slots:
    void update_tests_view();
};

#endif // MAINWINDOW_H
