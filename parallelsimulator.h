/*
 * parallelsimulator.h
 *
 *  Created on: Aug 2, 2016
 *      Author: Herajy
 */

#ifndef PARALLELSIMULATOR_H_
#define PARALLELSIMULATOR_H_

#include "cellsimulator.h"

class ParallelSimulator: public CellSimulator
{
private:
	    //this process rank
	    unsigned int m_nProcessID;

	    //total number of processes
	    int m_nProcessCount;

	    //start process
	    unsigned int m_nStartProcessID;

	    //end process ID
	    unsigned int m_nEndProcessID;

protected:


protected:

	    //simulate a cell from birth to division
	    void SimulateOneCell();

	    //send a cell
	    void SendCell(Cell* p_pcCell, const unsigned int& p_nRecvID);

	    //receive a cell from a sender
	    Cell* ReceiveCell(const unsigned int& p_nsenderID);

	    //collect the simulation results
	    void CollectResults();

	    //overloaded function
	    virtual void FireReaction(const unsigned int& p_nReactionID);

	    //propagate cells to other processes
	    virtual void PropagateCells(const unsigned int& p_nNextProcess,
	    		                    Cell* p_pcCell);


public:
	   ParallelSimulator(const unsigned int& p_nPID);
	   virtual ~ParallelSimulator();

	    //initialize the simulation (the parallel version)
	   	virtual bool InitSimulator();

	   //start simulation
	   void SimulateCell();

	   //start the simulation
	   void StartSimulation();
};

#endif /* PARALLELSIMULATOR_H_ */
