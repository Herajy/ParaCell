/*
 * randomnumbergenerator.h
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

#include <random>

class RandomNumberGenerator
{
private:
	     //random device
	    /* std::random_device* m_pcRandomDevice;

	     //random generator
	     std::mt19937* m_pcGenerator;

	     //random distribution
	     std::uniform_real_distribution<>* m_pcDist;*/
public:
	   RandomNumberGenerator();
	   virtual ~RandomNumberGenerator();

	   double GenerateRandom();
};

#endif /* RANDOMNUMBERGENERATOR_H_ */
