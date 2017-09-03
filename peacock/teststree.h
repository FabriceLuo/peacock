#ifndef TESTSTREE_H
#define TESTSTREE_H

#include "peacock.h"

#include <QWidget>
#include <QTreeWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class TestsTree : public QWidget
{
    Q_OBJECT
public:
    TestsTree(QWidget *parent = 0);
    TestsTree(TestNode *root, QWidget *parent = 0);

    void set_tests_tree(TestNode *root);
    bool display_tree();
protected:
    QTreeWidgetItem* build_tests_tree(TestNode *root, QTreeWidgetItem *parent);
private:
    TestNode *tests_root;
    QTreeWidget *tests_tree;
    bool  m_check_child;
    bool  m_check_parent;
    bool  m_check_start;

signals:
    void leaf_chosen(TestNode *node);
public slots:
    void export_chosen_leaves(QString path);
    void select_tests_node(QTreeWidgetItem *item, int column);
};

#endif // TESTSTREE_H
