/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAposRelTranslatorParserOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3p5a 20-May-2021
 * Requirements: requires text parsed by BAI Sequentially Activated Neuronal Input (SANI)
 * Description: Part-of-speech Relation Translator Parser Operations
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_POS_REL_TRANSLATOR_PARSER_OPERATIONS
#define HEADER_GIA_POS_REL_TRANSLATOR_PARSER_OPERATIONS

#include "GIAglobalDefs.hpp"

#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3
#ifdef GIA_POS_REL_TRANSLATOR_RULES_USE

#include "GIAsentenceClass.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAsentenceClass.hpp"
//#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3_USE_SEM_REL_TRANSLATOR_PARSER
#include "GIAsemRelTranslatorOperations.hpp"
//#endif
#include "GIAtranslatorOperations.hpp"
#include "GIAtranslatorGrammar.hpp"
#ifdef GIA_BOT_SWITCH_FIRST_AND_SECOND_PERSON
#include "GIAbot.hpp"
#endif
#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3_USE_SYN_REL_TRANSLATOR_FEATURES
#include "GIAsynRelTranslatorRedistributeRelations.hpp"
#endif
#ifdef SANI_DEBUG_PRINT_FINAL
#include "SANIpropagateOperations.hpp"
#endif
#include "GIAtranslatorReferencing.hpp"
#include "GIAsemRelTranslatorParser.hpp"
#include "GIAsynRelTranslatorParser.hpp"
#include "SANIrules.hpp"
#include "SANInodesGroupClass.hpp"
#include "SANInodesComponentClass.hpp"
#include "GIAposRelTranslatorHybrid.hpp"

#include "GIAsynRelTranslatorDefineSubstances.hpp"
#include "GIAsynRelTranslatorApplyAdvancedFeatures.hpp"
#include "SHAREDvars.hpp"

class GIAposRelTranslatorParserOperationsClass
{
	private: GIAentityNodeClassClass GIAentityNodeClassObject;
	private: GIAsentenceClassClass GIAsentenceClass;
	//#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3_USE_SEM_REL_TRANSLATOR_PARSER
	private: GIAsemRelTranslatorOperationsClass GIAsemRelTranslatorOperations;
	//#endif
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	#ifdef GIA_BOT_SWITCH_FIRST_AND_SECOND_PERSON
	private: GIAbotClass GIAbot;
	#endif
	private: GIAtranslatorGrammarClass GIAtranslatorGrammar;
	#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3_USE_SYN_REL_TRANSLATOR_FEATURES
	private: GIAsynRelTranslatorRedistributeRelationsClass GIAsynRelTranslatorRedistributeRelations;
	#endif
	#ifdef SANI_DEBUG_PRINT_FINAL
	private: SANIpropagateOperationsClass SANIpropagateOperations;
	#endif
	private: GIAtranslatorReferencingClass GIAtranslatorReferencing;
	private: GIAsemRelTranslatorParserClass GIAsemRelTranslatorParser;
	private: GIAsynRelTranslatorParserClass GIAsynRelTranslatorParser;
	private: SANIrulesClass SANIrules;
	private: SANInodesGroupClass SANInodesGroupClassObject;
	private: SANInodesComponentClass SANInodesComponentClassObject;
	private: GIAposRelTranslatorHybridClass GIAposRelTranslatorHybrid;

	private: GIAsynRelTranslatorDefineSubstancesClass GIAsynRelTranslatorDefineSubstances;
	private: GIAsynRelTranslatorApplyAdvancedFeaturesClass GIAsynRelTranslatorApplyAdvancedFeatures;
	private: LRPpreprocessorSentenceClass LRPpreprocessorSentenceClassObject;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	private: SHAREDvarsClass SHAREDvars;
	
	public: bool generateSemanticRelationsFromTxtRelationsWrapper(GIAtranslatorVariablesClass* translatorVariables, SANIGroupParseTree* firstParseTreeGroup, int layer);
		private: bool generateSemanticRelationsFromTxtRelations(GIAtranslatorVariablesClass* translatorVariables, SANIGroupParseTree* currentParseTreeGroup, GIAposRelTranslatorParserForwardPropogationSignalData* parserForwardPropogationSignalData, int layer);
			public: bool generateSemanticRelationsFromTxtRelationsPart2(GIAtranslatorVariablesClass* translatorVariables, SANIGroupParseTree* currentParseTreeGroup, vector<GIAposRelTranslatorParserForwardPropogationSignalData>* parseTreeComponentSignalDataArray, GIAposRelTranslatorParserForwardPropogationSignalData* parserForwardPropogationSignalData, int layer);
				private: bool createSemanticRelationOrdered(GIAtranslatorVariablesClass* translatorVariables, const string semanticRelationFunctionName, string semanticRelationFunctionConditionNewName, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, GIAentityNode* entitySemanticRelationFunctionSubject, GIAentityNode* entitySemanticRelationFunctionObject, GIAentityNode* entitySemanticRelationFunctionDelimiter, bool sameReferenceSet, int layer);
				private: bool createSemanticRelationPair(GIAtranslatorVariablesClass* translatorVariables, const string semanticRelationFunctionName, GIAentityNode* entitySemanticRelationFunction1, GIAentityNode* entitySemanticRelationFunction2, bool sameReferenceSet, const bool semanticRelationReturnConnectionDynamic, int layer);
					private: bool createSemanticRelation(GIAtranslatorVariablesClass* translatorVariables, const string semanticRelationFunctionName, string semanticRelationFunctionConditionNewName, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, GIAentityNode* entitySemanticRelationFunction1, GIAentityNode* entitySemanticRelationFunction2, GIAentityNode* entitySemanticRelationFunction3, bool sameReferenceSet, const bool semanticRelationReturnConnectionDynamic, int layer);
						#ifdef GIA_POS_REL_TRANSLATOR_RULES_GIA3_USE_SEM_REL_TRANSLATOR_PARSER
						private: bool createSemanticRelationInMemory(GIAtranslatorVariablesClass* translatorVariables, const string semanticRelationFunctionName, const string semanticRelationFunctionConditionNewName, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, const GIAentityNode* entitySemanticRelationFunction1, const GIAentityNode* entitySemanticRelationFunction2, const GIAentityNode* entitySemanticRelationFunction3, bool sameReferenceSet, const bool semanticRelationReturnConnectionDynamic);
						#else
						private: bool createSemanticRelationInNetwork(GIAtranslatorVariablesClass* translatorVariables, const string semanticRelationFunctionName, string semanticRelationFunctionConditionNewName, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, GIAentityNode* entitySemanticRelationFunction1, GIAentityNode* entitySemanticRelationFunction2, GIAentityNode* entitySemanticRelationFunction3, bool sameReferenceSet, const bool semanticRelationReturnConnectionDynamic);
						#endif
							private: bool createSemanticRelationMultiwordAuxiliary(GIAtranslatorVariablesClass* translatorVariables, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, bool sameReferenceSet);
							private: bool createSemanticRelationMultiwordPreposition(GIAtranslatorVariablesClass* translatorVariables, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, bool sameReferenceSet);
							private: bool createSemanticRelationMultiwordNoun(GIAtranslatorVariablesClass* translatorVariables, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, bool sameReferenceSet);
							private: bool createSemanticRelationMultiwordAlias(GIAtranslatorVariablesClass* translatorVariables, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, bool sameReferenceSet);
							#ifdef GIA_POS_REL_TRANSLATOR_RULES_CODE_DATE
							private: bool createSemanticRelationMultiwordDate(GIAtranslatorVariablesClass* translatorVariables, vector<GIAentityNode*>* entitySemanticRelationFunctionListArray, bool sameReferenceSet);
							#endif
};

#endif
#endif

#endif
