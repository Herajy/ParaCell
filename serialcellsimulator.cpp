/*
 * serialcellsimulator.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#include "serialcellsimulator.h"

#include <iostream>

#include "randomnumbergenerator.h"

#include <math.h>

SerialCellSimulator::SerialCellSimulator()
{

}

SerialCellSimulator::~SerialCellSimulator()
{

}

void SerialCellSimulator::SimulateCell()
{
        double l_nLastOutputTime=0;

        //division factor
        double l_ndf=0.4;


        unsigned long l_nSimulatedCellCount=0;

        double l_nElabsedTime=0;

	    //while we did not reach the end simulation time
        while(m_nCurrentTime<m_nsimulationEnd && l_nElabsedTime<=28800)
        {
        	//calculate next time step
        	double l_nTau=SimulateSingleStep();

        	//increase current time
        	m_nCurrentTime+=l_nTau;

        	//update the cell volume
        	double l_Volume=m_pcCurrentCell->UpdateCellVolume(m_nCurrentTime);

        	//check if the cell can divide
        	if(m_pcCurrentCell->CheckCellDivision(m_nCurrentTime))
        	{
        		 //divide the cell
        	     Cell* l_pcDaughterCell=m_pcCurrentCell->DivideCell(m_nCurrentTime,l_ndf);
        	     Cell* l_pcMotherCell=m_pcCurrentCell->DivideCell(m_nCurrentTime,1-l_ndf);

        	     m_pcCellList->push_back(l_pcMotherCell);
        	     m_pcCellList->push_back(l_pcDaughterCell);

        	     //mark the daughter cell
        	     l_pcDaughterCell->SetAsDaughterCell();

        	     //we take the next cell to simulate
        	     m_pcCurrentCell=(*m_pcCellList)[++m_nCurrentCellID];

        		 m_pcCurrentCell->UpdatePropensities();

        		 std::cout<<"The cell division has occurred at time: "<<m_nCurrentTime<<std::endl;

        		 m_nCurrentTime=m_pcCurrentCell->GetBirthTime();

        		 l_nSimulatedCellCount++;

        		 l_nElabsedTime=((float)(clock()-m_nStartRealTime)/CLOCKS_PER_SEC);
        		 std::cout<<"Current Computer Time: "<<l_nElabsedTime<<std::endl;
        	}


        	//check if we need to record the system state
        	/*if(m_nCurrentTime>m_nCurrentOutputPoint*m_nOutputStep)
        	{
        		RecordOutputPoint();
        	}*/
        }

        //calculate simulation statistics
        CalculateStatistics(l_nSimulatedCellCount);
}

void SerialCellSimulator::CalculateStatistics(const unsigned int& p_nSimulatedCellCount)
{
	  //age sum
	  double l_nMotherAgeSum=0;
	  double l_nDaughterAgeSum=0;

	  //volume sum
	  double l_nMotherVolumeSum=0;
	  double l_nDaughterVolumeSum=0;

	  //counts
	  unsigned int l_nMotherCellCount=0;
	  unsigned int l_nDaughterCellCount=0;

	  std::string l_sCellType;

	  std::cout<<"#\t age\t volume \t type"<<std::endl;

	  //list all the cell age and volume
      for (unsigned int l_nCellCount=0;l_nCellCount<p_nSimulatedCellCount;l_nCellCount++)
      {
    	   //cell age
    	   double l_nAge=(*m_pcCellList)[l_nCellCount]->GetCellAge();

    	   //cell volume
    	   double l_nVolume=(*m_pcCellList)[l_nCellCount]->GetCellVolume();

    	   if(l_nCellCount%2==0)
    	   {
    		   //Daughter cell
    		   l_nDaughterCellCount++;

    		   l_sCellType="daughter";

    		   l_nDaughterAgeSum+=l_nAge;
    		   l_nDaughterVolumeSum+=l_nVolume;

    	   }
    	   else
    	   {
    		   //mother cell
    		   l_nMotherCellCount++;

    		   l_sCellType="mother";

    		   l_nMotherAgeSum+=l_nAge;
    		   l_nMotherVolumeSum+=l_nVolume;
    	   }

           std::cout<<l_nCellCount<<"\t"<<l_nAge<<"\t"<<l_nVolume<<"\t"<<l_sCellType<<std::endl;
      }


      //Mother cells
      std::cout<<"------------Mother Cells ----------"<<std::endl;
      std::cout<<"Cell Count"<<l_nMotherCellCount<<std::endl;
      std::cout<<"Average Age @Division: "<<l_nMotherAgeSum/l_nMotherCellCount<<std::endl;
      std::cout<<"Average Volume @Division: "<<l_nMotherVolumeSum/l_nMotherCellCount<<std::endl;

      //Daughter cells
      std::cout<<"------------Daughter Cells ----------"<<std::endl;
	  std::cout<<"Cell Count"<<l_nDaughterCellCount<<std::endl;
	  std::cout<<"Average Age @Division: "<<l_nDaughterAgeSum/l_nDaughterCellCount<<std::endl;
	  std::cout<<"Average Volume @Division: "<<l_nDaughterVolumeSum/l_nDaughterCellCount<<std::endl;

	  //Total cells
	  std::cout<<"------------Total Cells ----------"<<std::endl;
	  std::cout<<"Cell Count"<<l_nMotherCellCount+l_nDaughterCellCount<<std::endl;
	  std::cout<<"Average Age @Division: "<<(l_nMotherAgeSum+l_nDaughterAgeSum)/(l_nDaughterCellCount+l_nMotherCellCount)<<std::endl;
	  std::cout<<"Average Volume @Division: "<<(l_nMotherVolumeSum+l_nDaughterVolumeSum)/(l_nDaughterCellCount+l_nMotherCellCount)<<std::endl;
}


