//============================================================================
// Name        : CellCycleSimulator.cpp
// Author      : M. Herajy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "simulators/serialcellsimulator.h"

#include "export/resultexporter.h"
#include "simulators/parallelsimulator.h"

#include <chrono>

#include <time.h>

#include <mpi.h>

using namespace std;

typedef std::chrono::steady_clock StopWatch;

//comment this line for serial simulation
#define PARASIM

//Symmetric division (df=0.5)
//#define SYMDIVISION

int main() {

	clock_t t1,t2;

    t1=clock();


#if defined(PARASIM)

	//parallel simulation
	int myrank, size;

	//initialize MPI communication
	MPI_Init(NULL, NULL);

	//get the number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//get the processor rank
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	//a simulator object is created for each process
	ParallelSimulator* l_pcParaSim=new ParallelSimulator(myrank);

	//initialize the simulation
	l_pcParaSim->InitSimulator();

	//simulate a cell
	l_pcParaSim->StartSimulation();

	//finalize the MPI work
	MPI_Finalize();

	//record the run time
	if(myrank==0){

		t2=clock();

		float diff = ((float)t2-(float)t1)/CLOCKS_PER_SEC;

		cout << "Running time: " << diff <<" s"<< endl;
	}

#else

	//serial simulation
	SerialCellSimulator* l_nCellSimulator=new SerialCellSimulator();

	ResultExporter* m_pcResultExporter=new ResultExporter();


            //initialize the simulator
	        l_nCellSimulator->InitSimulator();

	        l_nCellSimulator->SimulateCell();

	         //get the result matrix
	         Matrix2D m_nmResultMatrix=l_nCellSimulator->GetResultMatrix();

	         VectorDouble m_anTime=l_nCellSimulator->GetTime();

	         //volume results
	         VectorDouble m_anVolumeResult=l_nCellSimulator->GetCellularVolumeResult();


	         //export volume
	         m_pcResultExporter->ExportVolume(m_anTime,m_anVolumeResult,"volume.csv");

	        //delete the simulation objects
	        delete l_nCellSimulator;

	        delete m_pcResultExporter;

	        t2=clock();

			float diff = ((float)t2-(float)t1)/CLOCKS_PER_SEC;

			cout << "Running time: " << diff <<" s"<< endl;
#endif


	return 0;
}
