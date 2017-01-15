/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: GIAlrp.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1p1c 08-September-2012
 * Requirements: requires plain text file
 * Description: Language Reduction Preprocessor
 *
 *******************************************************************************/


#ifndef HEADER_GIA_LRP
#define HEADER_GIA_LRP

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIASentenceClass.h"

#define GIA_NLP_START_ENTITY_INDEX (1)
#define GIA_NLP_START_SENTENCE_INDEX (1)
//#define GIA_LRP_USE_OLD_PREPOSITION_SPECIFIC_CODE_NOT_REQUIRED

#define GIA_LRP_PHRASALVERB_DATABASE_FILE_NAME "CambridgePhrasalVerbs.txt"
#define GIA_LRP_IRREGULARVERB_DATABASE_FILE_NAME "WikipediaIrregularVerbs.txt"
#define GIA_LRP_MULTIWORDPREPOSITION_DATABASE_FILE_NAME "WikipediaMultiwordPrepositions.txt"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_OR "or"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMETHING_NAME "sth"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEWHERE_NAME "swh"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEBODY_NAME "sb"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMETHING (0)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEWHERE (1)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEBODY (2)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_UNDEFINED (GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMETHING)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_MAX_NUMBER_WORDS (3)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ALTERNATE (CHAR_FORWARDSLASH)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_OPEN_OPTIONAL (CHAR_OPEN_BRACKET)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_CLOSE_OPTIONAL (CHAR_CLOSE_BRACKET)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_MAX_NUM_TENSE_FORMS (5)	//run (infinitive), runs (present), running (continuous), ran (past), run (past partiple)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_INFINITIVE (0)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PRESENT (1)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_CONTINUOUS (2)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PAST (3)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PASTPARTICIPLE (4)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_MAX_NUM_TENSE_FORM_VERSIONS (2)	//standard/alternate (ie double constanant form OR irregular verb alternate case)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_VERSION_STANDARD (0)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_VERSION_ALTERNATE (1)
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PRESENT_APPEND "s"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_CONTINUOUS_APPEND "ing"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PAST_APPEND "ed"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PRESENT_APPEND_CASE3 "ies"
#define GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_TENSE_FORM_PAST_APPEND_CASE3 "ied"

#define GIA_LRP_PHRASALVERB_REPLACEMENT_STRING_DEFAULT ""	//will be tense specific

#define GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEBODY_NUMBER_OF_TYPES (3)
static string lrpPhrasalVerbDatabaseTagArbitraryNameArray[GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEBODY_NUMBER_OF_TYPES] = {GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMETHING_NAME, GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEWHERE_NAME, GIA_LRP_PHRASALVERB_DATABASE_TAG_ARBITRARYNAME_SOMEBODY_NAME};

#define GIA_LRP_NUMBER_OF_VOWELS (5)
#define GIA_LRP_NUMBER_OF_CONSTONANTS (21)
static char englishVowelArray[GIA_LRP_NUMBER_OF_VOWELS] = {'a', 'e', 'i', 'o', 'u'};
static char englishConsonantArray[GIA_LRP_NUMBER_OF_CONSTONANTS] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
/*
#define GIA_LRP_VERB_DOUBLE_CONSONANT_RULE1_LAST_LETTER_EXCEPTIONS_NUMBER_OF_TYPES (4)
static char lrpVerbDoubleConsonantRule1LastLetterExceptions[GIA_LRP_VERB_DOUBLE_CONSONANT_RULE1_LAST_LETTER_EXCEPTIONS_NUMBER_OF_TYPES] = {'w', 'x', 'y', 'z'};
*/

#define GIA_NLP_NUMBER_OF_PUNCTUATION_MARK_CHARACTERS (4)		//CHECKTHIS; need to location RelEx/Stanford dependency relation specification and match the exact same punction marks detected
static char nlpPunctionMarkCharacterArray[GIA_NLP_NUMBER_OF_PUNCTUATION_MARK_CHARACTERS] = {CHAR_FULLSTOP, CHAR_COMMA, CHAR_SEMICOLON, CHAR_COLON};
#define GIA_NLP_NUMBER_OF_WHITESPACE_CHARACTERS (3)		//CHECKTHIS; need to location RelEx/Stanford dependency relation specification and match the exact same punction marks detected
static char nlpWhitespaceCharacterArray[GIA_NLP_NUMBER_OF_WHITESPACE_CHARACTERS] = {CHAR_NEWLINE, CHAR_TAB, CHAR_SPACE};

#define GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP "fight"
#define GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PRESENT "fights"
#define GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_CONTINUOUS "fighting"
#define GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PAST "fought"
#define GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PASTPARTICIPLE "fought"
static string lrpDummyCollapsedPhrasalVerbNameForNLPgrammaticalTenseFormsArray[GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_MAX_NUM_TENSE_FORMS] = {GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP, GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PRESENT, GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_CONTINUOUS, GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PAST, GIA_LRP_DUMMY_COLLAPSED_PHRASAL_VERB_LEMMA_NAME_FOR_NLP_TENSE_FORM_PASTPARTICIPLE};

#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP "near"
/*
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_0 "dummy{reposition1"
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_1 "dummy{reposition2"
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_2 "dummy{reposition3"
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_3 "dummy{reposition4"
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_4 "dummy{reposition5"
#define GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_MAX_NUMBER_SENTENCE_INSTANCES (5)
string lrpDummyCollapsedMultiwordPrepositionLemmaNameForNLPArray[GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_MAX_NUMBER_SENTENCE_INSTANCES] = {GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_0, GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_1, GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_2, GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_3, GIA_LRP_DUMMY_COLLAPSED_MULTIWORD_PREPOSITION_NAME_FOR_NLP_SENTENCE_INSTANCE_4};
*/

#define ENTITY_INDEX_UNDEFINED -1
#define MAXIMUM_NUMBER_WORDS_PER_SENTENCE 1000	//same value from GIATranslatorOperations.h

class GIALRPtag
{
public:

	GIALRPtag(void);
	~GIALRPtag(void);

	string tagName;
	string tagNameLemma;

//phrasal verbs only:
	bool tagSpecialArbitraryName;	//used to indicate if the current tag is sth/swh/sb
	bool tagSpecialArbitraryNameType;

	bool optional;	//used to specify if a tag is optional designated by "(...)" in the phrasal verb database

	//bool primary;	//is the first word in the phrasal verb (assumed to be lemma)?
	//string primaryPhrasalVerbReplacementString;
	//string primaryPhrasalVerbReplacementStringNLPonly;

	bool base;	//used to indicate if the current tag in the phrasal verb is the base verb of the phrasal verb (or lemma) - NB the first word in each phrasal verb defined in the database is assumed to be the lemma, but there may be additional instances
	string grammaticalTenseFormsArray[GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_MAX_NUM_TENSE_FORMS][GIA_LRP_PHRASALVERB_DATABASE_TAG_BASE_MAX_NUM_TENSE_FORM_VERSIONS];		//only for lemma	[2: for alternate versions]
	int grammaticalTenseFormDetected;

//plain text only:
	int entityIndex;		//temp var
	int sentenceIndex;		//temp var
	bool collapsedPhrasalVerbExactDefinedSection;	//temp var [aslwas true]
	bool collapsedMultiwordPreposition;				//temp var

	GIALRPtag * alternateTag;			//used to specify an alternate (but corresponding) tag name designated by "/" in the phrasal verb database
	GIALRPtag * alternateSentence;		//used to specifiy an alternate (but corresponding) phrasal verb designated by "or" in the phrasal verb database
	GIALRPtag * nextTag;				//next tag in phrasal verb
	GIALRPtag * nextSentence;			//first tag in next phrasal verb

};

class GIALRPtagTextCorrespondenceInfo
{
public:

	GIALRPtagTextCorrespondenceInfo(void);
	~GIALRPtagTextCorrespondenceInfo(void);

	string wordWithLRP;		//LRP generated word name
	string lemmaWithLRP;		//LRP generated lemma name	
	string wordWithLRPforNLPonly;	//temporary/dummy word name such that NLP can properly parse the text

	int entityIndex;	//used to map the NLP dummy replacement lemma to the official LRP generated lemma (for entity name reversion after NLP)
	int sentenceIndex;	//used to map the NLP dummy replacement lemma to the official LRP generated lemma (for entity name reversion after NLP)

	GIALRPtagTextCorrespondenceInfo * next;
};


GIALRPtagTextCorrespondenceInfo * getCurrentGIALRPtagTextCorrespondenceInfo();
void setCurrentGIALRPtagTextCorrespondenceInfo(bool isQuery);
void initialiseCurrentGIALRPtagTextCorrespondenceInfo();

bool parseTextFileAndReduceLanguage(string inputTextPlainTXTFileName, string outputLRPTextPlainTXTFileName, string outputLRPTextForNLPonlyPlainTXTFileName);
	bool loadPhrasalVerbDataAndGenerateAllTenseVariants();
		bool loadIrregularVerbList(string irregularVerbListFileName, GIALRPtag * firstTagInIrregularVerbList);
		bool loadPhrasalVerbDataAndGenerateAllTenseVariants(string phrasalVerbDatabaseFileName, GIALRPtag * firstTagInPhrasalVerbList, GIALRPtag * firstTagInIrregularVerbList);
			bool generateTenseVariantsOfVerbBase(GIALRPtag * baseTag, GIALRPtag * firstTagInIrregularVerbList);
				void copyDefaultVerbTenseFormsToAlternateTenseForms(GIALRPtag * baseTag, bool irregularVerbFound);
		bool loadMultiWordPrepositionData(string multiwordPrepositionListFileName, GIALRPtag * firstTagInMultiwordPrepositionList);
		bool loadPlainTextFile(string plainTextInputFileName, GIALRPtag * firstTagInPlainText);
		bool searchAndReplaceAllPhrasalVerbsAndMultiwordPrepositions(GIALRPtag * firstTagInPlainText, GIALRPtag * firstTagInPhrasalVerbList, GIALRPtag * firstTagInMultiwordPrepositionList, string plainTextLRPOutputFileName, string plainTextLRPforNLPOutputFileName, GIALRPtagTextCorrespondenceInfo * firstGIALRPtagCorrespondenceInfo);
			bool writeTagListToFile(GIALRPtag * firstTagInPlainText, string plainTextLRPOutputFileName, string plainTextLRPforNLPOutputFileName);

void revertNLPtagNameToOfficialLRPtagName(Feature * feature, Sentence * currentSentenceInList, Relation * currentRelationInListForPrepositionsOnly, bool isPreposition, bool * foundOfficialLRPreplacementString);


string convertStringToLowerCase(string * arbitraryCaseString);

#endif