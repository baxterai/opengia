/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: GIAneuralNetworkXmlConversion.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3d2c 14-July-2017
 * Description: 
 *
 *******************************************************************************/


#include "GIAneuralNetworkXmlConversion.hpp"

bool GIAneuralNetworkXmlConversionClass::readNeuralNetXMLfile(const string xmlFileName, ANNneuron* firstInputNeuronInNetwork)
{
	bool result = false;

	long numberOfInputNeuronsLoaded;
	long numberOfOutputNeuronsLoaded;

	ANNneuron* firstOutputNeuronInNetwork = ANNxmlConversion.readNetXMLfileAndRecordFormationVariables(xmlFileName, firstInputNeuronInNetwork, &numberOfInputNeuronsLoaded, &numberOfOutputNeuronsLoaded);

	return result;
}

bool GIAneuralNetworkXmlConversionClass::writeNeuralNetXMLfile(const string xmlFileName, ANNneuron* firstInputNeuronInNetwork)
{
	bool result = true;

	if(!ANNxmlConversion.writeNetXMLfile(xmlFileName, firstInputNeuronInNetwork))
	{
		result = false;
	}
		
	return result;
}



