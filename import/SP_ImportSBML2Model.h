//////////////////////////////////////////////////////////////////////
// $Author: crohr $
// $Version: 0.1 $
// $Date: 2009/03/25 $
// Short Description: creates a stochastic petrinet on a SBML file
//////////////////////////////////////////////////////////////////////

#ifndef __SP_ImportSBML2Model_H__
#define __SP_ImportSBML2Model_H__

#include <sbml/SBMLTypes.h>

#include<map>
using namespace std;
#include "util/datatype.h"

struct ArcInfo
{
	string m_sPlaceName;
	int m_nMultiplicity;
};

class SP_ImportSBML2Model
{

private:



	std::map <int, std::string> m_mSpeciesID2Name;
	std::map <int, std::string> m_mReactionID2Name;

	std::map<long, std::vector<ArcInfo> > m_mTranID2PreArcInfoVector;
	std::map<long, std::vector<ArcInfo> > m_mTranID2PostArcInfoVector;

	VectorString m_vSpecies;
	VectorDouble m_anCurrentState;

	VectorString m_vReactions;
	VectorString m_vKinetics;


public:
	SP_ImportSBML2Model();
	virtual ~SP_ImportSBML2Model();
//
	Model* m_sbmlModel = nullptr;

	void getSpecies();
    void getReactions();

	//virtual bool ReadFile(const std::string& p_sFileName);
	virtual bool ReadFile();
	const ASTNode* getSBMLFormula(ASTNode* p_sbmlFormula);


};

#endif // __SP_ImportSBML2Model__
