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
 * File Name: GIAposRelTranslatorHybridReferenceSet.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3k11b 09-May-2020
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Hybrid Reference Set
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_POS_REL_TRANSLATOR_REFERENCE_SET
#define HEADER_GIA_POS_REL_TRANSLATOR_REFERENCE_SET

#include "GIAglobalDefs.hpp"
#include "GIAposRelTranslatorHybridSentenceClass.hpp"
#include "GIApreprocessorWordIdentification.hpp"

#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_TYPE_UNKNOWN (0)
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_TYPE_SUBJECT (1)
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_TYPE_OBJECT (2)
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_TYPE_DELIMITER (3)	//this is a virtual (fake) reference set created for data storage consistency purposes only

#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_TYPE_UNDEFINED (0)
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_TYPE_AUXILIARY (1)	//eg tom has/is the ball
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_TYPE_VERB (2)	//eg tom moves the ball
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_TYPE_PREPOSITION (3) 	//eg tom is near the ball 

#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_SPECIAL_CASE_UNDEFINED (0)
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_SPECIAL_CASE_DELIMITER_AND_OBJECT_REFER_TO_PREVIOUS_DELIMITER_VERB (1)	//eg tom rides the bike near the ball
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_SPECIAL_CASE_OBJECT_REFERS_TO_PREVIOUS_DELIMITER_VERB (2) 	//eg Tom rides fast
#define GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_DELIMITER_SPECIAL_CASE_DELIMITER_VERB_NOT_PRECEEDED_BY_THAT_WHICH_AND_NOT_PRECEEDED_BY_AUXILIARY (3) 	//eg "controlled" in "a controlled chicken was moved to"


class GIAposRelTranslatorHybridReferenceSetClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAposRelTranslatorHybridSentenceClassClass GIAposRelTranslatorHybridSentenceClass;
	private: GIApreprocessorWordClassClass GIApreprocessorWordClassObject;
	private: GIApreprocessorWordIdentificationClass GIApreprocessorWordIdentification;
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET
	public: bool generateSentenceWordList(GIApreprocessorMultiwordReductionWord* sentenceContentsFirstWord, vector<GIApreprocessorPlainTextWord*>* logicReferenceVariableWordList);
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_DEPRECIATED
	public: bool executeReferenceSetPreprocessor(const vector<GIApreprocessorPlainTextWord*>* logicReferenceVariableWordList, GIAposRelTranslatorHybridLogicReferenceVariable* logicReferenceVariable, const bool expectToFindSubjectAuxObjectLogicReferenceVariable, const int wordIndexSentence);
			#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_REFERENCE_SET_PREFERENCE_VERB_OR_NOUN_OVER_ADJECTIVE_POS_AMBIGUITY
			private: bool determineIsVerbAndAdjective(GIApreprocessorPlainTextWord* currentWordTag, bool usePOSprelim, bool grammaticallyStrict);
			#endif
			private: void updateIndices(const bool currentWordIsReferenceSetDelimiter, bool* referenceSetDelimiterDetected, bool* parsingReferenceSetDelimiter, const int currentDelimiterSpecialCase, const int wordIndexOfHypotheticalPreceedingThatWhich, const bool currentWordIsReferenceSetDelimiterPreceededByThatWhich, bool* referenceSetDelimiterIndicatesSameReferenceSet, int* firstIndexOfReferenceSetDelimiterText, int* lastIndexOfPreviousReferenceSet);
			private: bool formSubReferenceSetTextFromWordList(const vector<GIApreprocessorPlainTextWord*>* logicReferenceVariableWordList, vector<GIApreprocessorPlainTextWord*>* subReferenceSetText, const int firstIndexOfSubReferenceSet, const int lastIndexOfSubReferenceSet);
			private: bool addReferenceSetToReferenceSet(GIApreprocessorSubReferenceSet* firstSubReferenceSetInList, vector<GIApreprocessorPlainTextWord*>* subReferenceSetText, const bool referenceSetDelimiter, const int wordIndexLogicReference, const int wordIndexSentence, const int delimiterType, const int delimiterSpecialCase);
				private: bool addSubReferenceSetToReferenceSet(GIApreprocessorSubReferenceSet* firstSubReferenceSetInList, vector<GIApreprocessorPlainTextWord*>* subReferenceSetText, const bool referenceSetDelimiter, const int wordIndexLogicReference, const int wordIndexSentence, const int delimiterType, const int delimiterSpecialCase);
	#endif
			public: bool detectAuxiliary(const string currentWord);
			public: bool detectModalAuxiliary(const string currentWord);
			public: bool detectRcmodSameReferenceSetDelimiter(const string currentWord);

	public: bool hasReferenceSet(GIApreprocessorSubReferenceSet* referenceSet);
	public: void setReferenceSetText(GIApreprocessorSubReferenceSet* referenceSet, vector<GIApreprocessorPlainTextWord*>* text);
	public: vector<GIApreprocessorPlainTextWord*> getReferenceSetText(GIApreprocessorSubReferenceSet* referenceSet);
	public: void printSubReferenceSet(GIApreprocessorSubReferenceSet* currentSubReferenceSetInList);
	#endif
	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_DETERMINE_AMBIGUOUS_PREPOSITION_POS_TYPES_BASED_ON_CONTEXT
	public: bool verifyIsPrepositionNotProgressiveVerbBasedOnContext(const vector<GIApreprocessorPlainTextWord*>* sentenceContentsWordList, const int prepositionWordIndex, const bool usePOSprelim);
	#endif
};

#endif

