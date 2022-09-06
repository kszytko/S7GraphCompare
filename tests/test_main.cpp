#include <QTest>
#include "graphParserTest.cpp"

int main(int argc, char** argv){
    GraphParserTest testcases;
    return QTest::qExec(&testcases, argc,argv);

}
