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
 * File Name: GIAsentenceClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 2h9a 20-January-2015
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_GIA_SENTENCE_CLASS
#define HEADER_GIA_SENTENCE_CLASS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

//#define FEATURE_GRAMMATICAL_TENSE_DATE "date"
#define FEATURE_WORD_QUESTIONMARK "?"

#define MAX_NUMBER_OF_RELATIONS_PER_SENTENCE (1000)
#define MAX_NUMBER_OF_WORDS_PER_SENTENCE (1000)

//from http://wiki.opencog.org/w/Word_substances (intermediary - used for translation purposes into WordNet int grammaticalWordTypeTemp only)
#define FEATURE_RELEX_POS_TYPE_ADJECTIVE (1)
#define FEATURE_RELEX_POS_TYPE_ADVERB (2)
#define FEATURE_RELEX_POS_TYPE_CONJUNCTION (3)
#define FEATURE_RELEX_POS_TYPE_DETERMINATE (4)
#define FEATURE_RELEX_POS_TYPE_NOUN (5)
#define FEATURE_RELEX_POS_TYPE_PARTICLE (6)
#define FEATURE_RELEX_POS_TYPE_PREP (7)
#define FEATURE_RELEX_POS_TYPE_PUNCTUATION (8)
#define FEATURE_RELEX_POS_TYPE_VERB (9)
#define FEATURE_RELEX_POS_TYPE_WORD (10)
#define FEATURE_RELEX_POS_TYPE_ADJECTIVE_NAME "adj"
#define FEATURE_RELEX_POS_TYPE_ADVERB_NAME "adv"
#define FEATURE_RELEX_POS_TYPE_CONJUNCTION_NAME "conjunction"
#define FEATURE_RELEX_POS_TYPE_DETERMINATE_NAME "det"
#define FEATURE_RELEX_POS_TYPE_NOUN_NAME "noun"
#define FEATURE_RELEX_POS_TYPE_PARTICLE_NAME "particle"
#define FEATURE_RELEX_POS_TYPE_PREP_NAME "prep"
#define FEATURE_RELEX_POS_TYPE_PUNCTUATION_NAME "punctuation"
#define FEATURE_RELEX_POS_TYPE_VERB_NAME "verb"
#define FEATURE_RELEX_POS_TYPE_WORD_NAME "WORD"
#define FEATURE_RELEX_POS_NUMBER_OF_TYPES (11)
/*
add this "abbr" to POS types (eg Mr. -> wordnet noun)?
see relex/relex-1.4.0/data/relex-tagging-algs.txt
NB pronouns are "already tagged as nouns"
*/
static string featureRelexPOStypeArray[FEATURE_RELEX_POS_NUMBER_OF_TYPES] = {FEATURE_RELEX_POS_TYPE_PUNCTUATION_NAME, FEATURE_RELEX_POS_TYPE_ADJECTIVE_NAME, FEATURE_RELEX_POS_TYPE_ADVERB_NAME, FEATURE_RELEX_POS_TYPE_CONJUNCTION_NAME, FEATURE_RELEX_POS_TYPE_DETERMINATE_NAME, FEATURE_RELEX_POS_TYPE_NOUN_NAME, FEATURE_RELEX_POS_TYPE_PARTICLE_NAME, FEATURE_RELEX_POS_TYPE_PREP_NAME, FEATURE_RELEX_POS_TYPE_PUNCTUATION_NAME, FEATURE_RELEX_POS_TYPE_VERB_NAME, FEATURE_RELEX_POS_TYPE_WORD_NAME};


//#define FEATURE_GRAMMATICAL_COUNT ".c"



#ifdef GIA_USE_STANFORD_CORENLP
class StanfordCoreNLPmention
{
public:

	StanfordCoreNLPmention(void);
	~StanfordCoreNLPmention(void);

	bool representative;
	int sentence;
	int start;
	int end;
	int head;

	StanfordCoreNLPmention * next;
};

class StanfordCoreNLPcoreference
{
public:

	StanfordCoreNLPcoreference(void);
	~StanfordCoreNLPcoreference(void);

	StanfordCoreNLPmention * firstMentionInList;

	StanfordCoreNLPcoreference * next;
};

#endif


#ifdef GIA_USE_ADVANCED_REFERENCING
class GIAMention
{
public:

	GIAMention(void);
	~GIAMention(void);

	bool representative;
	long idActiveList;
	int entityIndex;	//ie "head"
	string entityName;
	bool intrasentenceReference;

	GIAMention * next;
};

class GIACoreference
{
public:

	GIACoreference(void);
	~GIACoreference(void);

	GIAMention * firstMentionInList;

	GIACoreference * next;
};

#endif




class Relation
{
public:

	Relation(void);
	~Relation(void);

	string relationType;
	#ifdef GIA_INITIALISE_PREPOSITION_ENTITIES_AT_START_OF_TRANSLATOR_NEW
	int relationTypeIndex;
	#endif
	string relationDependent;
	int relationDependentIndex;
	string relationGovernor;
	int relationGovernorIndex;

	bool disabled;
	//#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_LINK
	bool disabledDuringLink;
	//#endif

	#ifdef GIA_USE_RELEX
	bool subjObjRelationAlreadyAdded;	//Relex Only
	#endif

	#ifdef GIA_USE_STANFORD_CORENLP
	bool prepositionCombinationAlreadyCreatedTemp;
	#endif

	#ifdef GIA_RECORD_SAME_REFERENCE_SET_INFORMATION
	bool auxiliaryIndicatesDifferentReferenceSet;
	bool rcmodIndicatesSameReferenceSet;
	#endif

	#ifdef GIA_REDISTRIBUTE_RELATIONS_SUPPORT_NAME_OF
	bool isNameTemp;
	#endif

	#ifdef GIA_USE_CORPUS_DATABASE
	bool sameReferenceSet;
	#ifdef GIA2_SUPPORT_QUERIES
	string corpusSpecialRelationGovernorIsQuery;
	string corpusSpecialRelationDependentIsQuery;
	#endif
	#endif

	#ifdef GIA_LRP_NORMALISE_PREPOSITIONS
	#ifdef GIA_LRP_NORMALISE_INVERSE_PREPOSITIONS
	bool inverseRelation;
	#endif
	#ifdef GIA_LRP_NORMALISE_TWOWAY_PREPOSITIONS
	bool relationTwoWay;
	#ifdef GIA_LRP_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
	bool inverseRelationTwoWay;
	#endif
	#endif
	#endif
	
	Relation * next;
};


class Feature
{
public:

	Feature(void);
	~Feature(void);

	int entityIndex;
	string word;
	string lemma;
	#ifdef GIA_USE_LRP
	string wordWithLRPforNLPonly;
	#endif

	#ifdef GIA_USE_RELEX
	string type;
	string grammar;
	#endif

	int NER;
	#ifdef GIA_USE_STANFORD_CORENLP
	int CharacterOffsetBegin;
	int CharacterOffsetEnd;
	string stanfordPOS;
	string NormalizedNER;
	string Timex;
	#endif

	//derived variables:
	bool grammaticalIsDateOrTime;
	int grammaticalTense;
	bool grammaticalTenseModifierArray[GRAMMATICAL_TENSE_MODIFIER_NUMBER_OF_TYPES];
	int grammaticalNumber;
	bool grammaticalIsDefinite;
	bool grammaticalIsIndefinitePlural;
	bool grammaticalIsProperNoun;
	int grammaticalGender;
	bool grammaticalIsPronoun;
	int grammaticalWordType;	//grammaticalWordTypeTemp
	#ifdef GIA_RECORD_SAME_REFERENCE_SET_INFORMATION
	int grammaticalIndexOfDeterminer;
	#endif
	bool previousWordInSentenceIsTo;

	#ifndef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
	bool alreadyAssignedSubstancesBasedOnDeterminatesOfDefinitionEntitiesTemp;	//#ifdef GIA_DEFINE_SUBSTANCES_BASED_UPON_DETERMINATES_OF_DEFINITION_ENTITIES
	bool mustSetIsSubstanceConceptBasedOnApposRelation;
	bool isPronounReference;
	#endif

	bool entityDisabled;	//added 14 July 2012b

	#ifdef GIA_USE_CORPUS_DATABASE
	int GIAconnectionistNetworkPOStype;
	#endif
	
	#ifdef GIA_FEATURE_POS_TAG_NN_ONLY_MARK_AS_SINGULAR_WITH_DETERMINER
	bool determinerPotentiallySingularDetected;
	#endif

	Feature * next;
	Feature * previous;	//used for reference lookup
};



class Sentence
{
public:

	Sentence(void);
	~Sentence(void);

	int sentenceIndex;

	#ifdef GIA_USE_RELEX
	string sentenceText;		//not required - delete in future
	string constituentsText;	//not required - delete in future
	string featuresText;		//not required - delete in future
	string relationsText;		//not required - delete in future
	string linksText;		//not required - delete in future
	#endif

	#ifdef GIA_USE_STANFORD_CORENLP
	StanfordCoreNLPcoreference * firstCoreferenceInList;
	#endif

	int maxNumberOfWordsInSentence;

	Relation * firstRelationInList;
	Feature * firstFeatureInList;

	Sentence * next;
	Sentence * previous;	//used for reference lookup

	bool isQuestion;

	bool corpusLookupSuccessful;
	
	int conditionEntityArtificialIndexCurrent;	//added 2g1a/25-August-2014
};

class Paragraph
{
public:

	Paragraph(void);
	~Paragraph(void);

	Sentence * firstSentenceInList;

	Paragraph * next;
	Paragraph * previous;	//used for reference lookup
};

void copySentences(Sentence * sentenceToCopy, Sentence * newSentence);
void copyRelations(Relation * firstRelationInListToCopy, Relation * firstRelationInList);
void copyFeatures(Feature * firstFeatureInListToCopy, Feature * firstFeatureInList);
#ifdef GIA_USE_STANFORD_CORENLP
void copyStanfordCoreferences(StanfordCoreNLPcoreference * firstCoreferenceInListToCopy, StanfordCoreNLPcoreference * firstCoreferenceInList);
void copyStanfordMention(StanfordCoreNLPmention * firstMentionInListToCopy, StanfordCoreNLPmention * firstMentionInList);
#endif

#endif
