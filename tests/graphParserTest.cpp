#include "../graphparser.h"
#include <QTest>

class GraphParserTest: public QObject
{
    Q_OBJECT
private slots:
    void toUpper2();
};

void GraphParserTest::toUpper2()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

