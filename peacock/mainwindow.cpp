#include "mainwindow.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QString>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QWidget>

#include "testsfactory.h"
#include "testsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_tests_factory = new TestsFactory();
    QString tests("/home/mike/Code/peacock/scripts/tests_log");
    m_tests_root = m_tests_factory->loadFileTests(tests);
    //tests tree
    m_tests_tree = new TestsTree(m_tests_root);
    m_tests_tree->display_tree();

    //tests view
    m_tests_view = new TestsView();

    QWidget *main_widget = new QWidget();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(m_tests_tree);
    main_layout->addWidget(m_tests_view);

    main_widget->setLayout(main_layout);

    connect(m_tests_tree, SIGNAL(tests_chnaged()), this, SLOT(update_tests_view()));

    setCentralWidget(main_widget);

    QTreeWidgetItem *test = new QTreeWidgetItem();
}

MainWindow::~MainWindow()
{

}

void MainWindow::update_tests_view()
{
    QList<TestCase> tests = m_tests_tree->get_selected_tests();

    m_tests_view->show_tests(tests);
}
