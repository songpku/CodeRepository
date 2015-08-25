#ifndef _HI_MPI_IVE_H_
#define _HI_MPI_IVE_H_

#include "hi_comm_ive.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_DMA
*   Description  : Direct memory access (DMA):
*                  1.Direct memory copy;
*				   2. Copy with interval bytes;
*                  3. Memset using 3 bytes; 
*				   4. Memset using 8 bytes;
*   Input        : IVE_HANDLE          *pIveHandle        Returned handle ID of a task.
*                  IVE_DATA_S          *pstSrc            Input source data.The input data is treated as U8C1 data.
*				   IVE_DATA_S          *pstDst            Output result data.
*                  IVE_DMA_CTRL_S      *pstDmaCtrl        DMA control parameter.
*                  HI_BOOL              bInstant          Flag indicating whether to generate an interrupt.
*                                                         If the output result blocks the next operation,
*                                                         set bInstant to HI_TRUE.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 32x1 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*		2.  Data		 : 2013-07-19
*			Author		 : Chen Quanfu
*			Modification : Modify parameters
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_DMA(IVE_HANDLE *pIveHandle, IVE_DATA_S *pstSrc,
	IVE_DATA_S *pstDst, IVE_DMA_CTRL_S *pstDmaCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Filter
*   Description  : 5x5 template filter.
*   Input        : IVE_HANDLE            *pIveHandle         Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S       *pstSrc             Input source data.
*                                                            The U8C1,SP420 and SP422 input formats are supported.
*                  IVE_DST_IMAGE_S       *pstDst             Output result, of same type with the input. 
*                  IVE_FILTER_CTRL_S     *pstFilterCtrl      Control parameters of filter
*                  HI_BOOL               bInstant            For details, see HI_MPI_IVE_DMA.            
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-07-23
*           Author       : Chen Quanfu
*           Modification : Modified function parameters

*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Filter(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_IMAGE_S *pstDst, IVE_FILTER_CTRL_S *pstFilterCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_CSC
*   Description  : YUV2RGB\YUV2HSV\YUV2LAB\RGB2YUV color space conversion are supported.
*   Input        : IVE_HANDLE         *pIveHandle       Returned handle ID of a task         
*                  IVE_SRC_IMAGE_S    *pstSrc           Input source data:
*                                                       1. SP420\SP422 type for YUV2RGB\YUV2HSV\YUV2LAB;
*                                                       2. U8C3_PACKAGE\U8C3_PLANAR type for RGB2YUV;
*                  IVE_DST_IMAGE_S    *pstDst           Output result:
*                                                       1. U8C3_PACKAGE\U8C3_PLANAR typed for YUV2RGB\YUV2HSV\YUV2LAB;
*                                                       2. SP420\SP422 type for RGB2YUV;
*                  IVE_CSC_CTRL_S     *pstCscCtrl       Control parameters for CSC
*                  HI_BOOL             bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-08-09
*           Author       : Tan Bing
*           Modification : Modified function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_CSC(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_IMAGE_S *pstDst, IVE_CSC_CTRL_S *pstCscCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_FILTER_AND_CSC
*   Description  : Only support YUV2RGB color space convertion.
*   Input        : IVE_HANDLE                 *pIveHandle        Returned handle ID of a task.                   
*                  IVE_SRC_IMAGE_S            *pstSrc            Input source data.Only SP420\SP422 type are supported.                    
*                  IVE_DST_IMAGE_S            *pstDst            Output result.Only U8C3_PACKAGE\U8C3_PLANAR are supported.                  
*                  IVE_FILTER_AND_CSC_CTRL_S  *pstFltCscCtrl     Control parameters.
*                  HI_BOOL                     bInstant          For details, see HI_MPI_IVE_DMA.                  
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-08-09
*           Author       : Tan Bing
*           Modification : Modified function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_FilterAndCSC(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
        IVE_DST_IMAGE_S *pstDst, IVE_FILTER_AND_CSC_CTRL_S *pstFltCscCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Sobel
*   Description  : SOBEL is used to extract the gradient information. 
*   Input        : IVE_HANDLE           *pIveHandle      Returned handle ID of a task          
*                  IVE_SRC_IMAGE_S      *pstSrc          Input source data. Only the U8C1 input image is supported.
*                  IVE_DST_IMAGE_S      *pstDstH         The (horizontal) result of input image filtered by the input mask;        
*                  IVE_DST_IMAGE_S      *pstDstV         The (vertical) result  of input image filtered by the transposed mask;      
*                  IVE_SOBEL_CTRL_S     *pstSobelCtrl    Control parameters
*                  HI_BOOL               bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       1.  Date         : 2013-07-23
*           Author       : Chen Quanfu
*           Modification : Modified function parameters
*		
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Sobel(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
        IVE_DST_IMAGE_S *pstDstH, IVE_DST_IMAGE_S *pstDstV,
        IVE_SOBEL_CTRL_S *pstSobelCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_MagAndAng
*   Description  : MagAndAng is used to extract the edge information. 
*   Input        : IVE_HANDLE              *pIveHandle         Returned handle ID of a task             
*                  IVE_SRC_INFO_S          *pstSrc             Input source data. Only the U8C1 input format is supported.            
*                  IVE_MEM_INFO_S          *pstDstMag          Output magnitude.         
*                  IVE_MEM_INFO_S          *pstDstAng          Output angle.
*                                                              If the output mode is set to magnitude only,
*                                                              this item can be set to null.
*                  IVE_MAG_AND_ANG_CTRL_S  *pstMagAndAngCtrl   Control parameters
*                  HI_BOOL                  bInstant           For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*		2.  Date         : 2013-07-17
*			Author       : Chen Quanfu
*			Modification : Modified function and control parameter name
*		3.  Date         : 2013-07-23
*			Author       : Chen Quanfu
*			Modification : Modified function parameters
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_MagAndAng(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
        IVE_DST_IMAGE_S *pstDstMag, IVE_DST_IMAGE_S *pstDstAng,
        IVE_MAG_AND_ANG_CTRL_S *pstMagAndAngCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Dilate
*   Description  : 5x5 template dilate. Only the U8C1 binary image input is supported.Or else the result is not expected.
*   Input        : IVE_HANDLE             *pIveHandle          Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S        *pstSrc              Input binary image, which consists of 0 or 255;            
*                  IVE_DST_IMAGE_S        *pstDst              Output result.           
*                  IVE_DILATE_CTRL_S      *pstDilateCtrl       Control parameters.
*                  HI_BOOL                 bInstant            For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  The input value, output value, and mask value must be 0 or 255.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-07-23
*           Author       : Chen Quanfu
*           Modification : Modified parameters
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Dilate(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_IMAGE_S *pstDst, IVE_DILATE_CTRL_S *pstDilateCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Erode
*   Description  : 5x5 template erode. Only the U8C1 binary image input is supported.Or else the result is not correct.
*   Input        : IVE_HANDLE              *pIveHandle        Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S          *pstSrc           Input binary image, which consists of 0 or 255;            
*                  IVE_DST_IMAGE_S          *pstDst           Output result.          
*                  IVE_ERODE_CTRL_S         *pstErodeCtrl     Control parameters
*                  HI_BOOL                   bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE  *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  The input value, output value, and mask value must be 0 or 255.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-07-23
*           Author       : Chen Quanfu
*           Modification : Modified parameters
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Erode(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_IMAGE_S *pstDst, IVE_ERODE_CTRL_S *pstErodeCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Thresh 
*   Description  : Thresh operation to the input image.
*   Input        : IVE_HANDLE          *pIveHandle       Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S     *pstSrc           Input source data. Only the U8C1 input format is supported.           
*                  IVE_DST_IMAGE_S     *pstDst           Output result           
*                  IVE_THRESH_CTRL_S   *pstThreshCtrl    Control parameters
*                  HI_BOOL              bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*		2.  Date		 : 2013-07-23
*           Author		 : Tan Bing 
*			Modification : Modification
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Thresh(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_IMAGE_S *pstDst, IVE_THRESH_CTRL_S *pstThrCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_And
*   Description  : Binary images' AND operation. 
*   Input        : IVE_HANDLE         *pIveHandle       Returned handle ID of a task
*                  IVE_SRC_IMAGE_S    *pstSrc1          The input source1. Only U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S    *pstSrc2          The input source2.Only U8C1 input format is supported.
*                  IVE_DST_IMAGE_S    *pstDst           Output result of " src1 & src2 ".
*                  HI_BOOL             bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  The types, widths, heights of two input sources must be the same.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_And(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1, 
    IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_IMAGE_S *pstDst, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Sub
*   Description  : Two gray images' SUB operation. 
*   Input        : IVE_HANDLE          *pIveHandle   Returned handle ID of a task
*                  IVE_SRC_IMAGE_S     *pstSrc1      Minuend of the input source.Only the U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S     *pstSrc2      Subtrahend of the input source.Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S     *pstDst       Output result of src1 minus src2
*                  IVE_SUB_CTRL_S      *pstSubCtrl   Control parameter
*                  HI_BOOL              bInstant     For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  The types, widths, heights of two input sources must be the same.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-08-09
*           Author       : Tan Bing
*           Modification : Modified function parameter
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Sub(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1, 
    IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_IMAGE_S *pstDst, IVE_SUB_CTRL_S *pstSubCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Or
*   Description  : Two binary images' OR operation. 
*   Input        : IVE_HANDLE          *pIveHandle    Returned handle ID of a task
*                  IVE_SRC_IMAGE_S     *pstSrc1       Input source1. Only the U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S     *pstSrc2       Input source2. Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S     *pstDst        Output result src1 or src2
*                  HI_BOOL              bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  The types, widths, heights of two input sources must be the same.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.  Date         : 2013-08-09
*           Author       : Tan Bing
*           Modification : Modified function parameter
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Or(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1, 
    IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_IMAGE_S *pstDst, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_INTEG
*   Description  : Calculate the input gray image's integral image. 
*   Input        : IVE_HANDLE           *pIveHandle        Returned handle ID of a task
*                  IVE_SRC_IMAGE_S      *pstSrc            Input source data.Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S      *pstDst            Output result.Can be U32C1 or U64C1, relied on the control parameter.
*				   IVE_INTEG_CTRL_S     *pstIntegCtrl      Integ Control
*                  HI_BOOL               bInstant          For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The input image stride must be 16-byte-aligned.
*                  The output integral image must be 16-pixel-aligned. The pixel can be 32bit or 64 bit relied on the 
*                  control parameter.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*       2.	Date		 : 2013-03-18
*			Author		 : Tan  Bing
*			Modification : Modified function
*		3. Date			 : 2013-07-15
*		    Author		 : Chen Quanfu
*			Modification : Modified function
*			Spec		 : Modify IVE_INTEG_OUT_FMT_E to  IVE_INTEG_CTRL_S
*       4.	Date		 : 2013-07-23
*			Author		 : Chen Quanfu
*			Modification : Modified parameters
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Integ(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDst, IVE_INTEG_CTRL_S *pstIntegCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Hist
*   Description  : Calculate the input gray image's histogram. 
*   Input        : IVE_HANDLE          *pIveHandle      Returned handle ID of a task
*                  IVE_SRC_IMAGE_S     *pstSrc          Input source data. Only the U8C1 input format is supported.
*                  IVE_DST_MEM_INFO_S  *pstDst          Output result.
*                  HI_BOOL              bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Hist(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
    IVE_DST_MEM_INFO_S *pstDst, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Thresh_S16 
*   Description	 : S16 image's THRESH operation.
*   Input        : IVE_HANDLE              *pIveHandle             Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S         *pstSrc                 Input source data.Only the S16 input format is supported.             
*                  IVE_DST_IMAGE_S         *pstDst                 Output result.           
*                  IVE_THRESH_S16_CTRL_S   *pstThreshS16Ctrl       Control parameters
*                  HI_BOOL                  bInstant               For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data must be 2-byte-aligned
*				   The physical addresses of output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-05-16
*           Author       : Tan bing 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Thresh_S16(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDst, IVE_THRESH_S16_CTRL_S *pstThreshS16Ctrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Thresh_U16 
*   Description	 : U16 image's THRESH operation.
*   Input        : IVE_HANDLE                *pIveHandle        Returned handle ID of a task           
*                  IVE_SRC_IMAGE_S           *pstSrc            Input source data. Only the U16 input format is supported.           
*                  IVE_DST_IMAGE_S           *pstDst            Output result           
*                  IVE_THRESH_U16_CTRL_S     *pstThreshU16Ctrl  Control parameters
*                  HI_BOOL                    bInstant          For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data must be 2-byte-aligned
*				   The physical addresses of output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-05-16
*           Author       : Tan bing 
*           Modification : Created function
*       2.  Date         : 2013-08-07
*           Author       : Chen Quanfu 
*           Modification : Implement function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Thresh_U16(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDst, IVE_THRESH_U16_CTRL_S *pstThreshU16Ctrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_16BitTo8Bit
*   Description  : Scale the input 16bit data to the output 8bit data. 
*   Input        : IVE_HANDLE                *pIveHandle              Returned handle ID of a task
*                  IVE_SRC_IMAGE_S           *pstSrc                  Input source data.Only U16C1\S16C1 input is supported. 
*                  IVE_DST_IMAGE_S           *pstDst                  Output result
*				   IVE_16BITTO8BIT_CTRL_S    *pst16BitTo8BitCtrl      control parameter
*                  HI_BOOL                    bInstant                For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data must be 2-byte-aligned
*				   The physical addresses of output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-12
*           Author       : Tan Bing 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_16BitTo8Bit(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDst, IVE_16BIT_TO_8BIT_CTRL_S *pst16BitTo8BitCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_OrdStatFilter
*   Description  :Order Statistic Filter. It can be used as median\max\min value filter.
*   Input        : IVE_HANDLE                   *pIveHandle          Returned handle ID of a task
*                  IVE_SRC_IMAGE_S              *pstSrc              Input source data. Only U8C1 input is supported
*                  IVE_DST_IMAGE_S              *pstDst              Output result
*				   IVE_ORD_STAT_FILTER_CTRL_S   *pstOrdStatFltCtrl   Control parameter
*                  HI_BOOL                       bInstant            For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-12
*           Author       : Tan Bing 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_OrdStatFilter(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDst, IVE_ORD_STAT_FILTER_CTRL_S *pstOrdStatFltCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Bernsen
*   Description  : Image binaryzation using BERNSEN method or its extensional method.
*   Input        : IVE_HANDLE            *pIveHandle        Returned handle ID of a task
*                  IVE_SRC_IMAGE_S       *pstSrc            Input source. Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S       *pstDst            Output result 
*				   IVE_BERNSEN_CTRL_S    *pstBernsenCtrl    Control parameter
*                  HI_BOOL                bInstant          For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-15
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Bernsen(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc,
	IVE_DST_IMAGE_S *pstDst, IVE_BERNSEN_CTRL_S *pstBernsenCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Map
*   Description  : Map a image to another through a lookup table.
*   Input        : IVE_HANDLE           *pIveHandle  Returned handle ID of a task
*                  IVE_SRC_IMAGE_S      *pstSrc          Input source. Only the U8C1 input format is supported.
*                  IVE_SRC_MEM_INFO_S   *pstMap          Input lookup table. Must be an U8 array of size 256.
*                  IVE_DST_IMAGE_S      *pstDst          Output result.
*                  HI_BOOL               bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-17
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Map(IVE_HANDLE *pIveHandle,IVE_SRC_IMAGE_S *pstSrc, 
	IVE_SRC_MEM_INFO_S *pstMap, IVE_DST_IMAGE_S *pstDst,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_EqualizeHist
*   Description  : Enhance the input image's contrast through histogram equalization.
*   Input        : IVE_HANDLE                 *pIveHandle              Returned handle ID of a task
*                  IVE_SRC_IMAGE_S            *pstSrc                  Input source.Only U8C1 input format is supported.
*                  IVE_DST_IMAGE_S            *pstDst                  Output result.
*				   IVE_EQUALIZEHIST_CTRL_S    *pstEqualizeHistCtrl     EqualizeHist control parameter.
*                  HI_BOOL                     bInstant                For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-07-17
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_EqualizeHist(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc,
	IVE_DST_IMAGE_S *pstDst, IVE_EQUALIZE_HIST_CTRL_S *pstEqualizeHistCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Add
*   Description  : Two gray images' ADD operation. 
*   Input        : IVE_HANDLE          *pIveHandle      Returned handle ID of a task
*                  IVE_SRC_IMAGE_S     *pstSrc1         Augend of the input source.Only the U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S     *pstSrc2         Addend of the input source.Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S     *pstDst          Output result of src1 plus src2
*				   IVE_ADD_CTRL_S      *pstAddCtrl      Control parameter
*                  HI_BOOL              bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  The types, widths, heights of two input sources must be the same.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-07-17
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Add(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1,
	IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_IMAGE_S *pstDst, IVE_ADD_CTRL_S *pstAddCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Xor
*   Description  : Two binary images' XOR operation. 
*   Input        : IVE_HANDLE           *pIveHandle    Returned handle ID of a task
*                  IVE_SRC_IMAGE_S      *pstSrc1       The input source1.Only the U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S      *pstSrc2       The input source2.
*                  IVE_DST_IMAGE_S      *pstDst        Output result 
*                  HI_BOOL               bInstant      For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1080 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  The types, widths, heights of two input sources must be the same.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-07-17
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Xor(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1,
	IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_IMAGE_S *pstDst, HI_BOOL bInstant); 

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_NCC
*   Description  : Calculate two gray images' NCC (Normalized Cross Correlation). 
*   Input        : IVE_HANDLE            *pIveHandle     Returned handle ID of a task
*                  IVE_SRC_IMAGE_S       *pstSrc1        Input source1. Only the U8C1 input format is supported.
*                  IVE_SRC_IMAGE_S       *pstSrc2        Input source2. Must be of the same type¡¢size of source1.
*                  IVE_DST_MEM_INFO_S    *pstDst         Output result 
*                  HI_BOOL                bInstant       For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 8-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-16
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_NCC(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc1, 
	IVE_SRC_IMAGE_S *pstSrc2, IVE_DST_MEM_INFO_S *pstDst, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_CCL
*   Description  : Connected Component Labeling. Only 8-Connected method is supported.
*   Input        : IVE_HANDLE         *pIveHandle      Returned handle ID of a task
*                  IVE_SRC_IMAGE_S    *pstSrc          Input source
*                  IVE_MEM_INFO_S     *pstBlob         Output result of detected region;
*				   IVE_CCL_CTRL_S     *pstCclCtrl      CCL control parameter 
*                  HI_BOOL             bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 720 * 640 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-1
*           Author       : Cheng Jianmin
*           Modification : Created function
*****************************************************************************/
HI_S32 HI_MPI_IVE_CCL(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstSrc,
	IVE_DST_MEM_INFO_S *pstBlob, IVE_CCL_CTRL_S *pstCclCtrl, HI_BOOL bInstant); 

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_GMM
*   Description  : Separate foreground and background using GMM(Gaussian Mixture Model) method;
*                  Gray or RGB GMM and shadow detection are supported.
*   Input        : IVE_HANDLE          *pIveHandle  Returned handle ID of a task
*                  IVE_SRC_IMAGE_S     *pstSrc       Input source. Only support U8C1 or U8C3_PACKAGE input.
*				   IVE_DST_IMAGE_S     *pstFg        Output foreground (Binary) image.
*				   IVE_DST_IMAGE_S     *pstBg        Output background image. Of the sampe type of pstSrc. 
*				   IVE_MEM_INFO_S      *pstModel     Model data.
*				   IVE_GMM_CTRL_S      *pstGMMCtrl   Control parameter.
*                  HI_BOOL              bInstant     For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*                  IVE_DST_IMAGE_S *pstFg
*				   IVE_DST_IMAGE_S *pstBg
*				   IVE_MEM_INFO_S *pstModel
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 360x288 pixels to 720 * 576 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-07
*           Author       : Cheng Jianmin
*           Modification : Created function
*****************************************************************************/
HI_S32 HI_MPI_IVE_GMM(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstFg, 
	IVE_DST_IMAGE_S *pstBg, IVE_MEM_INFO_S *pstModel, IVE_GMM_CTRL_S *pstGMMCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Canny
*   Description  : Edge detection using Canny method.
*   Input        : IVE_HANDLE           *pIveHandle        Returned handle ID of a task
*                  IVE_SRC_IMAGE_S      *pstSrc            Input source. Only the U8C1 inpu format is supported
*                  IVE_DST_IMAGE_S      *pstDst            Output result. 
*				   IVE_CANNY_CTRL_S     *pstCannyCtrl      Control parameter.
*                  HI_BOOL               bInstant        For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-12
*           Author       : Chen Quanfu
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Canny(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc,
	IVE_DST_IMAGE_S *pstDst, IVE_CANNY_CTRL_S *pstCannyCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LBP
*   Description  : LBP calculation using the original method and a extensional method.
*   Input        : IVE_HANDLE         *pIveHandle     Returned handle ID of a task
*                  IVE_SRC_IMAGE_S    *pstSrc         Input source.Only the U8C1 inpu format is supported.
*                  IVE_DST_IMAGE_S    *pstDst         Output result 
*				   IVE_LBP_CTRL_S     *pstLbpCtrl     Control parameter
*                  HI_BOOL             bInstant       For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-09-22
*           Author       : Tan Bing
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LBP(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc,
	IVE_DST_IMAGE_S *pstDst, IVE_LBP_CTRL_S *pstLbpCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LKOpticalFlow
*   Description  : Calculate LK-Optical Flow in single-layer of the pyramid. 
*   Input        : IVE_HANDLE                  *pIveHandle          Returned handle ID of a task
*                  IVE_SRC_IMAGE_S             *pstPreSrc           Pre-frame input source.Must be U8C1 image
*				   IVE_SRC_IMAGE_S             *pstCurSrc			Cur-frame input source.Same size¡¢type with pstPreSrc.
*                  IVE_SRC_MEM_INFO_S          *pstPoint		    Intresting points coordinates in the cur-layer
*                                                                   for LKOpticalFlow tracking.
*                  IVE_MEM_INFO_S              *pstMV               Accumlative movements of the interesting points in pre-layers
*                                                                   or init 0s for the first-layer as input.                                                                init 0s .
*                                                                   Movements of the interesting points being tracked in cur-layer
*                                                                   as output.
*                  IVE_LKOPTICALFLOW_CTRL_S    *pstOpticalFlowCtrl  Control parameters.
*                  HI_BOOL                      bInstant            For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*				   IVE_MEM_INFO_S *pstMV     Output point moving
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 360x288 pixels to 720 * 576 pixels.
*                  The physical addresses of the input data and output data must be aligned by byte. 
*                  The stride must be 8-byte-aligned.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-23
*           Author       : Cheng Jianmin
*           Modification : Created function
/****************************************************************************/
HI_S32 HI_MPI_IVE_LKOpticalFlow(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstPreSrc, IVE_SRC_IMAGE_S *pstCurSrc,	
	IVE_SRC_MEM_INFO_S *pstPoint, IVE_MEM_INFO_S *pstMV, IVE_LK_OPTICAL_FLOW_CTRL_S *pstOpticalFlowCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_NormGrad
*   Description  : Gradient calculation and the output is normalized to S8. 
*   Input        : IVE_HANDLE             *pIveHandle  Returned handle ID of a task
*                  IVE_SRC_IMAGE_S        *pstSrc            Input source data
*                  IVE_DST_IMAGE_S        *pstDstH           The (horizontal) result of input image filtered by the input mask;        
*                  IVE_DST_IMAGE_S        *pstDstV           The (vertical) result  of input image filtered by the transposed mask;
*				   IVE_DST_IMAGE_S        *pstDstHV          Output the horizontal and vertical component in single image in package format.
*				   IVE_NORM_GRAD_CTRL_S   *pstNormGradCtrl   Control parameter
*                  HI_BOOL                 bInstant          For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-08-12
*           Author       : Tan Bing 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_NormGrad(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, 
	IVE_DST_IMAGE_S *pstDstH, IVE_DST_IMAGE_S *pstDstV, IVE_DST_IMAGE_S *pstDstHV, 
	IVE_NORM_GRAD_CTRL_S *pstNormGradCtrl, HI_BOOL bInstant);


/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Shitomasi
*   Description  : Corners detection using Shi-Tomasi-like method.
*   Input        : IVE_HANDLE            *pIveHandle         Returned handle ID of a task
*                  IVE_SRC_IMAGE_S       *pstSrc             Input source data
*                  IVE_DST_IMAGE_S       *pstDstEig          Output result of eig
*				   IVE_SHITOMASI_CTRL_S  *pstShitomasiCtrl   Control parameter
*                  HI_BOOL                bInstant           For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be byte-aligned. 
*                  The stride must be 16-byte-aligned.
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-09-16
*           Author       : Cheng Jianmin
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_ShiTomasi(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstDstEig,
	IVE_SHITOMASI_CTRL_S *pstShitomasiCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_UpdateBgModel
*   Description  :  
*   Input        : IVE_HANDLE            *pIveHandle       Returned handle ID of a task
*                  IVE_SRC_IMAGE_S       *pstDiffFg        Background subtraction foreground image
*                  IVE_SRC_IMAGE_S       *pstCurGrad       Current gradient image, both horizontally and vertically
*                                                          graded in accordance with [xyxyxy ...] format
*                  IVE_SRC_IMAGE_S       *pstBgGrad        Background gradient image
*                  IVE_GRAD_FG_CTRL_S    *pstGradFgCtrl    Gradient calculation parameters
*                  HI_BOOL                bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_DST_IMAGE_S       *pstGradFg        Gradient foreground image
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_GradFg(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstDiffFg, IVE_SRC_IMAGE_S *pstCurGrad,
	IVE_SRC_IMAGE_S *pstBgGrad, IVE_DST_IMAGE_S *pstGradFg, IVE_GRAD_FG_CTRL_S *pstGradFgCtrl, HI_BOOL bInstant);


/*****************************************************************************
*   Prototype    : HI_MPI_IVE_MatchBgModel
*   Description  :  
*   Input        : IVE_HANDLE                  *pIveHandle            Returned handle ID of a task
*                  IVE_SRC_IMAGE_S             *pstCurImg             Current grayscale image
*                  IVE_DATA_S                  *pstBgModel            Background model data
*                  IVE_IMAGE_S                 *pstFgFlag             Foreground status image
*                  IVE_MATCH_BG_MODEL_CTRL_S   *pstMatchBgModelCtrl   Background matching parameters
*                  HI_BOOL                      bInstant              For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_DST_IMAGE_S             *pstMatchFg            Foreground image obtained by background matching, 
*                                                                     the background pixel value is 0, the foreground pixel 
*                                                                     value is the gray difference value                                         
*                  IVE_DST_IMAGE_S             *pstDiffFg             Foreground image obtained by interframe difference,
*                                                                     the background pixel value is 0, the foreground pixel
*                                                                     value is the gray difference value
*                  IVE_DST_MEM_INFO_S          *pstStatData           result status data
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_MatchBgModel(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstCurImg, IVE_DATA_S *pstBgModel,
	IVE_IMAGE_S *pstFgFlag, IVE_DST_IMAGE_S *pstMatchFg, IVE_DST_IMAGE_S *pstDiffFg, IVE_DST_MEM_INFO_S *pstStatData,
	IVE_MATCH_BG_MODEL_CTRL_S *pstMatchBgModelCtrl,	HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_UpdateBgModel
*   Description  :  
*   Input        : IVE_HANDLE                  *pIveHandle              Returned handle ID of a task
*                  IVE_DATA_S                  *pstBgModel              Background model data
*                  IVE_IMAGE_S                 *pstFgFlag               Foreground status image
*                  IVE_UPDATE_BG_MODEL_CTRL_S  *pstUpdateBgModelCtrl    Background update parameters
*                  HI_BOOL                      bInstant                For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_DST_IMAGE_S             *pstBgImg                Background grayscale image
*                  IVE_DST_IMAGE_S             *pstChgStaImg            Change state life image, for still detection
*                  IVE_DST_IMAGE_S             *pstChgStaFg             Change state grayscale image, for still detection
*                  IVE_DST_IMAGE_S             *pstChgStaLife           Change state foreground image, for still detection
*                  IVE_DST_MEM_INFO_S          *pstStatData             result status data
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_UpdateBgModel(IVE_HANDLE *pIveHandle,	IVE_DATA_S *pstBgModel, IVE_IMAGE_S *pstFgFlag, 
	IVE_DST_IMAGE_S *pstBgImg, IVE_DST_IMAGE_S *pstChgStaImg, IVE_DST_IMAGE_S *pstChgStaFg, IVE_DST_IMAGE_S *pstChgStaLife, 
	IVE_DST_MEM_INFO_S *pstStatData, IVE_UPDATE_BG_MODEL_CTRL_S *pstUpdateBgModelCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Radon
*   Description  :  
*   Input        : IVE_HANDLE			*pIveHandle       Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		*pstSrc			  Input gray image
*                  IVE_RADON_CTRL_S     *pstRadonCtrl	  Radon tranform parameters
*                  HI_BOOL				 bInstant         For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			*pIveHandle
*				   IVE_DST_IMAGE_S		*pstDst			  Angle project image
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Radon(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstDst, 
	IVE_RADON_CTRL_S *pstRadonCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_ANN_MLP_Predict
*   Description  :  
*   Input        : IVE_HANDLE			   *pIveHandle          Returned handle ID of a task
*				   IVE_SRC_MEM_INFO_S	   *pstSrc			    Input sample
*                  IVE_SRC_MEM_INFO_S      *pstActivFuncTable   Look-up talbe for active function
*                  IVE_ANN_MLP_MODEL_S     *pstAnnMlpModel	    ANN_MLP model
*                  IVE_DST_MEM_INFO_S      *pstDst              Output layer
*                  HI_BOOL				    bInstant            For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			   *pIveHandle
*				   IVE_DST_MEM_INFO_S	   *pstDst			    
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-11-28
*           Author       : Tan Bing
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_ANN_MLP_Predict(IVE_HANDLE *pIveHandle, IVE_SRC_MEM_INFO_S *pstSrc, 
    IVE_LOOK_UP_TABLE_S *pstActivFuncTab, IVE_ANN_MLP_MODEL_S *pstAnnMlpModel,  
    IVE_DST_MEM_INFO_S *pstDst, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_SVM_Predict
*   Description  :  
*   Input        : IVE_HANDLE			   *pIveHandle          Returned handle ID of a task
*				   IVE_SRC_MEM_INFO_S	   *pstSrc			    Input sample
*                  IVE_SRC_MEM_INFO_S      *pstKernelTable      Look-up talbe for active function
*                  IVE_SVM_MODEL_S         *pstSvmModel         SVM model
*                  IVE_DST_MEM_INFO_S      *pstDstVote          Output Votes' array of each class
*                  HI_BOOL				    bInstant            For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			   *pIveHandle
*				   IVE_DST_MEM_INFO_S	   *pstDstVote			    
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-11-28
*           Author       : Tan Bing
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_SVM_Predict(IVE_HANDLE *pIveHandle, IVE_SRC_MEM_INFO_S *pstSrc, 
    IVE_LOOK_UP_TABLE_S *pstKernelTab, IVE_SVM_MODEL_S *pstSvmModel,
    IVE_DST_MEM_INFO_S *pstDstVote, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_AdpThresh
*   Description  :  
*   Input        : IVE_HANDLE			      *pIveHandle         Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		      *pstSrc			  Gray image
*				   IVE_SRC_IMAGE_S		      *pstInteg		      Integer image
*				   IVE_ADP_THRESH_CTRL_S      *pstAdpThrCtrl      Adaptive threshold parameters
*                  HI_BOOL				       bInstant           For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			      *pIveHandle
*				   IVE_DST_IMAGE_S		      *pstDst			  Binary image
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_AdpThresh(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_SRC_IMAGE_S *pstInteg,
	IVE_DST_IMAGE_S *pstDst, IVE_ADP_THRESH_CTRL_S *pstAdpThrCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_GrainCount
*   Description  :  
*   Input        : IVE_HANDLE			     *pIveHandle			   Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		     *pstSrc				   Gray image
*				   IVE_GRAIN_COUNT_CTRL_S    *pstGrainCountCtrl        Grain parameters 
*                  HI_BOOL				      bInstant			       For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			     *pIveHandle
*				   IVE_DST_IMAGE_S		     *pstDst				   Grain image
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_GrainCount(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstDst,
	IVE_GRAIN_COUNT_CTRL_S *pstGrainCountCtrl,HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LineFilterHor
*   Description  :  
*   Input        : IVE_HANDLE                   *pIveHandle            Returned handle ID of a task
*				   IVE_IMAGE_S                  *pstSrc		           Input Binary image
*				   IVE_LINE_FILTER_HOR_CTRL_S   *pstLineFltHorCtrl     Horizontal Line Filter parameters
*                  HI_BOOL                       bInstant              For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LineFilterHor(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstSrc,
	IVE_LINE_FILTER_HOR_CTRL_S *pstLineFltHorCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_NoiseRemove
*   Description  :  
*   Input        : IVE_HANDLE                 *pIveHandle              Returned handle ID of a task
*				   IVE_IMAGE_S	              *pstSrc		           Binary image
*				   IVE_NOISE_REMOVE_CTRL_S    *pstNoiseRemoveCtrl      Remove image noise parameters
*                  HI_BOOL                     bInstant                For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE                 *pIveHandle
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_NoiseRemove(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstSrc,
	IVE_NOISE_REMOVE_CTRL_S *pstNoiseRemoveCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_CharEnhance
*   Description  :  
*   Input        : IVE_HANDLE		         *pIveHandle             Returned handle ID of a task
*				   IVE_SRC_IMAGE_S	         *pstSrc			     Input gray image
*				   IVE_CHAR_ENHANCE_CTRL_S   *pstCharEnhanceCtrl     Edge enhance parameters
*                  HI_BOOL                    bInstant               For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE		         *pIveHandle
*				   IVE_DST_IMAGE_S           *pstCrestDst	         Crest image
*                  IVE_DST_IMAGE_S           *pstEdgeDst             Edge image
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_EdgeEnhance(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstCrestDst, 
	IVE_DST_IMAGE_S *pstEdgeDst, IVE_EDGE_ENHANCE_CTRL_S *pstEdgeEnhanceCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_CharEnhance
*   Description  :  
*   Input        : IVE_HANDLE			       *pIveHandle              Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		       *pstEnegyHist	        Energy Hist image														
*				   IVE_SRC_MEM_INFO_S	       *pstPlateInfo	        Plate model information
*                  IVE_PLATE_CHAR_POS_CTRL_S   *pstPlateCharPosCtrl     Plate char position parameters
*                  HI_BOOL				        bInstant                For details, see HI_MPI_IVE_DMA.
*   Output       : IVE_HANDLE			       *pIveHandle
*				   IVE_DST_MEM_INFO_S          *pstDst
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*
*                  
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_PlateCharPos(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstEnegyHist, IVE_SRC_MEM_INFO_S *pstPlateInfo,
	IVE_DST_MEM_INFO_S *pstCharPos, IVE_PLATE_CHAR_POS_CTRL_S *pstPlateCharPosCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Query
*   Description  : This API is used to query the status of a called function by using the returned IveHandle of the function.
                   In block mode, the system waits until the function that is being queried is called.
                   In non-block mode, the current status is queried and no action is taken.
*   Input        : IVE_HANDLE     IveHandle     IveHandle of a called function. It is entered by users.
*                  HI_BOOL       *pbFinish      Returned status
*                  HI_BOOL        bBlock        Flag indicating the block mode or non-block mode
*   Output       : HI_BOOL  *pbFinish
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Calls        : 
*   Called By    : 
*
*   History:
* 
*       1.  Date         : 2011-05-16
*           Author       : Jiang Xiaohua (employee ID: 00169368)
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Query(IVE_HANDLE IveHandle, HI_BOOL *pbFinish, HI_BOOL bBlock);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif/*__MPI_IVE_H__*/
