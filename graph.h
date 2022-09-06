#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QRegularExpression>
#include <QVector>

struct Transition;
struct Step;

struct Setting{
    QString variable;
    QString value;
};

struct Var{
    QString name;
    QString type;
    QString value;
    QString comment;
};

struct Set{
    QString name;
    QString value;
    QString option;
};

struct Step{
    QString name;
    QString number;
    QString comment;
    QVector<Set> sets;

    Transition* transitionFrom;
    QVector<Transition*> transitionsTo;
};

struct Transition{
    QString name;
    QString number;
    QString stepFrom;
    QString stepTo;
    QString condition;

    Step* stepFromObj;
    Step* stepToObj;
};




class Graph
{  
public:
    Graph(){};

public:
    void makeReferences();
    void printReferences();

public:
    QString name;
    QString comment;

    QVector<Setting> cmpSet;
    QVector<Setting> cmpSettings;

    QVector<Var> inputVars;
    QVector<Var> outputVars;
    QVector<Var> tempVars;

    QVector<Step*> steps;
    QVector<Transition*> transitions;
};


#endif // GRAPH_H
