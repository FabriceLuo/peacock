#include "mainwindow.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QString>
#include <QHeaderView>
#include <QHBoxLayout>
#include "testsfactory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*
    QTreeWidget *tWidget = new QTreeWidget();

    tWidget->setColumnCount(1);
    tWidget->header()->setHidden(true);
    //top level
    QTreeWidgetItem *t_tree1 = new QTreeWidgetItem(QStringList("level1_one"));
    t_tree1->setCheckState(0, Qt::Unchecked);
    //t_tree1->setFlags(t_tree1->flags() | Qt::ItemIsUserCheckable);


    QTreeWidgetItem *t_tree2 = new QTreeWidgetItem(QStringList("level2_two"));
    t_tree2->setCheckState(0, Qt::Unchecked);
    //t_tree2->setFlags(t_tree2->flags() | Qt::ItemIsUserCheckable);

    QTreeWidgetItem *t_tree1_child1 = new QTreeWidgetItem(t_tree1, QStringList("level1_child1_two"));
    t_tree1_child1->setCheckState(0, Qt::Unchecked);
    //t_tree1_child1->setFlags(t_tree1_child1->flags() | Qt::ItemIsUserCheckable);

    QTreeWidgetItem *t_tree1_child2 = new QTreeWidgetItem(t_tree1, QStringList("level1_child2_two"));
    t_tree1_child2->setCheckState(0, Qt::Unchecked);
    //t_tree1_child2->setFlags(t_tree1_child2->flags() | Qt::ItemIsUserCheckable);

    QTreeWidgetItem *t_tree2_child1 = new QTreeWidgetItem(t_tree2, QStringList("level2_child1_two"));
    //t_tree2_child1->setFlags(t_tree2_child1->flags() | Qt::ItemIsUserCheckable);
    t_tree2_child1->setCheckState(0, Qt::Unchecked);
    QTreeWidgetItem *t_tree2_child2 = new QTreeWidgetItem(t_tree2, QStringList("level2_child2_two"));
    //t_tree2_child2->setFlags(t_tree2_child2->flags() | Qt::ItemIsUserCheckable);
    t_tree2_child2->setCheckState(0, Qt::Unchecked);

    t_tree1->addChild(t_tree1_child1);
    t_tree1->addChild(t_tree1_child2);


    t_tree2->addChild(t_tree2_child1);
    t_tree2->addChild(t_tree2_child2);

    tWidget->addTopLevelItem(t_tree1);
    tWidget->addTopLevelItem(t_tree2);
    setCentralWidget(tWidget);

    TestsFactory fac = TestsFactory();
    QString path("/home/mike/Code/peacock/tests_log");
    TestNode *root = fac.loadFileTests(path);
    int i = 1;
    */

    m_tests_factory = new TestsFactory();
    QString tests("/home/mike/Code/peacock/scripts/tests_log");
    m_tests_root = m_tests_factory->loadFileTests(tests);
    m_tests_tree = new TestsTree(m_tests_root);
    m_tests_tree->display_tree();
    setCentralWidget(m_tests_tree);
    /*
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_tests_tree);
    setLayout(main_layout);
    */
}

MainWindow::~MainWindow()
{

}
