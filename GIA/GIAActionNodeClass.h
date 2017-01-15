/*******************************************************************************
 *
 * File Name: GIAActionNodeClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2011 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1b8b 22-Sept-11
 *
 *******************************************************************************/


#ifndef HEADER_GIA_ACTION_NODE_CLASS
#define HEADER_GIA_ACTION_NODE_CLASS


#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;


class GIAEntityNode;
class GIAConditionNode;

/*
//ConditionNodes;
	//where
	//LocationConditionNode;		//known location required to perform this action

	//when
	//TimeConditionNode;			//known time required to perform this action
	//PropertyConditionNodeInList;	//state of being required to perform this action

	//how
	//ActionConditionNodeInList;	//another action required to perform this action

//ReasonNodes;
	//why
	//ActionReasonNode;		//in order to perform an action
*/

	//this is effectively an action instance node [all actions are recorded for the associated entityNodeDefiningThisAction and are found by looking at entityNodeDefiningThisAction's AssociatedActionNodeList list]
class GIAActionNode
{
public:

	GIAActionNode(void);
	~GIAActionNode(void);
	
	bool initialisedForPrinting;	
	bool printed;
	int printX;
	int printY;
	int printXIndex;
	int printYIndex;
	int printTextX;
	int printTextY;
	
	string actionName;
	double confidence;

	//NB a reason appears to be the reverse of a condition
	
	//list of conditions

	//conditions: where, how, when
	
	vector<GIAConditionNode*> ConditionNodeList;
	vector<GIAConditionNode*>::iterator ConditionNodeListIterator;

	//reasons: why	[reverse action lookups; NB these may only be action conditions]
	vector<GIAConditionNode*> ConditionNodeReverseList;
	vector<GIAConditionNode*>::iterator ConditionNodeReverseListIterator;	
	
	//a template entity for the associated concept of this action/verb (eg verb=study, associated entity/noun = study):
	GIAEntityNode * entityNodeDefiningThisAction;
	
	//NB actions can be performed by and on entities, and by and on properties
	//record of entity that is the subject of this action instance
	GIAEntityNode * actionSubjectEntity;
	//record of which entity that is the object of this action instance
	GIAEntityNode * actionObjectEntity;
	
	//flat tree structures are not used - this is only used for the semanticNet xml parse (read) process;	
	GIAActionNode * next;
	long id;
};


#endif

