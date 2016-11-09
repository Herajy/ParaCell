/*
 * cell.h
 *
 *  Created on: Jul 25, 2016
 *      Author: Herajy
 */

#ifndef CELL_H_
#define CELL_H_

#include "datatype.h"

class Cell
{
private:
	    //species count
	    int m_nSCount;

	    //reaction count
	    int m_nRCount;

	    //initial cell volume
	    double m_nInitCellVolume;

	    //cellular volume
	    double m_nCellVolume;

	    //cell birth time (related to simulation time)
	    double m_nBirthTime;

	    //cell division time
	    double m_nDivTime;

	    //is ClbM reached a high value
	    bool m_bHighClbM;

	    //is a mother cell
	    bool m_bIsMother;

private:
	    //species names
	    VectorString m_asSpeciesName;

	    //initial values
	    VectorDouble m_anInitState;

	    //current values
	    VectorDouble m_anCurrentState;

	    //reaction propensities
	    VectorDouble m_anHazardValues;

protected:

	    //initialize species names and initial values
	    void InitSpecies();

	    //initialize reactions
	    void InitReactions();

	    //fire a reaction using the reaction ID
	    void _FireReaction(const unsigned int& p_nReactionID);
public:

	    Cell();
	    virtual ~Cell();

	    //calculate total propensity
	    double CalculateTotalPropensity();

	    //Initialize cell
	    void InitCell();

	    //fire a reaction
	    void FireReaction(const unsigned int& p_nReactionID){
	    	_FireReaction(p_nReactionID);
	    }

	    //get a list of transition propensities
	    VectorDouble& GetHazardValues(){return m_anHazardValues;}

	    //return current species values
	    VectorDouble& GetCurrentState(){return m_anCurrentState;}
	    void SetCurrentState(VectorDouble& p_anState){m_anCurrentState=p_anState;}

	    //initial state
	    VectorDouble& GetInitState(){return m_anInitState;}
	    void SetInitState(VectorDouble& p_anState){m_anInitState=p_anState;}

	    //birth time
	    double GetBirthTime(){return m_nBirthTime;}
	    void SetBirthTime(const double& p_nBirthTime){m_nBirthTime=p_nBirthTime;}

	    //division time
	    double GetDivisionTime(){return m_nDivTime;}
	    void SetDivisionTime(const double& p_nTime){m_nDivTime=p_nTime;}

	    //update the cell volume
	    double UpdateCellVolume(const double& p_nTime);

	    //update the propensities of all reactions
	    void UpdatePropensities();

	    //get current volume
        double GetCellVolume(){return m_nCellVolume;}
        void SetCellVolume(const double& p_nVolume){m_nCellVolume=p_nVolume;}

        //initial cell volume
        double GetInitCellVolume(){return m_nInitCellVolume;}
        void SetInitCellVolume(const double& p_nVolume){m_nInitCellVolume=p_nVolume;}

        //check if a cell can divide
        bool CheckCellDivision(const double& p_nCurrentTime);

        //divide the cell
        Cell* DivideCell(const double& p_nCurrentTime,
        		         const double& p_nDf);

        //return [ClbM]
        double GetClbMConc(){return m_anCurrentState[2]/( 0.6 *m_nCellVolume);}

        //get the number of species
        unsigned int GetVarCount(){return m_nSCount;}

        unsigned int GetReactionCount(){return m_nRCount; }

        //get cell age
        double GetCellAge(){return (m_nDivTime-m_nBirthTime);}

        //is mother cell
        bool IsMother(){return m_bIsMother;}
        void SetAsDaughterCell(){m_bIsMother= false;}
};

//define a list of cells
typedef std::vector<Cell*> VectorCells;

#endif /* CELL_H_ */
