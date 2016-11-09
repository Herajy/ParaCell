/*
 * resultexporter.h
 *
 *  Created on: Jul 27, 2016
 *      Author: Herajy
 */

#ifndef RESULTEXPORTER_H_
#define RESULTEXPORTER_H_

#include "util/datatype.h"

class ResultExporter
{
private:

protected:

	   //export a range of columns
	   void ExportRange(VectorDouble& p_anTime,
			            Matrix2D& p_nmResultMatrix,
						const unsigned long& p_nStart,
						const unsigned long& p_nEnd,
						const std::string& p_sFileName);

public:
	  ResultExporter();
	  virtual ~ResultExporter();

	  //export volume date
	  void ExportVolume(VectorDouble& p_anTime,
			            VectorDouble& p_anVolume,
			            const std::string& p_sFileName);

	  //export firing count
	  void ExportFiringCount(VectorLong& p_anFiringCount,
	                         const std::string& p_sFileName);
};

#endif /* RESULTEXPORTER_H_ */
