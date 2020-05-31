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
 * File Name: GIAposRelTranslatorSANIPropagateCompactGenerate.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2020 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3l1d 28-May-2020
 * Requirements: 
 * Description: Part-of-speech Relation Translator SANI (Sequentially Activated Neuronal Input neural network) Propagate Compact - unsupervised training of sequence grammar parse network
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_POS_REL_TRANSLATOR_SANI_PROPAGATE_COMPACT_GENERATE
#define HEADER_GIA_POS_REL_TRANSLATOR_SANI_PROPAGATE_COMPACT_GENERATE

#include "GIAglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "XMLparserClass.hpp"
#include "GIAposRelTranslatorRules.hpp"
#include "GIAposRelTranslatorRulesGroupClass.hpp"
#include "GIAposRelTranslatorRulesComponentClass.hpp"
#include "GIAposRelTranslatorSANIPropagateOperations.hpp"
#include "GIAposRelTranslatorSANIPropagateCompact.hpp"
#include "GIAposRelTranslatorSANIFormation.hpp"
#include "GIApreprocessorSentenceClass.hpp"
#include "GIApreprocessorWordClass.hpp"
#include "ANNdisplay.hpp"



#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR

class GIAposRelTranslatorSANIPropagateCompactGenerateClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: XMLparserClassClass XMLparserClass;
	private: GIApreprocessorWordClassClass GIApreprocessorWordClassObject;
	private: GIApreprocessorSentenceClass GIApreprocessorSentenceClassObject;
	private: GIAposRelTranslatorRulesClass GIAposRelTranslatorRules;
	private: GIAposRelTranslatorRulesGroupClass GIAposRelTranslatorRulesGroupClassObject;
	private: GIAposRelTranslatorRulesComponentClass GIAposRelTranslatorRulesComponentClassObject;
	private: GIAposRelTranslatorSANIPropagateOperationsClass GIAposRelTranslatorSANIPropagateOperations;
	private: GIAposRelTranslatorSANIPropagateCompactClass GIAposRelTranslatorSANIPropagateCompact;
	private: GIAposRelTranslatorSANIFormationClass GIAposRelTranslatorSANIFormation;

	private: ANNdisplayClass ANNdisplay;

	public: bool executeTxtRelTranslatorNeuralNetwork(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, const bool createNewConnections);
		public: bool executeTxtRelTranslatorNeuralNetwork(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAposRelTranslatorRulesGroupParseTree** topLevelParseTreeGroup, const bool parseIsolatedSubreferenceSets, const bool parserEnabled, int* performance, const bool createNewConnection);
			private: bool findAndReconcileVariationWrapper(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, vector<GIApreprocessorPlainTextWord*>* sentenceContents, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents);
				#ifndef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_SYMMETRICAL_TREE
				private: bool findAndReconcileVariationLimitNumComponentsSection(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents, int* indexInSequenceStart, GIAposRelTranslatorRulesGroupNeuralNetwork** highLevelNeuronPrior);
				#endif	
					#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_SYMMETRICAL_TREE
					private: bool findAndReconcileIncrementalVariationLimitNumComponentsSection(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents, int* indexInSequenceStart, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray);
					#else
					private: bool findAndReconcileIncrementalVariationLimitNumComponentsSection(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents, int* indexInSequenceStart, GIAposRelTranslatorRulesGroupNeuralNetwork** highLevelNeuronPrior);
					#endif
				private: bool findAndReconcileVariation(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents);
					private: bool findAndReconcileIncrementalVariation(GIAtranslatorVariablesClass* translatorVariables, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, const bool supportVariableFirstComponents);
						#ifndef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS
						private: GIAposRelTranslatorRulesGroupNeuralNetwork* splitNeuron(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupParseTree* partiallyActivatedNeuronWithMaxWordIndexCoverage);
						#endif
						private: bool addNeuronToList(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAposRelTranslatorRulesGroupNeuralNetwork* neuron, int* indexInSequence);
						#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_SYMMETRICAL_TREE
						private: bool connectListOfHighLevelNeuronsToNewNeuronLimitNumComponentsSection(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAposRelTranslatorRulesGroupNeuralNetwork** grammaticalSentenceNeuron, const bool createTopLevelNeuron, const bool completedIdentifyingSentenceHighLevelNeurons, int indexInSequenceStart, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray);
						#else
						private: bool connectListOfHighLevelNeuronsToNewNeuronLimitNumComponentsSection(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAposRelTranslatorRulesGroupNeuralNetwork** grammaticalSentenceNeuron, const bool createTopLevelNeuron, const bool completedIdentifyingSentenceHighLevelNeurons, int indexInSequenceStart, GIAposRelTranslatorRulesGroupNeuralNetwork** highLevelNeuronPrior);
						#endif
						private: bool connectListOfHighLevelNeuronsToNewNeuron(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons, GIAposRelTranslatorRulesGroupNeuralNetwork** grammaticalSentenceNeuron, const bool createTopLevelNeuron);
						#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_COMPONENT_DETECT_LOCAL_VARATION
						private: bool verifyAndMarkNeuronAsCandidateWrapper(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupParseTree* candidateNeuronBaseParseTree, GIAposRelTranslatorRulesComponentNeuralNetwork** candidateComponent2);
							private: bool verifyAndMarkNeuronAsCandidate(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron, GIAposRelTranslatorRulesComponentNeuralNetwork** candidateComponent2);
						#endif
						private: bool createOrAppendFirstLevelHiddenLayerGroup(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* currentLayerNeuronGroupStart, bool* creatingNewNeuronSequence, int* neuronSequenceIndex, GIAposRelTranslatorRulesGroupNeuralNetwork** newNeuronSequenceGroup, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeurons);
						#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_REQUIRE_NUM_COMPONENTS_ENFORCE_DURING_FIRST_HIDDEN_LAYER_GENERATION
						private: bool directWireLowLevelPOSneuronToGrammaticalSentenceNeuron(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* singleComponentNeuronCandidate, GIAposRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuron);
						#endif

	private: bool addComponentToFirstLevelHiddenLayerGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* inputLayerPOSneuron, GIAposRelTranslatorRulesGroupNeuralNetwork* newNeuronSequenceGroup);
	private: GIAposRelTranslatorRulesGroupNeuralNetwork* createNewHiddenLayerGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes);
	//private: GIAposRelTranslatorRulesGroupNeuralNetwork* createNewFirstLevelHiddenLayerGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorRulesGroupNeuralNetwork* inputLayerPOSneuron);
	private: GIAposRelTranslatorRulesGroupNeuralNetwork* splitGroupAtLastActivatedComponent(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorRulesGroupNeuralNetwork* neuronToSplit, int indexToSplitVector);
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_SUPPORT_PARTIAL_SENTENCE_PROPAGATION
	private: GIAposRelTranslatorRulesGroupNeuralNetwork* splitGroupAtLastActivatedComponentUnordered(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorRulesGroupNeuralNetwork* neuronToSplit, int indexToSplitVector1, int indexToSplitVector2);
	#endif	

	private: bool addVariableComponentToGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* group, GIAposRelTranslatorRulesGroupNeuralNetwork* higherLevelComponentGroupOwner, bool addToStart);
	private: bool addComponentToGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* group, GIAposRelTranslatorRulesGroupNeuralNetwork* higherLevelComponentGroupOwner, int componentType, bool insertAtStart);
	private: bool addComponentToGroup(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupNeuralNetwork* group, GIAposRelTranslatorRulesComponentNeuralNetwork* higherLevelComponent);
		private: GIAposRelTranslatorRulesGroupNeuralNetwork* createNewGroup();

	private: bool findGroupDirectlyAbove(GIAposRelTranslatorRulesGroupNeuralNetwork* group1, GIAposRelTranslatorRulesGroupNeuralNetwork* group2);

	private: bool verifyLastWordIndex(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, GIAposRelTranslatorRulesGroupParseTree* parseTreeGroup, int lastWordIndex, bool* adjacent);
	
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING
	
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING_EFFICIENT
	private: bool markSubNeurons(GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#endif
	private: bool markSubNeuronsReset(GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#endif
	
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_PREVENT_INTRASENTENCE_MATCHING_BASIC
	private: bool addSubNeuronsToList(vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeuronsCompleteHistory, GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS_OPTIMISE_FOR_DIVERGENT_CONVERGENT_PATHWAYS
	private: bool addSubNeuronsToListReset(GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#endif
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_GENERATE_ENSURE_ALL_NEURONS_IN_SUBGROUP_DO_NOT_HAVE_CONNECTIONS_TO_ANY_NEW_CANDIDATE
	private: bool addParentNeuronsToList(vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* listOfHighLevelNeuronsCompleteHistory, GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS_OPTIMISE_FOR_DIVERGENT_CONVERGENT_PATHWAYS
	private: bool addParentNeuronsToListReset(GIAposRelTranslatorRulesGroupNeuralNetwork* currentNeuron);
	#endif
	#endif
	
	#endif
		
	private: int calculateNextIndexInSequence(GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData);
	
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_ADD_NEW_NEURONS_TO_SYMMETRICAL_TREE
	#ifdef GIA_POS_REL_TRANSLATOR_SANI_SEQUENCE_GRAMMAR_LIMIT_NUM_COMPONENTS_SUPPORT_VARIABLE_FIRST_COMPONENTS_REQUIRE_MATCHING_DEPTH
	private: int calculateLowestLayerNeuronMaxDepth(vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray);
	#endif
	private: bool findLowestLayerNeuron(vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray, GIAposRelTranslatorRulesGroupNeuralNetwork** lowestLayerNeuron, int* lowestLayerNeuronIndex);
	private: bool findHighestLayerNeuron(vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray, GIAposRelTranslatorRulesGroupNeuralNetwork** highestLayerNeuron, int* highestLayerNeuronIndex);
	private: bool updateHighLevelNeuronHierachy(vector<GIAposRelTranslatorRulesGroupType*>* GIAposRelTranslatorRulesGroupTypes, GIAposRelTranslatorSANIForwardPropogationSentenceData* forwardPropogationSentenceData, vector<GIAposRelTranslatorRulesGroupNeuralNetwork*>* highLevelNeuronPriorArray, int lowestLayerNeuronIndex, GIAposRelTranslatorRulesGroupNeuralNetwork* grammaticalSentenceNeuronSubHigher, const bool completedIdentifyingSentenceHighLevelNeurons);
	#endif
};

#endif

#endif
