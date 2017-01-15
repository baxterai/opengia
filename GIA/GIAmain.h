/*******************************************************************************
 *
 * File Name: GIAmain.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1g6c 12-Feb-2012
 * Requirements: requires text parsed by RelEx (available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_GIA_MAIN
#define HEADER_GIA_MAIN

#include "GIAEntityNodeClass.h"

#define GIA_DEBUG_PRINT_QUERY_SEMANTIC_NETWORK

#define GIA_TM_STRUCT_YEAR_OFFSET 1900

#define GIA_COMPILE_FOR_BAI_APP_SERVER_RELEASE
//#define GIA_DO_NOT_PRINT_RESULTS

#ifndef GIA_COMPILE_FOR_BAI_APP_SERVER_RELEASE
	#define GIA_COMPILE_PRINT_INEXACT_ANSWER_AMBIENT_CONTEXT
#endif

//#define GIA_XML_DEBUG_TEST_WRITE_READ_WRITE

#define GIA_RELEX_EXECUTABLE_NAME "execute-relex.sh"
//OLD: #define GIA_RELEX_EXECUTABLE_RELATIVE_PATH_NAME "/relex-1.3.0/"	//gets added to executable path name

int main(int argc,char **argv);
bool parseRelexFile(string inputRelexXMLFileName, vector<GIAEntityNode*> *entityNodesCompleteList, unordered_map<string, GIAEntityNode*> *conceptEntityNodesList, vector<GIAEntityNode*> *propertyEntityNodesList, vector<GIAEntityNode*> *actionEntityNodesList, vector<GIAEntityNode*> *conditionEntityNodesList, vector<GIATimeConditionNode*> * timeConditionNodesList, vector<long> * timeConditionNumbersList, bool isQuery);
void executeRelex(string inputPlainTXTFileName, string inputRelexXMLFileName);


#endif
