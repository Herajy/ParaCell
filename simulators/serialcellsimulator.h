/*
 * serialcellsimulator.h
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#ifndef SERIALCELLSIMULATOR_H_
#define SERIALCELLSIMULATOR_H_

#include "cellsimulator.h"

class SerialCellSimulator: public CellSimulator
{

protected:
	     //collect simulation statistics
	     void CalculateStatistics(const unsigned int& p_nCellCount);
public:

	     SerialCellSimulator();
	     virtual ~SerialCellSimulator();

	     //simulate one cell
	     virtual void SimulateCell();
};

#endif /* SERIALCELLSIMULATOR_H_ */
