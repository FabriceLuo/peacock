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

    tests_tree = new QTreeWidget();

    tests_tree->setColumnCount(1);
    tests_tree->header()->setHidden(true);
    tests_tree->addTopLevelItem(root);

    connect(tests_tree, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(select_tests_node(QTreeWidgetItem*,int)));

    QVBoxLayout *tree_layout = new QVBoxLayout();
    tree_layout->addWidget(tests_tree);
    setLayout(tree_layout);

    return true;
}

QList<TestCase> TestsTree::get_selected_tests()
{
    QList<TestCase> list;
    if (!tests_tree)
    {
        return list;
    }

    QList<QTreeWidgetItem*> tests_queue;
    int count = tests_tree->topLevelItemCount();
    for(int i = 0;i < count; i++)
    {
        tests_queue.append(tests_tree->topLevelItem(i));
    }

    QTreeWidgetItem *item = NULL;
    while(tests_queue.count())
    {
        item = tests_queue.front();
        tests_queue.pop_front();

        if (item->childCount() == 0 && item->checkState(0) == Qt::Checked)
        {
            TestCase test_case;
            test_case.name = item->text(0);
            list.append(test_case);

        }
        else
        {
            int child_count = item->childCount();
            for (int i = 0; i < child_count; i++)
            {
                tests_queue.append(item->child(i));
            }
        }
    }

    return list;
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

TestNode *TestsTree::find_test_node(QTreeWidgetItem *item)
{
    if (!tests_root || !item)
    {
        return NULL;
    }

    QStringList path = get_test_path(item);

    return get_test_node(path);
}

TestNode *TestsTree::get_test_node(QStringList path)
{
    QString root = path.front();
    path.pop_front();
    if (root != tests_root->name)
    {
        return NULL;
    }


    TestNode *p_node = tests_root;

    QStringList::iterator begin = path.begin();
    QStringList::iterator end = path.end();

    while (begin != end) {
        if (p_node->type == TEST_NODE_FUNCTION)
        {
            if (p_node->name != *begin)
            {
                return NULL;
            }
        }
        else
        {
            //find node in child
            QList<TestNode*>::iterator t_begin = p_node->childs.begin();
            QList<TestNode*>::iterator t_end = p_node->childs.end();

            while (t_begin != t_end) {
                if ((*t_begin)->name == *begin)
                {
                    p_node = *t_begin;
                    break;
                }

                t_begin++;
            }
        }

        begin++;
    }

    return p_node;
}

QStringList TestsTree::get_test_path(QTreeWidgetItem *item)
{
    QStringList test_path;
    while(item)
    {
        test_path.push_front(item->text(0));
        item = item->parent();
    }
    return test_path;
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

        emit tests_chnaged();
    }
}
























