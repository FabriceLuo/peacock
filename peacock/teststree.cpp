#include "teststree.h"

#include <QString>
#include <QStringList>

#include <QJsonValue>
#include <QJsonObject>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QVBoxLayout>
#include <QHeaderView>

TestsTree::TestsTree(QWidget *parent):
    QWidget(parent)
{

}

TestsTree::TestsTree(TestNode *root, QWidget *parent):
    QWidget(parent)
{
    tests_root = root;
}

void TestsTree::set_tests_tree(TestNode *root)
{
    tests_root = root;
}

bool TestsTree::display_tree()
{
    if (! tests_root)
    {
        return false;
    }

    QTreeWidgetItem *root = build_tests_tree(tests_root, NULL);

    QTreeWidget *tWidget = new QTreeWidget();

    tWidget->setColumnCount(1);
    tWidget->header()->setHidden(true);
    tWidget->addTopLevelItem(root);

    connect(tWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(select_tests_node(QTreeWidgetItem*,int)));

    QVBoxLayout *tree_layout = new QVBoxLayout();
    tree_layout->addWidget(tWidget);
    setLayout(tree_layout);
    //connect(tWidget, SIGNAL()

    return true;
}

QTreeWidgetItem *TestsTree::build_tests_tree(TestNode *root, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent, QStringList(root->name));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(0, Qt::Unchecked);
    if (root->type == TEST_NODE_FUNCTION)
    {
        return item;
    }

    QList<TestNode*>::iterator begin = root->childs.begin();
    QList<TestNode*>::iterator end   = root->childs.end();

    while (begin != end) {
        QTreeWidgetItem *child_item = build_tests_tree(*begin, item);
        item->addChild(child_item);

        begin++;
    }
    return item;
}

void TestsTree::export_chosen_leaves(QString path)
{

}

void TestsTree::select_tests_node(QTreeWidgetItem *item, int column)
{
    if (column == 0)
    {
        bool changed_item = false;
        if (!m_check_start)
        {
            changed_item = true;
            m_check_start = true;
        }


        if (changed_item)
        {
            m_check_child = true;
            m_check_parent = false;
        }

        if (changed_item || m_check_child)
        {
            Qt::CheckState cur_state = item->checkState(0);
            //update children state
            int child_count = item->childCount();
            for(int i = 0; i < child_count; i++)
            {
                Qt::CheckState child_state = item->child(i)->checkState(0);
                if (child_state != cur_state)
                {
                    item->child(i)->setCheckState(0, cur_state);
                }
            }
        }

        //only pdate parent state by current node or parent node
        if (changed_item)
        {
            m_check_child = false;
            m_check_parent = true;
        }
        if (changed_item || m_check_parent)
        {
            QTreeWidgetItem *parent = item->parent();
            if(parent)
            {
                int p_child_count = parent->childCount();
                Qt::CheckState p_old_state = parent->checkState(0);
                Qt::CheckState p_new_state = parent->child(0)->checkState(0);
                for(int i = 1; i < p_child_count; i++)
                {
                    Qt::CheckState p_child_state = parent->child(i)->checkState(0);
                    if (p_child_state != p_new_state)
                    {
                        p_new_state = Qt::PartiallyChecked;
                        break;
                    }
                }
                //update only the parent state changed
                if (p_old_state != p_new_state)
                {
                    parent->setCheckState(0, p_new_state);
                }
            }
        }

        if (changed_item)
        {
            m_check_start = false;
        }
    }
}
























