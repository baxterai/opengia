/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAdraw.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 2g14a 05-November-2014
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Draws GIA nodes in GIA network/tree
 *
 *******************************************************************************/



#ifndef HEADER_GIA_DRAW
#define HEADER_GIA_DRAW

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "LDreferenceClass.h"
#include "XMLparserClass.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "GIAconditionNodeClass.h"



#ifdef GIA_DRAW_USE_PATENT
	//#define GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES	//switched off for patent diagrams
	//#define GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS	//switched on for patent diagrams
	#define GIA_DRAW_USE_SUPPORT_PRINT_OF_DOCUMENT_TO_GRAY_SCALE		//switched on for patent diagrams
#else
	#define GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES		//switched off for patent diagrams
	#define GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS	//switched on for patent diagrams
	//#define GIA_DRAW_USE_SUPPORT_PRINT_OF_DOCUMENT_TO_GRAY_SCALE		//switched on for patent diagrams
#endif

#define GIA_USE_SVG_ELLIPTICAL_BOXES (true)

#define MAX_GIA_TREE_DEPTH (100000)
#define DRAW_X_INITIAL_OFFSET (150)
#define DRAW_Y_INITIAL_OFFSET (150)

#define GIA_DRAW_THICKNESS_NORMAL (1)
#define GIA_DRAW_THICKNESS_THICK (2)

#define GIA_DRAW_USE_CONNECTION_TYPE_NAME_TEXT (true)


/*
#define GIA_DRAW_CONDITION_NODE_COLOUR (DAT_FILE_COLOUR_RED)				//this was red in the original spec
#define GIA_DRAW_CONDITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_RED)			//this was red in the original spec
#define GIA_DRAW_CONDITION_CONNECTION_DEFINITION_COLOUR (DAT_FILE_COLOUR_ORANGE)	//colour not defined in original GIA spec
//#define GIA_DRAW_CONDITION_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//Not used	//this was red in the original GIA spec		[uses whatever colour the definition is already, eg cyan for entity substance]
#define GIA_DRAW_CONDITION_DEFINITION_TIME_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//this was red in the original spec
*/

#ifdef GIA_DRAW_USE_SUPPORT_PRINT_OF_DOCUMENT_TO_GRAY_SCALE
	#define GIA_DRAW_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_BLUE)	//this could be black
	#define GIA_DRAW_CONCEPT_NODE_COLOUR (DAT_FILE_COLOUR_WHITE)
#else
	#define GIA_DRAW_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_BLUE)			//this was black in the original spec
	#define GIA_DRAW_CONCEPT_NODE_COLOUR (DAT_FILE_COLOUR_BLUE)				//this was blue in the original spec
#endif
#ifdef GIA_DISABLE_ALIAS_ENTITY_MERGING
	#define GIA_DRAW_DEFINITION_MARK_AS_ALIAS_CONNECTION_COLOUR (DAT_FILE_COLOUR_DARKBLUE)
#endif

#define GIA_DRAW_ACTION_NODE_COLOUR (DAT_FILE_COLOUR_GREEN)				//this was green in the original spec
#define GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_GREEN)			//this was black in the original spec
#ifdef GIA_DRAW_USE_CONNECTION_TYPE_NAME_TEXT == (true)
	#define GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_GREEN)			//this was black in the original spec
#else
	#define GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_YELLOW)
#endif
#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
	#define GIA_DRAW_ACTION_SPECIAL_POSSESSIVE_NODE_COLOUR (DAT_FILE_COLOUR_WHITE)			//new 2c1a
#endif

#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES
	#define GIA_DRAW_ACTION_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_BROWN)			//this was dark green to original GIA specA)
#else
	#define GIA_DRAW_ACTION_DEFINITION_NODE_COLOUR (GIA_DRAW_CONCEPT_NODE_COLOUR)
#endif
#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS
	#define GIA_DRAW_ACTION_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_BROWN)		//colour not defined in original GIA spec
#else
	#define GIA_DRAW_ACTION_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#endif

#define GIA_DRAW_CONDITION_NODE_COLOUR (DAT_FILE_COLOUR_RED)				//this was green in the original spec
#define GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_RED)			//this was black in the original spec
#ifdef GIA_DRAW_USE_CONNECTION_TYPE_NAME_TEXT == (true)
	#define GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_RED)			//this was black in the original spec
#else
	#define GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_YELLOW)
#endif
#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES
	#define GIA_DRAW_CONDITION_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//this was dark green to original GIA spec
#else
	#define GIA_DRAW_CONDITION_DEFINITION_NODE_COLOUR (GIA_DRAW_CONCEPT_NODE_COLOUR)		//this was dark green to original GIA spec
#endif
#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS
	#define GIA_DRAW_CONDITION_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_ORANGE)	//colour not defined in original GIA spec
#else
	#define GIA_DRAW_CONDITION_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#endif

#define GIA_DRAW_CONDITION_TIME_CONNECTION_COLOUR (DAT_FILE_COLOUR_RED)	//colour not defined in original GIA spec
#define GIA_DRAW_CONDITION_TIME_NODE_COLOUR (DAT_FILE_COLOUR_RED)		//this was red in the original spec
//#define GIA_DRAW_CONDITION_DEFINITION_TIME_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//colour not defined in original GIA spec

//#define GIA_DRAW_CONDITION_TIME_STATE_NODE_COLOUR (DAT_FILE_COLOUR_DARKRED)
#define GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR (DAT_FILE_COLOUR_AQUA)

#define GIA_DRAW_PROPERTY_CONNECTION_COLOUR (DAT_FILE_COLOUR_CYAN)			//this was magenta/purple in the original spec
#define GIA_DRAW_SUBSTANCE_NODE_COLOUR (DAT_FILE_COLOUR_CYAN)
				//this was cyan(?) in the original spec

#define GIA_DRAW_SUBSTANCE_CONCEPT_NODE_COLOUR (GIA_DRAW_CONCEPT_NODE_COLOUR)
#define GIA_DRAW_ACTION_CONCEPT_NODE_COLOUR (GIA_DRAW_ACTION_DEFINITION_NODE_COLOUR)

#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES
	#define GIA_DRAW_SUBSTANCE_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#else
	#define GIA_DRAW_SUBSTANCE_DEFINITION_NODE_COLOUR (GIA_DRAW_CONCEPT_NODE_COLOUR)
#endif
#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS
	#define GIA_DRAW_SUBSTANCE_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)	//colour not defined in original GIA spec
#else
	#define GIA_DRAW_SUBSTANCE_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#endif

#define GIA_DRAW_SUBSTANCE_QUANTITY_NODE_COLOUR (DAT_FILE_COLOUR_PURPLE)
#define GIA_DRAW_SUBSTANCE_MEASURE_NODE_COLOUR (DAT_FILE_COLOUR_LIGHTGREY)

#define GIA_DRAW_QUERY_QUESTION_NODE_COLOUR (DAT_FILE_COLOUR_YELLOW)
#define GIA_DRAW_QUERY_ANSWER_NODE_COLOUR (DAT_FILE_COLOUR_YELLOW)
#define GIA_DRAW_QUERY_ANSWER_CONTEXT_NODE_COLOUR (DAT_FILE_COLOUR_DARKGREY)

#define GIA_DRAW_CONDITION_NODE_HEIGHT (5)
#define GIA_DRAW_CONDITION_NODE_WIDTH (20)
#define GIA_DRAW_ACTION_NODE_HEIGHT (5)
#define GIA_DRAW_ACTION_NODE_WIDTH (20)
#define GIA_DRAW_BASICENTITY_NODE_HEIGHT (5)
#define GIA_DRAW_BASICENTITY_NODE_WIDTH (20)
#define GIA_DRAW_SUBSTANCE_NODE_HEIGHT (5)
#define GIA_DRAW_SUBSTANCE_NODE_WIDTH (20)



#define DRAW_Y_SPACE_BETWEEN_ENTITIES (0)				//OLD: should really be 1 for initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_ENTITIES (300)
#define DRAW_Y_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE (50)			//OLD: should really be 1 for initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE (0)

#define DRAW_Y_SPACE_BETWEEN_ACTION_NODES (0)
#define DRAW_X_SPACE_BETWEEN_ACTION_NODES (100)		//should not be used during initialiseForPrint
#define DRAW_Y_SPACE_BETWEEN_ACTIONS_OF_SAME_NODE (100)
#define DRAW_X_SPACE_BETWEEN_ACTIONS_OF_SAME_NODE (0)		//should not be used during initialiseForPrint
//#define DRAW_Y_SPACE_BETWEEN_ACTION_DEFINITION_NODES (30)	//should not be used during initialiseForPrint
//#define DRAW_X_SPACE_BETWEEN_ACTION_DEFINITION_NODES (-50)	//should not be used during initialiseForPrint

#define DRAW_Y_SPACE_BETWEEN_CONDITION_NODES (20)		//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_CONDITION_NODES (30)		//should not be used during initialiseForPrint
#define DRAW_Y_SPACE_BETWEEN_CONDITIONS_OF_SAME_NODE (15)	//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_CONDITIONS_OF_SAME_NODE (0)	//should not be used during initialiseForPrint
//#define DRAW_Y_SPACE_BETWEEN_CONDITION_DEFINITION_NODES (30)		//should not be used during initialiseForPrint
//#define DRAW_X_SPACE_BETWEEN_CONDITION_DEFINITION_NODES (-50)	//should not be used during initialiseForPrint

#define DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT (0)

#define DRAW_Y_SPACE_BETWEEN_SUBSTANCE_NODES (50)			//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_SUBSTANCE_NODES (30)
#define DRAW_Y_SPACE_BETWEEN_SUBSTANCES_OF_SAME_NODE (15)	//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_SUBSTANCES_OF_SAME_NODE (0)	//should not be used during initialiseForPrint
//#define DRAW_Y_SPACE_BETWEEN_SUBSTANCE_DEFINITION_NODES (30)	//should not be used during initialiseForPrint
//#define DRAW_X_SPACE_BETWEEN_SUBSTANCE_DEFINITION_NODES (-50)	//should not be used during initialiseForPrint

#define DRAW_Y_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES (30)	//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES (-50)	//should not be used during initialiseForPrint

#define SVG_SCALE_FACTOR (1)
#define SVG_TEXT_SCALE_FACTOR (5)

#define DRAW_CONNECTION_Z (0.0)
#define GIA_FILE_TEXT_BOX_OUTLINE_WIDTH_SVG (1.0)

#define INITIALISE_FOR_PRINT (0)
#define PRINT_TO_SVG_AND_CREATE_LDR_REFERENCES (1)
#define DRAW_INITIALISE (INITIALISE_FOR_PRINT)
#define DRAW_PRINT (PRINT_TO_SVG_AND_CREATE_LDR_REFERENCES)
#define DRAW_CREATE_LDR_REFERENCES (0)
#define DRAW_CREATE_SVG_REFERENCES (1)
#define DRAW_CREATE_LDR_OR_SVG_REFERENCES (2)

#define GIA_OUTPUT_Z_POSITION_CONNECTIONS (0.6)
#define GIA_OUTPUT_Z_POSITION_NODES (0.4)
#define GIA_OUTPUT_Z_POSITION_TEXT (0.2)


#define GIA_DRAW_UNDEFINED_CONNECTION_COLOUR (INT_DEFAULT_VALUE)

static int entityVectorConnectionDrawPosYinitialArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {DRAW_Y_SPACE_BETWEEN_ACTION_NODES, -DRAW_Y_SPACE_BETWEEN_ACTION_NODES, DRAW_Y_SPACE_BETWEEN_CONDITION_NODES, -DRAW_Y_SPACE_BETWEEN_CONDITION_NODES, DRAW_Y_SPACE_BETWEEN_SUBSTANCE_NODES, -DRAW_Y_SPACE_BETWEEN_SUBSTANCE_NODES, -DRAW_Y_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES, -DRAW_Y_SPACE_BETWEEN_ACTION_NODES, DRAW_Y_SPACE_BETWEEN_ACTION_NODES, -DRAW_Y_SPACE_BETWEEN_CONDITION_NODES, DRAW_Y_SPACE_BETWEEN_CONDITION_NODES, -DRAW_Y_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES};
static int entityVectorConnectionDrawPosXinitialArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {DRAW_X_SPACE_BETWEEN_ACTION_NODES, -DRAW_X_SPACE_BETWEEN_ACTION_NODES, DRAW_X_SPACE_BETWEEN_CONDITION_NODES, -DRAW_X_SPACE_BETWEEN_CONDITION_NODES, DRAW_X_SPACE_BETWEEN_SUBSTANCE_NODES, -DRAW_X_SPACE_BETWEEN_SUBSTANCE_NODES, -DRAW_X_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_X_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_X_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES, -DRAW_X_SPACE_BETWEEN_ACTION_NODES, DRAW_X_SPACE_BETWEEN_ACTION_NODES, -DRAW_X_SPACE_BETWEEN_CONDITION_NODES, DRAW_X_SPACE_BETWEEN_CONDITION_NODES, -DRAW_X_SPACE_BETWEEN_INSTANCE_DEFINITION_NODES};
static int entityVectorConnectionDrawPosYspacingArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {DRAW_Y_SPACE_BETWEEN_ACTIONS_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_ACTIONS_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_CONDITIONS_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_CONDITIONS_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_SUBSTANCES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_SUBSTANCES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_ENTITIES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_SUBSTANCES_OF_SAME_NODE, DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT, DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT, DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT, DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT, DRAW_Y_SPACE_BETWEEN_BASICCONNECTION_OF_SAME_NODE_IRRELEVANT};
#ifdef GIA_DRAW_PRINT_ENTITY_NODES_IN_ORDER_OF_SENTENCE_INDEX_ADVANCED
static int entityVectorConnectionDrawColourNameArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_PROPERTY_CONNECTION_COLOUR, GIA_DRAW_PROPERTY_CONNECTION_COLOUR, GIA_DRAW_DEFINITION_CONNECTION_COLOUR, GIA_DRAW_DEFINITION_CONNECTION_COLOUR, DAT_FILE_COLOUR_MAGENTA, GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR, DAT_FILE_COLOUR_MAGENTA};	//instance colour is dynamicallyDetermined
static bool entityVectorConnectionDrawConnectionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true};
#else
static int entityVectorConnectionDrawColourNameArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_PROPERTY_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_DEFINITION_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR};	//instance colour is dynamicallyDetermined
static bool entityVectorConnectionDrawConnectionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {false, false, false, false, false, true, false, true, false, true, true, true, true, true};
#endif
//temp test;
//static int entityVectorConnectionDrawColourNameArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_PROPERTY_CONNECTION_COLOUR, GIA_DRAW_PROPERTY_CONNECTION_COLOUR, GIA_DRAW_DEFINITION_CONNECTION_COLOUR, GIA_DRAW_DEFINITION_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR, GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_SUBJECT_CONNECTION_COLOUR, GIA_DRAW_CONDITION_OBJECT_CONNECTION_COLOUR, GIA_DRAW_UNDEFINED_CONNECTION_COLOUR};	//instance colour is dynamicallyDetermined
//static bool entityVectorConnectionDrawConnectionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, true, true, true, true, true, true, true, false, true, true, true, true, true};


void printGIAnetworkNodes(vector<GIAentityNode*> *entityNodesActiveListComplete, int width, int height, string outputFileNameLDR, string outputFileNameSVG, string outputFileNamePPM, bool display, bool useOutputLDRfile, bool useOutputPPMfile, bool useOutputSVGfile, int maxNumberSentences);

void determineBasicPrintPositionsOfAllNodes(vector<GIAentityNode*> *entityNodesActiveListComplete, bool printType[], Reference * firstReferenceInPrintList, XMLparserTag ** currentTag, int maxNumberSentences);

void initiateMaxXAtParticularY();
Reference * initialiseEntityNodeForPrinting(GIAentityNode * entityNode, int y, int x, bool printType[], Reference * currentReferenceInPrintList, XMLparserTag ** currentTag, int sentenceIndex, bool thisIsDefinitionAndPreviousNodeWasInstance);
	Reference * initialiseEntityConnectionForPrinting(vec * pos1, GIAentityConnection * entityConnection, Reference * currentReferenceInPrintList, bool printType[], string connectionName, int entityConnectionColour, XMLparserTag ** currentTag);
	Reference * initialiseTimeConditionNodeForPrinting(GIAtimeConditionNode * timeConditionNode, int y, int x, bool printType[], Reference * currentReferenceInPrintList, XMLparserTag ** currentTag);

Reference * createReferenceConnectionWithText(Reference * currentReferenceInPrintList, vec * pos1, vec * pos2, int colour, XMLparserTag ** currentTag, string connectionTypeName, bool printType[]);
	Reference * createReferenceConnection(Reference * currentReferenceInPrintList, vec * pos1, vec * pos2, int colour, XMLparserTag ** currentTag, bool printType[]);
Reference * createBox(Reference * currentReferenceInPrintList, vec * vect, double width, double height, int colour, string * text, XMLparserTag ** currentTag, int thickness, bool printType[]);





/*
#define GIA_OUTPUT_Z_POSITION_FILE_CONNECTIONS (0.6)
#define GIA_OUTPUT_Z_POSITION_FILE_CONTAINER_BIG_BOX (0.5)
#define GIA_OUTPUT_Z_POSITION_FUNCTION_CONNECTIONS (0.4)
#define GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_BOX (0.3)
#define GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_TEXT (0.2)

#define GIA_FILE_OR_FUNCTION_TEXT_BOX_SCALE_FACTOR_X (0.4)
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_LDR (0.05)
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG (0.03)
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG_B (0.067)
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_X_SPACING_FRACTION_SVG (0.8)
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_SVG (0.1)

#define GIA_FILE_FUNCTIONS_DISABLED_VECTOROBJECTS_SCALE_FACTOR (500)
#define GIA_FILE_FUNCTIONS_ENABLED_VECTOROBJECTS_SCALE_FACTOR (200)
#define GIA_FILE_MAX_TEXT_LENGTH (20)
#define GIA_FILE_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH (1.25)
#define GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION (0.9)
#define GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION (0.3)
#define GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION (0.7)
#define GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION (1.0)
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X (5.0)
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X_SPACING_FRACTION_B (0.65)
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_B (0.9)
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_C (0.4)
#define GIA_FILE_TEXT_BOX_OUTLINE_WIDTH_SVG (0.3)

#define GIA_FUNCTION_VECTOROBJECTS_SCALE_FACTOR (50)
#define GIA_FUNCTION_MAX_TEXT_LENGTH (25)
#define GIA_FUNCTION_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH (1.00)
#define GIA_FUNCTION_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION (0.7)
#define GIA_FUNCTION_TEXT_BOX_OUTLINE_WIDTH_SVG (0.1)

#define GIA_LAYER_0_COLOUR (6)
#define GIA_LAYER_1_COLOUR (1)
#define GIA_LAYER_2_COLOUR (2)
#define GIA_LAYER_3_COLOUR (3)
#define GIA_LAYER_4_COLOUR (4)
#define GIA_LAYER_5_COLOUR (22)
#define GIA_LAYER_6_COLOUR (25)
#define GIA_LAYER_7_COLOUR (14)
#define GIA_LAYER_8_COLOUR (5)
#define GIA_LAYER_9_COLOUR (7)
#define GIA_LAYER_10_COLOUR (8)
#define GIA_LAYER_11_COLOUR (0)
#define GIA_LAYER_12_COLOUR (15)

#define GIA_FUNCTION_CONNECTION_HIGHLIGHT_COLOUR (5)
#define GIA_FUNCTION_BOX_HIGHLIGHT_COLOUR (5)
*/

/*
#define GIA_OUTPUT_Z_POSITION_FILE_CONNECTIONS_NAME "GIA_OUTPUT_Z_POSITION_FILE_CONNECTIONS"
#define GIA_OUTPUT_Z_POSITION_FILE_CONTAINER_BIG_BOX_NAME "GIA_OUTPUT_Z_POSITION_FILE_CONTAINER_BIG_BOX"
#define GIA_OUTPUT_Z_POSITION_FUNCTION_CONNECTIONS_NAME "GIA_OUTPUT_Z_POSITION_FUNCTION_CONNECTIONS"
#define GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_BOX_NAME "GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_BOX"
#define GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_TEXT_NAME "GIA_OUTPUT_Z_POSITION_FILE_AND_FUNCTION_TEXT"

#define GIA_FILE_OR_FUNCTION_TEXT_BOX_SCALE_FACTOR_X_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_SCALE_FACTOR_X"
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_LDR_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_LDR"
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG"
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG_B_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_TEXT_SCALE_FACTOR_Y_SVG_B"
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_X_SPACING_FRACTION_SVG_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_X_SPACING_FRACTION_SVG"
#define GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_SVG_NAME "GIA_FILE_OR_FUNCTION_TEXT_BOX_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_SVG"

#define GIA_FILE_FUNCTIONS_DISABLED_VECTOROBJECTS_SCALE_FACTOR_NAME "GIA_FILE_FUNCTIONS_DISABLED_VECTOROBJECTS_SCALE_FACTOR"
#define GIA_FILE_FUNCTIONS_ENABLED_VECTOROBJECTS_SCALE_FACTOR_NAME "GIA_FILE_FUNCTIONS_ENABLED_VECTOROBJECTS_SCALE_FACTOR"
#define GIA_FILE_MAX_TEXT_LENGTH_NAME "GIA_FILE_MAX_TEXT_LENGTH"
#define GIA_FILE_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH_NAME "GIA_FILE_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH"
#define GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION_NAME "GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION"
#define GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_NAME "GIA_FILE_FUNCTIONS_DISABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION"
#define GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION_NAME "GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_X_SPACING_FRACTION"
#define GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_NAME "GIA_FILE_FUNCTIONS_ENABLED_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION"
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X_NAME "GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X"
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X_SPACING_FRACTION_B_NAME "GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_X_SPACING_FRACTION_B"
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_B_NAME "GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_B"
#define GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_C_NAME "GIA_FILE_FUNCTIONS_ENABLED_LARGE_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_C"
#define GIA_FILE_TEXT_BOX_OUTLINE_WIDTH_SVG_NAME "GIA_FILE_TEXT_BOX_OUTLINE_WIDTH_SVG"

#define GIA_FUNCTION_VECTOROBJECTS_SCALE_FACTOR_NAME "GIA_FUNCTION_VECTOROBJECTS_SCALE_FACTOR"
#define GIA_FUNCTION_MAX_TEXT_LENGTH_NAME "GIA_FUNCTION_MAX_TEXT_LENGTH"
#define GIA_FUNCTION_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH_NAME "GIA_FUNCTION_TEXT_BOX_PADDING_FRACTION_OF_TEXT_LENGTH"
#define GIA_FUNCTION_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION_NAME "GIA_FUNCTION_TEXT_BOX_SCALE_FACTOR_Y_SPACING_FRACTION"
#define GIA_FUNCTION_TEXT_BOX_OUTLINE_WIDTH_SVG_NAME "GIA_FUNCTION_TEXT_BOX_OUTLINE_WIDTH_SVG"

#define GIA_LAYER_0_COLOUR_NAME "GIA_LAYER_0_COLOUR"
#define GIA_LAYER_1_COLOUR_NAME "GIA_LAYER_1_COLOUR"
#define GIA_LAYER_2_COLOUR_NAME "GIA_LAYER_2_COLOUR"
#define GIA_LAYER_3_COLOUR_NAME "GIA_LAYER_3_COLOUR"
#define GIA_LAYER_4_COLOUR_NAME "GIA_LAYER_4_COLOUR"
#define GIA_LAYER_5_COLOUR_NAME "GIA_LAYER_5_COLOUR"
#define GIA_LAYER_6_COLOUR_NAME "GIA_LAYER_6_COLOUR"
#define GIA_LAYER_7_COLOUR_NAME "GIA_LAYER_7_COLOUR"
#define GIA_LAYER_8_COLOUR_NAME "GIA_LAYER_8_COLOUR"
#define GIA_LAYER_9_COLOUR_NAME "GIA_LAYER_9_COLOUR"
#define GIA_LAYER_10_COLOUR_NAME "GIA_LAYER_10_COLOUR"
#define GIA_LAYER_11_COLOUR_NAME "GIA_LAYER_11_COLOUR"
#define GIA_LAYER_12_COLOUR_NAME "GIA_LAYER_12_COLOUR"

#define GIA_FUNCTION_CONNECTION_HIGHLIGHT_COLOUR_NAME "GIA_FUNCTION_CONNECTION_HIGHLIGHT_COLOUR"
#define GIA_FUNCTION_BOX_HIGHLIGHT_COLOUR_NAME "GIA_FUNCTION_BOX_HIGHLIGHT_COLOUR"
*/




#endif
