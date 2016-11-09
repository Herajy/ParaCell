/*
 * serialsimulatorsymetricdivision.cpp
 *
 *  Created on: Sep 24, 2016
 *      Author: Herajy
 */

#include "serialsimulatorsymetricdivision.h"

#include <iostream>

#include "randomnumbergenerator.h"

#include <math.h>


SerialSimulatorSymetricDivision::SerialSimulatorSymetricDivision():
CellSimulator()
{


}

SerialSimulatorSymetricDivision::~SerialSimulatorSymetricDivision() {

}

void SerialSimulatorSymetricDivision::SimulateCell()
{
        //division factor
        double l_ndf=0.5;

        unsigned long l_nSimulatedCellCount=0;

        std::cout<<"Simulating, please wait ... "<<std::endl;

	    //while we did not reach the end simulation time
        while(m_nCurrentTime<m_nsimulationEnd)
        {
        	//calculate next time step
        	double l_nTau=SimulateSingleStep();

        	//increase current time
        	m_nCurrentTime+=l_nTau;

        	//update the cell volume
        	double l_nCellVolume=m_pcCurrentCell->UpdateCellVolume(m_nCurrentTime);

        	//check if the cell can divide
        	if(m_pcCurrentCell->CheckCellDivision(m_nCurrentTime))
        	{
        		 //divide the cell
        	     Cell* l_pcDaughterCell=m_pcCurrentCell->DivideCell(m_nCurrentTime,l_ndf);

        	     m_pcCellList->push_back(l_pcDaughterCell);

        	     //we take the next cell to simulate
        	     m_pcCurrentCell=l_pcDaughterCell;

        		 m_pcCurrentCell->UpdatePropensities();

        		 std::cout<<"The cell division has occurred at time: "<<m_nCurrentTime<<"-"<<l_nCellVolume<<std::endl;

        		 l_nSimulatedCellCount++;
        	}

        	//check if we need to record the system state
        	if(m_nCurrentTime>m_nCurrentOutputPoint*m_nOutputStep)
        	{
        		RecordOutputPoint();
        	}
        }

        //calculate simulation statistics
        CalculateStatistics(l_nSimulatedCellCount);
}

void SerialSimulatorSymetricDivision::CalculateStatistics(const unsigned int& p_nSimulatedCellCount)
{
	  //age sum
	  double l_nAgeSum=0;

	  //age mean
	  double l_nAgeMean=0;

	  //age variance
	  double l_nAgeVariance=0;

	  //age standard deviation
	  double l_nAgeSD=0;

	  //volume sum
	  double l_nVolumeSum=0;

	  //volume mean
	  double l_nVolumeMean=0;

	  //volume variance
	  double l_nVolumeVariance=0;

	  //volume standard deviation
	  double l_nVolumeSD=0;

	  std::cout<<"#\t age\t volume \t type"<<std::endl;

	  //
	  double l_nAnalysedCells=p_nSimulatedCellCount-20;

	  //list all the cell age and volume
      for (unsigned int l_nCellCount=20;l_nCellCount<p_nSimulatedCellCount;l_nCellCount++)
      {
    	   //cell age
    	   double l_nAge=(*m_pcCellList)[l_nCellCount]->GetCellAge();

    	   //cell volume
    	   double l_nVolume=(*m_pcCellList)[l_nCellCount]->GetCellVolume();

           std::cout<<l_nCellCount<<"\t"<<l_nAge<<"\t"<<l_nVolume<<std::endl;

           //age sum
           l_nAgeSum+=l_nAge;

           //volume sum
           l_nVolumeSum+=l_nVolume;
      }

      //calculate the averages
      l_nAgeMean=l_nAgeSum/l_nAnalysedCells;
      l_nVolumeMean=l_nVolumeSum/l_nAnalysedCells;

      //calculate the standard deviation
      for (unsigned int l_nCellCount=20;l_nCellCount<p_nSimulatedCellCount;l_nCellCount++)
       {
    	  //cell age
    	  double l_nAge=(*m_pcCellList)[l_nCellCount]->GetCellAge();

		   //cell volume
		   double l_nVolume=(*m_pcCellList)[l_nCellCount]->GetCellVolume();

		   l_nAgeVariance+=pow((l_nAgeMean-l_nAge),2);

		   l_nVolumeVariance+=pow((l_nVolumeMean-l_nVolume),2);
       }

      l_nAgeVariance=l_nAgeVariance/l_nAnalysedCells;

      l_nVolumeVariance=l_nVolumeVariance/l_nAnalysedCells;

      //calculate standard divisions
      l_nAgeSD=sqrt(l_nAgeVariance);

      l_nVolumeSD=sqrt(l_nVolumeVariance);


	  //Total cells
	  std::cout<<"------------Total Cells ----------"<<std::endl;
	  std::cout<<"Cell Count"<<p_nSimulatedCellCount-1<<std::endl;
	  std::cout<<"Average Age @Division: "<<l_nAgeMean<<std::endl;
	  std::cout<<"Average Volume @Division: "<< l_nVolumeMean<<std::endl;

	  //SD
	  std::cout<<"SD of Age @Division: "<<l_nAgeSD<<std::endl;
	  std::cout<<"SD of Volume @Division: "<< l_nVolumeSD<<std::endl;

	  //CV
	  std::cout<<"CV of Age @Division: "<<l_nAgeSD/l_nAgeMean<<std::endl;
	  std::cout<<"CV of Volume @Division: "<< l_nVolumeSD/l_nVolumeMean<<std::endl;
}



