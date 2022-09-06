#ifndef GRAPHPARSER_H
#define GRAPHPARSER_H

#include "graph.h"

#include <QString>
#include <QRegularExpression>
#include <QVector>

class GraphParser
{
public:
    GraphParser();
    Graph* parseData(QString data);

private:
   void prepareRegExp();

   void parseFunction();
   void parseCmpSet();
   void parseCmpSettings();
   void parseVars();
   void parseVarInput();
   void parseVarOutput();
   void parseVarTemp();
   void parseSteps();
   void parseTransitions();

private:
    QString _data;
    Graph* _graph;

    QRegularExpressionMatch match;
    QRegularExpressionMatchIterator i,j;
    QString subData;

    QRegularExpression reFuncBlock  ;
    QRegularExpression reCmpSet     ;
    QRegularExpression reCmpSettings;
    QRegularExpression reCmpValues  ;
    QRegularExpression reVarInput   ;
    QRegularExpression reVarOutput  ;
    QRegularExpression reVarTemp    ;
    QRegularExpression reVarValues  ;
    QRegularExpression reStep       ;
    QRegularExpression reSet        ;
    QRegularExpression reTransition ;
    QRegularExpression reVariables  ;

};

#endif // GRAPHPARSER_H
