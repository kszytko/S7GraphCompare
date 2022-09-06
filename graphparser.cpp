#include "graphparser.h"
#include <QDebug>

GraphParser::GraphParser()
{

}

Graph *GraphParser::parseData(QString data)
{
    _graph = new Graph();
    _data = data;

    prepareRegExp();
    parseFunction();
    parseCmpSet();
    parseCmpSettings();
    parseVarInput();
    parseVarOutput();
    parseVarTemp();
    parseSteps();
    parseTransitions();

    return _graph;
}


void GraphParser::prepareRegExp()
{
    const char * expFuncBlock   = R"(FUNCTION_BLOCK \"(.+)\"\n.+\$_COM\s(.+)\*\))";
    const char * ecpCmpSet      = R"(\$_CMPSET\n([^\*\)]+))";
    const char * ecpCmpSettings = R"(\$_SETTINGS\n([^\*\)]+))";
    const char * ecpCmpValues   = R"(\s*(.+):\s*(.+))";
    const char * ecpVarInput    = R"(VAR_INPUT([\s\S]+?)END_VAR)";
    const char * ecpVarOutput   = R"(VAR_OUTPUT([\s\S]+?)END_VAR)";
    const char * ecpVarTemp     = R"(VAR_TEMP([\s\S]+?)END_VAR)";
    const char * ecpVarValues   = R"(\s*(\S+)\s+:\s+(\S+)(\s+:=\s+(\S+))?;(\(\*(.+)\*\))?)";
    const char * ecpStep        = R"((^STEP|^INITIAL_STEP) (\S+) \S+ (\d+).+\n\S+ (.+)\*.+\n\n([\S\s]+?)END_STEP)";
    const char * ecpSet         = R"("(\S+)\s+(:= )?(\S+)?\s+\((\S+)\))";
    const char * ecpTransition  = R"(TRANSITION (\S+) \S+ (\d+).+\n\s+FROM (\S+)\n\s+TO (\S+)(.+)?\nCONDITION := (.+)\nEND_TRANSITION)";
    const char * ecpVariables   = R"("(\S+))";

    reFuncBlock  .setPattern(expFuncBlock  );
    reCmpSet     .setPattern(ecpCmpSet     );
    reCmpSettings.setPattern(ecpCmpSettings);
    reCmpValues  .setPattern(ecpCmpValues  );
    reVarInput   .setPattern(ecpVarInput   );
    reVarOutput  .setPattern(ecpVarOutput  );
    reVarTemp    .setPattern(ecpVarTemp    );
    reVarValues  .setPattern(ecpVarValues  );
    reStep       .setPattern(ecpStep       );
    reSet        .setPattern(ecpSet        );
    reTransition .setPattern(ecpTransition );
    reVariables  .setPattern(ecpVariables  );

    reFuncBlock  .setPatternOptions(QRegularExpression::MultilineOption);
    reCmpSet     .setPatternOptions(QRegularExpression::MultilineOption);
    reCmpSettings.setPatternOptions(QRegularExpression::MultilineOption);
    reVarInput   .setPatternOptions(QRegularExpression::MultilineOption);
    reVarTemp    .setPatternOptions(QRegularExpression::MultilineOption);
    reVarOutput  .setPatternOptions(QRegularExpression::MultilineOption);
    reStep       .setPatternOptions(QRegularExpression::MultilineOption);
    reTransition .setPatternOptions(QRegularExpression::MultilineOption);
}

void GraphParser::parseFunction()
{
    match = reFuncBlock.match(_data);
    if (match.hasMatch()) {
        _graph->name = match.captured(1);
        _graph->comment = match.captured(2);

        qDebug() << "reFuncBlock:: "<<_graph->name << " " << _graph->comment;
    }
}

void GraphParser::parseCmpSet()
{
    match = reCmpSet.match(_data);
    if (match.hasMatch()) {
        subData = match.captured(1);

        i = reCmpValues.globalMatch(subData);
        while (i.hasNext()) {
            match = i.next();
            QString variable = match.captured(1);
            QString value =  match.captured(2);

            _graph->cmpSet.push_back({variable, value});
            qDebug() <<"reCmpSet:: "<< variable << " :\t" << value;
        }
    }
}

void GraphParser::parseCmpSettings()
{
    match = reCmpSettings.match(_data);
    if (match.hasMatch()) {
        subData = match.captured(1);

        i = reCmpValues.globalMatch(subData);
        while (i.hasNext()) {
            match = i.next();
            QString variable = match.captured(1);
            QString value =  match.captured(2);

            _graph->cmpSettings.push_back({variable, value});
            qDebug() <<"reCmpSettings:: "<<  variable << " :\t" << value;
        }
    }
}

void GraphParser::parseVarInput()
{
    match = reVarInput.match(_data);
    if (match.hasMatch()) {
        subData = match.captured(1);

        i = reVarValues.globalMatch(subData);
        while (i.hasNext()) {
            match = i.next();
            QString name = match.captured(1);
            QString type =  match.captured(2);
            QString value =  match.captured(4);
            QString comment =  match.captured(6);

            _graph->inputVars.push_back({name, type, value, comment});
            qDebug() << "reVarInput:: "<< name << "\t"  << type << "\t"  << value << "\t"  << comment;
        }
    }
}

void GraphParser::parseVarOutput()
{
    match = reVarOutput.match(_data);
    if (match.hasMatch()) {
        subData = match.captured(1);

        i = reVarValues.globalMatch(subData);
        while (i.hasNext()) {
            match = i.next();
            QString name = match.captured(1);
            QString type =  match.captured(2);
            QString value =  match.captured(4);
            QString comment =  match.captured(6);

            _graph->outputVars.push_back({name, type, value, comment});
            qDebug() <<"reVarOutput:: "<< name << "\t"  << type << "\t"  << value << "\t"  << comment;
        }
    }
}

void GraphParser::parseVarTemp()
{
    match = reVarTemp.match(_data);
    if (match.hasMatch()) {
        subData = match.captured(1);

        i = reVarValues.globalMatch(subData);
        while (i.hasNext()) {
            match = i.next();
            QString name = match.captured(1);
            QString type =  match.captured(2);
            QString value =  match.captured(4);
            QString comment =  match.captured(6);

            _graph->tempVars.push_back({name, type, value, comment});
            qDebug() << "reVarTemp:: "<<name << "\t"  << type << "\t"  << value << "\t"  << comment;
        }
    }
}

void GraphParser::parseSteps()
{
    i = reStep.globalMatch(_data);
    while (i.hasNext()) {
        match = i.next();
        Step* step = new Step;

        step->name = match.captured(2);
        step->number =  match.captured(3);
        step->comment =  match.captured(4);
        subData = match.captured(5);
        qDebug() << "reStep::\t" << step->name << "\t" << step->number << "\t" << step->comment;

        j = reSet.globalMatch(subData);
        while (j.hasNext()) {
            match = j.next();
            QString name = match.captured(1);
            QString value =  match.captured(3);
            QString option =  match.captured(4);

            step->sets.push_back({name,value,option});

            qDebug() << "reSet:: "<<name << "\t"  << value << "\t"  << option;
        }
        _graph->steps.append(step);
    }
}

void GraphParser::parseTransitions()
{
    i = reTransition.globalMatch(_data);
    while (i.hasNext()) {
        match = i.next();
        Transition* transition = new Transition;

        transition->name = match.captured(1);
        transition->number =  match.captured(2);
        transition->stepFrom =  match.captured(3);
        transition->stepTo =  match.captured(4);
        transition->condition =  match.captured(6);

        qDebug() << "reTransition::\t" << transition->name << "\t" << transition->number << "\t" << transition->stepFrom << "\t" << transition->stepTo;
        qDebug() << transition->condition;

        _graph->transitions.append(transition);
    }
}



