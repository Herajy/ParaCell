/*
 * cell.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: Herajy
 */

#include "cell.h"

#include <iostream>
#include <math.h>
using namespace std;


Cell::Cell():
    m_nSCount(58),
	m_nRCount(176),
	m_nInitCellVolume(1.0),
	m_nCellVolume(1.0),
	m_nBirthTime(0.0),
	m_nDivTime(0.0),
	m_bHighClbM(false),
	m_bIsMother(true)
{
	      //initialize species
		  InitSpecies();
}

Cell::~Cell() {

}

void Cell::InitSpecies()
{
	//resize the vectors
	m_asSpeciesName.assign(m_nSCount+1,"");
	m_anInitState.assign(m_nSCount+1,0);
	m_anCurrentState.assign(m_nSCount+1,0);

	m_asSpeciesName[1]="cln3";
	m_anInitState[1]=0;

	m_asSpeciesName[2]="clbM";
	m_anInitState[2]=1;

    m_asSpeciesName[3]="clbS";
    m_anInitState[3]=6;

    m_asSpeciesName[4]="cdc14";
    m_anInitState[4]=2;

	m_asSpeciesName[5]="sbf";
	m_anInitState[5]=2;

	m_asSpeciesName[6]="sbfp1";
	m_anInitState[6]=0;

	m_asSpeciesName[7]="sbfp2";
	m_anInitState[7]=0;

	m_asSpeciesName[8]="sbfp3";
	m_anInitState[8]=0;

	m_asSpeciesName[9]="sbfp4";
	m_anInitState[9]=0;

	m_asSpeciesName[10]="whi5";
	m_anInitState[10]=227;

	m_asSpeciesName[11]="whi5p1";
	m_anInitState[11]=68;

	m_asSpeciesName[12]="whi5p2";
	m_anInitState[12]=16;

	m_asSpeciesName[13]="whi5p3";
	m_anInitState[13]=4;

	m_asSpeciesName[14]="whi5p4";
	m_anInitState[14]=1;

	m_asSpeciesName[15]="whi5p5";
	m_anInitState[15]=0;

	m_asSpeciesName[16]="whi5p6";
	m_anInitState[16]=0;

	m_asSpeciesName[17]="net1";
	m_anInitState[17]=210;

	m_asSpeciesName[18]="net1p1";
	m_anInitState[18]=11;

	m_asSpeciesName[19]="net1p2";
	m_anInitState[19]=1;

	m_asSpeciesName[20]="net1p3";
	m_anInitState[20]=0;

	m_asSpeciesName[21]="net1p4";
	m_anInitState[21]=0;

	m_asSpeciesName[22]="net1p5";
	m_anInitState[22]=0;

	m_asSpeciesName[23]="net1p6";
	m_anInitState[23]=0;

	m_asSpeciesName[24]="net1p7";
	m_anInitState[24]=0;

	m_asSpeciesName[25]="net1p8";
	m_anInitState[25]=0;

	m_asSpeciesName[26]="rent";
	m_anInitState[26]=133;

	m_asSpeciesName[27]="rentp1";
	m_anInitState[27]=7;

	m_asSpeciesName[28]="rentp2";
	m_anInitState[28]=0;

	m_asSpeciesName[29]="rentp3";
	m_anInitState[29]=0;

	m_asSpeciesName[30]="rentp4";
	m_anInitState[30]=0;

	m_asSpeciesName[31]="rentp5";
	m_anInitState[31]=0;

	m_asSpeciesName[32]="cmp";
	m_anInitState[32]=117;

	m_asSpeciesName[33]="cmpp1";
	m_anInitState[33]=27;

	m_asSpeciesName[34]="cmpp2";
	m_anInitState[34]=6;

	m_asSpeciesName[35]="cdh1";
	m_anInitState[35]=176;

	m_asSpeciesName[36]="cdh1p1";
	m_anInitState[36]=25;

	m_asSpeciesName[37]="cdh1p2";
	m_anInitState[37]=4;

	m_asSpeciesName[38]="cdh1p3";
	m_anInitState[38]=1;

	m_asSpeciesName[39]="cdh1p4";
	m_anInitState[39]=0;

	m_asSpeciesName[40]="cdh1p5";
	m_anInitState[40]=0;

	m_asSpeciesName[41]="cdh1p6";
	m_anInitState[41]=0;

	m_asSpeciesName[42]="cdh1p7";
	m_anInitState[42]=0;

	m_asSpeciesName[43]="cdh1p8";
	m_anInitState[43]=0;

	m_asSpeciesName[44]="cdh1p9";
	m_anInitState[44]=0;

	m_asSpeciesName[45]="cdh1p10";
	m_anInitState[45]=0;

	m_asSpeciesName[46]="hbf";
	m_anInitState[46]=128;

	m_asSpeciesName[47]="hi5";
	m_anInitState[47]=128;

	m_asSpeciesName[48]="ht1";
	m_anInitState[48]=102;

	m_asSpeciesName[49]="mn3";
	m_anInitState[49]=7;

	m_asSpeciesName[50]="mbS";
	m_anInitState[50]=2;

	m_asSpeciesName[51]="mbM";
	m_anInitState[51]=7;

	m_asSpeciesName[52]="mi5";
	m_anInitState[52]=7;

	m_asSpeciesName[53]="mc14";
	m_anInitState[53]=7;

	m_asSpeciesName[54]="mt1";
	m_anInitState[54]=7;

	m_asSpeciesName[55]="mh1";
	m_anInitState[55]=7;

	m_asSpeciesName[56]="mhbf";
	m_anInitState[56]=10;

	m_asSpeciesName[57]="mhi5";
	m_anInitState[57]=10;

	m_asSpeciesName[57]="mht1";
	m_anInitState[57]=10;

}

void Cell::InitReactions()
{
	    //resize the vectors
	    m_anHazardValues.clear();

	    m_anHazardValues.assign(m_nRCount+1,0);
}

void Cell::InitCell()
{
	int i = 0;

	for (auto n : m_anInitState)
	{
		m_anCurrentState[i++] = n;
	}

    //initialize reactions
	InitReactions();
}

void Cell::UpdatePropensities()
{

	//rate constants
	const double aksbM=0.27,akdbMa=0.025,akdbMi=1.7E-5,gdbM=0.03;
	const double akph1=0.033,akph1p=0.18,akdh1=0.134,akdh1p=1.65,gdh1=0.01;
	const double aksbS=0.3,gdbS=0.1;
	const double akpbf=0.0625,akdbf=4.6E-3,akdbfp=0.0165,gdbf=0.01;
	const double akac=0.0417,akdc=0.2;
	const double gdi5=0.01,akpi5=0.1835,akpi5p=0.0475,akdi5=9.6E-3,akdi5p=0.033;
	const double akpcm=0.1835,akpcmp=0.0475,akdcm=9.6E-3,akdcmp=0.033;
	const double akpt1=0.042,akdt1=3.3E-3,gdt1=0.015;
	const double akpnt=0.042,akdnt=3.3E-3;
	const double gdc14=0.02,akar=0.042,akdr=0.075;
	const double aksn3=0.0024,gdn3=0.14;
	const double akag=0.25,akdg=12.0;
	const double gdhbf=0.01,gdhi5=0.01,gdht1=0.01;
	const double aksmbS=11.5,gdmbS=0.25;
	const double aksmn3=7.5,gdmn3=1.0;
	const  double aksmbM=5.25,gdmbM=0.7;
	const double aksmt1=5.25,gdmt1=0.7;
	const double aksmi5=5.25,gdmi5=0.7;
	const  double aksmh1=5.25,gdmh1=0.7;
	const double aksmc14=5.25,gdmc14=0.7;
	const double aksmhbf=7.0,gdmhbf=0.7;
	const double aksmhi5=7.0,gdmhi5=0.7;
	const double aksmht1=7.0,gdmht1=0.7;
	const double aksh1=0.275,aksbf=1.53,aksi5=0.715;
	const double akst1=0.725,aksc14=0.38;
	const double akshbf=0.1275,akshi5=0.1275,aksht1=0.102;

    double pl=1;

    //wrapper to the cellular volume
    double v=m_nCellVolume;


	    double icdh1i=m_anCurrentState[36]+m_anCurrentState[37]+
				 m_anCurrentState[38]+m_anCurrentState[39]+
				 m_anCurrentState[40]+m_anCurrentState[41]+
				 m_anCurrentState[42]+m_anCurrentState[43]+
				 m_anCurrentState[44]+m_anCurrentState[45];

	    double icdh1a=m_anCurrentState[35];

		double ga=(akag*m_anCurrentState[5]*pl)/(akag*m_anCurrentState[5]+v*akdg);

		double vpbf=(akpbf/v)*m_anCurrentState[2];
		double vdbf=(akdbf*m_anCurrentState[46]+akdbfp*m_anCurrentState[4])/v;
		double vpi5=(akpi5*m_anCurrentState[1]+akpi5p*m_anCurrentState[3])/v;
		double vdi5=(akdi5*m_anCurrentState[47]+akdi5p*m_anCurrentState[4])/v;
		double vpcm=(akpcm*m_anCurrentState[1]+akpcmp*m_anCurrentState[3])/v;
		double vdcm=(akdcm*m_anCurrentState[47]+akdcmp*m_anCurrentState[4])/v;
		double vph1=(akph1p*m_anCurrentState[2]+akph1*m_anCurrentState[3])/v;
		double vdh1=akdh1*m_anCurrentState[4]/v+akdh1p;
		double vpt1=(akpt1/v)*m_anCurrentState[2];
		double vdt1=(akdt1/v)*m_anCurrentState[48];
		double vpnt=(akpnt/v)*m_anCurrentState[2];
		double vdnt=(akdnt/v)*m_anCurrentState[48];

		//propensities
		m_anHazardValues[0]=0;
		m_anHazardValues[1]=aksmbM*pl;
		m_anHazardValues[2]=gdmbM*m_anCurrentState[51];
		m_anHazardValues[3]=aksbM*(v/pl)*m_anCurrentState[51];
		m_anHazardValues[4]=(gdbM+(akdbMi*icdh1i+akdbMa*icdh1a)/v)*m_anCurrentState[2];
		m_anHazardValues[5]=aksmbS*ga;
		m_anHazardValues[6]=gdmbS*m_anCurrentState[50];
		m_anHazardValues[7]=aksbS*(v/pl)*m_anCurrentState[50];
		m_anHazardValues[8]=gdbS*m_anCurrentState[3];
		m_anHazardValues[9]=aksbf*v;
		m_anHazardValues[10]=vpbf*m_anCurrentState[5];
		m_anHazardValues[11]=vpbf*m_anCurrentState[6];
		m_anHazardValues[12]=vpbf*m_anCurrentState[7];
		m_anHazardValues[13]=vpbf*m_anCurrentState[8];
		m_anHazardValues[14]=vdbf*m_anCurrentState[6];
		m_anHazardValues[15]=vdbf*m_anCurrentState[7];
		m_anHazardValues[16]=vdbf*m_anCurrentState[8];
		m_anHazardValues[17]=vdbf*m_anCurrentState[9];
		m_anHazardValues[18]=gdbf*m_anCurrentState[5];
		m_anHazardValues[19]=gdbf*m_anCurrentState[6];
		m_anHazardValues[20]=gdbf*m_anCurrentState[7];
		m_anHazardValues[21]=gdbf*m_anCurrentState[8];
		m_anHazardValues[22]=gdbf*m_anCurrentState[9];
		m_anHazardValues[23]=aksmhbf*pl;
		m_anHazardValues[24]=gdmhbf*m_anCurrentState[56];
		m_anHazardValues[25]=akshbf*(v/pl)*m_anCurrentState[56];
		m_anHazardValues[26]=gdhbf*m_anCurrentState[46];
		m_anHazardValues[27]=aksmi5*pl;
		m_anHazardValues[28]=gdmi5*m_anCurrentState[52];
		m_anHazardValues[29]=aksi5*(v/pl)*m_anCurrentState[52];
		m_anHazardValues[30]=vpi5*m_anCurrentState[10];
		m_anHazardValues[31]=vpi5*m_anCurrentState[11];
		m_anHazardValues[32]=vpi5*m_anCurrentState[12];
		m_anHazardValues[33]=vpi5*m_anCurrentState[13];
		m_anHazardValues[34]=vpi5*m_anCurrentState[14];
		m_anHazardValues[35]=vpi5*m_anCurrentState[15];
		m_anHazardValues[36]=vdi5*m_anCurrentState[11];
		m_anHazardValues[37]=vdi5*m_anCurrentState[12];
		m_anHazardValues[38]=vdi5*m_anCurrentState[13];
		m_anHazardValues[39]=vdi5*m_anCurrentState[14];
		m_anHazardValues[40]=vdi5*m_anCurrentState[15];
		m_anHazardValues[41]=vdi5*m_anCurrentState[16];
		m_anHazardValues[42]=gdi5*m_anCurrentState[10];
		m_anHazardValues[43]=gdi5*m_anCurrentState[11];
		m_anHazardValues[44]=gdi5*m_anCurrentState[12];
		m_anHazardValues[45]=gdi5*m_anCurrentState[13];
		m_anHazardValues[46]=gdi5*m_anCurrentState[14];
		m_anHazardValues[47]=gdi5*m_anCurrentState[15];
		m_anHazardValues[48]=gdi5*m_anCurrentState[16];
		m_anHazardValues[49]=aksmhi5*pl;
		m_anHazardValues[50]=gdmhi5*m_anCurrentState[57];
		m_anHazardValues[51]=akshi5*(v/pl)*m_anCurrentState[57];
		m_anHazardValues[52]=gdhi5*m_anCurrentState[47];
		m_anHazardValues[53]=(akac/v)*m_anCurrentState[10]*m_anCurrentState[5];
		m_anHazardValues[54]=(akac/v)*m_anCurrentState[11]*m_anCurrentState[5];
		m_anHazardValues[55]=(akac/v)*m_anCurrentState[12]*m_anCurrentState[5];
		m_anHazardValues[56]=akdc*m_anCurrentState[32];
		m_anHazardValues[57]=akdc*m_anCurrentState[33];
		m_anHazardValues[58]=akdc*m_anCurrentState[34];
		m_anHazardValues[59]=vpcm*m_anCurrentState[32];
		m_anHazardValues[60]=vpcm*m_anCurrentState[33];
		m_anHazardValues[61]=vdcm*m_anCurrentState[33];
		m_anHazardValues[62]=vdcm*m_anCurrentState[34];
		m_anHazardValues[63]=gdi5*m_anCurrentState[32];
		m_anHazardValues[64]=gdi5*m_anCurrentState[33];
		m_anHazardValues[65]=gdi5*m_anCurrentState[34];
		m_anHazardValues[66]=gdbf*m_anCurrentState[32];
		m_anHazardValues[67]=gdbf*m_anCurrentState[33];
		m_anHazardValues[68]=gdbf*m_anCurrentState[34];
		m_anHazardValues[69]=aksmh1*pl;
		m_anHazardValues[70]=gdmh1*m_anCurrentState[55];
		m_anHazardValues[71]=aksh1*(v/pl)*m_anCurrentState[55];
		m_anHazardValues[72]=vph1*m_anCurrentState[35];
		m_anHazardValues[73]=vph1*m_anCurrentState[36];
		m_anHazardValues[74]=vph1*m_anCurrentState[37];
		m_anHazardValues[75]=vph1*m_anCurrentState[38];
		m_anHazardValues[76]=vph1*m_anCurrentState[39];
		m_anHazardValues[77]=vph1*m_anCurrentState[40];
		m_anHazardValues[78]=vph1*m_anCurrentState[41];
		m_anHazardValues[79]=vph1*m_anCurrentState[42];
		m_anHazardValues[80]=vph1*m_anCurrentState[43];
		m_anHazardValues[81]=vph1*m_anCurrentState[44];
		m_anHazardValues[82]=vdh1*m_anCurrentState[36];
		m_anHazardValues[83]=vdh1*m_anCurrentState[37];
		m_anHazardValues[84]=vdh1*m_anCurrentState[38];
		m_anHazardValues[85]=vdh1*m_anCurrentState[39];
		m_anHazardValues[86]=vdh1*m_anCurrentState[40];
		m_anHazardValues[87]=vdh1*m_anCurrentState[41];
		m_anHazardValues[88]=vdh1*m_anCurrentState[42];
		m_anHazardValues[89]=vdh1*m_anCurrentState[43];
		m_anHazardValues[90]=vdh1*m_anCurrentState[44];
		m_anHazardValues[91]=vdh1*m_anCurrentState[45];
		m_anHazardValues[92]=gdh1*m_anCurrentState[35];
		m_anHazardValues[93]=gdh1*m_anCurrentState[36];
		m_anHazardValues[94]=gdh1*m_anCurrentState[37];
		m_anHazardValues[95]=gdh1*m_anCurrentState[38];
		m_anHazardValues[96]=gdh1*m_anCurrentState[39];
		m_anHazardValues[97]=gdh1*m_anCurrentState[40];
		m_anHazardValues[98]=gdh1*m_anCurrentState[41];
		m_anHazardValues[99]=gdh1*m_anCurrentState[42];
		m_anHazardValues[100]=gdh1*m_anCurrentState[43];
		m_anHazardValues[101]=gdh1*m_anCurrentState[44];
		m_anHazardValues[102]=gdh1*m_anCurrentState[45];
		m_anHazardValues[103]=aksmt1*pl;
		m_anHazardValues[104]=gdmt1*m_anCurrentState[54];
		m_anHazardValues[105]=akst1*(v/pl)*m_anCurrentState[54];
		m_anHazardValues[106]=vpt1*m_anCurrentState[17];
		m_anHazardValues[107]=vpt1*m_anCurrentState[18];
		m_anHazardValues[108]=vpt1*m_anCurrentState[19];
		m_anHazardValues[109]=vpt1*m_anCurrentState[20];
		m_anHazardValues[110]=vpt1*m_anCurrentState[21];
		m_anHazardValues[111]=vpt1*m_anCurrentState[22];
		m_anHazardValues[112]=vpt1*m_anCurrentState[23];
		m_anHazardValues[113]=vpt1*m_anCurrentState[24];
		m_anHazardValues[114]=vdt1*m_anCurrentState[18];
		m_anHazardValues[115]=vdt1*m_anCurrentState[19];
		m_anHazardValues[116]=vdt1*m_anCurrentState[20];
		m_anHazardValues[117]=vdt1*m_anCurrentState[21];
		m_anHazardValues[118]=vdt1*m_anCurrentState[22];
		m_anHazardValues[119]=vdt1*m_anCurrentState[23];
		m_anHazardValues[120]=vdt1*m_anCurrentState[24];
		m_anHazardValues[121]=vdt1*m_anCurrentState[25];
		m_anHazardValues[122]=gdt1*m_anCurrentState[17];
		m_anHazardValues[123]=gdt1*m_anCurrentState[18];
		m_anHazardValues[124]=gdt1*m_anCurrentState[19];
		m_anHazardValues[125]=gdt1*m_anCurrentState[20];
		m_anHazardValues[126]=gdt1*m_anCurrentState[21];
		m_anHazardValues[127]=gdt1*m_anCurrentState[22];
		m_anHazardValues[128]=gdt1*m_anCurrentState[23];
		m_anHazardValues[129]=gdt1*m_anCurrentState[24];
		m_anHazardValues[130]=gdt1*m_anCurrentState[25];
		m_anHazardValues[131]=aksmht1*pl;
		m_anHazardValues[132]=gdmht1*m_anCurrentState[58];
		m_anHazardValues[133]=aksht1*(v/pl)*m_anCurrentState[58];
		m_anHazardValues[134]=gdht1*m_anCurrentState[48];
		m_anHazardValues[135]=aksmc14*pl;
		m_anHazardValues[136]=gdmc14*m_anCurrentState[53];
		m_anHazardValues[137]=aksc14*(v/pl)*m_anCurrentState[53];
		m_anHazardValues[138]=gdc14*m_anCurrentState[4];
		m_anHazardValues[139]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[17];
		m_anHazardValues[140]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[18];
		m_anHazardValues[141]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[19];
		m_anHazardValues[142]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[20];
		m_anHazardValues[143]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[21];
		m_anHazardValues[144]=(akar/v)*m_anCurrentState[4]*m_anCurrentState[22];
		m_anHazardValues[145]=akdr*m_anCurrentState[26];
		m_anHazardValues[146]=akdr*m_anCurrentState[27];
		m_anHazardValues[147]=akdr*m_anCurrentState[28];
		m_anHazardValues[148]=akdr*m_anCurrentState[29];
		m_anHazardValues[149]=akdr*m_anCurrentState[30];
		m_anHazardValues[150]=akdr*m_anCurrentState[31];
		m_anHazardValues[151]=vpnt*m_anCurrentState[26];
		m_anHazardValues[152]=vpnt*m_anCurrentState[27];
		m_anHazardValues[153]=vpnt*m_anCurrentState[28];
		m_anHazardValues[154]=vpnt*m_anCurrentState[29];
		m_anHazardValues[155]=vpnt*m_anCurrentState[30];
		m_anHazardValues[156]=vdnt*m_anCurrentState[27];
		m_anHazardValues[157]=vdnt*m_anCurrentState[28];
		m_anHazardValues[158]=vdnt*m_anCurrentState[29];
		m_anHazardValues[159]=vdnt*m_anCurrentState[30];
		m_anHazardValues[160]=vdnt*m_anCurrentState[31];
		m_anHazardValues[161]=gdc14*m_anCurrentState[26];
		m_anHazardValues[162]=gdc14*m_anCurrentState[27];
		m_anHazardValues[163]=gdc14*m_anCurrentState[28];
		m_anHazardValues[164]=gdc14*m_anCurrentState[29];
		m_anHazardValues[165]=gdc14*m_anCurrentState[30];
		m_anHazardValues[166]=gdc14*m_anCurrentState[31];
		m_anHazardValues[167]=gdt1*m_anCurrentState[26];
		m_anHazardValues[168]=gdt1*m_anCurrentState[27];
		m_anHazardValues[169]=gdt1*m_anCurrentState[28];
		m_anHazardValues[170]=gdt1*m_anCurrentState[29];
		m_anHazardValues[171]=gdt1*m_anCurrentState[30];
		m_anHazardValues[172]=gdt1*m_anCurrentState[31];
		m_anHazardValues[173]=aksn3*(v/pl)*(v/pl)*m_anCurrentState[49];
		m_anHazardValues[174]=gdn3*m_anCurrentState[1];
		m_anHazardValues[175]=aksmn3*pl;
		m_anHazardValues[176]=gdmn3*m_anCurrentState[49];
}


void Cell::_FireReaction(const unsigned int& p_nReactionID)
{
         switch (p_nReactionID)
         {
         case 1:
                 m_anCurrentState[51]+=1;
				 break;
         case 2:
                 m_anCurrentState[51]-=1;
				 break;
         case 3:
                 m_anCurrentState[2]+=1;
                 break;
         case 4:
                 m_anCurrentState[2]-=1;
                 break;
         case 5:
                 m_anCurrentState[50]+=1;
                 break;
         case 6:
                 m_anCurrentState[50]-=1;
                 break;
         case 7:
                 m_anCurrentState[3]+=1;
                 break;
         case 8:
                 m_anCurrentState[3]-=1;;
                 break;
         case 9:
                 m_anCurrentState[5]+=1;;
                 break;
         case 10:
                 m_anCurrentState[5]-=1;
                 m_anCurrentState[6]+=1;
				 break;
         case 11:
                 m_anCurrentState[6]-=1;
                 m_anCurrentState[7]+=1;
				 break;
         case 12:
                 m_anCurrentState[7]-=1;
                 m_anCurrentState[8]+=1;
				 break;
         case 13:
                 m_anCurrentState[8]-=1;
                 m_anCurrentState[9]+=1;
				 break;
         case 14:
                 m_anCurrentState[6]-=1;
                 m_anCurrentState[5]+=1;
				 break;
         case 15:
                 m_anCurrentState[7]-=1;
                 m_anCurrentState[6]+=1;
				 break;
         case 16:
                 m_anCurrentState[8]-=1;
                 m_anCurrentState[7]+=1;
				 break;
         case 17:
                 m_anCurrentState[9]-=1;
                 m_anCurrentState[8]+=1;
				 break;
         case 18:
                 m_anCurrentState[5]-=1;
                 break;
         case 19:
                 m_anCurrentState[6]-=1;
                 break;
         case 20:
                 m_anCurrentState[7]-=1;
                 break;
         case 21:
                 m_anCurrentState[8]-=1;
                 break;
         case 22:
                 m_anCurrentState[9]-=1;
                 break;
         case 23:
                 m_anCurrentState[56]+=1;
                 break;
         case 24:
                 m_anCurrentState[56]-=1;
                 break;
         case 25:
                 m_anCurrentState[46]+=1;
                 break;
         case 26:
                 m_anCurrentState[46]-=1;
                 break;
         case 27:
                 m_anCurrentState[52]+=1;
                 break;
         case 28:
                 m_anCurrentState[52]-=1;
                 break;
         case 29:
                 m_anCurrentState[10]+=1;
                 break;
         case 30:
                 m_anCurrentState[10]-=1;
                 m_anCurrentState[11]+=1;
				 break;
         case 31:
                 m_anCurrentState[11]-=1;
                 m_anCurrentState[12]+=1;
				 break;
         case 32:
                 m_anCurrentState[12]-=1;
                 m_anCurrentState[13]+=1;
				 break;
         case 33:
                 m_anCurrentState[13]-=1;
                 m_anCurrentState[14]+=1;
				 break;
         case 34:
                 m_anCurrentState[14]-=1;
                 m_anCurrentState[15]+=1;
				 break;
         case 35:
                 m_anCurrentState[15]-=1;
                 m_anCurrentState[16]+=1;
				 break;
         case 36:
                 m_anCurrentState[11]-=1;
                 m_anCurrentState[10]+=1;
				 break;
         case 37:
                 m_anCurrentState[12]-=1;
                 m_anCurrentState[11]+=1;
				 break;
         case 38:
                 m_anCurrentState[13]-=1;
                 m_anCurrentState[12]+=1;
				 break;
         case 39:
                 m_anCurrentState[14]-=1;
                 m_anCurrentState[13]+=1;
				 break;
         case 40:
                 m_anCurrentState[15]-=1;
                 m_anCurrentState[14]+=1;
				 break;
         case 41:
                 m_anCurrentState[16]-=1;
                 m_anCurrentState[15]+=1;
				 break;
         case 42:
                 m_anCurrentState[10]-=1;
                 break;
         case 43:
                 m_anCurrentState[11]-=1;
                 break;
         case 44:
                 m_anCurrentState[12]-=1;
                 break;
         case 45:
                 m_anCurrentState[13]-=1;
                 break;
         case 46:
                 m_anCurrentState[14]-=1;
                 break;
         case 47:
                 m_anCurrentState[15]-=1;
                 break;
         case 48:
                 m_anCurrentState[16]-=1;
                 break;
         case 49:
                 m_anCurrentState[57]+=1;
                 break;
         case 50:
                 m_anCurrentState[57]-=1;
                 break;
         case 51:
                 m_anCurrentState[47]+=1;
                 break;
         case 52:
                 m_anCurrentState[47]-=1;
                		 break;
         case 53:
                 m_anCurrentState[5]-=1;
                 m_anCurrentState[10]-=1;
                 m_anCurrentState[32]+=1;
                		 break;
         case 54:
                 m_anCurrentState[5]-=1;
                 m_anCurrentState[11]-=1;
                 m_anCurrentState[33]+=1;
				 break;
         case 55:
                 m_anCurrentState[5]-=1;
                 m_anCurrentState[12]-=1;
                 m_anCurrentState[34]+=1;
				 break;
         case 56:
                 m_anCurrentState[32]-=1;
                 m_anCurrentState[5]+=1;
                 m_anCurrentState[10]+=1;
				 break;
         case 57:
                 m_anCurrentState[33]-=1;
                 m_anCurrentState[5]+=1;
                 m_anCurrentState[11]+=1;
				 break;
         case 58:
                 m_anCurrentState[34]-=1;
                 m_anCurrentState[5]+=1;
                 m_anCurrentState[12]+=1;
				 break;
         case 59:
                 m_anCurrentState[32]-=1;
                 m_anCurrentState[33]+=1;
				 break;
         case 60:
                 m_anCurrentState[33]-=1;
                 m_anCurrentState[34]+=1;
				 break;
         case 61:
                 m_anCurrentState[33]-=1;
                 m_anCurrentState[32]+=1;
				 break;
         case 62:
                 m_anCurrentState[34]-=1;
                 m_anCurrentState[33]+=1;
				 break;
         case 63:
                 m_anCurrentState[32]-=1;
                 m_anCurrentState[5]+=1;
				 break;
         case 64:
                 m_anCurrentState[33]-=1;
                 m_anCurrentState[5]+=1;
				 break;
         case 65:
                 m_anCurrentState[34]-=1;
                 m_anCurrentState[5]+=1;
				 break;
         case 66:
                 m_anCurrentState[32]-=1;
                 m_anCurrentState[10]+=1;
				 break;
         case 67:
                 m_anCurrentState[33]-=1;
                 m_anCurrentState[11]+=1;
				 break;
         case 68:
                 m_anCurrentState[34]-=1;
                 m_anCurrentState[12]+=1;
				 break;
         case 69:
                 m_anCurrentState[55]+=1;
                 break;
         case 70:
                 m_anCurrentState[55]-=1;
                 break;
         case 71:
                 m_anCurrentState[35]+=1;
                 break;
         case 72:
                 m_anCurrentState[35]-=1;
                 m_anCurrentState[36]+=1;
				 break;
         case 73:
                 m_anCurrentState[36]-=1;
                 m_anCurrentState[37]+=1;
				 break;
         case 74:
                 m_anCurrentState[37]-=1;
                 m_anCurrentState[38]+=1;
				 break;
         case 75:
                 m_anCurrentState[38]-=1;
                 m_anCurrentState[39]+=1;
				 break;
         case 76:
                 m_anCurrentState[39]-=1;
                 m_anCurrentState[40]+=1;
				 break;
         case 77:
                 m_anCurrentState[40]-=1;
                 m_anCurrentState[41]+=1;
				 break;
         case 78:
                 m_anCurrentState[41]-=1;
                 m_anCurrentState[42]+=1;
				 break;
         case 79:
                 m_anCurrentState[42]-=1;
                 m_anCurrentState[43]+=1;
				 break;
         case 80:
                 m_anCurrentState[43]-=1;
                 m_anCurrentState[44]+=1;
				 break;
         case 81:
                 m_anCurrentState[44]-=1;
                 m_anCurrentState[45]+=1;
				 break;
         case 82:
                 m_anCurrentState[36]-=1;
                 m_anCurrentState[35]+=1;
				 break;
         case 83:
                 m_anCurrentState[37]-=1;
                 m_anCurrentState[36]+=1;
				 break;
         case 84:
                 m_anCurrentState[38]-=1;
                 m_anCurrentState[37]+=1;
				 break;
         case 85:
                 m_anCurrentState[39]-=1;
                 m_anCurrentState[38]+=1;
				 break;
         case 86:
                 m_anCurrentState[40]-=1;
                 m_anCurrentState[39]+=1;
				 break;
         case 87:
                 m_anCurrentState[41]-=1;
                 m_anCurrentState[40]+=1;
				 break;
         case 88:
                 m_anCurrentState[42]-=1;
                 m_anCurrentState[41]+=1;
				 break;
         case 89:
                 m_anCurrentState[43]-=1;
                 m_anCurrentState[42]+=1;
				 break;
         case 90:
                 m_anCurrentState[44]-=1;
                 m_anCurrentState[43]+=1;
				 break;
         case 91:
                 m_anCurrentState[45]-=1;
                 m_anCurrentState[44]+=1;
				 break;
         case 92:
                 m_anCurrentState[35]-=1;
                 break;
         case 93:
                 m_anCurrentState[36]-=1;
                 break;
         case 94:
                 m_anCurrentState[37]-=1;
                break;
         case 95:
                 m_anCurrentState[38]-=1;
                break;
         case 96:
                 m_anCurrentState[39]-=1;
                 break;
         case 97:
                 m_anCurrentState[40]-=1;
                 break;
         case 98:
                 m_anCurrentState[41]-=1;
                 break;
         case 99:
                 m_anCurrentState[42]-=1;
                break;
         case 100:
                 m_anCurrentState[43]-=1;
                 break;
         case 101:
                 m_anCurrentState[44]-=1;
                 break;
         case 102:
                 m_anCurrentState[45]-=1;
                 break;
         case 103:
                 m_anCurrentState[54]+=1;
                 break;
         case 104:
                 m_anCurrentState[54]-=1;
                 break;
         case 105:
                 m_anCurrentState[17]+=1;
                 break;
         case 106:
                 m_anCurrentState[17]-=1;
                 m_anCurrentState[18]+=1;
				 break;
         case 107:
                 m_anCurrentState[18]-=1;
                 m_anCurrentState[19]+=1;
				 break;
         case 108:
                 m_anCurrentState[19]-=1;
                 m_anCurrentState[20]+=1;
				 break;
         case 109:
                 m_anCurrentState[20]-=1;
                 m_anCurrentState[21]+=1;
				 break;
         case 110:
                 m_anCurrentState[21]-=1;
                 m_anCurrentState[22]+=1;
				 break;
         case 111:
                 m_anCurrentState[22]-=1;
                 m_anCurrentState[23]+=1;
				 break;
         case 112:
                 m_anCurrentState[23]-=1;
                 m_anCurrentState[24]+=1;
				 break;
         case 113:
                 m_anCurrentState[24]-=1;
                 m_anCurrentState[25]+=1;
				 break;
         case 114:
                 m_anCurrentState[18]-=1;
                 m_anCurrentState[17]+=1;
				 break;
         case 115:
                 m_anCurrentState[19]-=1;
                 m_anCurrentState[18]+=1;
				 break;
         case 116:
                 m_anCurrentState[20]-=1;
                 m_anCurrentState[19]+=1;
				 break;
         case 117:
                 m_anCurrentState[21]-=1;
                 m_anCurrentState[20]+=1;
				 break;
         case 118:
                 m_anCurrentState[22]-=1;
                 m_anCurrentState[21]+=1;
				 break;
         case 119:
                 m_anCurrentState[23]-=1;
                 m_anCurrentState[22]+=1;
				 break;
         case 120:
                 m_anCurrentState[24]-=1;
                 m_anCurrentState[23]+=1;
				 break;
         case 121:
                 m_anCurrentState[25]-=1;
                 m_anCurrentState[24]+=1;
                 break;
         case 122:
                 m_anCurrentState[17]-=1;
				 break;
         case 123:
                 m_anCurrentState[18]-=1;
                 break;
         case 124:
                 m_anCurrentState[19]-=1;
                 break;
         case 125:
                 m_anCurrentState[20]-=1;
                break;
         case 126:
                 m_anCurrentState[21]-=1;
                 break;
         case 127:
                 m_anCurrentState[22]-=1;
                 break;
         case 128:
                 m_anCurrentState[23]-=1;
                 break;
         case 129:
                 m_anCurrentState[24]-=1;
                 break;
         case 130:
                 m_anCurrentState[25]-=1;
                 break;
         case 131:
                 m_anCurrentState[58]+=1;
                 break;
         case 132:
                 m_anCurrentState[58]-=1;
                 break;
         case 133:
                 m_anCurrentState[48]+=1;
                 break;
         case 134:
                 m_anCurrentState[48]-=1;
                 break;
         case 135:
                 m_anCurrentState[53]+=1;
                 break;
         case 136:
                 m_anCurrentState[53]-=1;
                 break;
         case 137:
                 m_anCurrentState[4]+=1;
                 break;
         case 138:
                 m_anCurrentState[4]-=1;
                 break;
         case 139:
                 m_anCurrentState[17]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[26]+=1;
				 break;
         case 140:
                 m_anCurrentState[18]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[27]+=1;
				 break;
         case 141:
                 m_anCurrentState[19]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[28]+=1;
				 break;
         case 142:
                 m_anCurrentState[20]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[29]+=1;
				 break;
         case 143:
                 m_anCurrentState[21]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[30]+=1;
				 break;
         case 144:
                 m_anCurrentState[22]-=1;
                 m_anCurrentState[4]-=1;
                 m_anCurrentState[31]+=1;
				 break;
         case 145:
                 m_anCurrentState[26]-=1;
                 m_anCurrentState[17]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 146:
                 m_anCurrentState[27]-=1;
                 m_anCurrentState[18]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 147:
                 m_anCurrentState[28]-=1;
                 m_anCurrentState[19]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 148:
                 m_anCurrentState[29]-=1;
                 m_anCurrentState[20]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 149:
                 m_anCurrentState[30]-=1;
                 m_anCurrentState[21]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 150:
                 m_anCurrentState[31]-=1;
                 m_anCurrentState[22]+=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 151:
                 m_anCurrentState[26]-=1;
                 m_anCurrentState[27]+=1;
				 break;
         case 152:
                 m_anCurrentState[27]-=1;
                 m_anCurrentState[28]+=1;
				 break;
         case 153:
                 m_anCurrentState[28]-=1;
                 m_anCurrentState[29]+=1;
				 break;
         case 154:
                 m_anCurrentState[29]-=1;
                 m_anCurrentState[30]+=1;
				 break;
         case 155:
                 m_anCurrentState[30]-=1;
                 m_anCurrentState[31]+=1;
				 break;
         case 156:
                 m_anCurrentState[27]-=1;
                 m_anCurrentState[26]+=1;
				 break;
         case 157:
                 m_anCurrentState[28]-=1;
                 m_anCurrentState[27]+=1;
				 break;
         case 158:
                 m_anCurrentState[29]-=1;
                 m_anCurrentState[28]+=1;
				 break;
         case 159:
                 m_anCurrentState[30]-=1;
                 m_anCurrentState[29]+=1;
				 break;
         case 160:
                 m_anCurrentState[31]-=1;
                 m_anCurrentState[30]+=1;
				 break;
         case 161:
                 m_anCurrentState[26]-=1;
                 m_anCurrentState[17]+=1;
				 break;
         case 162:
                 m_anCurrentState[27]-=1;
                 m_anCurrentState[18]+=1;
				 break;
         case 163:
                 m_anCurrentState[28]-=1;
                 m_anCurrentState[19]+=1;
				 break;
         case 164:
                 m_anCurrentState[29]-=1;
                 m_anCurrentState[20]+=1;
				 break;
         case 165:
                 m_anCurrentState[30]-=1;
                 m_anCurrentState[21]+=1;
				 break;
         case 166:
                 m_anCurrentState[31]-=1;
                 m_anCurrentState[22]+=1;
				 break;
         case 167:
                 m_anCurrentState[26]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 168:
                 m_anCurrentState[27]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 169:
                 m_anCurrentState[28]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 170:
                 m_anCurrentState[29]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 171:
                 m_anCurrentState[30]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 172:
                 m_anCurrentState[31]-=1;
                 m_anCurrentState[4]+=1;
				 break;
         case 173:
                 m_anCurrentState[1]+=1;
                 break;
         case 174:
                 m_anCurrentState[1]-=1;
                 break;
         case 175:
                 m_anCurrentState[49]+=1;
                 break;
         case 176:
                 m_anCurrentState[49]-=1;
                 break;
           default:
        	     cout<<"Unknown reaction ID: "<<p_nReactionID;
         }
}

double Cell::UpdateCellVolume(const double& p_nTime)
{
	const double l_nAmu=0.007;

	m_nCellVolume=m_nInitCellVolume*exp(l_nAmu*(p_nTime-m_nBirthTime));

	//update propensities (should be called after updating the cell volume)
	UpdatePropensities();

	return m_nCellVolume;
}

double Cell::CalculateTotalPropensity()
{
  double l_na0=0.0;

            //update propensities
            UpdatePropensities();

		    // sum all individual propensity
            for(auto l_nValue:m_anHazardValues){

            	l_na0+=l_nValue;
            }

            return l_na0;
}

bool Cell::CheckCellDivision(const double& p_nCurrentTime)
{
	   //get the concentration of ClbM
	   double ClbM=m_anCurrentState[2]/( 0.6 *m_nCellVolume);

	   //we perform the first check ( [ClbM]>20 )
	   if(!m_bHighClbM && ClbM > 20)
	   {
		   m_bHighClbM=true;

		   return false;
	   }
	   //second check [ClbM] increase and then decreased
	   else if(m_bHighClbM && ClbM<12.5)
	   {

		   return true;
	   }

	   return false;
}

Cell* Cell::DivideCell(const double& p_nCurrentTime,const double& p_nDf)
{
	   // set this cell division time
	   m_nDivTime=p_nCurrentTime;

	   //create a new daughter cell
	   Cell* l_pcDaughterCell=new Cell();

	   l_pcDaughterCell->InitCell();

	   //calculate the volume
	   double l_nIniVolume=p_nDf*m_nCellVolume;
	   l_pcDaughterCell->SetInitCellVolume(l_nIniVolume);
	   l_pcDaughterCell->SetCellVolume(l_nIniVolume);

	   //calculate the cell initial state
	   VectorDouble l_anInitialState;
	   l_anInitialState.assign(m_nSCount+1,0);

	   //calculate the initial state
	   for (int i=1;i<=m_nSCount;i++)
	   {
		   l_anInitialState[i]=round(m_anCurrentState[i]*p_nDf);
	   }

	   //set the initial state
	   l_pcDaughterCell->SetInitState(l_anInitialState);

	   //TODO: this is a duplicate initialization
	   l_pcDaughterCell->SetCurrentState(l_anInitialState);

	   //set birth time
	   l_pcDaughterCell->SetBirthTime(p_nCurrentTime);

	   m_bHighClbM=false;

	   //return the daughter cell
	   return l_pcDaughterCell;
}

