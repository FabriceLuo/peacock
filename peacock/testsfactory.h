#ifndef TESTSFACTORY_H
#define TESTSFACTORY_H

#include "peacock.h"
#include <QJsonObject>


class TestsFactory
{
public:
    TestsFactory();
    TestNode* loadFileTests(QString &path);
private:
    QString readTestsFile(const QString &path);
    QJsonObject* convertFileTests(const QString data);
    TestNode* parseFileTests(QJsonObject *root);
    TestNode* generate_test_node(QJsonObject *node);
    TestNode* new_test_node(TEST_NODE_TYPE type);
};

#endif // TESTSFACTORY_H
