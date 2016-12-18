#ifndef __ROUTINE_H
#define __ROUTINE_H

#include "mogicTower.h"


bool isEnd(const Status& stat);

string getRoute(const Status& stat, GraphNode* choice);

void moveTo(int targetIdx, Status& stat, bool update = true);

#endif
