/*
 * resultexporter.cpp
 *
 *  Created on: Jul 27, 2016
 *      Author: Herajy
 */

#include "resultexporter.h"
#include <fstream>
#include <iostream>

#include <sstream>
#include <iterator>

ResultExporter::ResultExporter()
{

}

ResultExporter::~ResultExporter()
{
}

void ResultExporter::ExportVolume(VectorDouble& p_anTime,
		                          VectorDouble& p_anVolume,
			                       const std::string& p_sFileName)
{
	     //output file
		 std::ofstream l_isOutputFile;

		 l_isOutputFile.open(p_sFileName,std::ifstream::out);

		 //make sure the file has been open correctly
          if(l_isOutputFile.is_open()!=true)
          {
             std::cout<<"cannot open the file"<<std::endl;

             return;
          }


          //write the result
          for (int i=0;i<p_anVolume.size();i++)
          {
        	  std::ostringstream l_sBuffer;

        	  l_sBuffer<<p_anTime[i];

        	  l_sBuffer<<"\t";

        	  l_sBuffer<<p_anVolume[i];

        	  l_sBuffer<<"\n";

        	  l_isOutputFile.write(l_sBuffer.str().c_str(), l_sBuffer.str().length());
          }

          //close the file
          l_isOutputFile.close();

}

void ResultExporter::ExportFiringCount(VectorLong& p_anFiringCount,
	                                   const std::string& p_sFileName)
{

	        std::vector<int> v;

	        //get the total sum
	        double l_nSum=0;

	         for (int i=1;i<p_anFiringCount.size();i++)
	         {
	        	 l_nSum+=p_anFiringCount[i];
	         }

	        //separate those who has length than 1% firing frequency
	        for (int i=1;i<p_anFiringCount.size();i++)
			 {
				 double l_nFiringFrequency=(p_anFiringCount[i]/l_nSum)*100;

				 if(l_nFiringFrequency<0.1)
				 {
                    v.push_back(i);
				 }
			 }


	         //output files
			 std::ofstream l_isOutputFile1;
			 std::ofstream l_isOutputFile2;

			 std::string l_sFileName1=p_sFileName+"1.csv";
			 std::string l_sFileName2=p_sFileName+"2.csv";

			 l_isOutputFile1.open(l_sFileName1,std::ifstream::out);
			 l_isOutputFile2.open(l_sFileName2,std::ifstream::out);

			 //make sure the file has been open correctly
	          if(l_isOutputFile1.is_open()!=true || l_isOutputFile2.is_open()!=true)
	          {
	             std::cout<<"cannot open the file"<<std::endl;

	             return;
	          }


	          //write the result
	          for (int i=1;i<p_anFiringCount.size();i++)
	          {
	        	  std::ostringstream l_sBuffer;

	        	  l_sBuffer<<i;

	        	  l_sBuffer<<"\t";

	        	  l_sBuffer<<p_anFiringCount[i];

	        	  l_sBuffer<<"\n";

	        	  if(std::find(v.begin(), v.end(),i)!=v.end())
	        	  {
	        		  //write to the m_RNA file
	        		  l_isOutputFile1.write(l_sBuffer.str().c_str(), l_sBuffer.str().length());
	        	  }
	        	  else
	        	  {
	        		  //other species
	        		 l_isOutputFile2.write(l_sBuffer.str().c_str(), l_sBuffer.str().length());
	        	  }


	          }

	          //close the file
	          l_isOutputFile1.close();
	          l_isOutputFile2.close();

}

void ResultExporter::ExportRange(VectorDouble& p_anTime,
			            Matrix2D& p_nmResultMatrix,
						const unsigned long& p_nStart,
						const unsigned long& p_nEnd,
						const std::string& p_sFileName)
{

}

