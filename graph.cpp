#include "graph.h"
#include <QDebug>


void Graph::makeReferences()
{
    for(auto& trans : transitions){
        for(auto& step : steps){
            if(trans->stepTo == step->name){
                step->transitionFrom = trans;
                trans->stepToObj = step;

            }
            if(trans->stepFrom == step->name){
                step->transitionsTo.append(trans);
                trans->stepFromObj = step;

            }
        }
    }
}

void Graph::printReferences(){
    for(auto& step: steps){
        for(auto& trans : step->transitionsTo){
            qDebug() << "S_" << step->number << " -> T_" << trans->number;
        }
        qDebug();
    }
}
