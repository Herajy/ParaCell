//////////////////////////////////////////////////////////////////////
// $Author: fei $
// $Version: 0.1 $
// $Date: 2016/11/18 $
// Short Description: convert
//////////////////////////////////////////////////////////////////////

#include "import/SP_ImportSBML2Model.h"

#include <fstream>
#include <iostream>

#include <sstream>
#include <iterator>
using namespace std;

SP_ImportSBML2Model::SP_ImportSBML2Model()
{

}

SP_ImportSBML2Model::~SP_ImportSBML2Model()
{

}

//bool SP_ImportSBML2Model::ReadFile(const std::string& p_sFileName)
bool SP_ImportSBML2Model::ReadFile()

{
	//output file
	string filename;
	cout << "Enter the name for a new sbml file (absolute path):\n";
	cin >> filename;


	SBMLDocument* l_sbmlDocument=NULL;
	l_sbmlDocument = readSBML(filename.c_str());
	if (!l_sbmlDocument)
	{
		cout << "file format error\n";
		return false;
	}
		

	m_sbmlModel = l_sbmlDocument->getModel();
	if (!m_sbmlModel)
	{
		cout << "file format error\n";
		return false;
	}

	getSpecies();
	getReactions();

	return true;
}


void SP_ImportSBML2Model::getSpecies()
{
	unsigned int l_nID = 0;
	for (unsigned int n = 0; n < m_sbmlModel->getNumSpecies(); ++n)
	{
		Species* l_sbmlSpecies = m_sbmlModel->getSpecies(n);

		std::string l_sID = "";
		if (l_sbmlSpecies->isSetId())
		{
			l_sID = l_sbmlSpecies->getId();
			
		}
		std::string l_sName;
		if (l_sbmlSpecies->isSetName())
		{
			l_sName = l_sbmlSpecies->getName();
		}

		m_mSpeciesID2Name[l_nID] = l_sID;// +"_" + l_sName;
		m_vSpecies.push_back(l_sID);

		double l_dInitialvalue = 0;
		if (l_sbmlSpecies->isSetInitialAmount())
		{
			l_dInitialvalue = l_sbmlSpecies->getInitialAmount();			
		}
		m_anCurrentState.push_back(l_dInitialvalue);

		l_nID++;
	}
		
}

void SP_ImportSBML2Model::getReactions()
{
	unsigned int l_nID = 0;

	for (unsigned int i = 0; i < m_sbmlModel->getNumReactions(); ++i)
	{
		Reaction* l_sbmlReaction = m_sbmlModel->getReaction(i);
		string l_ReactionId = "";
		string l_ReactionName;
		if (l_sbmlReaction->isSetId())
		{
			l_ReactionId = l_sbmlReaction->getId();
		}
		if (l_sbmlReaction->isSetName())
		{
			l_ReactionName = l_sbmlReaction->getName();
		}
		m_mReactionID2Name[l_nID] = l_ReactionId;// +"_" + l_ReactionName;
		
		m_vReactions.push_back(l_ReactionId);

		const ListOfSpeciesReferences* rectants = l_sbmlReaction->getListOfReactants();
		const ListOfSpeciesReferences* products = l_sbmlReaction->getListOfProducts();
		// get rectants of actual reaction
		std::vector<ArcInfo> l_vPreArc;
		for (unsigned int lor = 0; lor < rectants->size(); ++lor)
		{
			auto l_sbmlReactant = l_sbmlReaction->getReactant(lor);
			string l_eductName = l_sbmlReactant->getSpecies();
			auto l_sbmlSpecies = m_sbmlModel->getSpecies(l_eductName);
			int l_nMultiplicity = l_sbmlReactant->getStoichiometry();
			ArcInfo l_arcInfo;
			l_arcInfo.m_sPlaceName = l_eductName;
			l_arcInfo.m_nMultiplicity = l_nMultiplicity;
			l_vPreArc.push_back(l_arcInfo);
		}
		m_mTranID2PreArcInfoVector[l_nID] = l_vPreArc;
		std::vector<ArcInfo> l_vPostArc;
		for (unsigned int lop = 0; lop < products->size(); ++lop)
		{
			auto l_sbmlProduct = l_sbmlReaction->getProduct(lop);
			string l_productName = l_sbmlProduct->getSpecies();
			auto l_sbmlSpecies = m_sbmlModel->getSpecies(l_productName);
			int l_nMultiplicity = l_sbmlProduct->getStoichiometry();
			ArcInfo l_arcInfo;
			l_arcInfo.m_sPlaceName = l_productName;
			l_arcInfo.m_nMultiplicity = l_nMultiplicity;
			l_vPostArc.push_back(l_arcInfo);
		}
		m_mTranID2PostArcInfoVector[l_nID] = l_vPostArc;


		string l_kinetic = "0";
		if (l_sbmlReaction->isSetKineticLaw())
		{
			KineticLaw* l_sbmlKineticLaw = l_sbmlReaction->getKineticLaw();
			ASTNode* l_sbmlMath = nullptr;
			if (l_sbmlKineticLaw->getMath())
			{
				l_sbmlMath = l_sbmlKineticLaw->getMath()->deepCopy();
			}

			char* formula = SBML_formulaToString(getSBMLFormula(l_sbmlMath));
			string l_kinetic = formula;
			free(formula);			
		}
		m_vKinetics.push_back(l_kinetic);

		l_nID++;
	}
}


const ASTNode*
SP_ImportSBML2Model::getSBMLFormula(ASTNode* p_sbmlFormula)
{
	

	ASTNode* l_sbmlFormula = p_sbmlFormula;

	if (l_sbmlFormula->getType() == AST_FUNCTION_POWER)
	{
		l_sbmlFormula->setType(AST_POWER);
	}
	else if (l_sbmlFormula->isUMinus())
	{
		//TODO: need to be fixed, is only temp workaround!!!!
		//continuous simulation can't deal with unary minus
		//i.e. a + -b dont work so we insert a zero
		// ->  a + 0 - b should be the same at all
		ASTNode* l_ASTLeft = new ASTNode(AST_INTEGER);
		l_ASTLeft->setValue(0);
		l_sbmlFormula->prependChild(l_ASTLeft);
	}

	for (unsigned int i = 0; i < l_sbmlFormula->getNumChildren(); i++)
	{

		getSBMLFormula(l_sbmlFormula->getChild(i));

	}
	return l_sbmlFormula;
}

