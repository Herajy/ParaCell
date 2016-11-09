/*
 * cellsimulator.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#include "cellsimulator.h"

#include "util/randomnumbergenerator.h"

#include <iostream>

CellSimulator::CellSimulator():
m_nsimulationEnd(10000),
m_nSimulationStart(0),
m_nOutputStep(0.1),
m_nCurrentOutputPoint(0),
m_nCurrentCellID(0)
{
	//create a random number generators
	m_pcRandGenerator= new RandomNumberGenerator();

	//create a list of cells
	m_pcCellList=new VectorCells();

	m_pcSimulatedCellList=new VectorCells();

	m_pcCellList->clear();

	m_pcSimulatedCellList->clear();


	m_nStartRealTime=clock();
}

CellSimulator::~CellSimulator()
{
	delete m_pcRandGenerator;

	//delete created cells
	for (auto l_pcCell: *m_pcCellList)
	{
		delete l_pcCell;
	}

	//delete the list of cells
	delete m_pcCellList;

	//delete simulated cell list
	delete m_pcSimulatedCellList;
}

unsigned int CellSimulator::SelectNextReaction(const double& p_na0)
{
	   unsigned int l_nReactionIndex;

	   //number of reactions
	   unsigned int l_nReactionCount=m_pcCurrentCell->GetHazardValues().size();

      //we make 100 trials to find a reaction
       for (int i=0; i<100; i++)
       {
    	   //make a trial
    	   l_nReactionIndex=TryToSelectReaction(p_na0);

    	   //if we get a valid reaction index then we return it
    	   if(l_nReactionIndex< l_nReactionCount)
    	   {
    		   return l_nReactionIndex;
    	   }
       }

       //no reaction to fire, we escape it
      return  l_nReactionCount;
}

unsigned int CellSimulator::TryToSelectReaction(const double& p_na0)
{
	       //get hazard values
	       VectorDouble l_anHazardValues=m_pcCurrentCell->GetHazardValues();

	       //generate a random number
		   double l_nR2=m_pcRandGenerator->GenerateRandom();

		   double l_nSum=0;

		   double l_nR2a0=p_na0*l_nR2;

		   //we reset reaction index
		   unsigned int l_Rmu=0;

		   for(auto l_nHazardValue:l_anHazardValues)
		   {
			   l_nSum +=l_nHazardValue;

			   if(l_nSum>l_nR2a0){
				   return l_Rmu;
			   }

			   l_Rmu++;
		   }

		   return 0; //TODO: check this
}

void CellSimulator::FireReaction(const unsigned int& p_nReactionID)
{
	   m_pcCurrentCell->FireReaction(p_nReactionID);

	   //increase the firing count of this reaction
	   m_anFiringCount[p_nReactionID]++;
}

bool CellSimulator::InitSimulator()
{

	  //create a cell
	   m_pcCurrentCell=new Cell();

	   //initialize the cell
	   m_pcCurrentCell->InitCell();

	   m_pcCellList->push_back(m_pcCurrentCell);

	   //calculate the number of output points
	   unsigned int l_nOutputPointCount=
			   (m_nsimulationEnd-m_nSimulationStart)/m_nOutputStep;

	   //add another point (at time 0)
	   l_nOutputPointCount=l_nOutputPointCount+1;

	   //record the number of output points
	   m_nmSimulationResult.resize(l_nOutputPointCount);

	   //get the number of species + the volume variable
	   m_nVarCount=m_pcCurrentCell->GetVarCount();

	   //resize individual rows
	   for(unsigned int i=0; i<l_nOutputPointCount;i++){

		   m_nmSimulationResult[i].assign(m_nVarCount,0);
	   }

	   //initializing the rate result matrix
	   m_nmReactionRateResult.resize(l_nOutputPointCount);

	   //get the number of reactions
	   long l_nReactionCount=m_pcCurrentCell->GetReactionCount();

	   //resize individual rows
	   for(unsigned int i=0; i<l_nOutputPointCount;i++){

		   m_nmReactionRateResult[i].assign(l_nReactionCount,0);
	   }

	   //resize the volume
	   m_anVolumeResult.assign(l_nOutputPointCount,0);

	   m_anTime.assign(l_nOutputPointCount,0);

	   //set the current output point to zero
	   m_nCurrentOutputPoint=0;

	   //initialize firing count
	   m_anFiringCount.assign(l_nReactionCount+1,0);

	   return true;
}

void CellSimulator::RecordOutputPoint()
{
	    //get the current cell state
	    VectorDouble l_nCurrentState=m_pcCurrentCell->GetCurrentState();

	    //record the current output point
	    m_anTime[m_nCurrentOutputPoint]=m_nCurrentOutputPoint*m_nOutputStep;

	    //record the cell volume
	    m_anVolumeResult[m_nCurrentOutputPoint]=m_pcCurrentCell->GetCellVolume();

	    //record the system state
	    for(unsigned int i=1;i<l_nCurrentState.size();i++)
	    {
	    	m_nmSimulationResult[m_nCurrentOutputPoint][i-1]=
	    			        l_nCurrentState[i];
	    }

	    //record the reaction rate
	    RecordreactionRates();

	    //increase the number of output points
	    m_nCurrentOutputPoint++;
}

void CellSimulator::RecordreactionRates()
{

}

double CellSimulator::SimulateSingleStep()
{
	  //calculate total propensity
	
	  double l_na0 = m_pcCurrentCell->CalculateTotalPropensity();
	
	  double l_nr1=m_pcRandGenerator->GenerateRandom();

	  //calculate next time step
	  double l_nTau=-1*log(l_nr1)/l_na0;

	  //select a reaction to file
	  unsigned int l_nMu = SelectNextReaction(l_na0);
	 
	  
	  if(l_nMu>176)
	  {
		  std::cout<<"we cannot fire this reaction"<<std::endl;

		  return 0.0;
	  }

	  //fire this reaction
	  FireReaction(l_nMu);

	  return l_nTau;
}


