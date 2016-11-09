/*
 * randomnumbergenerator.cpp
 *
 *  Created on: Jul 26, 2016
 *      Author: Herajy
 */

#include "randomnumbergenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{
	 //create a random device
	/* m_pcRandomDevice=new std::random_device();

	 //create a generator
	 m_pcGenerator=new std::mt19937(m_pcRandomDevice);

	 //create a distribution
	 m_pcDist= new std::uniform_real_distribution<>(0,1);*/

}

RandomNumberGenerator::~RandomNumberGenerator()
{
	//free objects
	/*delete m_pcRandomDevice;

	delete m_pcGenerator;

	delete m_pcDist;*/
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);


double RandomNumberGenerator::GenerateRandom()
{
	 return dis(gen);
}
