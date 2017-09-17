#ifndef TESTSVIEW_H
#define TESTSVIEW_H

#include <QWidget>
#include "peacock.h"
#include <QTableWidget>
#include <QTableWidgetItem>

class TestsView : public QWidget
{
    Q_OBJECT
public:
    explicit TestsView(QWidget *parent = 0);
    void clear_tests();
    void show_tests(QList<TestCase> tests);
private:
    QTableWidget *m_tests;
signals:

public slots:
};

#endif // TESTSVIEW_H
