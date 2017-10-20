#include "detector.h"

//排序函数的define
#define CV_IMPLEMENT_QSORT_EX( func_name, T, LT, user_data_type )                   \
void func_name( T *array, size_t total, user_data_type aux )                        \
{                                                                                   \
    int isort_thresh = 7;                                                           \
    T t;                                                                            \
    int sp = 0;                                                                     \
                                                                                    \
    struct                                                                          \
    {                                                                               \
        T *lb;                                                                      \
        T *ub;                                                                      \
    }                                                                               \
    stack[48];                                                                      \
                                                                                    \
    aux = aux;                                                                      \
                                                                                    \
    if( total <= 1 )                                                                \
        return;                                                                     \
                                                                                    \
    stack[0].lb = array;                                                            \
    stack[0].ub = array + (total - 1);                                              \
                                                                                    \
    while( sp >= 0 )                                                                \
    {                                                                               \
        T* left = stack[sp].lb;                                                     \
        T* right = stack[sp--].ub;                                                  \
                                                                                    \
        for(;;)                                                                     \
        {                                                                           \
            int i, n = (int)(right - left) + 1, m;                                  \
            T* ptr;                                                                 \
            T* ptr2;                                                                \
                                                                                    \
            if( n <= isort_thresh )                                                 \
            {                                                                       \
            insert_sort:                                                            \
                for( ptr = left + 1; ptr <= right; ptr++ )                          \
                {                                                                   \
                    for( ptr2 = ptr; ptr2 > left && LT(ptr2[0],ptr2[-1]); ptr2--)   \
                        CV_SWAP( ptr2[0], ptr2[-1], t );                            \
                }                                                                   \
                break;                                                              \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                T* left0;                                                           \
                T* left1;                                                           \
                T* right0;                                                          \
                T* right1;                                                          \
                T* pivot;                                                           \
                T* a;                                                               \
                T* b;                                                               \
                T* c;                                                               \
                int swap_cnt = 0;                                                   \
                                                                                    \
                left0 = left;                                                       \
                right0 = right;                                                     \
                pivot = left + (n/2);                                               \
                                                                                    \
                if( n > 40 )                                                        \
                {                                                                   \
                    int d = n / 8;                                                  \
                    a = left, b = left + d, c = left + 2*d;                         \
                    left = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))     \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                                                                                    \
                    a = pivot - d, b = pivot, c = pivot + d;                        \
                    pivot = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))    \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                                                                                    \
                    a = right - 2*d, b = right - d, c = right;                      \
                    right = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))    \
                                      : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));    \
                }                                                                   \
                                                                                    \
                a = left, b = pivot, c = right;                                     \
                pivot = LT(*a, *b) ? (LT(*b, *c) ? b : (LT(*a, *c) ? c : a))        \
                                   : (LT(*c, *b) ? b : (LT(*a, *c) ? a : c));       \
                if( pivot != left0 )                                                \
                {                                                                   \
                    CV_SWAP( *pivot, *left0, t );                                   \
                    pivot = left0;                                                  \
                }                                                                   \
                left = left1 = left0 + 1;                                           \
                right = right1 = right0;                                            \
                                                                                    \
                for(;;)                                                             \
                {                                                                   \
                    while( left <= right && !LT(*pivot, *left) )                    \
                    {                                                               \
                        if( !LT(*left, *pivot) )                                    \
                        {                                                           \
                            if( left > left1 )                                      \
                                CV_SWAP( *left1, *left, t );                        \
                            swap_cnt = 1;                                           \
                            left1++;                                                \
                        }                                                           \
                        left++;                                                     \
                    }                                                               \
                                                                                    \
                    while( left <= right && !LT(*right, *pivot) )                   \
                    {                                                               \
                        if( !LT(*pivot, *right) )                                   \
                        {                                                           \
                            if( right < right1 )                                    \
                                CV_SWAP( *right1, *right, t );                      \
                            swap_cnt = 1;                                           \
                            right1--;                                               \
                        }                                                           \
                        right--;                                                    \
                    }                                                               \
                                                                                    \
                    if( left > right )                                              \
                        break;                                                      \
                    CV_SWAP( *left, *right, t );                                    \
                    swap_cnt = 1;                                                   \
                    left++;                                                         \
                    right--;                                                        \
                }                                                                   \
                                                                                    \
                if( swap_cnt == 0 )                                                 \
                {                                                                   \
                    left = left0, right = right0;                                   \
                    goto insert_sort;                                               \
                }                                                                   \
                                                                                    \
                n = MIN( (int)(left1 - left0), (int)(left - left1) );               \
                for( i = 0; i < n; i++ )                                            \
                    CV_SWAP( left0[i], left[i-n], t );                              \
                                                                                    \
                n = MIN( (int)(right0 - right1), (int)(right1 - right) );           \
                for( i = 0; i < n; i++ )                                            \
                    CV_SWAP( left[i], right0[i-n+1], t );                           \
                n = (int)(left - left1);                                            \
                m = (int)(right1 - right);                                          \
                if( n > 1 )                                                         \
                {                                                                   \
                    if( m > 1 )                                                     \
                    {                                                               \
                        if( n > m )                                                 \
                        {                                                           \
                            stack[++sp].lb = left0;                                 \
                            stack[sp].ub = left0 + n - 1;                           \
                            left = right0 - m + 1, right = right0;                  \
                        }                                                           \
                        else                                                        \
                        {                                                           \
                            stack[++sp].lb = right0 - m + 1;                        \
                            stack[sp].ub = right0;                                  \
                            left = left0, right = left0 + n - 1;                    \
                        }                                                           \
                    }                                                               \
                    else                                                            \
                        left = left0, right = left0 + n - 1;                        \
                }                                                                   \
                else if( m > 1 )                                                    \
                    left = right0 - m + 1, right = right0;                          \
                else                                                                \
                    break;                                                          \
            }                                                                       \
        }                                                                           \
    }                                                                               \
}

//降序排序
#define hough_cmp_gt(l1,l2) (aux[l1] > aux[l2])
//排序函数的名称
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32s, int, hough_cmp_gt, const int* )
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32f, int, hough_cmp_gt, const float* )






//-------------------------------------------------------------------------------
//检测器，构造函数
Detector::Detector(QSettings &settings, QObject *parent)
    : QObject(parent)
{
    readParamFromFile(settings);
    thread_pool = new QThreadPool(this);
    thread_pool->setMaxThreadCount(QThread::idealThreadCount()-3);
    thread_pool->setExpiryTimeout(3000);
}
//检测器，析构函数
Detector::~Detector()
{
    thread_pool->deleteLater();
}

//检测器，接收图像槽函数
void Detector::receiveFrame(FrameRawDataStruct frame)
{
    //新建worker对象
    Worker* worker = new Worker(param,frame);
    worker->setAutoDelete(true);

    //连接信号和槽
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");
    connect(worker, &Worker::resultReady, this, &Detector::resultReady);

    //dowork,如果没有分配成功要删除对象
    //if(!QThreadPool::globalInstance()->tryStart(worker))
    if(!thread_pool->tryStart(worker))
        worker->deleteLater();
}

//从文件读取参数
void Detector::readParamFromFile(QSettings &settings)
{
    //读取参数
     param.dp              = settings.value("DETECTOR/DP").toDouble();
     param.min_dist        = settings.value("DETECTOR/MIN_DIST").toDouble();
     param.canny_threshold = settings.value("DETECTOR/CANNY_THRESHOLD").toInt();
     param.acc_threshold   = settings.value("DETECTOR/ACC_THRESHOLD").toInt();
     param.minRadius       = settings.value("DETECTOR/MIN_RADIUS").toInt();
     param.maxRadius       = settings.value("DETECTOR/MAX_RADIUS").toInt();
     param.ROI_CenterLine  = settings.value("ROI/CENTER_LINE").toInt();
     param.ROI_CenterRange = settings.value("ROI/HEIGHT").toInt();
     param.ROI_Heigh       = settings.value("ROI/CENTER_RANGE").toInt();
     param.maxCentBrightness = settings.value("ROI/MAX_CENT_BRIGHTNESS").toInt();
}


//--------------------------------------------------------------------------------------------
//检测器类的实现

//类构造函数
Worker::Worker(DetectParamStruct param, FrameRawDataStruct frame, QObject *parent)
        : QObject(parent),
          param(param),
          frame(frame)
{


}

//析构函数
Worker::~Worker(void)
{

}

//重载run函数
void Worker::run()
{
    //计时函数
    getIntervalMillisecond();

    //构建图像
    cv::Mat src_full_size(frame.imgHeigh, frame.imgWidth, CV_8UC1, frame.imgData.data());

    //对图像进行降采样
    cv::Size decimation_size(960, (960*frame.imgHeigh/frame.imgWidth));
    cv::Mat src;
    cv::resize(src_full_size, src, decimation_size, 0.0, 0.0, cv::INTER_LINEAR);

    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("降采样耗时:")<<getIntervalMillisecond();
    //用于存储检测结果
    DetectResultStruct result;
    result.isCircleDetected = false;

    //计算直方图，同时求出二值化阈值
    cv::MatND histogram = getHistogram(src);
    result.histogramImg = this->Histogram2QImage(histogram);
    int threshold = thresholdOtsu(src,histogram);
    param.canny_threshold = threshold*2;

    //开始检测
    findBestCircle(param,src,result);

    //发射信号
    emit resultReady(result);
}
//查找罐口函数
void Worker::findBestCircle(DetectParamStruct &param, cv::Mat &img, DetectResultStruct &result)
{
    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("开始检测:");
    getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //第一步，根据图像边缘的梯度画圆的法线，结果存在accum里
    cv::Mat edges,accum;
    std::vector<cv::Point> nz(img.rows*img.cols);

    //图像预处理
    edges = cv::Mat(img.rows,img.cols,CV_8UC1);
    cv::Canny(img,edges,MAX(param.canny_threshold/2,1),param.canny_threshold,3);
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("canny耗时:")<<getIntervalMillisecond();
    //梯度计算,结果在dx,dy中
    cv::Mat dx(img.rows,img.cols,CV_16SC1);
    cv::Mat dy(img.rows,img.cols,CV_16SC1);
    cv::Sobel(img,dx,CV_16S,1,0,3);
    cv::Sobel(img,dy,CV_16S,0,1,3);
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("sobel耗时:")<<getIntervalMillisecond();
    //hough梯度空间变换，变换后的结果存在accum中
    double dp = param.dp;
    if(dp < 1.f)
        dp=1.f;
    float idp=1.f/dp;
    accum=cv::Mat(cvCeil((float)img.rows*idp)+2,cvCeil((float)img.cols*idp)+2,CV_32SC1,cv::Scalar(0));
    int rows = img.rows;
    int cols = img.cols;
    int* adata=(int*)(accum.data);
    int arows = accum.rows-2;
    int acols = accum.cols-2;
    int astep = accum.step/sizeof(adata[0]);
    const int SHIFT = 10, ONE = 1<< SHIFT;
    int min_radius=param.minRadius;
    int max_radius=param.maxRadius;
    nz.clear();
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("hough梯度空间变换耗时:")<<getIntervalMillisecond();
    //开始计算Accumulate circle evidence for each edge pixel
    for(int y=0; y<rows; y++)
    {
        const uchar* edges_row = edges.ptr<uchar>(y);
        const short* dx_row = dx.ptr<short>(y);
        const short* dy_row = dy.ptr<short>(y);
        for(int x=0; x<cols; x++)
        {
            float vx = dx_row[x];
            float vy = dy_row[x];

            if(!edges_row[x] || (vx==0 && vy==0))
                continue;

            float mag = sqrt(vx*vx+vy*vy);
            if(mag < 1) continue;
            int sx = cvRound((vx*idp)*ONE/mag);
            int sy = cvRound((vy*idp)*ONE/mag);
            int x0 = cvRound((x*idp)*ONE);
            int y0 = cvRound((y*idp)*ONE);
            int x1,y1,x2,y2;
            //从最小圆半径到最大圆半径对每个梯度方向进行转换
            for(int k1=0; k1<2; k1++)
            {
                x1 = x0 + min_radius * sx;
                y1 = y0 + min_radius * sy;
                for(int r=min_radius; r<=max_radius; x1 += sx, y1 += sy, r++)
                {
                    x2 = x1 >> SHIFT;
                    y2 = y1 >> SHIFT;
                    if((unsigned)x2 >= (unsigned)acols || (unsigned)y2 >= (unsigned)arows)
                        break;
                    adata[y2*astep+x2]++;//这里是画点+1；
                }
                sx = -sx;
                sy = -sy;
            }
            //记录计算过的非零点
            nz.push_back(cv::Point(x,y));
        }
    }
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("计算Accum耗时:")<<getIntervalMillisecond();
    //转换中间过程图像
    result.detectImg_contour=MatCopy2QImage(edges);
    //result.detectImg_contour=MatScaled2QImage(edges,dp);//将edge转换成图像存入result中

    result.circleRadius = 0;
    result.brightness = 0;
    result.raw_strength = 0;
    result.satisfie_Circles = 0;
    result.detectImg_hough=MatCopy2QImage(accum);//accum转换成图像存入result中

    //出错返回
    if(nz.empty()) return;


    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("转换中间过程图像耗时:")<<getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //第二步，查找可能的圆心点，并按该点在accum里的亮度排序
    std::vector<int> centers(nz.size());

    //遍历accum，查找可能的圆心,结果存在centers里面,注意类型不同
    int acc_threshold = param.acc_threshold;
    adata = (int*)accum.data;
    centers.clear();
    arows = accum.rows-2;
    acols = accum.cols-2;
    for(int y=1; y<arows-1; y++)
    {
        for(int x=1; x<acols-1; x++)
        {
            int base = y*(acols+2)+x;

            if((adata[base] > acc_threshold) && (adata[base] > adata[base-1]) && (adata[base] > adata[base+1]) && (adata[base] > adata[base-acols-2]) && (adata[base] > adata[base+acols+2]))
            {
                    centers.push_back(base);
            }
        }
    }

    //对所有圆心点的坐标按照在accum中的亮度值降序排序
    icvHoughSortDescent32s((int*)centers.data(),centers.size(),adata);

    //出错返回
    if(centers.empty()) return;


    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("第二步耗时:")<<getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //第三步，在可能是圆心点centers中进一步筛选符合条件的圆
    std::vector<cv::Vec4f> results(255);

    //准备运算变量
    float min_dist2=(float)param.min_dist*(float)param.min_dist;
    float min_radius_f = (float)param.minRadius;
    float max_radius_f = (float)param.maxRadius;
    acols = accum.cols-2;
    results.clear();

    //遍历每一个centers中的点
    for(unsigned int i=0,j; i < centers.size(); i++)
    {
        //取第一个圆心，将圆心的坐标换算到原图中的坐标cx0,cy0
        int ofs = centers[i];
        int y = ofs / (acols+2);
        int x = ofs - (y*(acols+2));
        float cx0 = (float)((x+0.5f)*dp);
        float cy0 = (float)((y+0.5f)*dp);

        //如果中心点和之前计算过的中心点相邻，则排除
        cv::Vec4f current;
        float dx,dy;
        for(j = 0; j < results.size(); j++)
        {
            current = results[j];
            dx = current[0]-cx0;
            dy = current[1]-cy0;
            if((dx*dx+dy*dy) < min_dist2)
                break;
        }
        if(j < results.size())
            continue;

        //计算当前中心点(cx0,cy0)到图像中每一个点的距离,存在dist_buf0中
        uint nz_count=nz.size();
        cv::Mat dist_circles(1,nz_count,CV_32FC1);

        std::vector<int>   sort_circles(nz_count);
        sort_circles.resize(nz_count);
        int* sorts_circles = sort_circles.data();
        int circles_count=0;

        float* ddata_circles= (float*)dist_circles.data;

        //遍历edges图像中的所有非零点nz
        cv::Point *point = nz.data();
        for(j = 0; j<nz_count; j++)
        {
            float _dx0,_dy0,_dist0;
            _dx0 = cx0 - point->x;
            _dy0 = cy0 - point->y;

            _dist0 = std::powf((_dx0*_dx0 + _dy0*_dy0),0.5f);

            if(min_radius_f<=_dist0 && _dist0<=max_radius_f)
            {//对圆的半径进行记录
                ddata_circles[circles_count] = _dist0;
                sorts_circles[circles_count] = circles_count;
                circles_count++;
            }
            point++;
        }

        sort_circles.resize(circles_count);

        dist_circles.cols = circles_count;

        if(circles_count==0)
            continue;

        //对圆的半径进行排序
        //icvHoughSortDescent32f(sorts_circles,circles_count,ddata_circles);

        //估算最佳半径
        float dr=(float)dp;
        float r_best = 0;
        int max_count = 0;
        int start_idx,count;
        float start_dist;
        float* ddata;
        int* sdata;

        start_idx = circles_count-1;
        count = circles_count;
        ddata = ddata_circles;
        sdata = sorts_circles;

        start_dist = ddata[sdata[start_idx]];
        for(int j=count - 2; j>=0; j--)
        {
            float d=ddata[sdata[j]];

            if(d>max_radius_f)
                break;

            if(d-start_dist > dr)
            {
                float r_cur = ddata[sdata[(j + start_idx)/2]];
                if((start_idx-j)*r_best >= max_count*r_cur || (r_best < FLT_EPSILON && start_idx-j >= max_count))
                {
                    r_best=r_cur;
                    max_count=start_idx-j;
                }
                start_dist=d;
                start_idx=j;
            }
        }

        //确认圆上是否有足够的像素
        if(max_count > acc_threshold)
        {
            current[0] = cx0;//中心点x
            current[1] = cy0;//中心点y
            current[2] = r_best;//半径（虚半径）
            current[3] = max_count;//密度
            results.push_back(current);
        }
    }

    //出错返回
    result.satisfie_Circles = results.size();
    if(results.empty()) return;
    //qDebug()<<results[0][0]<<results[0][1]<<results[0][2]<<results[0][3];
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("第三步耗时:")<<getIntervalMillisecond();
    //-----------------------------------------------------------------------------------------
    //第四步，在符合条件的圆中筛选最合适的一个
    cv::Vec4f bestcircle;
    bool foundedBestOne=false;
    int circle_x0,circle_y0,circle_r,circle_mean;


    //遍历上一步找到的results
    for(uint i=0; i<results.size(); i++)
    {
        //划出ROI-当前圆的外接矩形,注意防止越界
        circle_x0 = cvRound(results[i][0]);
        circle_y0 = cvRound(results[i][1]);
        circle_r = cvRound(results[i][2]);
        //qDebug()<<"x"<<circle_x0<<"y"<<circle_y0<<"r"<<circle_r<<"cols"<<img.cols<<"rows"<<img.rows;
        if(((circle_x0-circle_r) <= 0) || ((circle_y0-circle_r) <= 0) || \
           ((circle_x0+circle_r) >= img.cols) || ((circle_y0+circle_r) >= img.rows))
            continue;
        cv::Rect roiRect(circle_x0-circle_r,circle_y0-circle_r,circle_r*2,circle_r*2);
        cv::Mat srcROI = img(roiRect);
        //对ROI进行模糊处理
        cv::Mat roi;
        cv::blur(srcROI,roi,cv::Size(3,3));
        //选出ROI中最暗的点的亮度和坐标
        double maxVal,minVal;
        cv::Point maxPoint,minPoint;
        cv::minMaxLoc(roi,&minVal,&maxVal,&minPoint,&maxPoint);
        //二值化，求出暗部的mask
        cv::Mat mask;
        cv::threshold(roi,mask,minVal+10,255,cv::THRESH_BINARY_INV);
        //求mask下的平均亮度
        int brightness = cvRound(cv::mean(roi,mask)[0]);
        //亮度>max亮度直接舍弃，防止查找到错误的罐口
        if( brightness > param.maxCentBrightness )
        {
            continue;
        }
        else
        {
            if(foundedBestOne)
            {
                //如果有一个以上的圆满足亮度条件,找出count最高的一个
                if(bestcircle[3] < results[i][3])
                {
                    bestcircle=results[i];
                    circle_mean=brightness;
                }
            }
            else
            {
                foundedBestOne=true;
                bestcircle=results[i];
                circle_mean=brightness;

            }
        }
    }

    //结果存入result结构中，坐标要转换一下
    if(foundedBestOne)
    {
        result.isCircleDetected = true;

        int offset = param.ROI_CenterLine*2-(param.ROI_Heigh);
        result.circleCenter.setX(bestcircle[0] / param.dp);
        result.circleCenter.setY((bestcircle[1]+offset) / param.dp);
        result.circleRadius = bestcircle[2] / param.dp;
        result.accum_count = cvRound(bestcircle[3]);
        result.raw_strength = bestcircle[3]/(bestcircle[2] * 6.28f);
        result.brightness = circle_mean;
        //qDebug()<<"result:"<<result.raw_x<<result.raw_y<<result.raw_r<<result.raw_strength<<result.raw_brightness;
    }
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("第四步耗时:")<<getIntervalMillisecond()<<'\n';
    return;
}

//Mat转QImage(拷贝)
QImage Worker::MatCopy2QImage(const cv::Mat &mat)
{
    // 处理CV_8UC1类型的图像
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::QImage::Format_Grayscale8);
        //QImage image(mat.cols, mat.rows, QImage::QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        //image.setColorCount(256);
        //for(int i = 0; i < 256; i++)
        //{
            //image.setColor(i, qRgb(i, i, i));
        //}
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 处理CV_32SC1类型的图像
    else if(mat.type() == CV_32SC1)
    {
        //将32SC1图像转换成可以显示的图像
        double min,max;
        cv::minMaxLoc(mat,&min,&max);
        cv::Mat dstImg;
        mat.convertTo(dstImg,CV_8UC1,-255/max,255);

        QImage image(dstImg.cols, dstImg.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = dstImg.data;
        for(int row = 0; row < dstImg.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, dstImg.cols);
            pSrc += dstImg.step;
        }
        return image;
    }
    else
    {
        return QImage();
    }
}

//Mat转QImage(缩放)(QImage::Format_Indexed8)
QImage Worker::MatScaled2QImage(const cv::Mat &mat,double dp)
{
    // 只处理CV_8UC1类型的图像
    if(mat.type() == CV_8UC1)
    {
        cv::Mat dst;
        //对图像进行缩放
        cv::resize(mat,dst,cv::Size(0,0),1/dp,1/dp,cv::INTER_LINEAR);
        QImage image(dst.cols, dst.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = dst.data;
        for(int row = 0; row < dst.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, dst.cols);
            pSrc += dst.step;
        }
        return image;
    }
    else
    {
        return QImage();
    }
}

//计算直方图
cv::MatND Worker::getHistogram(const cv::Mat &image)
{
    cv::MatND hist;

    int histSize[1]={256};
    float hranges[2]={0.0,255.0};
    const float* ranges[1];
    int channels[1]={0};
    ranges[0]=hranges;
    // Compute histogram
    cv::calcHist(&image,
                1,			// histogram of 1 image only
                channels,	// the channel used
                cv::Mat(),	// no mask is used
                hist,		// the resulting histogram
                1,			// it is a 1D histogram
                histSize,	// number of bins
                ranges		// pixel value range
                );

    return hist;
}

//直方图转QImage(QImage::Format_ARGB32_Premultiplied)
QImage Worker::Histogram2QImage(const cv::Mat &hist)
{
    if(hist.empty())
    {
        return QImage();
    }
    else
    {
        //创建直方图图像，尺寸固定为256*128
        QImage image(256, 128, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgba(i,i,i,i));
        }

        double max_val;  //直方图的最大值
        cv::minMaxLoc(hist, 0, &max_val, 0, 0); //计算直方图最大值

        double alpha = 127.f/max_val;
        cv::Mat matCalc;
        hist.convertTo(matCalc,CV_8UC1,alpha,0);

        // 绘制图像
        uchar *pSrc,*pDest;
        for(int row = 0; row < 128; row++)//cols=1 rows=256
        {
            pSrc = matCalc.data;
            pDest = image.scanLine(row);
            for(int col = 0; col < 256; col ++)
            {
                if(128-row < pSrc[col])  {pDest[col] = 255;}
                else             {pDest[col] = 0;}
            }
        }

        return image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }
}

//Otsu法计算二值化阈值
int Worker::thresholdOtsu(cv::Mat &img,cv::MatND &histogram)
{
    int height=img.rows;
    int width=img.cols;

    //normalize histogram
    long size = height * width;
    for(int i = 0; i < 256; i++)
    {
        histogram.at<float>(i) = histogram.at<float>(i) / size;
    }

    //average pixel value
    float avgValue=0;
    for(int i=0; i < 256; i++)
    {
        avgValue += i * histogram.at<float>(i);  //整幅图像的平均灰度
    }
    int threshold;
    float maxVariance=0;
    float w = 0, u = 0;
    for(int i = 0; i < 256; i++)
    {
        w += histogram.at<float>(i);  //假设当前灰度i为阈值, 0~i 灰度的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例
        u += i * histogram.at<float>(i);  // 灰度i 之前的像素(0~i)的平均灰度值： 前景像素的平均灰度值

        float t = avgValue * w - u;
        float variance = t * t / (w * (1 - w) );
        if(variance > maxVariance)
        {
            maxVariance = variance;
            threshold = i;
        }
    }
    if(threshold>255)
        threshold=255;
    return threshold;
}

//私有函数，计算耗时
qreal Worker::getIntervalMillisecond()
{
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t2);
    qreal retval;

    retval = (t2.QuadPart - t1.QuadPart)*1000.0/tc.QuadPart;
    t1 = t2;
    return retval;
}







