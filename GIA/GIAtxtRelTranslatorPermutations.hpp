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
 * File Name: GIAtxtRelTranslatorPermutations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3j1d 03-August-2019
 * Requirements: requires plain text file
 * Description: Textual Relation Translator Permutations
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_TXT_REL_TRANSLATOR_PERMUTATIONS
#define HEADER_GIA_TXT_REL_TRANSLATOR_PERMUTATIONS

#include "GIAglobalDefs.hpp"

#ifdef GIA_TXT_REL_TRANSLATOR_RULES_GIA3

//#include "SHAREDvars.hpp"
#include "GIAtranslatorOperations.hpp"
#ifdef GIA_TXT_REL_TRANSLATOR_HYBRID
#include "GIAtxtRelTranslatorHybrid.hpp"
#endif
#include "GIAtxtRelTranslatorRules.hpp"
#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_HEAVY
#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_HEAVY_UNOPTIMISED
#include "GIAtxtRelTranslatorNeuralNetworkHeavyUnoptimised.hpp"
#else
#include "GIAtxtRelTranslatorNeuralNetworkHeavyOptimised.hpp"
#endif
#else
#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_UNOPTIMISED
#include "GIAtxtRelTranslatorNeuralNetworkLightUnoptimised.hpp"
#else
#include "GIAtxtRelTranslatorNeuralNetworkLightOptimised.hpp"
#endif
#endif
#else
#include "GIAtxtRelTranslatorNeuralNetworkInverse.hpp"
#endif
#include "GIAtxtRelTranslatorNeuralNetworkOperations.hpp"
#include "GIApreprocessorPOStagger.hpp"
#include "GIApreprocessorPOStaggerDatabase.hpp"
#include "GIApreprocessorWordClass.hpp"
#ifdef GIA_OUTPUT_INTERNAL_RELATIONS_IN_RELEX_FORMAT
#include "GIAnlp.hpp"
#endif
//#include "GIAtranslator.hpp"
#include "SHAREDvars.hpp"

class GIAtxtRelTranslatorPermutationsClass
{
	//private: SHAREDvarsClass SHAREDvars;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	#ifdef GIA_TXT_REL_TRANSLATOR_HYBRID
	private: GIAtxtRelTranslatorHybridClass GIAtxtRelTranslatorHybrid;
	#endif
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_HEAVY
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_HEAVY_UNOPTIMISED
	private: GIAtxtRelTranslatorNeuralNetworkHeavyUnoptimisedClass GIAtxtRelTranslatorNeuralNetwork;
	#else
	private: GIAtxtRelTranslatorNeuralNetworkHeavyOptimisedClass GIAtxtRelTranslatorNeuralNetwork;
	#endif
	#else
	#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_LIGHT_UNOPTIMISED
	private: GIAtxtRelTranslatorNeuralNetworkLightUnoptimisedClass GIAtxtRelTranslatorNeuralNetwork;	
	#else
	private: GIAtxtRelTranslatorNeuralNetworkLightOptimisedClass GIAtxtRelTranslatorNeuralNetwork;	
	#endif
	#endif
	private: GIAtxtRelTranslatorNeuralNetworkFormationClass GIAtxtRelTranslatorNeuralNetworkFormation;
	#else
	private: GIAtxtRelTranslatorNeuralNetworkInverseClass GIAtxtRelTranslatorNeuralNetworkInverse;	
	#endif
	private: GIAtxtRelTranslatorNeuralNetworkOperationsClass GIAtxtRelTranslatorNeuralNetworkOperations;	//required for printComponent/printParseTreeDebugIndentation	
	private: GIAtxtRelTranslatorRulesClass GIAtxtRelTranslatorRules;
	private: GIApreprocessorPOStaggerClass GIApreprocessorPOStagger;
	private: GIApreprocessorPOStaggerDatabaseClass GIApreprocessorPOStaggerDatabase;
	private: GIApreprocessorWordClassClass GIApreprocessorWordClassObject;
	private: GIApreprocessorSentenceClass GIApreprocessorSentenceClassObject;
	#ifdef GIA_OUTPUT_INTERNAL_RELATIONS_IN_RELEX_FORMAT
	private: GIAnlpClass GIAnlp;
	#endif
	private: SHAREDvarsClass SHAREDvars;


	public: bool executeTxtRelTranslatorWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes);
		public: bool executeTxtRelTranslatorWrapper2(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIApreprocessorSentence* currentGIApreprocessorSentenceInList);
		#ifndef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PARSE_SIMULTANEOUS_SET_WORD_POSTYPE_INFERRED_DYNAMIC
		private: bool transferParseTreePOStypeInferredToWordList(GIAtranslatorVariablesClass* translatorVariables);
			private: bool transferParseTreePOStypeInferredToWordList(GIAtxtRelTranslatorRulesGroupParseTree* currentParseTreeGroup, int layer);
		#endif
		public: bool executeTxtRelTranslator(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIApreprocessorSentence* currentGIApreprocessorSentenceInList, vector<uint64_t>* POSambiguityInfoPermutation);
			#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
			private: bool generateParseTreeIntroWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIApreprocessorSentence* currentGIApreprocessorSentenceInList, GIAtxtRelTranslatorRulesGroupParseTree* firstParseTreeGroup, int* performance, const bool parseIsolatedSubreferenceSets, vector<vector<uint64_t>*>* POSambiguityInfoUnambiguousPermutationArray, int* iOptimum, int* minIndexOfMatchesFoundBackupOptimum);
			#else
			private: bool generateParseTreeIntroWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<XMLparserTag*>* GIAtxtRelTranslatorRulesTokenLayers, vector<GIAtxtRelTranslatorRulesGroupType*>* GIAtxtRelTranslatorRulesGroupTypes, GIApreprocessorSentence* currentGIApreprocessorSentenceInList, GIAtxtRelTranslatorRulesGroupParseTree* firstParseTreeGroup, int* performance, const bool parseIsolatedSubreferenceSets, vector<uint64_t>* POSambiguityInfoPermutation);
			#endif
				#ifdef GIA_TXT_REL_TRANSLATOR_RULES_ITERATE_OVER_UNAMBIGUOUS_POS_PERMUTATIONS_AT_START
				private: bool setSentenceContentsWordsUnambiguousPOSindex(vector<GIApreprocessorPlainTextWord*>* sentenceContents, vector<uint64_t>* POSambiguityInfoPermutationTemp);
				#endif
				#ifdef GIA_TXT_REL_TRANSLATOR_NEURAL_NETWORK
				private: bool updatePerformanceNeuralNetwork(const int performanceTemp, int* performance, GIApreprocessorSentence* currentGIApreprocessorSentenceInList, GIAtxtRelTranslatorRulesGroupParseTree* firstParseTreeGroupTemp, const bool passedTemp, const int permutationIndex, int* performanceMaxPermutationIndex);
				private: bool deleteAllSubgroupsRecurse(GIAtxtRelTranslatorRulesGroupParseTree* currentParseTreeGroup, int layer);
				#endif
				
	#ifdef GIA_DEBUG_TXT_REL_TRANSLATOR_NEURAL_NETWORK_PRINT_FINAL2
	private: bool printParseTree(GIAtxtRelTranslatorRulesGroupParseTree* currentParseTreeGroup, int layer);
	#endif

};
#endif




#endif