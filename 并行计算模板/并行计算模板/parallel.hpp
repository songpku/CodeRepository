/**@ Test parallel_for and parallel_for_
/**@ Author: chouclee
/**@ 03/17/2013*/
#include <opencv2/core/internal.hpp>
namespace cv
{
	class parallelTestBody : public ParallelLoopBody//参考官方给出的answer，构造一个并行的循环体类
	{
	public:
			parallelTestBody(Mat& _src)//class constructor
			{
				src = &_src;
			}
			void operator()(const Range& range) const//重载操作符（）
			{
				int yStart = range.start, yEnd = range.end;
				Mat& srcMat = *src;
				int nchannels = srcMat.channels(),cols = srcMat.cols;
				//uchar* data = srcMat.datastart;
				//int stepSrc = (int)(srcMat.step/srcMat.elemSize1());//获取每一行的元素总个数（相当于cols*channels，等同于step1)
				for (int y = yStart; y < yEnd; y++)
				{
					uchar* data = srcMat.data + cols*y*nchannels;
					for (int x = 0; x < cols; x++,data += nchannels)
						*data = 255 - *data;
						/**(data+1) = 255 - *(data+1);
						*(data+2) = 255 - *(data+2);*/
				}	
			}

	private:
			Mat* src;
	};


	
	void parallelTestWithParallel_for_(InputArray _src)//'parallel_for_' loop
	{
		CV_Assert(_src.kind() == _InputArray::MAT);
		Mat src = _src.getMat();
		int totalCols = src.rows;
		typedef parallelTestBody parallelTestBody;
		parallel_for_(Range(0, totalCols), parallelTestBody(src));
	};

	void show(InputArray _src)
	{
		
		Mat& srcMat = _src.getMat();
		int yStart = 0, yEnd = srcMat.rows;
		int nchannels = srcMat.channels(),cols = srcMat.cols;
				//uchar* data = srcMat.datastart;
				//int stepSrc = (int)(srcMat.step/srcMat.elemSize1());//获取每一行的元素总个数（相当于cols*channels，等同于step1)
		for (int y = yStart; y < yEnd; y++)
		{
		uchar* data = srcMat.data + cols*y*nchannels;
		for (int x = 0; x < cols; x++,data += nchannels)
				*data = 255 - *data;
						/**(data+1) = 255 - *(data+1);
						*(data+2) = 255 - *(data+2);*/
		}	
	}
}//namespace cv
