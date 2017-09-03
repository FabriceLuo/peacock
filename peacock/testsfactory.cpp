#include "testsfactory.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

TestsFactory::TestsFactory()
{

}

TestNode *TestsFactory::loadFileTests(QString &path)
{
    QString data = readTestsFile(path);
    if (data.isEmpty())
    {
        cerr << "tests file content is empty";
        return NULL;
    }

    QJsonObject *root = convertFileTests(data);
    if (!root)
    {
        cerr << "parse file tests failed";
        return NULL;
    }

    return parseFileTests(root);
}

QString TestsFactory::readTestsFile(const QString &path)
{
    QFile file(path);
    if (! file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cerr << "open tests file failed";
        return QString();
    }

    QString data = file.readAll();

    return data;
}

QJsonObject* TestsFactory::convertFileTests(const QString data)
{
    QJsonDocument test_doc = QJsonDocument::fromJson(data.toUtf8());
    if (test_doc.isNull())
    {
        cerr << "parse tests raw to json doc failed";
        return NULL;
    }

    if (! test_doc.isObject())
    {
        cerr << "file tests not compatable";
        return NULL;
    }

    return new QJsonObject(test_doc.object());
}

TestNode *TestsFactory::parseFileTests(QJsonObject *root)
{
    if (root == NULL)
    {
        cerr << "file tests object is null";
        return NULL;
    }

    return generate_test_node(root);
}

TestNode *TestsFactory::generate_test_node(QJsonObject *node)
{
    QString node_type = node->value("type").toString();
    TEST_NODE_TYPE type;

    //todo
    if (node_type == "package")
    {
        type = TEST_NODE_PACKAGE;
    }
    else if(node_type == "module")
    {
        type = TEST_NODE_MODULE;
    }
    else if(node_type == "class")
    {
        type = TEST_NODE_CLASS;
    }
    else if(node_type == "function")
    {
        type = TEST_NODE_FUNCTION;
    }
    else {
        cerr << "test type was not support";
        return NULL;
    }

    TestNode *temp_node = new_test_node(type);

    temp_node->name = node->value("name").toString();
    temp_node->desc = node->value("desc").toString();
    temp_node->note = node->value("note").toString();

    if (type == TEST_NODE_FUNCTION)
    {
        QJsonArray label_arr = node->value("label").toArray();
        int count = label_arr.count();
        for(int i=0; i < count; i++)
        {
            temp_node->label.append(label_arr.at(i).toString());
        }
    }
    else {
        QJsonObject tests_obj = node->value("data").toObject();
        QStringList keys = tests_obj.keys();

        int tests_count = keys.count();
        for(int i=0;i < tests_count; i++)
        {
            QJsonObject child = tests_obj.value(keys.at(i)).toObject();
            TestNode *child_node = generate_test_node(&child);
            if (! child_node)
            {
                cerr << "generate test node failed";
                return NULL;
            }
            temp_node->childs.append(child_node);
        }
    }

    return temp_node;
}

TestNode *TestsFactory::new_test_node(TEST_NODE_TYPE type)
{
    TestNode *temp_node = new TestNode();

    //todo check type
    temp_node->type = type;
    return temp_node;
}





































