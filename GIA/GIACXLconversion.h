/*******************************************************************************
 *
 * File Name: GIAXMLconversion.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1j4a 28-Apr-2012
 * Description: Converts GIA network nodes into an XML, or converts an XML file into GIA network nodes
 *
 *******************************************************************************/
 

#ifndef HEADER_GIA_CXL_CONVERSION
#define HEADER_GIA_CXL_CONVERSION



#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "XMLParserClass.h"
#include "GIAEntityNodeClass.h"
#include "GIAConditionNodeClass.h"

#ifdef GIA_CMAP_CONVERSION_SANITISED
	#define GIA_CMAP_CONVERSION_SANITISED_DO_NOT_ADD_REDUNDANT_CONCEPT_NODES
	/*
	#ifdef GIA_CMAP_CONVERSION_SANITISED_DO_NOT_ADD_REDUNDANT_CONCEPT_NODES
		//#define GIA_CMAP_CONVERSION_SANITISED_DO_NOT_ADD_REDUNDANT_CONCEPT_NODES_OLD
	#endif
	*/
	#define GIA_CMAP_CONVERSION_SANITISED_DO_NOT_ADD_TIME_CONDITION_NODES
#endif
#define GIA_CXL_EXPAND_RATIO (3)

#define GIA_SEMANTIC_NET_CXL_REORDER_CONCEPT_IDS_UPON_CXL_WRITE_INSTEAD_OF_CXL_READ		//required for time nodes

/*CXL*/

#define MAX_ATTRIBUTE_VALUE_SIZE 200

#define NET_CXL_TAG_cmap ((string)"cmap")
#define NET_CXL_ATTRIBUTE_xmlns ((string)"xmlns")
#define NET_CXL_ATTRIBUTE_xmlns_DEFAULT_VALUE ((string)"http://cmap.ihmc.us/xml/cmap/")
#define NET_CXL_ATTRIBUTE_xmlnsdc ((string)"xmlns:dc")
#define NET_CXL_ATTRIBUTE_xmlnsdc_DEFAULT_VALUE ((string)"http://purl.org/dc/elements/1.1/")
#define NET_CXL_TAG_map ((string)"map")

#define NET_CXL_TAG_conceptList ((string)"concept-list")
#define NET_CXL_TAG_linkingPhraseList ((string)"linking-phrase-list")
#define NET_CXL_TAG_concept ((string)"concept")
#define NET_CXL_TAG_linkingPhrase ((string)"linking-phrase")
#define NET_CXL_ATTRIBUTE_id ((string)"id")
#define NET_CXL_ATTRIBUTE_label ((string)"label")

#define NET_CXL_TAG_connectionList ((string)"connection-list")
#define NET_CXL_TAG_connection ((string)"connection")
#define NET_CXL_TAG_fromid ((string)"from-id")
#define NET_CXL_TAG_toid ((string)"to-id")

#define NET_CXL_TAG_conceptAppearanceList ((string)"concept-appearance-list")
#define NET_CXL_TAG_linkingPhraseAppearanceList ((string)"linking-phrase-appearance-list")
#define NET_CXL_TAG_conceptAppearance ((string)"concept-appearance")
#define NET_CXL_TAG_linkingPhraseAppearance ((string)"linking-phrase-appearance")
#define NET_CXL_ATTRIBUTE_x ((string)"x")
#define NET_CXL_ATTRIBUTE_y ((string)"y")


bool writeCMapToolsCXLFileOptimised(string xmlFileName, vector<GIAEntityNode*> *entityNodesCompleteList, unordered_map<string, GIAEntityNode*> *conceptEntityNodesListMap, vector<GIAEntityNode*> *propertyEntityNodesList, vector<GIAEntityNode*> *actionEntityNodesList, vector<GIAEntityNode*> *conditionEntityNodesList);
	bool writeCMapToolsCXLFile(string xmlFileName, vector<GIAEntityNode*> *entityNodesCompleteList, vector<GIAEntityNode*> *conceptEntityNodesList, vector<GIAEntityNode*> *propertyEntityNodesList, vector<GIAEntityNode*> *actionEntityNodesList, vector<GIAEntityNode*> *conditionEntityNodesList);
		bool generateCXLEntityNodeTagList(XMLParserTag * firstTagInMap, vector<GIAEntityNode*> *entityNodesCompleteList, vector<GIAEntityNode*> *conceptEntityNodesList, vector<GIAEntityNode*> *propertyEntityNodesList, vector<GIAEntityNode*> *actionEntityNodesList, vector<GIAEntityNode*> *conditionEntityNodesList, long * currentEntityNodeIDInConceptEntityNodesList, bool conceptOrLinkingPhraseList, bool appearanceList);
			XMLParserTag * addToCXLEntityNodeTagList(XMLParserTag * currentTagL1, vector<GIAEntityNode*> *entityNodesList, long * currentEntityNodeIDInConceptEntityNodesList, bool conceptOrLinkingPhraseList, bool appearanceList);
				XMLParserTag * generateCXLEntityNodeTag(XMLParserTag * currentTagL1, string entityName, long entityID, int printXIndex, int printYIndex, bool conceptOrLinkingPhraseList, bool appearanceList);
		bool generateCXLConnectionNodeTagList(XMLParserTag * firstTagInMap, vector<GIAEntityNode*> *entityNodesCompleteList, vector<GIAEntityNode*> *conceptEntityNodesList, vector<GIAEntityNode*> *propertyEntityNodesList, vector<GIAEntityNode*> *actionEntityNodesList, vector<GIAEntityNode*> *conditionEntityNodesList, long * currentCmapNodeIDInCmapNodeList, XMLParserTag * firstTagInLinkingPhraseList, XMLParserTag * firstTagInLinkingPhraseAppearanceList);
			XMLParserTag * addToCXLConnectionNodeTagList(XMLParserTag * currentTagL1, vector<GIAEntityNode*> *entityNodesList, long * currentCmapNodeIDInCmapNodeList, XMLParserTag * firstTagL1, XMLParserTag ** currentTagInLinkingPhraseList, XMLParserTag ** currentTagInLinkingPhraseAppearanceList, XMLParserTag * firstTagInConnectionsList);
				XMLParserTag * generateCXLConnectionNodeTagAndLinkingPhraseTags(XMLParserTag * currentTagL1, GIAEntityNode * entity1, GIAEntityNode * entity2, string connectionTypeName, long * currentCmapNodeIDInCmapNodeList, XMLParserTag ** currentTagInLinkingPhraseList, XMLParserTag ** currentTagInLinkingPhraseAppearanceList, XMLParserTag * firstTagInConnectionsList, bool alreadyMadeLinkingPhrase);
					XMLParserTag * generateCXLConnectionNodeTag(XMLParserTag * currentTagL1, long fromID, long toID);

		#ifdef GIA_SEMANTIC_NET_CXL_REORDER_CONCEPT_IDS_UPON_CXL_WRITE_INSTEAD_OF_CXL_READ
		void resetIDsForNodeList2(vector<GIAEntityNode*> *entityNodesList, long * currentEntityNodeIDInConceptEntityNodesList);
		//void resetIDsForNodeMap(unordered_map<string, GIAEntityNode*> *entityNodesMap, long * currentEntityNodeIDInConceptEntityNodesList);	
		#endif

#ifdef GIA_CMAP_CONVERSION_SANITISED_DO_NOT_ADD_REDUNDANT_CONCEPT_NODES	
bool checkIfPassedRedundantConceptNodeRemoval(GIAEntityNode * currentEntity);
#endif
		
#endif
