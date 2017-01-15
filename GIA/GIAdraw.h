/*******************************************************************************
 *
 * File Name: GIAdraw.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2011 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1d4b 01-Nov-2011
 * Requirements: requires text parsed by RelEx (available in .CFF format <relations>)
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
#include "GIAEntityNodeClass.h"
#include "GIAConditionNodeClass.h"

//#define GIA_DRAW_DEBUG

//#define GIA_DRAW_USE_PATENT
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

#define MAX_GIA_TREE_DEPTH (10000)
#define DRAW_X_INITIAL_OFFSET (150)
#define DRAW_Y_INITIAL_OFFSET (150)

#define GIA_DRAW_THICKNESS_NORMAL (1)
#define GIA_DRAW_THICKNESS_THICK (2)

#define GIA_DRAW_USE_CONNECTION_TYPE_NAME_TEXT (true)

/*
#define GIA_DRAW_CONDITION_NODE_COLOUR (DAT_FILE_COLOUR_RED)				//this was red in the original spec	
#define GIA_DRAW_CONDITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_RED)			//this was red in the original spec
#define GIA_DRAW_CONDITION_CONNECTION_DEFINITION_COLOUR (DAT_FILE_COLOUR_ORANGE)	//colour not defined in original GIA spec	
//#define GIA_DRAW_CONDITION_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//Not used	//this was red in the original GIA spec		[uses whatever colour the definition is already, eg cyan for entity property]
#define GIA_DRAW_CONDITION_DEFINITION_TIME_NODE_COLOUR (DAT_FILE_COLOUR_ORANGE)		//this was red in the original spec			
*/

#ifdef GIA_DRAW_USE_SUPPORT_PRINT_OF_DOCUMENT_TO_GRAY_SCALE
	#define GIA_DRAW_CONCEPT_CONNECTION_COLOUR (DAT_FILE_COLOUR_BLUE)	//this could be black			
	#define GIA_DRAW_CONCEPT_NODE_COLOUR (DAT_FILE_COLOUR_WHITE)					
#else
	#define GIA_DRAW_CONCEPT_CONNECTION_COLOUR (DAT_FILE_COLOUR_BLUE)			//this was black in the original spec
	#define GIA_DRAW_CONCEPT_NODE_COLOUR (DAT_FILE_COLOUR_BLUE)				//this was blue in the original spec	
#endif

#define GIA_DRAW_ACTION_NODE_COLOUR (DAT_FILE_COLOUR_GREEN)				//this was green in the original spec	
#define GIA_DRAW_ACTION_SUBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_GREEN)			//this was black in the original spec	
#ifdef GIA_DRAW_USE_CONNECTION_TYPE_NAME_TEXT == (true)
	#define GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_GREEN)			//this was black in the original spec	
#else
	#define GIA_DRAW_ACTION_OBJECT_CONNECTION_COLOUR (DAT_FILE_COLOUR_YELLOW)
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

#define GIA_DRAW_CONDITION_TIME_STATE_NODE_COLOUR (DAT_FILE_COLOUR_DARKRED)
#define GIA_DRAW_PROPERTY_QUALITY_NODE_COLOUR (DAT_FILE_COLOUR_AQUA)

#define GIA_DRAW_PROPERTY_CONNECTION_COLOUR (DAT_FILE_COLOUR_CYAN)			//this was magenta/purple in the original spec	
#define GIA_DRAW_PROPERTY_NODE_COLOUR (DAT_FILE_COLOUR_CYAN)
				//this was cyan(?) in the original spec	

#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_NODES
	#define GIA_DRAW_PROPERTY_DEFINITION_NODE_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#else
	#define GIA_DRAW_PROPERTY_DEFINITION_NODE_COLOUR (GIA_DRAW_CONCEPT_NODE_COLOUR)
#endif	
#ifdef GIA_DRAW_USE_UNIQUE_COLOURS_FOR_ENTITY_DEFINITION_CONNECTIONS
	#define GIA_DRAW_PROPERTY_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)	//colour not defined in original GIA spec	
#else
	#define GIA_DRAW_PROPERTY_DEFINITION_CONNECTION_COLOUR (DAT_FILE_COLOUR_MAGENTA)
#endif		

#define GIA_DRAW_PROPERTY_QUANTITY_NODE_COLOUR (DAT_FILE_COLOUR_PURPLE)
#define GIA_DRAW_PROPERTY_MEASURE_NODE_COLOUR (DAT_FILE_COLOUR_LIGHTGREY)

#define GIA_DRAW_QUERY_QUESTION_NODE_COLOUR (DAT_FILE_COLOUR_YELLOW)
#define GIA_DRAW_QUERY_ANSWER_NODE_COLOUR (DAT_FILE_COLOUR_YELLOW)
#define GIA_DRAW_QUERY_ANSWER_CONTEXT_NODE_COLOUR (DAT_FILE_COLOUR_DARKGREY)

#define GIA_DRAW_CONDITION_NODE_HEIGHT (5)
#define GIA_DRAW_CONDITION_NODE_WIDTH (20)
#define GIA_DRAW_ACTION_NODE_HEIGHT (5)
#define GIA_DRAW_ACTION_NODE_WIDTH (20)
#define GIA_DRAW_BASICENTITY_NODE_HEIGHT (5)
#define GIA_DRAW_BASICENTITY_NODE_WIDTH (20)
#define GIA_DRAW_PROPERTY_NODE_HEIGHT (5)
#define GIA_DRAW_PROPERTY_NODE_WIDTH (20)



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

#define DRAW_Y_SPACE_BETWEEN_PROPERTY_NODES (50)			//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_PROPERTY_NODES (30)	
#define DRAW_Y_SPACE_BETWEEN_PROPERTIES_OF_SAME_NODE (15)	//should not be used during initialiseForPrint
#define DRAW_X_SPACE_BETWEEN_PROPERTIES_OF_SAME_NODE (0)	//should not be used during initialiseForPrint
//#define DRAW_Y_SPACE_BETWEEN_PROPERTY_DEFINITION_NODES (30)	//should not be used during initialiseForPrint
//#define DRAW_X_SPACE_BETWEEN_PROPERTY_DEFINITION_NODES (-50)	//should not be used during initialiseForPrint

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

#define GIA_OUTPUT_Z_POSITION_CONNECTIONS (0.6)
#define GIA_OUTPUT_Z_POSITION_NODES (0.4)
#define GIA_OUTPUT_Z_POSITION_TEXT (0.2)


void printGIAnetworkNodes(vector<GIAEntityNode*> *entityNodesCompleteList, int width, int height, string outputFileNameLDR, string outputFileNameSVG, string outputFileNamePPM, bool display, bool useOutputLDRFile, bool useOutputPPMFile);

void determineBasicPrintPositionsOfAllNodes(vector<GIAEntityNode*> *entityNodesCompleteList, int initialiseOrPrint, Reference * firstReferenceInPrintList, ofstream * writeFileObject);

void initiateMaxXAtAParticularY();
Reference * initialiseEntityNodeForPrinting(GIAEntityNode * entityNode, int y, int x, int initialiseOrPrint, Reference * currentReferenceInPrintList, ofstream * writeFileObject);
Reference * initialiseTimeConditionNodeForPrinting(GIATimeConditionNode * timeConditionNode, int y, int x, int initialiseOrPrint, Reference * currentReferenceInPrintList, ofstream * writeFileObject);

Reference * createReferenceConnectionWithText(Reference * currentReferenceInPrintList, vec * pos1, vec * pos2, int colour, ofstream * writeFileObject, string connectionTypeName);
	Reference * createReferenceConnection(Reference * currentReferenceInPrintList, vec * pos1, vec * pos2, int colour, ofstream * writeFileObject);
Reference * createBox(Reference * currentReferenceInPrintList, vec * vect, double width, double height, int colour, string * text, ofstream * writeFileObject, int thickness);





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
