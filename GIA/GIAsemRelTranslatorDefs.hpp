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
 * File Name: GIAsemRelTranslatorDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3g1n 24-April-2018
 * Requirements: 
 * Description: Syntactic Relation Translator - Converts relation objects into GIA nodes (of type entity, action, condition etc) in GIA network/tree
 *
 *******************************************************************************/

#ifndef HEADER_GIA_SEM_REL_TRANSLATOR_DEFS
#define HEADER_GIA_SEM_REL_TRANSLATOR_DEFS

#include "GIAentityNodeClass.hpp"
#include "GIAsentenceClass.hpp"





//no longer hard coded;
#define ENTITY_POSSESSIVEENDING_APOSTROPHE_S "'s"
#define ENTITY_POSSESSIVEENDING_APOSTROPHE "'"

/*
//http://en.wikipedia.org/wiki/English_auxiliaries_and_contractions
#define ENTITY_AUXILIARY_BEING_ARRAY_NUMBER_OF_TYPES (8)
#define ENTITY_AUXILIARY_HAVING_ARRAY_NUMBER_OF_TYPES (4)
#define ENTITY_AUXILIARY_DOING_ARRAY_NUMBER_OF_TYPES (4)
static string entityAuxiliaryBeingArray[ENTITY_AUXILIARY_BEING_ARRAY_NUMBER_OF_TYPES] = {"am", "is", "are", "was", "were", "be", "being", "been"};
static string entityAuxiliaryHavingArray[ENTITY_AUXILIARY_HAVING_ARRAY_NUMBER_OF_TYPES] = {"have", "has", "had", "having"};
static string entityAuxiliaryDoingArray[ENTITY_AUXILIARY_DOING_ARRAY_NUMBER_OF_TYPES] = {"do", "does", "did", "doing"};	

//additional cases not identified by [/mapped to existing] Relex Word Type:
#define ENTITY_WH_ARRAY_NUMBER_OF_TYPES (9)
static string entityWhArray[ENTITY_WH_ARRAY_NUMBER_OF_TYPES] = {"which", "what", "who", "whom", "whose", "where", "when", "how", "why"};	//http://courses.washington.edu/hypertxt/csar-v02/penntable.html + http://www.computing.dcu.ie/~acahill/tagset.html

#define ENTITY_POSSESSIVEENDING_APOSTROPHE_S "'s"
#define ENTITY_POSSESSIVEENDING_APOSTROPHE "'"
#define ENTITY_POSSESSIVEENDING_NUMBER_OF_TYPES (2)
static string entityPossessiveEndingArray[ENTITY_POSSESSIVEENDING_NUMBER_OF_TYPES] = {ENTITY_POSSESSIVEENDING_APOSTROPHE_S, ENTITY_POSSESSIVEENDING_APOSTROPHE};
#define ENTITY_MODALAUXILIARY_NUMBER_OF_TYPES (9)
static string entityModalAuxiliaryArray[ENTITY_MODALAUXILIARY_NUMBER_OF_TYPES] = {"can", "could", "may", "might", "must", "shall", "should", "will", "would"};	//en.wikipedia.org/wiki/Modal_verb
#define ENTITY_CARDINALNUMBER_ARRAY_NUMBER_OF_TYPES (43)
static string entityCardinalNumberArray[ENTITY_CARDINALNUMBER_ARRAY_NUMBER_OF_TYPES] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred", "thousand", "million", "billion", "trillion"};
#define ENTITY_PRONOUN_PERSONAL_ARRAY_NUMBER_OF_TYPES (16)
static string entityPronounPersonalArray[ENTITY_PRONOUN_PERSONAL_ARRAY_NUMBER_OF_TYPES] = {"I", "you", "he", "she", "it", "me", "you", "him", "her", "it", "we", "you", "they", "us", "you", "them"};			//http://grammar.ccc.commnet.edu/grammar/cases.htm#cases
#define ENTITY_PRONOUN_POSSESSIVE_ARRAY_NUMBER_OF_TYPES (14)
static string entityPronounPossessiveArray[ENTITY_PRONOUN_POSSESSIVE_ARRAY_NUMBER_OF_TYPES] = {"my", "mine", "your", "yours", "his", "her", "hers", "its", "our", "ours", "your", "yours", "their", "theirs"};	//http://grammar.ccc.commnet.edu/grammar/cases.htm#cases
#define ENTITY_PREDETERMINER_ARRAY_NUMBER_OF_TYPES (13)
static string entityPredeterminerArray[ENTITY_PREDETERMINER_ARRAY_NUMBER_OF_TYPES] = {"all", "both", "double", "half", "quadruple", "quite", "rather", "such", "times", "treble", "twice", "quarter", "many"};	//removed "what"	//http://englishwithyeasir.blogspot.com.au/2013/05/predeterminers.html
	//predeterminer could be merged with adjective

#define ENTITY_REFERENCE_SET_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES (2)
static string entityRcmodSameReferenceSetDelimiter[ENTITY_REFERENCE_SET_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES] = {"that", "which"};		//see preprocessorMathRcmodSameReferenceSetDelimiter
*/

//the following definitions must map to relationGovernorCompositionNameArray[]:
#define GIA_SEM_REL_TRANSLATOR_RELATION_GOVERNOR_COMPOSITION_PAST_TENSE_NAME_ARRAY_NUMBER_OF_TYPES (3)
static string relationGovernorCompositionPastTenseNameArray[GIA_SEM_REL_TRANSLATOR_RELATION_GOVERNOR_COMPOSITION_PAST_TENSE_NAME_ARRAY_NUMBER_OF_TYPES] = {"contained", "comprised", "had"};
#define GIA_SEM_REL_TRANSLATOR_RELATION_GOVERNOR_COMPOSITION_CONTINUOUS_TENSE_NAME_ARRAY_NUMBER_OF_TYPES (3)
static string relationGovernorCompositionContinuousTenseNameArray[GIA_SEM_REL_TRANSLATOR_RELATION_GOVERNOR_COMPOSITION_CONTINUOUS_TENSE_NAME_ARRAY_NUMBER_OF_TYPES] = {"containing", "comprised" "having"};
#define GIA_SEM_REL_TRANSLATOR_RELATION_AUXILIARY_PAST_TENSE_NAME_ARRAY_NUMBER_OF_TYPES (4)
static string relationAuxiliaryPastTenseNameArray[GIA_SEM_REL_TRANSLATOR_RELATION_AUXILIARY_PAST_TENSE_NAME_ARRAY_NUMBER_OF_TYPES] = {"was", "were", "had", "did"};
#define GIA_SEM_REL_TRANSLATOR_RELATION_AUXILIARY_FUTURE_TENSE_NAME_ARRAY_NUMBER_OF_TYPES (1)
static string relationAuxiliaryFutureTenseNameArray[GIA_SEM_REL_TRANSLATOR_RELATION_AUXILIARY_FUTURE_TENSE_NAME_ARRAY_NUMBER_OF_TYPES] = {"will"};	//FUTURE: take into account all principal modal verbs; can, could, may, might, must, shall, should, will, would
//must use LRP to determine continuous tense..

#define GIA_TRANSLATOR_ENTITY_AUXILIARY_NOT_NUMBER_OF_TYPES (1)
static string GIAtranslatorEntityAuxiliaryNotArray[GIA_TRANSLATOR_ENTITY_AUXILIARY_NOT_NUMBER_OF_TYPES] = {"not"};	



#define GIA_SHARED_POS_TYPE_UNDEFINED 0
#define GIA_SHARED_POS_TYPE_CONJUNCTION 1
#define GIA_SHARED_POS_TYPE_NUMBER 2
#define GIA_SHARED_POS_TYPE_DETERMINER 3
#define GIA_SHARED_POS_TYPE_UNKNOWN 4
#define GIA_SHARED_POS_TYPE_PREDETERMINER 5
#define GIA_SHARED_POS_TYPE_POSSESSIVEENDING 6
#define GIA_SHARED_POS_TYPE_MODALAUXILIARY 7
#define GIA_SHARED_POS_TYPE_PREPOSITION 8
#define GIA_SHARED_POS_TYPE_ADJECTIVE 9
#define GIA_SHARED_POS_TYPE_NOUN 10
#define GIA_SHARED_POS_TYPE_ADVERB 11
#define GIA_SHARED_POS_TYPE_PRONOUN_PERSONAL 12
#define GIA_SHARED_POS_TYPE_PRONOUN_POSSESSIVE 13
#define GIA_SHARED_POS_TYPE_PARTICLE 14
#define GIA_SHARED_POS_TYPE_INTERJECTION 15
#define GIA_SHARED_POS_TYPE_VERB 16
#define GIA_SHARED_POS_TYPE_WH 17
#define GIA_SHARED_POS_TYPE_PUNCTUATION_QUOTE 18
#define GIA_SHARED_POS_TYPE_PUNCTUATION_DIVISION 19
#define GIA_SHARED_POS_TYPE_PUNCTUATION_END_OF_SENTENCE 20
#define GIA_SHARED_POS_TYPE_AUXILIARY_BEING 21
#define GIA_SHARED_POS_TYPE_AUXILIARY_HAVING 22
#define GIA_SHARED_POS_TYPE_AUXILIARY_DOING 23
#define GIA_SHARED_POS_TYPE_AUXILIARY 24
#define GIA_SHARED_POS_TYPE_PRONOUN_DEMONSTRATIVE 25
#define GIA_SHARED_POS_TYPE_PRONOUN_INDEFINITE 26
#define GIA_SHARED_POS_TYPE_PRONOUN_INTERROGATIVE 27
#define GIA_SHARED_POS_TYPE_PRONOUN_PERSONAL_OBJECT 28
#define GIA_SHARED_POS_TYPE_PRONOUN_PERSONAL_SUBJECT 29
#define GIA_SHARED_POS_TYPE_PRONOUN_POSSESSIVE_ADJECTIVE 30
#define GIA_SHARED_POS_TYPE_PRONOUN_POSSESSIVE_ALONE 31
#define GIA_SHARED_POS_TYPE_PRONOUN_REFLEXIVE 32
#define GIA_SHARED_POS_TYPE_PRONOUN_RELATIVE 33
#define GIA_SHARED_POS_TYPE_CONJUNCTION_COORDINATING 34
#define GIA_SHARED_POS_TYPE_CONJUNCTION_SUBCOORDINATING 35
#define GIA_SHARED_POS_TYPE_CONJUNCTION_CORRELATIVE_FIRST 36	
#define GIA_SHARED_POS_TYPE_CONJUNCTION_CORRELATIVE_SECOND 37
#define GIA_SHARED_POS_TYPE_DATE 38
#define GIA_SHARED_POS_TYPE_UNIT 39
#define GIA_SHARED_POS_TYPE_MONEY 40
#define GIA_SHARED_POS_TYPE_TITLE 41
#define GIA_SHARED_POS_TYPE_PROPERNOUN_FIRST_MALE 42
#define GIA_SHARED_POS_TYPE_PROPERNOUN_FIRST_FEMALE 43
#define GIA_SHARED_POS_TYPE_PROPERNOUN_FAMILY 44
#define GIA_SHARED_POS_TYPE_PROPERNOUN_PLACE 45
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE5 46
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE6 47
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE7 48
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE8 49
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE9 50
#define GIA_SHARED_POS_TYPE_POSINSERTTEMPLATE0 51


#define GIA_SHARED_POS_TYPE_ARRAY_NUMBER_OF_TYPES (52)	
#define GIA_SHARED_POS_TYPE_NAME_UNDEFINED "undefined"
#define GIA_SHARED_POS_TYPE_NAME_CONJUNCTION "conjunction"
#define GIA_SHARED_POS_TYPE_NAME_NUMBER "number"
#define GIA_SHARED_POS_TYPE_NAME_DETERMINER "determiner"
#define GIA_SHARED_POS_TYPE_NAME_UNKNOWN "unknown"
#define GIA_SHARED_POS_TYPE_NAME_PREDETERMINER "predeterminer"
#define GIA_SHARED_POS_TYPE_NAME_POSSESSIVEENDING "possessiveEnding"
#define GIA_SHARED_POS_TYPE_NAME_MODALAUXILIARY "modalAuxiliary"
#define GIA_SHARED_POS_TYPE_NAME_PREPOSITION "preposition"
#define GIA_SHARED_POS_TYPE_NAME_ADJECTIVE "adjective"
#define GIA_SHARED_POS_TYPE_NAME_NOUN "noun"
#define GIA_SHARED_POS_TYPE_NAME_ADVERB "adverb"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_PERSONAL "pronounPersonal"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_POSSESSIVE "pronounPossessive"
#define GIA_SHARED_POS_TYPE_NAME_PARTICLE "particle"
#define GIA_SHARED_POS_TYPE_NAME_INTERJECTION "interjection"
#define GIA_SHARED_POS_TYPE_NAME_VERB "verb"
#define GIA_SHARED_POS_TYPE_NAME_WH "wh"
#define GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_QUOTE "punctuationQuote"
#define GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_DIVISION "punctuationDivision"
#define GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_END_OF_SENTENCE "punctuationEndOfSentence"
#define GIA_SHARED_POS_TYPE_NAME_AUXILIARY_BEING "auxiliaryBeing"
#define GIA_SHARED_POS_TYPE_NAME_AUXILIARY_HAVING "auxiliaryHaving"
#define GIA_SHARED_POS_TYPE_NAME_AUXILIARY_DOING "auxiliaryDoing"
#define GIA_SHARED_POS_TYPE_NAME_AUXILIARY "auxiliary"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_DEMONSTRATIVE "pronounDemonstrative"	
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_INDEFINITE "pronounIndefinite"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_INTERROGATIVE "pronounInterrogative"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_PERSONAL_OBJECT "pronounPersonalObject"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_PERSONAL_SUBJECT "pronounPersonalSubject"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_POSSESSIVE_ADJECTIVE "pronounPossessiveAdjective"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_POSSESSIVE_ALONE "pronounPossessiveAlone"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_REFLEXIVE "pronounReflexive"
#define GIA_SHARED_POS_TYPE_NAME_PRONOUN_RELATIVE "pronounRelative"
#define GIA_SHARED_POS_TYPE_NAME_CONJUNCTION_COORDINATING "conjunctionCoordinating"
#define GIA_SHARED_POS_TYPE_NAME_CONJUNCTION_SUBCOORDINATING "conjunctionSubcoordinating"
#define GIA_SHARED_POS_TYPE_NAME_CONJUNCTION_CORRELATIVE_FIRST "conjunctionCorrelativeFirst"
#define GIA_SHARED_POS_TYPE_NAME_CONJUNCTION_CORRELATIVE_SECOND "conjunctionCorrelativeSecond"
#define GIA_SHARED_POS_TYPE_NAME_DATE "date"
#define GIA_SHARED_POS_TYPE_NAME_UNIT "unit"
#define GIA_SHARED_POS_TYPE_NAME_MONEY "money"
#define GIA_SHARED_POS_TYPE_NAME_TITLE "title"
#define GIA_SHARED_POS_TYPE_NAME_PROPERNOUN_FIRST_MALE "propernounFirstMale"
#define GIA_SHARED_POS_TYPE_NAME_PROPERNOUN_FIRST_FEMALE "propernounFirstFemale"
#define GIA_SHARED_POS_TYPE_NAME_PROPERNOUN_FAMILY "propernounFamily"
#define GIA_SHARED_POS_TYPE_NAME_PROPERNOUN_PLACE "propernounPlace"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE5 "posinserttemplate5"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE6 "posinserttemplate6"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE7 "posinserttemplate7"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE8 "posinserttemplate8"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE9 "posinserttemplate9"
#define GIA_SHARED_POS_TYPE_NAME_POSINSERTTEMPLATE0 "posinserttemplate10"

#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_NAME_DETERMINER_LIMITED_INDEFINITE "determinerLimitedIndefinite"
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_NAME_SPECIAL_REDUCED_CONJUNCTION "specialReducedConjunction"
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_UNDEFINED (GIA_SHARED_POS_TYPE_UNDEFINED)		//added in case Stanford POS extraction does not equate exactly to PENN tree bank specification
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_CONJUNCTION (GIA_SHARED_POS_TYPE_CONJUNCTION)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_NUMBER (GIA_SHARED_POS_TYPE_NUMBER)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_DETERMINER (GIA_SHARED_POS_TYPE_DETERMINER)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_UNKNOWN (GIA_SHARED_POS_TYPE_UNKNOWN)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PREDETERMINER (GIA_SHARED_POS_TYPE_PREDETERMINER)	//predeterminer could be merged with adjective
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_POSSESSIVEENDING (GIA_SHARED_POS_TYPE_POSSESSIVEENDING)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_MODALAUXILIARY (GIA_SHARED_POS_TYPE_MODALAUXILIARY)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PREPOSITION (GIA_SHARED_POS_TYPE_PREPOSITION)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_ADJECTIVE (GIA_SHARED_POS_TYPE_ADJECTIVE)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_NOUN (GIA_SHARED_POS_TYPE_NOUN)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_ADVERB (GIA_SHARED_POS_TYPE_ADVERB)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PRONOUN_PERSONAL (GIA_SHARED_POS_TYPE_PRONOUN_PERSONAL)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PRONOUN_POSSESSIVE (GIA_SHARED_POS_TYPE_PRONOUN_POSSESSIVE)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PARTICLE (GIA_SHARED_POS_TYPE_PARTICLE)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_INTERJECTION (GIA_SHARED_POS_TYPE_INTERJECTION)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_VERB (GIA_SHARED_POS_TYPE_VERB)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_WH (GIA_SHARED_POS_TYPE_WH)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PUNCTUATION_DIVISION (GIA_SHARED_POS_TYPE_PUNCTUATION_DIVISION)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PUNCTUATION_QUOTE (GIA_SHARED_POS_TYPE_PUNCTUATION_QUOTE)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PUNCTUATION_END_OF_SENTENCE (GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_END_OF_SENTENCE)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_BEING (GIA_SHARED_POS_TYPE_AUXILIARY_BEING)		//additional case required for GIA semantics extraction
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_HAVING (GIA_SHARED_POS_TYPE_AUXILIARY_HAVING)		//additional case required for GIA semantics extraction
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_DOING (GIA_SHARED_POS_TYPE_AUXILIARY_DOING)		//additional case required for GIA semantics extraction






#ifdef GIA_SEM_REL_TRANSLATOR

#define FEATURE_POS_TAG_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_NUMBER_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_DETERMINER_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_UNKNOWN_ARRAY_NUMBER_OF_TYPES 6
#define FEATURE_POS_TAG_PREDETERMINER_ARRAY_NUMBER_OF_TYPES 1		//predeterminer could be merged with adjective
#define FEATURE_POS_TAG_POSSESSIVEENDING_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_MODALAUXILIARY_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_PREPOSITION_ARRAY_NUMBER_OF_TYPES 2
#define FEATURE_POS_TAG_ADJECTIVE_ARRAY_NUMBER_OF_TYPES 3
#define FEATURE_POS_TAG_NOUN_ARRAY_NUMBER_OF_TYPES 4
#define FEATURE_POS_TAG_ADVERB_ARRAY_NUMBER_OF_TYPES 3
#define FEATURE_POS_TAG_PRONOUN_PERSONAL_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_PRONOUN_POSSESSIVE_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_PARTICLE_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_INTERJECTION_ARRAY_NUMBER_OF_TYPES 1
#define FEATURE_POS_TAG_VERB_ARRAY_NUMBER_OF_TYPES 6
#define FEATURE_POS_TAG_WH_ARRAY_NUMBER_OF_TYPES 4
#define FEATURE_POS_TAG_PUNCTUATION_QUOTE_ARRAY_NUMBER_OF_TYPES 7
#ifdef GIA_SEM_REL_TRANSLATOR_SUPPORT_QUERIES
#define FEATURE_POS_TAG_PUNCTUATION_DIVISION_ARRAY_NUMBER_OF_TYPES 3
#define FEATURE_POS_TAG_PUNCTUATION_END_OF_SENTENCE_ARRAY_NUMBER_OF_TYPES 1
#else
#define FEATURE_POS_TAG_PUNCTUATION_DIVISION_ARRAY_NUMBER_OF_TYPES 2
#define FEATURE_POS_TAG_PUNCTUATION_END_OF_SENTENCE_ARRAY_NUMBER_OF_TYPES 2
#endif
static string featurePOStagCoordinatingConjunctionArray[FEATURE_POS_TAG_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_COORDINATING_CONJUNCTION_CC};
static string featurePOStagNumberArray[FEATURE_POS_TAG_NUMBER_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_CARDINALNUMBER_CD};
static string featurePOStagDeterminerArray[FEATURE_POS_TAG_DETERMINER_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_DETERMINER};
static string featurePOStagUnknownArray[FEATURE_POS_TAG_UNKNOWN_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_UNKNOWN_FOREIGNWORD_FW, FEATURE_POS_TAG_UNKNOWN_EXISTENTIAL_THERE, FEATURE_POS_TAG_UNKNOWN_LISTITEMMARKER_LS, FEATURE_POS_TAG_UNKNOWN_SYMBOL_SYM, FEATURE_POS_TAG_PUNCTUATION_HASH, FEATURE_POS_TAG_PUNCTUATION_DOLLAR};
static string featurePOStagPredeterminerArray[FEATURE_POS_TAG_PREDETERMINER_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_UNKNOWN_PREDETERMINER_PDT};	//predeterminer could be merged with adjective
static string featurePOStagPossessiveEndingArray[FEATURE_POS_TAG_POSSESSIVEENDING_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_UNKNOWN_POSSESSIVEENDING_POS};
static string featurePOStagModalAuxiliaryArray[FEATURE_POS_TAG_MODALAUXILIARY_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_MODALAUXILIARY_MD};
static string featurePOStagPrepositionArray[FEATURE_POS_TAG_PREPOSITION_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PREPOSITION_IN, FEATURE_POS_TAG_PREPOSITION_TO};
static string featurePOStagAdjectiveArray[FEATURE_POS_TAG_ADJECTIVE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_ADJECTIVE_JJ, FEATURE_POS_TAG_ADJECTIVE_COMPARATIVE_JJR, FEATURE_POS_TAG_ADJECTIVE_SUPERLATIVE_JJS};
static string featurePOStagNounArray[FEATURE_POS_TAG_NOUN_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_NOUN_NN, FEATURE_POS_TAG_NOUN_NNS, FEATURE_POS_TAG_NOUN_NNP, FEATURE_POS_TAG_NOUN_NNPS};
static string featurePOStagAdverbArray[FEATURE_POS_TAG_ADVERB_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_ADVERB, FEATURE_POS_TAG_ADVERB_COMPARATIVE, FEATURE_POS_TAG_ADVERB_SUPERLATIVE};
static string featurePOStagPronounPersonalArray[FEATURE_POS_TAG_PRONOUN_PERSONAL_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PRONOUN_PERSONAL_PRONOUN_PRP};
static string featurePOStagPronounPossessiveArray[FEATURE_POS_TAG_PRONOUN_POSSESSIVE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PRONOUN_POSSESSIVE_PRONOUN_PPDOLLAR};
static string featurePOStagParticleArray[FEATURE_POS_TAG_PARTICLE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PARTICLE_RP};
static string featurePOStagInterjectionArray[FEATURE_POS_TAG_INTERJECTION_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_INTERJECTION_UH};
static string featurePOStagVerbArray[FEATURE_POS_TAG_VERB_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_VERB_VB, FEATURE_POS_TAG_VERB_VBD, FEATURE_POS_TAG_VERB_VBG, FEATURE_POS_TAG_VERB_VBN, FEATURE_POS_TAG_VERB_VBP, FEATURE_POS_TAG_VERB_VBZ};
static string featurePOStagWhArray[FEATURE_POS_TAG_WH_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_WH_DETERMINER_WDT, FEATURE_POS_TAG_WH_PRONOUN_WP, FEATURE_POS_TAG_WH_POSSESIVEPRONOUN_WPDOLLAR, FEATURE_POS_TAG_WH_ADVERB_WRB};
static string featurePOStagPunctuationQuoteArray[FEATURE_POS_TAG_PUNCTUATION_QUOTE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PUNCTUATION_QUOTE_LEFTBRACKET, FEATURE_POS_TAG_PUNCTUATION_QUOTE_RIGHTBRACKET, FEATURE_POS_TAG_PUNCTUATION_QUOTE_STRAIGHTDOUBLEQUOTE, FEATURE_POS_TAG_PUNCTUATION_QUOTE_LEFTOPENSINGLEQUOTE, FEATURE_POS_TAG_PUNCTUATION_QUOTE_LEFTOPENDOUBLEQUOTE, FEATURE_POS_TAG_PUNCTUATION_QUOTE_RIGHTCLOSESINGLEQUOTE, FEATURE_POS_TAG_PUNCTUATION_QUOTE_RIGHTCLOSEDOUBLEQUOTE};
#ifdef GIA_SEM_REL_TRANSLATOR_SUPPORT_QUERIES
static string featurePOStagPunctuationDivisionArray[FEATURE_POS_TAG_PUNCTUATION_DIVISION_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PUNCTUATION_DIVISION_COMMA, FEATURE_POS_TAG_PUNCTUATION_DIVISION_COLON_OR_SEMICOLON, FEATURE_POS_TAG_PUNCTUATION_QUESTIONMARK};	//NB FEATURE_POS_TAG_PUNCTUATION_QUESTIONMARK has been set to a different POS value than FEATURE_POS_TAG_PUNCTUATION_QUOTE_FULLSTOP; but otherwise its inclusion here is arbitrary
static string featurePOStagPunctuationEndOfSentenceArray[FEATURE_POS_TAG_PUNCTUATION_QUOTE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PUNCTUATION_QUOTE_FULLSTOP};	//is this used? (added 3f1a)
#else
static string featurePOStagPunctuationDivisionArray[FEATURE_POS_TAG_PUNCTUATION_DIVISION_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PUNCTUATION_DIVISION_COMMA, FEATURE_POS_TAG_PUNCTUATION_DIVISION_COLON_OR_SEMICOLON};
static string featurePOStagPunctuationEndOfSentenceArray[FEATURE_POS_TAG_PUNCTUATION_QUOTE_ARRAY_NUMBER_OF_TYPES] = {FEATURE_POS_TAG_PUNCTUATION_QUOTE_FULLSTOP, FEATURE_POS_TAG_PUNCTUATION_QUESTIONMARK};
#endif



#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_DETERMINER_LIMITED_INDEFINITE (GIA_SHARED_POS_TYPE_AUXILIARY_DOING+1)	//OLD: GIA_SHARED_POS_TYPE_AUXILIARY_DOING
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_SPECIAL_REDUCED_CONJUNCTION (GIA_SHARED_POS_TYPE_AUXILIARY_DOING+2)	//OLD: GIA_SHARED_POS_TYPE_AUXILIARY_DOING+1
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_ARRAY_NUMBER_OF_TYPES (GIA_SHARED_POS_TYPE_AUXILIARY_DOING+3)		//OLD: GIA_SHARED_POS_TYPE_AUXILIARY_DOING+2
static string GIAconnectionistNetworkPOStypeNameArray[GIA_SEM_REL_TRANSLATOR_POS_TYPE_ARRAY_NUMBER_OF_TYPES] = {GIA_SHARED_POS_TYPE_NAME_UNDEFINED, GIA_SHARED_POS_TYPE_NAME_CONJUNCTION, GIA_SHARED_POS_TYPE_NAME_NUMBER, GIA_SHARED_POS_TYPE_NAME_DETERMINER, GIA_SHARED_POS_TYPE_NAME_UNKNOWN, GIA_SHARED_POS_TYPE_NAME_PREDETERMINER, GIA_SHARED_POS_TYPE_NAME_POSSESSIVEENDING, GIA_SHARED_POS_TYPE_NAME_MODALAUXILIARY, GIA_SHARED_POS_TYPE_NAME_PREPOSITION, GIA_SHARED_POS_TYPE_NAME_ADJECTIVE, GIA_SHARED_POS_TYPE_NAME_NOUN, GIA_SHARED_POS_TYPE_NAME_ADVERB, GIA_SHARED_POS_TYPE_NAME_PRONOUN_PERSONAL, GIA_SHARED_POS_TYPE_NAME_PRONOUN_POSSESSIVE, GIA_SHARED_POS_TYPE_NAME_PARTICLE, GIA_SHARED_POS_TYPE_NAME_INTERJECTION, GIA_SHARED_POS_TYPE_NAME_VERB, GIA_SHARED_POS_TYPE_NAME_WH, GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_QUOTE, GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_DIVISION, GIA_SHARED_POS_TYPE_NAME_PUNCTUATION_END_OF_SENTENCE, GIA_SHARED_POS_TYPE_NAME_AUXILIARY_BEING, GIA_SHARED_POS_TYPE_NAME_AUXILIARY_HAVING, GIA_SHARED_POS_TYPE_NAME_AUXILIARY_DOING, GIA_SEM_REL_TRANSLATOR_POS_TYPE_NAME_DETERMINER_LIMITED_INDEFINITE, GIA_SEM_REL_TRANSLATOR_POS_TYPE_NAME_SPECIAL_REDUCED_CONJUNCTION};
static int featureRelexPOStypeCrossReferenceGIAconnectionistNetworkPOStypeArray[FEATURE_RELEX_POS_NUMBER_OF_TYPES] = {GIA_SEM_REL_TRANSLATOR_POS_TYPE_UNDEFINED, GIA_SEM_REL_TRANSLATOR_POS_TYPE_ADJECTIVE, GIA_SEM_REL_TRANSLATOR_POS_TYPE_ADVERB, GIA_SEM_REL_TRANSLATOR_POS_TYPE_PUNCTUATION_DIVISION, GIA_SEM_REL_TRANSLATOR_POS_TYPE_DETERMINER, GIA_SEM_REL_TRANSLATOR_POS_TYPE_NOUN, GIA_SEM_REL_TRANSLATOR_POS_TYPE_PARTICLE, GIA_SEM_REL_TRANSLATOR_POS_TYPE_PREPOSITION, GIA_SEM_REL_TRANSLATOR_POS_TYPE_PUNCTUATION_QUOTE, GIA_SEM_REL_TRANSLATOR_POS_TYPE_VERB, GIA_SEM_REL_TRANSLATOR_POS_TYPE_UNKNOWN};

#ifdef GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISE_BASED_ON_CONJUNCTIONS
	#define FEATURE_SPECIAL_REDUCED_CONJUNCTIONS_NUMBER_OF_TYPES (2)
	static string featureSpecialReducedConjunctionArray[FEATURE_SPECIAL_REDUCED_CONJUNCTIONS_NUMBER_OF_TYPES] = {"and", "or"};
	#define GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISE_BASED_ON_CONJUNCTIONS_ILLEGAL_CENTRAL_WORD_NUMBER_OF_TYPES  (3)
	static string semanticParserOptimiseBasedOnConjunctionsIllegalSecondWordInTupleArray[GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISE_BASED_ON_CONJUNCTIONS_ILLEGAL_CENTRAL_WORD_NUMBER_OF_TYPES] = {",", "and", "or"};

#endif

/*
//requires updating (add more cases from PENN tree)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_NOUN (0)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_VERB_OR_PARTICIPLE (1)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_ADJECTIVE_OR_ADVERB (2)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_PREPOSITION (3)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_BEING (4)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_HAVING (5)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_DOING (6)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_AUXILIARY_MODAL (7)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_DETERMINER_THATWHICH (8)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_DETERMINER (9)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_COMMA (10)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_CONJUNCTION (11)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_INTERJECTION (12)
#define GIA_SEM_REL_TRANSLATOR_POS_TYPE_ARRAY_NUMBER_OF_TYPES (13)
static string GIAconnectionistNetworkPOStypeNameArray[GIA_SEM_REL_TRANSLATOR_POS_TYPE_ARRAY_NUMBER_OF_TYPES] = {"isNoun", "isVerbOrParticiple", "isAdjectiveOrAdverb", "isPreposition", "isAuxillaryBeing", "isAuxillaryHaving", "isAuxillaryDoing", "isAuxillaryModal", "isDeterminerThatWhich", "isDeterminer", "isComma", "isConjunction", "isInterjection"};
*/



#ifdef GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE
#define GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE_SEMANTIC_RELATION_NUMBER_OF_DIRECTIONS (2)
#define GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE_SEMANTIC_RELATION_NUMBER_OF_SAMEREFERENCESET (2)
#define GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE_SEMANTIC_RELATION_NUMBER_OF_TYPES (GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_NUMBER_OF_TYPES*GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE_SEMANTIC_RELATION_NUMBER_OF_DIRECTIONS*GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE_SEMANTIC_RELATION_NUMBER_OF_SAMEREFERENCESET)
#endif

#define GIA_SEM_REL_TRANSLATOR_SYNTACTIC_DEPENDENCY_RELATION_SECONDARY_NUMBER_OF_TYPES (4)
static string GIA2syntacticDependencyRelationSecondaryNameArray[GIA_SEM_REL_TRANSLATOR_SYNTACTIC_DEPENDENCY_RELATION_SECONDARY_NUMBER_OF_TYPES] = {GIA_SYN_REL_TRANSLATOR_RELATION_TYPE_MODAL_AUX, GIA_SYN_REL_TRANSLATOR_RELATION_TYPE_PASSIVE_AUX, GIA_SYN_REL_TRANSLATOR_RELATION_TYPE_COPULA, GIA_SYN_REL_TRANSLATOR_RELATION_TYPE_DETERMINER};		//is GIA_SYN_REL_TRANSLATOR_RELATION_TYPE_PRENOMIAL_MODIFIER required to be added to this list?
#define GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_SECONDARY_NUMBER_OF_TYPES (3)
static string GIA2semanticDependencyRelationSecondaryNameArray[GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_SECONDARY_NUMBER_OF_TYPES] = {"determiner", "compositionAuxiliary", "modalAuxiliaryOrCopula"};		//required to disable is/have etc nodes only

#endif

#ifdef GIA_SEM_REL_TRANSLATOR_COMMON

#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY_DIRECT (12)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION_DIRECT (13)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_DETERMINER (14)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MODAL_AUXILIARY_OR_COPULA (15)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MODAL_AUXILIARY_OR_COPULA_SINGLE (16)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_QUANTITY (17)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_COMPOSITION_AUXILIARY_NOT_USED (18)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION_DIRECT_ALIAS (19)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION_ALIAS (20)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION_REVERSE_ALIAS (21)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_PRENOMINAL_MODIFIER (22)
#ifdef GIA_SEM_REL_TRANSLATOR_SUBSETS_OPTIMISED_DATABASE
	#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_NONE (23)
#endif
#ifdef GIA_TXT_REL_TRANSLATOR_RULES
//#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ENTITY_GRAMMAR
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MULTIWORD_AUXILIARY (24)
//#ifndef GIA_PREPROCESSOR_WORD_MULTIWORD_REDUCTION
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MULTIWORD_PREPOSITION (25)	//assumes that GIA_PREPROCESSOR_WORD_MULTIWORD_REDUCTION multiword preposition reduction is disabled
//#endif
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MULTIWORD_ALIAS (26)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MULTIWORD_DATE (27)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_PREDETERMINER (28)
//#endif
//#ifdef GIA_TXT_REL_TRANSLATOR_RULES_LOGIC_REFERENCES
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_DEFINITION (29)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_DEFINITION_REVERSE (30)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_ACTION (31)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_ACTION_REVERSE (32)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_CONDITION (33)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_CONDITION_REVERSE (34)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_CONCLUSION (35)	//direct
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_LOGIC_CONJUNCTION (36)	//direct
//#endif
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION_NEW (37)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MEASURE (38)
#define GIA_ENTITY_VECTOR_CONNECTION_TYPE_MEASURE_PER (39)
#endif
#ifdef GIA_TXT_REL_TRANSLATOR_RULES
#define GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_NUMBER_OF_TYPES (GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES + 12 + 16)	//extends GIAentityNodeClass.h GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES
static string GIA2semanticDependencyRelationNameArray[GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_NUMBER_OF_TYPES] = {"action", "actionReverse", "condition", "conditionReverse", "property", "propertyReverse", "definition", "definitionReverse", "relationshipSubject", "relationshipObject", "instance", "instanceReverse", "propertyDirect", "definitionDirect", "determiner", "modalAuxiliaryOrCopula", "modalAuxiliaryOrCopulaSingle", "quantity", "compositionAuxiliaryNOTUSED", "definitionDirectAlias", "definitionAlias", "definitionReverseAlias", "prenominalModifier", "none", "multiwordAuxiliary", "multiwordPreposition", "multiwordAlias", "multiwordDate", "numerosityPredeterminer", "logicDefinition", "logicDefinitionReverse", "logicAction", "logicActionReverse", "logicCondition", "logicConditionReverse", "logicConclusion", "logicConjunction", "conditionNew", "measure", "measurePer"};
#else
#define GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_NUMBER_OF_TYPES (GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES + 12)	//extends GIAentityNodeClass.h GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES
static string GIA2semanticDependencyRelationNameArray[GIA_SEM_REL_TRANSLATOR_SEMANTIC_DEPENDENCY_RELATION_NUMBER_OF_TYPES] = {"action", "actionReverse", "condition", "conditionReverse", "property", "propertyReverse", "definition", "definitionReverse", "relationshipSubject", "relationshipObject", "instance", "instanceReverse", "propertyDirect", "definitionDirect", "determiner", "modalAuxiliaryOrCopula", "modalAuxiliaryOrCopulaSingle", "quantity", "compositionAuxiliaryNOTUSED", "definitionDirectAlias", "definitionAlias", "definitionReverseAlias", "prenominalModifier", "none"};
#endif

#endif





#endif
