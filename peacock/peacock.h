#ifndef PEACOCK_H
#define PEACOCK_H
#include <iostream>
#include <QList>
#include <QString>
#include <QStringList>

using namespace std;

enum TEST_NODE_TYPE {
    TEST_NODE_FUNCTION,
    TEST_NODE_CLASS,
    TEST_NODE_MODULE,
    TEST_NODE_PACKAGE
};

struct TestNode{
    QString name;
    QString desc;
    QString note;
    QStringList label;
    TEST_NODE_TYPE type;
    QList<TestNode*> childs;
};

#endif // PEACOCK_H
