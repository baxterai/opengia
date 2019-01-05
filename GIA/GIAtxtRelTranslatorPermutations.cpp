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
 * File Name: GIAtxtRelTranslatorPermutations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3g1c 24-April-2018
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Permutations
 * /
 *******************************************************************************/


#include "GIAtxtRelTranslatorPermutations.hpp"

#ifdef GIA_TXT_REL_TRANSLATOR_RULES_GIA3


bool GIAtxtRelTranslatorPermutationsClass::executeTxtRelTranslatorWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes)
{
	bool result = true;

	/*
	algorithm (v0.1);
		For every word in sentence
			calculate pos ambiguity info (possible pos types)
		Generate all possible pos sequences representing sentence
		For every possible pos sequence representing sentence
			identify the set of logic/reference set groups supporting (successfully parsing) the pos sequence
				interpret unknown words (pos types) as wild cards
				take the logic/reference set group that most successfully parses the sentence

		In the future use a neural net to train the system to identify new rule groups (or upgrade/refine rule groups)
	*/
	
	//cout << "GIAtxtRelTranslatorPermutationsClass::executeTxtRelTranslatorWrapper" << endl;

	GIApreprocessorSentence* currentGIApreprocessorSentenceInList = translatorVariables->firstGIApreprocessorSentenceInList;
	while(currentGIApreprocessorSentenceInList->next != NULL)
	{			
		#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_RULES_PRINT_PARSE_PROCESS
		cout << "GIAtxtRelTranslatorPermutationsClass::executeTxtRelTranslator{}: sentence " << currentGIApreprocessorSentenceInList->sentenceIndexOriginal << ", sentenceContents = " << GIApreprocessorWordClassObject.printWordListString(GIApreprocessorSentenceClassObject.getSentenceContents(currentGIApreprocessorSentenceInList)) << endl;
		#endif
			
		vector<uint64_t> POSambiguityInfoPermutation;
		vector<GIApreprocessorPlainTextWord*>* sentenceContents = GIApreprocessorSentenceClassObject.getSentenceContents(currentGIApreprocessorSentenceInList);
		
		if(!GIApreprocessorPOStagger.determinePOSambiguityInfoWrapper(sentenceContents, &POSambiguityInfoPermutation))
		{
			result = false;
		}
			
		if(!executeTxtRelTranslator(translatorVariables, GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, currentGIApreprocessorSentenceInList, &POSambiguityInfoPermutation))
		{
			result = false;
		}
			
		currentGIApreprocessorSentenceInList = currentGIApreprocessorSentenceInList->next;
	}
	
	#ifndef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
	if(!transferParseTreePOStypeInferredToWordList(translatorVariables))	//is this required without GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START?
	{
		result = false;
	}
	#endif
	
	return result;
}


bool GIAtxtRelTranslatorPermutationsClass::executeTxtRelTranslator(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIApreprocessorSentence* currentGIApreprocessorSentenceInList, vector<uint64_t>* POSambiguityInfoPermutation)
{
	bool result = true;

	vector<GIApreprocessorPlainTextWord*>* sentenceContents = GIApreprocessorSentenceClassObject.getSentenceContents(currentGIApreprocessorSentenceInList);

	/*
	algorithm (v0.1);
		For every word in sentence
			calculate pos ambiguity info (possible pos types)
		Generate all possible pos sequences representing sentence
		For every possible pos sequence representing sentence
			identify the set of logic/reference set groups supporting (successfully parsing) the pos sequence
				interpret unknown words (pos types) as wild cards
				take the logic/reference set group that most successfully parses the sentence

		In the future use a neural net to train the system to identify new rule groups (or upgrade/refine rule groups)
	*/
	
	GIAtxtRelTranslatorRulesGroup* firstParseTreeGroup = new GIAtxtRelTranslatorRulesGroup();
	currentGIApreprocessorSentenceInList->firstParseTreeGroup = firstParseTreeGroup;
		
		
	int performance = 0; 
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
	int minIndexOfMatchesFoundBackupOptimum = calculateMinIndexOfMatchesFound(sentenceContents);
	vector<vector<uint64_t>*> POSambiguityInfoUnambiguousPermutationArray;
	vector<uint64_t>* POSambiguityInfoUnambiguousPermutationNew = new vector<uint64_t>(POSambiguityInfoPermutation->size());
	POSambiguityInfoUnambiguousPermutationArray.push_back(POSambiguityInfoUnambiguousPermutationNew);
	GIApreprocessorPOStagger.generatePOSambiguityInfoUnambiguousPermutationArray(&POSambiguityInfoUnambiguousPermutationArray, POSambiguityInfoPermutation, POSambiguityInfoUnambiguousPermutationNew, 0);
	int iOptimum = 0;
	#endif
	bool foundParse = false;
	bool parseIsolatedSubreferenceSets1 = false;
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_PARSE_ISOLATED_SUBREFERENCE_SETS_OPTIMISED
	GIApreprocessorSentenceClassObject.calculateParseIsolatedSubreferenceSets1(currentGIApreprocessorSentenceInList, &parseIsolatedSubreferenceSets1);
	#endif

	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
	if(generateParseTreeIntroWrapper(translatorVariables, GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, firstParseTreeGroup, &performance, parseIsolatedSubreferenceSets1, &POSambiguityInfoUnambiguousPermutationArray, &iOptimum, &minIndexOfMatchesFoundBackupOptimum))	
	#else
	if(generateParseTreeIntroWrapper(translatorVariables, GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, firstParseTreeGroup, &performance, parseIsolatedSubreferenceSets1, POSambiguityInfoPermutation))
	#endif
	{
		foundParse = true;
	}
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_PARSE_ISOLATED_SUBREFERENCE_SETS
	if(!foundParse)
	{
		bool parseIsolatedSubreferenceSets2 = true;
		#ifdef GIA_TXT_REL_TRANSLATOR_RULES_PARSE_ISOLATED_SUBREFERENCE_SETS_OPTIMISED
		if(GIApreprocessorSentenceClassObject.calculateParseIsolatedSubreferenceSets2(currentGIApreprocessorSentenceInList, &parseIsolatedSubreferenceSets2))
		{
		#endif
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
			if(generateParseTreeIntroWrapper(translatorVariables, GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, firstParseTreeGroup, &performance, parseIsolatedSubreferenceSets2, &POSambiguityInfoUnambiguousPermutationArray, &iOptimum, &minIndexOfMatchesFoundBackupOptimum))	
			#else
			if(generateParseTreeIntroWrapper(translatorVariables, GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, firstParseTreeGroup, &performance, parseIsolatedSubreferenceSets2, POSambiguityInfoPermutation))
			#endif
			{
				foundParse = true;
			}
		#ifdef GIA_TXT_REL_TRANSLATOR_RULES_PARSE_ISOLATED_SUBREFERENCE_SETS_OPTIMISED
		}
		#endif
	}
	#endif
	if(!foundParse)
	{
		//result = false;
	}

	#ifndef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
	if(foundParse)
	{

	}
	else
	{
		clearAllWordsAlreadyFoundMatchInComponent(sentenceContents, minIndexOfMatchesFoundBackupOptimum);	//redundant?	
		cerr << "GIAtxtRelTranslatorPermutationsClass::executeTxtRelTranslator{}: Failed to parse sentence " << currentGIApreprocessorSentenceInList->sentenceIndexOriginal << ", sentenceContents = " << GIApreprocessorWordClassObject.printWordListString(GIApreprocessorSentenceClassObject.getSentenceContents(currentGIApreprocessorSentenceInList)) << endl;
		//exit(EXIT_ERROR);
	}
	#endif
	#endif
	
	return result;
}


#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
bool GIAtxtRelTranslatorPermutationsClass::generateParseTreeIntroWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAtxtRelTranslatorRulesGroup* firstParseTreeGroup, int* performance, const bool parseIsolatedSubreferenceSets, vector<vector<uint64_t>*>* POSambiguityInfoUnambiguousPermutationArray, int* iOptimum, int* minIndexOfMatchesFoundBackupOptimum)
#else
bool GIAtxtRelTranslatorPermutationsClass::generateParseTreeIntroWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAtxtRelTranslatorRulesGroup* firstParseTreeGroup, int* performance, const bool parseIsolatedSubreferenceSets, vector<uint64_t>* POSambiguityInfoPermutation)
#endif
{
	bool result = false;
	
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
	int performanceMaxPermutationIndex = INT_DEFAULT_VALUE;
	int performanceMax = 0;
	#endif
	
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
	for(int i=0; i<POSambiguityInfoUnambiguousPermutationArray->size(); i++)
	{
		vector<uint64_t>* POSambiguityInfoPermutationTemp = (*POSambiguityInfoUnambiguousPermutationArray)[i];
		setSentenceContentsWordsUnambiguousPOSindex(sentenceContents, POSambiguityInfoPermutationTemp);

		//#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_RULES_PRINT_PARSE_PROCESS	
		#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE
		cout << "POSambiguityInfoUnambiguousPermutationArray index = " << i << endl;
		//GIApreprocessorPOStagger.printPOSambiguityInfoPermutation(POSambiguityInfoPermutationTemp);
		#endif

		GIAtxtRelTranslatorRulesGroup* firstParseTreeGroupTemp = new GIAtxtRelTranslatorRulesGroup();

		int minIndexOfMatchesFoundBackup2 = calculateMinIndexOfMatchesFound(sentenceContents);
	#else
		for(int w=0; w<sentenceContents->size(); w++)
		{
			(sentenceContents->at(w))->POSambiguityInfo = (*POSambiguityInfoPermutation)[w];
		}
		GIAtxtRelTranslatorRulesGroup* firstParseTreeGroupTemp = firstParseTreeGroup;
	#endif
	
		int performanceTemp = 0;
		bool passedTemp = false;
		#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
		if(GIAtxtRelTranslatorNeuralNetwork.executeTxtRelTranslatorNeuralNetwork(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, &performanceTemp, parseIsolatedSubreferenceSets, false))
		{
			passedTemp =  true;
			result = true;
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
			if(performanceTemp > performanceMax)
			{
				performanceMax = performanceTemp;
				performanceMaxPermutationIndex = i;
			}
			#endif
		}
		#else	
		if(generateParseTreeIntro(GIAtxtRelTranslatorRulesTokenLayers, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, firstParseTreeGroupTemp, &performanceTemp, parseIsolatedSubreferenceSets))
		{
			passedTemp =  true;
			result = true;
			#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_RULES_PRINT_PARSE_PROCESS
			cout << "passedTemp" << endl;
			#endif
			#ifndef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START	
			*performance = performanceTemp;
			#endif
		}
		#endif

	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START	
	}
	vector<uint64_t>* POSambiguityInfoPermutationTemp = (*POSambiguityInfoUnambiguousPermutationArray)[performanceMaxPermutationIndex];
	setSentenceContentsWordsUnambiguousPOSindex(sentenceContents, POSambiguityInfoPermutationTemp);
	int performanceTemp = 0;
	if(GIAtxtRelTranslatorNeuralNetwork.executeTxtRelTranslatorNeuralNetwork(translatorVariables, GIAtxtRelTranslatorRulesGroupTypes, sentenceContents, &performanceTemp, parseIsolatedSubreferenceSets, true))
	{
		result = true;	
		*performance = sentenceContents->size();	//hard set to maximum performance
	}		
	#endif
	#else
	#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START	
		if(updatePerformance(performanceTemp, performance, firstParseTreeGroup, firstParseTreeGroupTemp, passedTemp, minIndexOfMatchesFoundBackupOptimum, sentenceContents, minIndexOfMatchesFoundBackup2, NULL))
		{
			*iOptimum = i;	
		}
		
	}
	
	if(result)
	{
		//cout << "performance = " << performance << endl;
		restoreAllWordsAlreadyFoundMatchInComponent(sentenceContents, *performance);
	}
	#endif
	#endif

	return result;
}	

#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
bool GIAtxtRelTranslatorPermutationsClass::setSentenceContentsWordsUnambiguousPOSindex(vector<GIApreprocessorPlainTextWord*>* sentenceContents, vector<uint64_t>* POSambiguityInfoPermutationTemp)
{
	bool result = true;
	
	for(int w=0; w<sentenceContents->size(); w++)
	{
		GIApreprocessorPlainTextWord* contextWord = sentenceContents->at(w);
		unsigned char unambiguousPOSinfoIndex = GIA_PREPROCESSOR_POS_TYPE_UNDEFINED;
		bool wordAmbiguous = GIApreprocessorPOStaggerDatabase.determinePOSambiguityInfoIsAmbiguous(POSambiguityInfoPermutationTemp->at(w), &unambiguousPOSinfoIndex, false);
		contextWord->unambiguousPOSindex = unambiguousPOSinfoIndex;
		#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PROPAGATE
		//#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_RULES_PRINT_PARSE_PROCESS
		//cout << "unambiguousPOSinfoIndex = " << int(unambiguousPOSinfoIndex) << endl;
		cout << "GIApreprocessorPOStypeNameArray[unambiguousPOSinfoIndex] = " << GIApreprocessorPOStypeNameArray[unambiguousPOSinfoIndex] << endl;
		#endif
	}

	return result;
}
#endif
	

#endif
