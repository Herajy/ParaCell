/*
 * serialsimulatorsymetricdivision.h
 *
 *  Created on: Sep 24, 2016
 *      Author: Herajy
 */

#ifndef SERIALSIMULATORSYMETRICDIVISION_H_
#define SERIALSIMULATORSYMETRICDIVISION_H_

#include "cellsimulator.h"

class SerialSimulatorSymetricDivision: public CellSimulator
{
protected:

	   //collect simulation statistics
	   void CalculateStatistics(const unsigned int& p_nCellCount);
public:

	SerialSimulatorSymetricDivision();
	virtual ~SerialSimulatorSymetricDivision();

	//simulate one cell
    virtual void SimulateCell();
};

#endif /* SERIALSIMULATORSYMETRICDIVISION_H_ */
