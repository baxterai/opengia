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
 * File Name: GIAposRelTranslatorHybridSentenceClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3p5a 20-May-2021
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Hybrid Sentence Class
 * /
 *******************************************************************************/


#include "GIAposRelTranslatorHybridSentenceClass.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"


#ifdef GIA_POS_REL_TRANSLATOR_HYBRID

LRPpreprocessorSubReferenceSet::LRPpreprocessorSubReferenceSet(void)
{
	sentenceIndex = INT_DEFAULT_VALUE;
	//subReferenceSetContents = "";
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_ADD_DUMMY_NLP_TEXT
	//subReferenceSetContentsOutputForNLP = "";
	#endif
	#ifdef LRP_PREPROCESSOR_WORD_MULTIWORD_REDUCTION
	firstIndexOfReferenceSetText = INT_DEFAULT_VALUE;
	lastIndexOfReferenceSetText = INT_DEFAULT_VALUE;
	dummyNLPtestOffset = 0;
	#endif
	
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_LOGIC_REFERENCE
	primaryEntityTemp = NULL;
	#endif
	
	isReferenceSetDelimiter = false;	
	next = NULL;
	
	delimiterType = GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_TYPE_UNDEFINED;
	delimiterSpecialCase = GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_SPECIAL_CASE_UNDEFINED;
	
	#ifdef LRP_PREPROCESSOR_RECORD_REFERENCES
	sentenceReference = NULL;
	#endif
	
	#ifdef GIA_NEURAL_NETWORK_NON_SEMANTIC
	definite = false;
	#endif

	isFirstSubreferenceSetInList = false;
}
LRPpreprocessorSubReferenceSet::~LRPpreprocessorSubReferenceSet(void)
{
}

GIAposRelTranslatorHybridLogicReferenceVariable::GIAposRelTranslatorHybridLogicReferenceVariable(void)
{
	#ifdef LRP_PREPROCESSOR_ASSIGN_UNIQUE_SENTENCE_INDICES_FOR_LOGIC_REFERENCE_VARIABLES
	sentenceIndex = INT_DEFAULT_VALUE;
	#endif
	
	//logicReferenceVariableContents = "";
	logicReferenceVariableNameIndex = INT_DEFAULT_VALUE;
	logicReferenceVariableName = "";
	
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET
	referenceSetSubject = new LRPpreprocessorSubReferenceSet();
	referenceSetObject = new LRPpreprocessorSubReferenceSet();
	referenceSetDelimiter = new LRPpreprocessorSubReferenceSet();
	#endif
	
	#ifdef LRP_PREPROCESSOR_WORD_MULTIWORD_REDUCTION
	wordIndexSentence = INT_DEFAULT_VALUE;
	#endif
}
GIAposRelTranslatorHybridLogicReferenceVariable::~GIAposRelTranslatorHybridLogicReferenceVariable(void)
{
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET
	delete referenceSetSubject;
	delete referenceSetObject;
	delete referenceSetDelimiter;
	#endif
}

GIAposRelTranslatorHybridLogicReference::GIAposRelTranslatorHybridLogicReference(void)
{
	//logicReferenceContents = "";
	logicReferenceClass = GIA_POS_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_UNDEFINED;		//if necessary (ie is set to GIA_POS_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_UNDEFINED_TYPE_UNKNOWN) this will be replaced with GIA_POS_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_CONJUNCTION_TYPE_and/GIA_POS_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_CONJUNCTION_TYPE_or upon the detection of a subsequent and/or
	logicReferenceClassType = GIA_POS_REL_TRANSLATOR_RULES_TOKENS_LOGIC_REFERENCE_CLASS_UNDEFINED_TYPE_unknown;
	logicReferenceVariable = new GIAposRelTranslatorHybridLogicReferenceVariable();
	
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_LOGIC_REFERENCE
	firstSubLogicReferenceInListGovernor = NULL;
	firstSubLogicReferenceInListDependent = NULL;
	firstSubLogicReferenceInListArray = NULL;
	lastLogicReferenceInUpperLevel = NULL;
	next = NULL;
	previous = NULL;
	hasSubLogicReference = false;
	hasSubLogicReferenceArray = false;
	isSubLogicReferenceGovernor = false;
	isSubLogicReferenceDependent = false;
	isSubLogicReferenceArray = false;
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_LOGIC_REFERENCE_OUTPUT_LOGIC_REFERENCE_SETS_FOR_HIGH_LEVEL_SEMANTIC_PARSE_VERBOSE
	//logicReferenceSetContentsWithVariableNames = "";
	logicReferenceSetContentsWithVariableNamesSentenceIndex = INT_DEFAULT_VALUE;
	#endif
	#endif
}
GIAposRelTranslatorHybridLogicReference::~GIAposRelTranslatorHybridLogicReference(void)
{
	delete logicReferenceVariable;
	if(next != NULL)
	{
		delete next;
	}
}

#endif



