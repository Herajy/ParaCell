/*
 * cellsimulator.h
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#ifndef CELLSIMULATOR_H_
#define CELLSIMULATOR_H_

#include "cell/cell.h"

#include <time.h>


class RandomNumberGenerator;

class CellSimulator
{
protected:

	     //current simulation time
	     double m_nCurrentTime;

         //current cell to simulate
	     Cell* m_pcCurrentCell;

	     //random generator
	     RandomNumberGenerator* m_pcRandGenerator;

	     //simulation results
	     Matrix2D m_nmSimulationResult;

	     //reaction rate matrix
	     Matrix2D m_nmReactionRateResult;

	     //a vector to same the volume time course result
	     VectorDouble m_anVolumeResult;

	     //time vector
	     VectorDouble m_anTime;

	     //simulation intervals
	     double m_nsimulationEnd;

	     //start recording
	     double m_nSimulationStart;

	     //output recording steps
	     double m_nOutputStep;

	     //number of variables (species + volume)
	     unsigned int m_nVarCount;

	     //current output point
	     unsigned int m_nCurrentOutputPoint;

	     //list of cells
	     VectorCells* m_pcCellList;

	     //list of simulated cells
	     VectorCells* m_pcSimulatedCellList;

	     //current cell index
	     unsigned int m_nCurrentCellID;

	     //firing count
	     VectorLong  m_anFiringCount;

	     clock_t  m_nStartRealTime;

protected:

	     //advance the simulator one step
	     virtual double SimulateSingleStep();

	     //simulate a one cell from birth to division
	     virtual void SimulateCell()=0;

	     //select a reaction
	     virtual unsigned int SelectNextReaction(const double& p_na0);

	     //try to select a reaction
	     unsigned int TryToSelectReaction(const double& p_na0);

	     //fire a reaction
	     virtual void FireReaction(const unsigned int& p_nReactionID);

	     //record the data about the current output point
	     void RecordOutputPoint();

	     //record reaction rates
	     void RecordreactionRates();

	     //add a cell to the to be simulated cell list
	     virtual void AddCellToToDoList(Cell* p_pcCell){
	    	 m_pcCellList->push_back(p_pcCell);
	     }

	     //return the next list to be simulated
	     Cell* GetNextList(){
	    	   return (*m_pcCellList)[m_nCurrentCellID++];
	     }

public:

	     CellSimulator();
	     virtual ~CellSimulator();

	     //initialize the simulation
	     virtual bool InitSimulator();

	     //return the result matrix
	     Matrix2D& GetResultMatrix(){return m_nmSimulationResult;}

	     Matrix2D& GetRateMatrix(){return m_nmReactionRateResult;}

	     //get cell volume result
	     VectorDouble& GetCellularVolumeResult(){return m_anVolumeResult;}

	     VectorLong& GetFiringCount(){return m_anFiringCount;}

	     //get the time vector
	     VectorDouble& GetTime(){return m_anTime;}
};

#endif /* CELLSIMULATOR_H_ */
