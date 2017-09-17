#include "testsview.h"
#include <QLayout>
#include <QVBoxLayout>

TestsView::TestsView(QWidget *parent) : QWidget(parent)
{
    m_tests = new QTableWidget(0, 3);
    m_tests->setFixedSize(400, 800);
    //init test headers
    QStringList headers;
    headers.append("Test Name");
    headers.append("Description");
    headers.append("Node");

    m_tests->setHorizontalHeaderLabels(headers);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(m_tests);
    setLayout(main_layout);
}

void TestsView::clear_tests()
{
    this->m_tests->clearContents();
}

void TestsView::show_tests(QList<TestCase> tests)
{
    int count = tests.count();
    this->m_tests->setRowCount(count);

    for (int i = 0;i < count; i++)
    {
        TestCase test = tests.at(i);
        m_tests->setItem(i, 0, new QTableWidgetItem(test.name));
        m_tests->setItem(i, 1, new QTableWidgetItem(test.desc));
        m_tests->setItem(i, 2, new QTableWidgetItem(test.note));
    }
}
