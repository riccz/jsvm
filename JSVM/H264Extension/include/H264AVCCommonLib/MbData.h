/*
********************************************************************************

NOTE - One of the two copyright statements below may be chosen
       that applies for the software.

********************************************************************************

This software module was originally developed by

Heiko Schwarz    (Fraunhofer HHI),
Tobias Hinz      (Fraunhofer HHI),
Karsten Suehring (Fraunhofer HHI)

in the course of development of the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video
Coding) for reference purposes and its performance may not have been optimized.
This software module is an implementation of one or more tools as specified by
the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding).

Those intending to use this software module in products are advised that its
use may infringe existing patents. ISO/IEC have no liability for use of this
software module or modifications thereof.

Assurance that the originally developed software module can be used
(1) in the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) once the
ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) has been adopted; and
(2) to develop the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding): 

To the extent that Fraunhofer HHI owns patent rights that would be required to
make, use, or sell the originally developed software module or portions thereof
included in the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) in a
conforming product, Fraunhofer HHI will assure the ISO/IEC that it is willing
to negotiate licenses under reasonable and non-discriminatory terms and
conditions with applicants throughout the world.

Fraunhofer HHI retains full right to modify and use the code for its own
purpose, assign or donate the code to a third party and to inhibit third
parties from using the code for products that do not conform to MPEG-related
ITU Recommendations and/or ISO/IEC International Standards. 

This copyright notice must be included in all copies or derivative works.
Copyright (c) ISO/IEC 2005. 

********************************************************************************

COPYRIGHT AND WARRANTY INFORMATION

Copyright 2005, International Telecommunications Union, Geneva

The Fraunhofer HHI hereby donate this source code to the ITU, with the following
understanding:
    1. Fraunhofer HHI retain the right to do whatever they wish with the
       contributed source code, without limit.
    2. Fraunhofer HHI retain full patent rights (if any exist) in the technical
       content of techniques and algorithms herein.
    3. The ITU shall make this code available to anyone, free of license or
       royalty fees.

DISCLAIMER OF WARRANTY

These software programs are available to the user without any license fee or
royalty on an "as is" basis. The ITU disclaims any and all warranties, whether
express, implied, or statutory, including any implied warranties of
merchantability or of fitness for a particular purpose. In no event shall the
contributor or the ITU be liable for any incidental, punitive, or consequential
damages of any kind whatsoever arising from the use of these programs.

This disclaimer of warranty extends to the user of these programs and user's
customers, employees, agents, transferees, successors, and assigns.

The ITU does not represent or warrant that the programs furnished hereunder are
free of infringement of any third-party patents. Commercial implementations of
ITU-T Recommendations, including shareware, may be subject to royalty fees to
patent holders. Information regarding the ITU-T patent policy is available from 
the ITU Web site at http://www.itu.int.

THIS IS NOT A GRANT OF PATENT RIGHTS - SEE THE ITU-T PATENT POLICY.

********************************************************************************
*/




#if !defined(AFX_MBDATA_H__6F1A2BEC_47BC_4944_BE36_C0E96ED39557__INCLUDED_)
#define AFX_MBDATA_H__6F1A2BEC_47BC_4944_BE36_C0E96ED39557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "H264AVCCommonLib/Mv.h"
#include "H264AVCCommonLib/MbMvData.h"
#include "H264AVCCommonLib/MbTransformCoeffs.h"
#include "H264AVCCommonLib/MbDataStruct.h"

H264AVC_NAMESPACE_BEGIN

// TMM_ESS {
enum SMbIdx
{
  C_0 = 0x00,  V_0 = 0x01,  C_1	= 0x02,
  H_0 = 0x03,  M   = 0x04,  H_1	= 0x05,
  C_2 = 0x06,  V_1 = 0x07,  C_3	= 0x08
};
// TMM_ESS }

class H264AVCCOMMONLIB_API MbData :
public MbDataStruct
{
public:
  MbData()
  : m_pcMbTCoeffs         ( 0 )
  , m_pcMbIntraBaseTCoeffs( 0 )
  {
    m_apcMbMvdData   [ LIST_0 ]  = NULL;
    m_apcMbMvdData   [ LIST_1 ]  = NULL;
    m_apcMbMotionData[ LIST_0 ]  = NULL;
    m_apcMbMotionData[ LIST_1 ]  = NULL;
  }

  ~MbData()
  {
    clearIntraBaseCoeffs();
  }

  Void init(  MbTransformCoeffs*  pcMbTCoeffs,
              MbMvData*           pcMbMvdDataList0,
              MbMvData*           pcMbMvdDataList1,
              MbMotionData*       pcMbMotionDataList0,
              MbMotionData*       pcMbMotionDataList1)
  {
    m_pcMbTCoeffs           = pcMbTCoeffs;
    m_pcMbIntraBaseTCoeffs  = 0;
    m_apcMbMvdData[0]       = pcMbMvdDataList0;
    m_apcMbMvdData[1]       = pcMbMvdDataList1;
    m_apcMbMotionData[0]    = pcMbMotionDataList0;
    m_apcMbMotionData[1]    = pcMbMotionDataList1;
  }

public:
  MbTransformCoeffs&        getMbTCoeffs    ()                          { return *m_pcMbTCoeffs; }
  MbMvData&                 getMbMvdData    ( ListIdx eListIdx )        { return *m_apcMbMvdData   [ eListIdx ]; }
  MbMotionData&             getMbMotionData ( ListIdx eListIdx )        { return *m_apcMbMotionData[ eListIdx ]; }

  const MbTransformCoeffs&  getMbTCoeffs    ()                    const { return *m_pcMbTCoeffs; }
  const MbMvData&           getMbMvdData    ( ListIdx eListIdx )  const { return *m_apcMbMvdData   [ eListIdx ]; }
  const MbMotionData&       getMbMotionData ( ListIdx eListIdx )  const { return *m_apcMbMotionData[ eListIdx ]; }

  operator MbTransformCoeffs& ()                                        { return *m_pcMbTCoeffs; }


  ErrVal  loadAll( FILE* pFile );
  ErrVal  saveAll( FILE* pFile );

  ErrVal  copyMotion    ( MbData& rcMbData, UInt    uiSliceId = MSYS_UINT_MAX );
  ErrVal  copyMotionBL  ( MbData& rcMbData, Bool bDirect8x8, UInt    uiSliceId = MSYS_UINT_MAX );
  ErrVal  upsampleMotion( MbData& rcMbData, Par8x8  ePar8x8, Bool bDirect8x8   );

	// TMM_ESS {
  ErrVal  upsampleMotionNonDyad( MbData* rcBaseMbData, Int iMbPelOrigX, Int iMbPelOrigY, ResizeParameters* pcParameters );
  ErrVal  upsampleMotion3_2( const  MbData* apcBaseMbData[4],SMbIdx   eSMbIdx, Bool bDirect8x8, ResizeParameters* pcParameters);
  ErrVal  noUpsampleMotion(); 
	// TMM_ESS }

  Void                clearIntraBaseCoeffs  ()                                { delete m_pcMbIntraBaseTCoeffs; m_pcMbIntraBaseTCoeffs = 0; }
  ErrVal              storeIntraBaseCoeffs  ( MbTransformCoeffs& rcCoeffs );
  MbTransformCoeffs&  getIntraBaseCoeffs    ()                                { return *m_pcMbIntraBaseTCoeffs; }

private:
  MbTransformCoeffs*  m_pcMbTCoeffs;
  MbTransformCoeffs*  m_pcMbIntraBaseTCoeffs;
  MbMvData*           m_apcMbMvdData[2];
  MbMotionData*       m_apcMbMotionData[2];

// TMM_ESS {
  Int       m_iPelOrigX;
  Int       m_iPelOrigY;
  MbMode    m_aeBl4x4MbMode[16];  // mb mode for each 4x4 blk
  SChar     m_ascBl4x4RefIdx[2][16];  // ref index of list_0/1 for each 4x4 blk
  Mv        m_acBl4x4Mv[2][16];  // motion vectors of list_0/1 for each 4x4 blk
  Bool      m_abBl8x8Intra[4];   // flag indicating if blk 8x8 is in intra or not
  Bool		m_bDirect8x8;
  
 typedef struct 
  {
	  UShort usNbMbBase; //nb base corresponding MBs
	  UShort usNbBl8x8; //nb base corresponding 8x8 blocks per base MBs
	  UShort usLutIdx;  //
	  UInt auiIdxMbData[4]; //Base MBs idx inside the hyperMacroblock
	  UInt auiIdxBl8x8[4][4]; //8x8 scan indexes 
	  UChar puc4x4Map[16]; //4x4 base blocks indexes 
	  const BlkMode* peModeSMb; //Table given the 8x8 block modes as a function of base corresponding MB mode
  } MbClassMotionData;
  
  static const MbData::MbClassMotionData m_mbmotiondata[9];
  static const UChar m_aucPredictor[2][4];
  static const BlkMode m_eModesCorner[20];
  static const BlkMode m_eModesVertical[10];
  static const BlkMode m_eModesHorizontal[10];
  static const BlkMode m_eModesCenter[5];

  //Generic
  ErrVal  xInherit4x4BlkMotion( Int iB4x4X , Int iB4x4Y , MbData *rcBaseMbData, ResizeParameters* pcParameters );
  ErrVal  xDecide8x8BlkPartition( Int iB4x4X , Int iB4x4Y, ResizeParameters* pcParameters );
  ErrVal  xDecideMacroblockMode( );
  //3_2  
  ErrVal xInheritMbMotionData3_2(const MbData* apcMbData[4], const SMbIdx  eSMbIdx);
  //ESS common Tools	
  ErrVal xTryToMergeBl8x8(const UInt uiB8x8Idx);
  ErrVal xTryToMergeBl16x16();	
  Bool   xAreIdentical(const UInt uiBlIdx1,const UInt uiBlIdx2, const bool bB8x8=false);
  ErrVal xMergeBl8x8MvAndRef(const UInt uiBlIdx,const UInt uiWhich);
  ErrVal xMergeBlXxYMvAndRef(const UInt uiBlIdx,const Bool is8x4, const UInt uiWhich=0);
  ErrVal xMergeBl4x4MvAndRef(const UInt uiBlIdx);
  ErrVal xFillMvandRefBl4x4(const UInt uiBlIdx,const UChar* pucWhich,const UInt uiList,const SChar* psChosenRefIdx);
  ErrVal xCopyBl8x8(const UInt uiBlIdx,const UInt uiBlIdxCopy); 
  ErrVal xRemoveIntra(const UInt uiBlIdx);
  ErrVal xFillMbMvData(ResizeParameters* pcParameters );
// TMM_ESS }
};


H264AVC_NAMESPACE_END


#endif // !defined(AFX_MBDATA_H__6F1A2BEC_47BC_4944_BE36_C0E96ED39557__INCLUDED_)
