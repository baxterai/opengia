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
 * File Name: GIAmain.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 2p3c 14-January-2017
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_GIA_MAIN
#define HEADER_GIA_MAIN

#include "GIAglobalDefs.h"
#include "GIAsentenceClass.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#ifdef USE_CE
	#include "CECodeextensionClass.h"
#endif
#include "GIAtranslator.h"
#include "GIAtranslatorOperations.h"
#include "GIAdraw.h"
#include "GIAquery.h"
#include "GIAxmlConversion.h"
#include "GIAcxlConversion.h"
#include "GIAdatabase.h"
#include "GIAnlp.h"
#include "XMLrulesClass.h"
#include "LDsprite.h"
#include "LDopengl.h"
#include "GIAwordnet.h"
#include "GIAnlg.h"
#include "GIAlrp.h"
#include "GIAsemanticParser.h"
#include "GIAsemanticParserDatabase.h"

#define GIA_MAXIMUM_NUMBER_OF_FILES_IN_INPUT_FILE_LIST (1000000)
//#define GIA_XML_DEBUG_TEST_WRITE_READ_WRITE



#ifndef USE_NLC
	int main(const int argc, const char** argv);
#endif

class GIAmainClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAtranslatorClass GIAtranslator;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: GIAdatabaseClass GIAdatabase;
	private: GIAlrpClass GIAlrp;
	private: GIAnlpClass GIAnlp;
	private: XMLrulesClassClass XMLrulesClass;
	private: GIAqueryClass GIAquery;
	private: GIAwordnetClass GIAwordnet;
	private: GIAdrawClass GIAdraw;
	private: LDopenglClass LDopengl;
	private: LDspriteClass LDsprite;
	private: GIAxmlConversionClass GIAxmlConversion;
	private: GIAcxlConversionClass GIAcxlConversion;
	private: GIAnlgClass GIAnlg;
	#ifdef USE_GIA2
	private: GIAsemanticParserClass GIAsemanticParser;
	private: GIAsemanticParserDatabaseClass GIAsemanticParserDatabase;
	#endif

public: bool executeGIA(

	int NLPfeatureParser,
	int NLPdependencyRelationsParser,
	bool NLPrelexCompatibilityMode,
	bool NLPassumePreCollapsedStanfordRelations,

	int queryNLPfeatureParser,
	int queryNLPdependencyRelationsParser,
	bool queryNLPrelexCompatibilityMode	,
	bool queryNLPassumePreCollapsedStanfordRelations,

	string NLPexeFolderArray[],

	bool useInputTextPlainTXTFile,
	string inputTextPlainTXTfileName,

#ifdef USE_CE
	bool useInputTextCodeextensionsTXTFileName,
	string inputTextCodeextensionsTXTFileName,
#endif

	bool useInputTextNLPrelationXMLFile,
	string inputTextNLPrelationXMLfileName,
	bool useInputTextNLPfeatureXMLFile,
	string inputTextNLPfeatureXMLfileName,
	bool useOutputTextCFFFile,
	string outputTextCFFFileName,
	bool useInputTextXMLFile,
	string inputTextXMLFileName,
	bool useOutputTextXMLFile,
	string outputTextXMLFileName,
	bool useOutputTextCXLFile,
	string outputTextCXLFileName,
	bool useOutputTextLDRFile,
	string outputTextLDRFileName,
	bool useOutputTextPPMFile,
	string outputTextPPMFileName,
	bool useOutputTextSVGFile,
	string outputTextSVGFileName,
	bool useInputQueryPlainTXTFile,
	string inputQueryPlainTXTFileName,
	bool useInputQueryNLPrelationXMLFile,
	string inputQueryNLPrelationXMLFileName,
	bool useInputQueryNLPfeatureXMLFile,
	string inputQueryNLPfeatureXMLFileName,
	bool useOutputQueryCFFFile,
	string outputQueryCFFFileName,
	bool useInputQueryXMLFile,
	string inputQueryXMLFileName,
	bool useOutputQueryXMLFile,
	string outputQueryXMLFileName,
	bool useOutputQueryCXLFile,
	string outputQueryCXLFileName,
	bool useOutputQueryLDRFile,
	string outputQueryLDRFileName,
	bool useOutputQueryPPMFile,
	string outputQueryPPMFileName,
	bool useOutputQuerySVGFile,
	string outputQuerySVGFileName,
	bool useOutputTextAllFile,
	string outputTextAllFileName,
	bool useOutputTextAnswerPlainTXTFile,
	string outputTextAnswerPlainTXTFileName,

#ifdef GIA_INPUT_FILE_LISTS
	bool inputFileList,
#endif
	bool printOutput,
	bool printOutputQuery,
	bool displayInOpenGLAndOutputScreenshot,

	int rasterImageWidth,
	int rasterImageHeight,

	bool useInputQuery,

#ifdef GIA_DATABASE
	bool readFromDatabase,
	bool writeToDatabase,
	bool useDatabase,
	string databaseFolderName,
#endif

#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName,
#endif

#ifdef GIA_LRP
	bool useLRP,
	bool useOutputLRPTextPlainTXTFile,
	string outputLRPTextPlainTXTFileName,
	bool useOutputLRPTextForNLPonlyPlainTXTFile,
	string outputLRPTextForNLPonlyPlainTXTFileName,
	bool useOutputQueryLRPTextPlainTXTFile,
	string outputQueryLRPTextPlainTXTFileName,
	bool useOutputQueryLRPTextForNLPonlyPlainTXTFile,
	string outputQueryLRPTextForNLPonlyPlainTXTFileName,
	string lrpDataFolderName,
#endif

#ifdef USE_WORDNET
	int synonymnDetectionStatus,
#endif

	vector<GIAentityNode*>* entityNodesActiveListComplete,
	unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes,
	map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences,
	unordered_map<long, GIAtimeConditionNode*>* timeConditionNodesActiveList,

	int* maxNumberSentences
	);

#ifdef GIA_INPUT_FILE_LISTS
	public: int getFilesFromFileList(const string inputListFileName, string* inputFileNameArray);
#endif

#ifdef USE_CS_WORKAROUND
	public: bool executeGIA2();
#endif
};

#endif
