/*
 * parallelsimulator.cpp
 *
 *  Created on: Aug 2, 2016
 *      Author: Herajy
 */

#include "parallelsimulator.h"

#include <iostream>

#include <mpi.h>

ParallelSimulator::ParallelSimulator(const unsigned int& p_nPID):
m_nProcessID(p_nPID),
m_nStartProcessID(0),
m_nEndProcessID(0)
{
		m_nStartRealTime=clock();
}

ParallelSimulator::~ParallelSimulator()
{

}

void ParallelSimulator::SimulateOneCell()
{

	        //initially we set the simulation time to the birth time
	        double l_nBirthTime= m_pcCurrentCell->GetBirthTime();

	        m_nCurrentTime=l_nBirthTime;
	        double l_nLastOutputTime=l_nBirthTime;

	        std::cout<<"Process="<<m_nProcessID<<": "<<"starting simulating a new cell at time= "<<m_nCurrentTime<<std::endl;

		    //the cell should divide before age of 1000
	        while(m_nCurrentTime<l_nBirthTime+1000)
	        {
	        	//calculate next time step
	        	double l_nTau=SimulateSingleStep();


	        	if(l_nTau<0){

	        		std::cout<<"tau is less than zero, we exit"<<std::endl;

	        		exit(0);
	        	}

	        	//increase current time
	        	m_nCurrentTime+=l_nTau;

	        	//update the cell volume
	        	double l_Volume=m_pcCurrentCell->UpdateCellVolume(m_nCurrentTime);

	            if(m_nCurrentTime>l_nLastOutputTime+100)
	            {
	               std::cout<<m_nCurrentTime<<" - "<<l_Volume<<"-"<<m_pcCurrentCell->GetClbMConc()<<std::endl;

	               l_nLastOutputTime+=100;
	             }

	        	//check if the cell can divide
	        	if(m_pcCurrentCell->CheckCellDivision(m_nCurrentTime))
	        	{
	        		std::cout<<"PID="<<m_nProcessID<<": "<<"The cell division has occurred at time: "<<m_nCurrentTime<<std::endl;

	        		//we end the simulation here
	        		return;
	        	}
	        }
}

void ParallelSimulator::SimulateCell()
{
	  //start the simulation
	  SimulateOneCell();
}

void ParallelSimulator::SendCell(Cell* p_pcCell, const unsigned int& p_nRecvID)
{
        //send cell volume
	    double l_nVolume=p_pcCell->GetCellVolume();

	    //send cell volume
	    MPI_Send(&l_nVolume,1,MPI_DOUBLE,p_nRecvID,m_nProcessID,MPI_COMM_WORLD);

	    //send initial system state
	    VectorDouble l_anInitState=p_pcCell->GetCurrentState();
	    //copy the initial state in a vector
	     double* l_pcState=&l_anInitState[0];
	     MPI_Send(l_pcState,l_anInitState.size(),MPI_DOUBLE,p_nRecvID,m_nProcessID,MPI_COMM_WORLD);

	    //birth time
	    double l_nBirthTime=p_pcCell->GetBirthTime();
	    MPI_Send(&l_nBirthTime,1,MPI_DOUBLE,p_nRecvID,m_nProcessID,MPI_COMM_WORLD);

	    //division time
	    double l_nDivisionTime=p_pcCell->GetDivisionTime();
	    MPI_Send(&l_nDivisionTime,1,MPI_DOUBLE,p_nRecvID,m_nProcessID,MPI_COMM_WORLD);

}

Cell* ParallelSimulator::ReceiveCell(const unsigned int& p_nsenderID)
{
	   Cell* l_pcNewCell=new Cell();

	   //initialize the cell
	   l_pcNewCell->InitCell();

	   //receive the cell volume
	   double l_nVolume=0;
	   MPI_Recv(&l_nVolume,1,MPI_DOUBLE,p_nsenderID,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

	   //set the cell volume to the received one
	   l_pcNewCell->SetCellVolume(l_nVolume);

	   //set the initial volume to the current volume
	   //TODO: will this be true all the time?
	   l_pcNewCell->SetInitCellVolume(l_nVolume);

	   //receive initial system state
	    VectorDouble l_anInitState=l_pcNewCell->GetCurrentState();
	    double* l_pcState=&l_anInitState[0];
	    MPI_Recv(l_pcState,l_anInitState.size(),MPI_DOUBLE,p_nsenderID,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    l_pcNewCell->SetInitState(l_anInitState);

	   //receive birth time
	   double l_nBirthTime=0;
	   MPI_Recv(&l_nBirthTime,1,MPI_DOUBLE,p_nsenderID,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	   l_pcNewCell->SetBirthTime(l_nBirthTime);

	   //division time
	   double l_nDivTime=0;
	   MPI_Recv(&l_nDivTime,1,MPI_DOUBLE,p_nsenderID,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	   l_pcNewCell->SetDivisionTime(l_nDivTime);


	   return  l_pcNewCell;
}

bool ParallelSimulator::InitSimulator()
{
	  //get the total number of processes
	  MPI_Comm_size(MPI_COMM_WORLD, &m_nProcessCount);

	  //master process create a new cell, while all other processes
	  //wait for the master to get a seed
	  if(m_nProcessID==0)
	  {
		    //take a pointer to the cell
		    m_pcCurrentCell=new Cell();

		    //initialize a cell
		  	m_pcCurrentCell->InitCell();

		  	m_nStartProcessID=1;

		  	m_nEndProcessID=m_nProcessCount-1;
	  }
	  else
	  {
		   //receive a cell from the master process
		   //other processes have to wait for the initialization until they
		   //receive a seed cell
		   m_pcCurrentCell=ReceiveCell(MPI_ANY_SOURCE);

		   std::cout<<"Process: "<<m_nProcessID<<"has received a cell"<<std::endl;

		   //receive the start and end process ID that this process will send seed cells to them
		   int l_anBuffer[2];
		   MPI_Recv(&l_anBuffer[0],2,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

		   //set start process ID
		   m_nStartProcessID=l_anBuffer[0];
		   m_nEndProcessID=l_anBuffer[1];
	  }

	  return true;
}

void ParallelSimulator::StartSimulation()
{
	    //division factor
	    double l_ndf=0.4;

	    unsigned int l_nWorkingProcess=m_nStartProcessID;

	    double l_nElabsedTime=0;

	     while(m_nCurrentTime<=m_nsimulationEnd && l_nElabsedTime<=28800)
	     {
	    	 //first we simulate a cell
	    	 SimulateCell();

	    	 //then we divide the current cell into two cells the parent
	    	 //cell is: m_pcCurrentCell, while the daughter is the returned one

			 Cell* l_nMotherCell=m_pcCurrentCell->DivideCell(m_nCurrentTime,1-l_ndf);

	    	 Cell* l_pcDaughterCell=m_pcCurrentCell->DivideCell(m_nCurrentTime,l_ndf);

	    	 //mark the daughter cell
	    	 l_pcDaughterCell->SetAsDaughterCell();

	    	 //add this cell to the simulated cell list
	    	 m_pcSimulatedCellList->push_back(m_pcCurrentCell);

	    	 //if there are still a process in the range that did not
	    	 //a seed cell, we send it daughter cell.
	    	 if(l_nWorkingProcess<=m_nEndProcessID)
	    	 {
	    		 //send a cell to the next process in the range
	    		 PropagateCells(l_nWorkingProcess++,l_pcDaughterCell);

	    		  //the next cell to simulate is the mother cell
	    		  m_pcCurrentCell=l_nMotherCell;
	    	 }
	    	 else
	    	 {
                 //we add the mother and daughter cells to the list
	    		 AddCellToToDoList(l_pcDaughterCell);
	    		 AddCellToToDoList(l_nMotherCell);

				 //then we select one from the list
	    		 m_pcCurrentCell=GetNextList();
	    	 }

	    	 l_nElabsedTime=((float)(clock()-m_nStartRealTime)/CLOCKS_PER_SEC);
	    	std::cout<<"Current Computer Time: "<<l_nElabsedTime<<std::endl;
	     }

	     //collect simulation results
	    CollectResults();
}

void ParallelSimulator::CollectResults()
{
	     //data for volume sum, age sum, and cell count
	     float l_nGlobalCollectedData[6];
	     float l_nLocalCollectedData[6];

		 for(int j=0;j<6;j++)
			 l_nLocalCollectedData[j]=0;

		 int l_nMCellCount=0;
		 int l_nDCount=0;

		 //for all simulated cells
		 for(auto l_pcCell:(*m_pcSimulatedCellList))
		 {
			 //for mother cells
            if(l_pcCell->IsMother())
            {
            	l_nLocalCollectedData[0]+=l_pcCell->GetCellVolume();

            	l_nLocalCollectedData[1]+=l_pcCell->GetCellAge();

            	l_nMCellCount++;
            }
            //for daughter cells
            else
            {
            	l_nLocalCollectedData[3]+=l_pcCell->GetCellVolume();

            	l_nLocalCollectedData[4]+=l_pcCell->GetCellAge();

            	l_nDCount++;
            }
		 }

		 //assign the counters to the arrays
		 l_nLocalCollectedData[2]=l_nMCellCount;

		 //daughter cells
		 l_nLocalCollectedData[5]=l_nDCount;


		 //number of cells per each process
		 int l_nCellCount=l_nMCellCount+l_nMCellCount;


		 int *l_nGlobalCellCounts=NULL;

		  if (m_nProcessID == 0) {

			  l_nGlobalCellCounts = new int[m_nProcessCount];
		  }

		 //collect cell count of each process
		 MPI_Gather(&l_nCellCount, 1, MPI_INT,l_nGlobalCellCounts, 1,
				 MPI_INT, 0, MPI_COMM_WORLD);

		 //sum all the cell volumes in all processes
		 MPI_Reduce(l_nLocalCollectedData, l_nGlobalCollectedData, 6,
				     MPI_FLOAT, MPI_SUM, 0,MPI_COMM_WORLD);

		 //total number of generated cells
		 int l_nLocalGenratedCellCount=m_pcCellList->size();
		 int l_nGlobalGenratedCellCount=0;

		 MPI_Reduce(&l_nLocalGenratedCellCount,&l_nGlobalGenratedCellCount,1,
		 				     MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);

		 //log the result
		 if(m_nProcessID==0)
		 {
			std::cout<<"==== Number of cells per process ====="<<std::endl;

			std::cout<<"Process ID"<<"\t\t"<<"Number of Cells"<<std::endl;

			for (int i=0;i<m_nProcessCount;i++)
			{
				std::cout<<i<<"\t\t"<<l_nGlobalCellCounts[i]<<std::endl;
			}

			 //mother cells
			double l_nCellCount=l_nGlobalCollectedData[2];

			std::cout<<"==== Mother cells ====="<<std::endl;

			 //output the data
		    std::cout<<"Total number of simulated cells: "<<l_nCellCount<<std::endl;
		    std::cout<<"Average volume: "<<l_nGlobalCollectedData[0]/l_nCellCount<<std::endl;
		    std::cout<<"Average age: "<<l_nGlobalCollectedData[1]/l_nCellCount<<std::endl;

		    //daughter cells
		    l_nCellCount=l_nGlobalCollectedData[5];

		    std::cout<<"==== Daughter cells ====="<<std::endl;

			 //output the data
			std::cout<<"Total number of simulated cells: "<<l_nCellCount<<std::endl;
			std::cout<<"Average volume: "<<l_nGlobalCollectedData[3]/l_nCellCount<<std::endl;
			std::cout<<"Average age: "<<l_nGlobalCollectedData[4]/l_nCellCount<<std::endl;

			std::cout<<"Total number of generated cells: "<<l_nGlobalGenratedCellCount<<std::endl;
			std::cout<<"Current Simulation time: "<<m_nCurrentTime<<std::endl;
		 }
}

void ParallelSimulator::FireReaction(const unsigned int& p_nReactionID)
{
	   m_pcCurrentCell->FireReaction(p_nReactionID);
}

void ParallelSimulator::PropagateCells(const unsigned int& p_nNextProcess, Cell* p_pcCell)
{
	  SendCell(p_pcCell,p_nNextProcess);

	  int l_nBuffer[2];

	 unsigned int l_nBeginRange=p_nNextProcess+1;

	 if(l_nBeginRange<=m_nEndProcessID)
	 {
		  //this process divides the remaining range of processes  between it and its child
		  int l_nRemainingProcessCount=(m_nEndProcessID-l_nBeginRange)+1;

		  int l_nMid=l_nBeginRange+((double)l_nRemainingProcessCount/2)-1;

		  l_nBuffer[0]=l_nMid+1;
		  l_nBuffer[1]=m_nEndProcessID;

		  //this process new end range
		  m_nEndProcessID=l_nMid;
	 }
	 else
	 {
		 l_nBuffer[0]=m_nEndProcessID+1;
		 l_nBuffer[1]=m_nEndProcessID;
	 }

	 MPI_Send(&l_nBuffer[0],2,MPI_INT,p_nNextProcess,m_nProcessID,MPI_COMM_WORLD);
}




