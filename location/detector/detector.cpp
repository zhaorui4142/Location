#include "detector.h"

//��������define
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

//��������
#define hough_cmp_gt(l1,l2) (aux[l1] > aux[l2])
//������������
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32s, int, hough_cmp_gt, const int* )
CV_IMPLEMENT_QSORT_EX(Worker::icvHoughSortDescent32f, int, hough_cmp_gt, const float* )






//-------------------------------------------------------------------------------
//����������캯��
Detector::Detector(QSettings &settings, QObject *parent)
    : QObject(parent)
{
    readParamFromFile(settings);
    thread_pool = new QThreadPool(this);
    thread_pool->setMaxThreadCount(QThread::idealThreadCount()-3);
    thread_pool->setExpiryTimeout(3000);
}
//���������������
Detector::~Detector()
{
    thread_pool->deleteLater();
}

//�����������ͼ��ۺ���
void Detector::receiveFrame(FrameRawDataStruct frame)
{
    //�½�worker����
    Worker* worker = new Worker(param,frame);
    worker->setAutoDelete(true);

    //�����źźͲ�
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");
    connect(worker, &Worker::resultReady, this, &Detector::resultReady);

    //dowork,���û�з���ɹ�Ҫɾ������
    //if(!QThreadPool::globalInstance()->tryStart(worker))
    if(!thread_pool->tryStart(worker))
        worker->deleteLater();
}

//���ļ���ȡ����
void Detector::readParamFromFile(QSettings &settings)
{
    //��ȡ����
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
//��������ʵ��

//�๹�캯��
Worker::Worker(DetectParamStruct param, FrameRawDataStruct frame, QObject *parent)
        : QObject(parent),
          param(param),
          frame(frame)
{


}

//��������
Worker::~Worker(void)
{

}

//����run����
void Worker::run()
{
    //��ʱ����
    getIntervalMillisecond();

    //����ͼ��
    cv::Mat src_full_size(frame.imgHeigh, frame.imgWidth, CV_8UC1, frame.imgData.data());

    //��ͼ����н�����
    cv::Size decimation_size(960, (960*frame.imgHeigh/frame.imgWidth));
    cv::Mat src;
    cv::resize(src_full_size, src, decimation_size, 0.0, 0.0, cv::INTER_LINEAR);

    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("��������ʱ:")<<getIntervalMillisecond();
    //���ڴ洢�����
    DetectResultStruct result;
    result.isCircleDetected = false;

    //����ֱ��ͼ��ͬʱ�����ֵ����ֵ
    cv::MatND histogram = getHistogram(src);
    result.histogramImg = this->Histogram2QImage(histogram);
    int threshold = thresholdOtsu(src,histogram);
    param.canny_threshold = threshold*2;

    //��ʼ���
    findBestCircle(param,src,result);

    //�����ź�
    emit resultReady(result);
}
//���ҹ޿ں���
void Worker::findBestCircle(DetectParamStruct &param, cv::Mat &img, DetectResultStruct &result)
{
    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("��ʼ���:");
    getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //��һ��������ͼ���Ե���ݶȻ�Բ�ķ��ߣ��������accum��
    cv::Mat edges,accum;
    std::vector<cv::Point> nz(img.rows*img.cols);

    //ͼ��Ԥ����
    edges = cv::Mat(img.rows,img.cols,CV_8UC1);
    cv::Canny(img,edges,MAX(param.canny_threshold/2,1),param.canny_threshold,3);
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("canny��ʱ:")<<getIntervalMillisecond();
    //�ݶȼ���,�����dx,dy��
    cv::Mat dx(img.rows,img.cols,CV_16SC1);
    cv::Mat dy(img.rows,img.cols,CV_16SC1);
    cv::Sobel(img,dx,CV_16S,1,0,3);
    cv::Sobel(img,dy,CV_16S,0,1,3);
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("sobel��ʱ:")<<getIntervalMillisecond();
    //hough�ݶȿռ�任���任��Ľ������accum��
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
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("hough�ݶȿռ�任��ʱ:")<<getIntervalMillisecond();
    //��ʼ����Accumulate circle evidence for each edge pixel
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
            //����СԲ�뾶�����Բ�뾶��ÿ���ݶȷ������ת��
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
                    adata[y2*astep+x2]++;//�����ǻ���+1��
                }
                sx = -sx;
                sy = -sy;
            }
            //��¼������ķ����
            nz.push_back(cv::Point(x,y));
        }
    }
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("����Accum��ʱ:")<<getIntervalMillisecond();
    //ת���м����ͼ��
    result.detectImg_contour=MatCopy2QImage(edges);
    //result.detectImg_contour=MatScaled2QImage(edges,dp);//��edgeת����ͼ�����result��

    result.circleRadius = 0;
    result.brightness = 0;
    result.raw_strength = 0;
    result.satisfie_Circles = 0;
    result.detectImg_hough=MatCopy2QImage(accum);//accumת����ͼ�����result��

    //������
    if(nz.empty()) return;


    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("ת���м����ͼ���ʱ:")<<getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //�ڶ��������ҿ��ܵ�Բ�ĵ㣬�����õ���accum�����������
    std::vector<int> centers(nz.size());

    //����accum�����ҿ��ܵ�Բ��,�������centers����,ע�����Ͳ�ͬ
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

    //������Բ�ĵ�����갴����accum�е�����ֵ��������
    icvHoughSortDescent32s((int*)centers.data(),centers.size(),adata);

    //������
    if(centers.empty()) return;


    qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("�ڶ�����ʱ:")<<getIntervalMillisecond();

    //-----------------------------------------------------------------------------------------
    //���������ڿ�����Բ�ĵ�centers�н�һ��ɸѡ����������Բ
    std::vector<cv::Vec4f> results(255);

    //׼���������
    float min_dist2=(float)param.min_dist*(float)param.min_dist;
    float min_radius_f = (float)param.minRadius;
    float max_radius_f = (float)param.maxRadius;
    acols = accum.cols-2;
    results.clear();

    //����ÿһ��centers�еĵ�
    for(unsigned int i=0,j; i < centers.size(); i++)
    {
        //ȡ��һ��Բ�ģ���Բ�ĵ����껻�㵽ԭͼ�е�����cx0,cy0
        int ofs = centers[i];
        int y = ofs / (acols+2);
        int x = ofs - (y*(acols+2));
        float cx0 = (float)((x+0.5f)*dp);
        float cy0 = (float)((y+0.5f)*dp);

        //������ĵ��֮ǰ����������ĵ����ڣ����ų�
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

        //���㵱ǰ���ĵ�(cx0,cy0)��ͼ����ÿһ����ľ���,����dist_buf0��
        uint nz_count=nz.size();
        cv::Mat dist_circles(1,nz_count,CV_32FC1);

        std::vector<int>   sort_circles(nz_count);
        sort_circles.resize(nz_count);
        int* sorts_circles = sort_circles.data();
        int circles_count=0;

        float* ddata_circles= (float*)dist_circles.data;

        //����edgesͼ���е����з����nz
        cv::Point *point = nz.data();
        for(j = 0; j<nz_count; j++)
        {
            float _dx0,_dy0,_dist0;
            _dx0 = cx0 - point->x;
            _dy0 = cy0 - point->y;

            _dist0 = std::powf((_dx0*_dx0 + _dy0*_dy0),0.5f);

            if(min_radius_f<=_dist0 && _dist0<=max_radius_f)
            {//��Բ�İ뾶���м�¼
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

        //��Բ�İ뾶��������
        //icvHoughSortDescent32f(sorts_circles,circles_count,ddata_circles);

        //������Ѱ뾶
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

        //ȷ��Բ���Ƿ����㹻������
        if(max_count > acc_threshold)
        {
            current[0] = cx0;//���ĵ�x
            current[1] = cy0;//���ĵ�y
            current[2] = r_best;//�뾶����뾶��
            current[3] = max_count;//�ܶ�
            results.push_back(current);
        }
    }

    //������
    result.satisfie_Circles = results.size();
    if(results.empty()) return;
    //qDebug()<<results[0][0]<<results[0][1]<<results[0][2]<<results[0][3];
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("��������ʱ:")<<getIntervalMillisecond();
    //-----------------------------------------------------------------------------------------
    //���Ĳ����ڷ���������Բ��ɸѡ����ʵ�һ��
    cv::Vec4f bestcircle;
    bool foundedBestOne=false;
    int circle_x0,circle_y0,circle_r,circle_mean;


    //������һ���ҵ���results
    for(uint i=0; i<results.size(); i++)
    {
        //����ROI-��ǰԲ����Ӿ���,ע���ֹԽ��
        circle_x0 = cvRound(results[i][0]);
        circle_y0 = cvRound(results[i][1]);
        circle_r = cvRound(results[i][2]);
        //qDebug()<<"x"<<circle_x0<<"y"<<circle_y0<<"r"<<circle_r<<"cols"<<img.cols<<"rows"<<img.rows;
        if(((circle_x0-circle_r) <= 0) || ((circle_y0-circle_r) <= 0) || \
           ((circle_x0+circle_r) >= img.cols) || ((circle_y0+circle_r) >= img.rows))
            continue;
        cv::Rect roiRect(circle_x0-circle_r,circle_y0-circle_r,circle_r*2,circle_r*2);
        cv::Mat srcROI = img(roiRect);
        //��ROI����ģ������
        cv::Mat roi;
        cv::blur(srcROI,roi,cv::Size(3,3));
        //ѡ��ROI����ĵ�����Ⱥ�����
        double maxVal,minVal;
        cv::Point maxPoint,minPoint;
        cv::minMaxLoc(roi,&minVal,&maxVal,&minPoint,&maxPoint);
        //��ֵ�������������mask
        cv::Mat mask;
        cv::threshold(roi,mask,minVal+10,255,cv::THRESH_BINARY_INV);
        //��mask�µ�ƽ������
        int brightness = cvRound(cv::mean(roi,mask)[0]);
        //����>max����ֱ����������ֹ���ҵ�����Ĺ޿�
        if( brightness > param.maxCentBrightness )
        {
            continue;
        }
        else
        {
            if(foundedBestOne)
            {
                //�����һ�����ϵ�Բ������������,�ҳ�count��ߵ�һ��
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

    //�������result�ṹ�У�����Ҫת��һ��
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
qDebug()<<QThread::currentThreadId()<<QString::fromLocal8Bit("���Ĳ���ʱ:")<<getIntervalMillisecond()<<'\n';
    return;
}

//MatתQImage(����)
QImage Worker::MatCopy2QImage(const cv::Mat &mat)
{
    // ����CV_8UC1���͵�ͼ��
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
    // ����CV_32SC1���͵�ͼ��
    else if(mat.type() == CV_32SC1)
    {
        //��32SC1ͼ��ת���ɿ�����ʾ��ͼ��
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

//MatתQImage(����)(QImage::Format_Indexed8)
QImage Worker::MatScaled2QImage(const cv::Mat &mat,double dp)
{
    // ֻ����CV_8UC1���͵�ͼ��
    if(mat.type() == CV_8UC1)
    {
        cv::Mat dst;
        //��ͼ���������
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

//����ֱ��ͼ
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

//ֱ��ͼתQImage(QImage::Format_ARGB32_Premultiplied)
QImage Worker::Histogram2QImage(const cv::Mat &hist)
{
    if(hist.empty())
    {
        return QImage();
    }
    else
    {
        //����ֱ��ͼͼ�񣬳ߴ�̶�Ϊ256*128
        QImage image(256, 128, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgba(i,i,i,i));
        }

        double max_val;  //ֱ��ͼ�����ֵ
        cv::minMaxLoc(hist, 0, &max_val, 0, 0); //����ֱ��ͼ���ֵ

        double alpha = 127.f/max_val;
        cv::Mat matCalc;
        hist.convertTo(matCalc,CV_8UC1,alpha,0);

        // ����ͼ��
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

//Otsu�������ֵ����ֵ
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
        avgValue += i * histogram.at<float>(i);  //����ͼ���ƽ���Ҷ�
    }
    int threshold;
    float maxVariance=0;
    float w = 0, u = 0;
    for(int i = 0; i < 256; i++)
    {
        w += histogram.at<float>(i);  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷȵ�����(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���
        u += i * histogram.at<float>(i);  // �Ҷ�i ֮ǰ������(0~i)��ƽ���Ҷ�ֵ�� ǰ�����ص�ƽ���Ҷ�ֵ

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

//˽�к����������ʱ
qreal Worker::getIntervalMillisecond()
{
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t2);
    qreal retval;

    retval = (t2.QuadPart - t1.QuadPart)*1000.0/tc.QuadPart;
    t1 = t2;
    return retval;
}







