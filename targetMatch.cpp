#include "stdafx.h"
#include "fstream"
#include "imgPro.h"
#include <time.h>
#ifdef __AFXWIN_H__
#include "targetMatch.h"
#include <direct.h>
extern bool b_useDB;
#else
class Target {
private:
	static const int MAXSIZE = 1000;
    Target* p_model;
    CvSeq *contour;
    typedef float type;
    type p_u[MAXSIZE], p_v[MAXSIZE];
    int x, y, w, h, ww, hh;	//Ŀ����ͼ���������Ϸ��ĵ�����ꣻĿ��Ŀ�Ⱥ͸߶�;��Ч��Ⱥ͸߶�
#define targetIsBlack 1

    void getSum(type *vec, int &len);
    void Normalize(type *vec, int &len, int toLength);
    void saveRGB(IplImage* img,cchar* name="");
    bool isTargetPoint(const int& i,const int& j);
    void projectionUV();
    void Normalize(int toLength_h,int toLength_w);
    void matchWidthHeight();
    void matchProjection();
    void matchContours();
    void matchBias();
    void Bias(uchar pgray[MAXSIZE][MAXSIZE]);//��б��������
public:
    uchar R[MAXSIZE][MAXSIZE],G[MAXSIZE][MAXSIZE],B[MAXSIZE][MAXSIZE];
    IplImage* tar_img;
    char fileName[128];
    double sum, entropy, whError, comError[2], huError, surfError,
		weightError[4], entrError,bias[3],biasError, Error;//�����б������3������
    Target(int xx=-1,int yy=-1,int ww=-1,int hh=-1);
    Target(cchar* path1,cchar* path2,cchar *saveError=0,int same=-1,int ww=0,int hh=0);
#ifdef __AFXWIN_H__
	Target(CString path1,CString path2,cchar *saveError,int same,int ww,int hh);
#endif
    ~Target();
    void showUVWH(string ps="");
    void getTargetInfo(cchar* path,int ask = 1,int show = 1);
#ifdef __AFXWIN_H__
	void getTargetInfo(CString path,int ask=0,int show=0);
#endif
    void getUVFromFile(cchar* filein);
    double compare(Target &model,cchar *saveError=0,int same=-1,int re=0,double *ratio=0,int ww=0,int hh=0);
    void saveUVToFile(cchar* fileout,cchar* ps=0,int hh=0,int ww=0);
};
const int Ch_Num = 11;	//������������

#endif

Target::Target(int xx,int yy,int ww,int hh) {
    x = xx;
    y = yy;
    w = ww;
    h = hh;
    whError = comError[0] = comError[1] = huError = surfError = 0;
	memset(weightError,0,sizeof(weightError));
    tar_img = 0;
    p_model = 0;
	contour = 0;
	srand((unsigned)time(NULL));
}
Target::~Target() {
	releaseImg(&tar_img);
	if(contour) cvReleaseMemStorage(&contour -> storage);
}
// �ж��Ƿ�ΪĿ���
bool Target::isTargetPoint(const int& i,const int& j) {
    if(targetIsBlack) {
        if(tar_img->nChannels==1)
            return R[i][j] < 128;//128
        else
            return R[i][j] + G[i][j] + B[i][j] < 376;	//128*3
    } else {
        if(tar_img->nChannels==1)
            return R[i][j] > 128;
        else
            return R[i][j] + G[i][j] + B[i][j] > 376;
    }
}
//������б����//���������Ƕ�ֵ�����������飬�Լ�ͼ��ĳ���
void Target::Bias(uchar pgray[MAXSIZE][MAXSIZE]) { 
    bias[0]=0;//��������б���¼
    bias[1]=0;//��������б��
    bias[2]=0;//��ֱ��б��
	//��ͼ��Ҷ����ݽ��б���
	for(int i=1; i<tar_img->height-1; i++)
		for(int j=1; j<tar_img->width-1; j++) {
			if(pgray[i][j]<150) {
				if(pgray[i+1][j-1]<150)	//����
					bias[0]++;
				if(pgray[i+1][j]<150)	//��
					bias[1]++;
				if(pgray[i+1][j+1]<150)	//����
					bias[2]++;
			}
		}
		//CString ss;
		//ss.Format("%g %g %g",bias[0],bias[1],bias[2]);
		//MessageBox(0,ss,0,0);
		double  sum=bias[0]+bias[1]+bias[2];
		if(sum>0){
			bias[1]=bias[1]/sum;//��һ����0-1֮��,�����鷽ʽ����
			bias[0]=bias[0]/sum;
			bias[2]=bias[2]/sum;
		}
}
// ��ֱ��ˮƽͶӰ
void Target::projectionUV() {
	memset(p_u,0,sizeof(p_u));
	memset(p_v,0,sizeof(p_v));
    int i,j;
    for(i=x; i<x+w; i++)	//��ֱͶӰ
        for(j=2; j<tar_img->height-2; j++)
            if(isTargetPoint(j,i))
                p_v[i-x]++;
    for(i=y; i<y+h; i++)	//ˮƽͶӰ
        for(j=2; j<tar_img->width-2; j++)
            if(isTargetPoint(i,j))
                p_u[i-y]++;
}
// �õ�ͶӰ����Ŀ������
void Target::getSum(type *vec, int &len) {
    sum = 0;
    for(int i=0; i<len; i++)
        sum += vec[i];
}
// ����ͼƬ������Ϣ������
void Target::saveRGB(IplImage* img,cchar* name) {
    if(img==0)
        return;
	if(img->height>MAXSIZE || img->width>MAXSIZE)
		throw string(name);
    uchar* data = (uchar*)img->imageData;
    if(img->nChannels==3) {
        for( int y = 0; y < img->height; y++ )
            for( int x = 0,yy = y * img->widthStep; x < img->width; x++ ) {
                R[y][x] = data[yy+3*x+2];
                G[y][x] = data[yy+3*x+1];
                B[y][x] = data[yy+3*x];
            }
    } else if(img->nChannels==1) {
        for( int y = 0; y < img->height; y++ )
            for( int x = 0,yy = y * img->widthStep; x < img->width; x++ )
                R[y][x] = data[yy+x];
    }
}
// ��һ��
void Target::Normalize(type *vec, int &len, int toLength) {
    int i;
    if(len!=toLength) {
        double scale = (double)len / toLength;
        if(scale<1) {	//��С����ת�Ƶ������䣬��Ӻ���ǰ
            for(i=toLength-1; i>=0; i--)
                vec[i] = vec[(int)(i*scale+.5)];
        } else if(scale>1) {	//�Ӵ�����ת�Ƶ�С���䣬���ǰ����
            for(i=0; i<toLength; i++)
                vec[i] = vec[(int)(i*scale+.5)];
        }
        len = toLength;
    }
    getSum(vec,len);
    if(fabs(sum-1) > 1e-3 && sum > 0)
        for(i=0; i<len; i++)
            vec[i] /= (float)sum;
}
// ��һ����������
void Target::Normalize(int toLength_h,int toLength_w) {
    Normalize(p_u,h,toLength_h);//ˮƽ�����һ��
    Normalize(p_v,w,toLength_w);//��ֱ�����һ��
}
// ƥ����Ч��߱���
void Target::matchWidthHeight() {
    if(hh<=0 || p_model->hh<=0) {
#ifndef __AFXWIN_H__
        if(hh<=0)
            cout<<">>>Ŀ�����δ��ʼ��<<<\n";
        if(hh>0 && p_model->hh<=0)
            cout<<">>>ģ�����δ��ʼ��<<<\n";
        fprintf(stderr,"���ʼ�����ٽ���ƥ��\n\n");
        exit(-1);
#else
        if(hh<=0)
            sprintf(info,"%s>>>Ŀ�����δ��ʼ��<<<\r\n",info);
        if(hh>0 && p_model->hh<=0)
            sprintf(info,"%s>>>ģ�����δ��ʼ��<<<\r\n",info);
        sprintf(info,"%s���ʼ�����ٽ���ƥ��\r\n",info);
#endif
    }
    double d1 = (double)ww / hh;
    double d2 = (double)p_model->ww / p_model->hh;
    if(d1>d2)
        whError = d2 / d1;
    else
        whError = d1 / d2;
#ifndef __AFXWIN_H__
    cout<<"������Ƹ���Ϊ:\t\t"<<setprecision(3)<<whError;
    if(whError<0.8)
        cout<<"  (warning : ��⵽���������)";
    cout<<endl;
#else
	sprintf(info,"%s������Ƹ���Ϊ:\t\t%g",info,whError);
    if(whError<0.8)
		sprintf(info,"%s  (warning : ��⵽���������)",info);
	sprintf(info,"%s\r\n",info);
#endif
}
// ƥ��ͶӰ
void Target::matchProjection() {
    if(h==p_model->h && w==p_model->w) {
        comError[0] = comError[1] = 0;
        int i;
        for(i=0; i<h; i++)
            comError[0] += fabs(p_u[i] - p_model->p_u[i]);
        for(i=0; i<w; i++)
            comError[1] += fabs(p_v[i] - p_model->p_v[i]);
		for(i=0;i<2;i++)
			if(comError[i]<1)
				comError[i] = (1-.5*comError[i]*comError[i]);
			else
				comError[i] = 1/(comError[i]+1);
#ifndef __AFXWIN_H__
        cout<<"ͶӰ���Ƹ���Ϊ:\t\t"<<comError[0]<<","<<comError[1]<<endl;
    } else
        cout<<"���Ƚ�����ͶӰ��һ����ͬһ���� !"<<endl;
#else
		sprintf(info,"%sͶӰ���Ƹ���Ϊ :\t%g,%g\r\n",info,comError[0],comError[1]);
	} else
		sprintf(info,"%s���Ƚ�����ͶӰ��һ����ͬһ���� !\r\n",info);
#endif
}
// ƥ������
void Target::matchContours() {
    if(contour && p_model->contour) {
		huError = cvMatchShapes(contour,p_model->contour,CV_CONTOURS_MATCH_I3);
        huError = 1 / (1.+huError);
#ifndef __AFXWIN_H__
        cout<<"����Hu�����Ƹ���Ϊ:\t"<<huError<<endl;
#else
		sprintf(info,"%s����Hu�����Ƹ���Ϊ :\t%g\r\n",info,huError);
#endif
    }
}
//ƥ��Ǽ���б����
double Target::matchBias() {
	Target &model = *p_model;
	double err = fabs(bias[0]-model.bias[0])+fabs(bias[1]-model.bias[1])+fabs(bias[2]-model.bias[2]);
#ifndef __AFXWIN_H__
	cout<<bias[0]<<"\t"<<bias[1]<<"\t"<<bias[2]<<endl
		<<model.bias[0]<<"\t"<<model.bias[1]<<"\t"<<model.bias[2]<<endl;
#endif
	//CString ss;
	//ss.Format("%s:%.3f  %.3f  %.3f\r\n%s:%.3f  %.3f  %.3f",fileName,bias[0],bias[1],bias[2],model.fileName,model.bias[0],model.bias[1],model.bias[2]);
	//MessageBox(0,ss,0,0);
	return (1-err/2)*(1-err/2)*(1-err/2);	//����΢��֮��Ĳ��
}
//���Ʋ��˳�ƫ�ף����Ƚϸߣ���������
void Target::controlWhtieNoise(int th)
{
	//��һ��˼�룺if(R[i][j]>th && G[i][j]>th && B[i][j]>th)
	for(int i=0; i<tar_img->height; i++)
		for(int j=0; j<tar_img->width; j++){
			if(tar_img->nChannels==3) {
				int sum = (int)R[i][j]+G[i][j]+B[i][j];
				if(sum>3*th)
					R[i][j] = G[i][j] = B[i][j] = (uchar)255;
				else
					R[i][j] = G[i][j] = B[i][j] = (uchar)((sum+1)/3);
			}else if(R[i][j]>th)
					R[i][j] = (uchar)255;
		}
}
//���浱ǰ��RGB���鵽IplImageָ����
void Target::saveIplImage()
{
	uchar* data = (uchar*)tar_img->imageData;
	if(tar_img->nChannels==3)
	{
		for( int y = 0; y < tar_img->height; y++ )
			for( int x = 0,yy = y * tar_img->widthStep; x < tar_img->width; x++ )
			{
				data[yy+3*x+2] = R[y][x];
				data[yy+3*x+1] = G[y][x];
				data[yy+3*x]   = B[y][x];
			}
	}
	else if(tar_img->nChannels==1)
	{
		for( int y = 0; y < tar_img->height; y++ )
			for( int x = 0,yy = y * tar_img->widthStep; x < tar_img->width; x++ )
				data[yy+x] = R[y][x];
	}
}

/**---- Target���ṩ�����ⲿ�ӿ� ----**/
// ��ʾĿ��������Ϣ
void Target::showUVWH(string ps) {
#ifndef __AFXWIN_H__
    cout<<ps<<" x:"<<x<<"\ty:"<<y<<"\th:"<<h<<"\tw:"<<w<<endl;
#else
	sprintf(info,"%s%s x:%d  y:%d  h:%d  w:%d\r\n",info,ps,x,y,h,w);
#endif
}
// ��ȡĿ��������Ϣ
void Target::getTargetInfo(cchar *path,int ask,int show) {
	x=y=w=h=-1;
	releaseImg(&tar_img);	//�ͷ�ǰһ���ù���ͼ��
	if(contour) {
		cvReleaseMemStorage(&contour -> storage);
		contour = 0;
	}
	whError = comError[0] = comError[1] = huError = surfError = 0;
	memset(weightError,0,sizeof(weightError));
	p_model = 0;
    strcpy(fileName,path);
	if (b_useDB){
		int t1 = clock();
#ifdef _MSC_VER
		if (!PathFileExists(db_t.source))
#endif
			CreateDirectory(db_t.source, 0);
		char newName[255] = "";
		char tmpbuf[255];
		char tmpbuf2[128];
		CString now = "", tmp, tmpName;
		time_t now_time = time(NULL);
		struct tm *newtime = localtime(&now_time);
		strftime(tmpbuf, 128, "%Y%m%d", newtime);
		strftime(tmpbuf2, 128, "%H%M%S", newtime);
		//sprintf_s(newName,"%s\\%s\\%s%s-%d",newName,db_t.source,tmpbuf,tmpbuf2,clock()%10000/*,strrchr(path,'\\')+1,1000+rand()%9000*/);
		sprintf_s(newName, "%s-%s-%d-%s", tmpbuf, tmpbuf2, clock() % 10000, strrchr(path, '\\') + 1);
		getcwd(tmpbuf, 128);		//�õ���ǰĿ¼
		sprintf_s(tmpbuf, "%s\\%s\\%s", tmpbuf, db_t.source, newName);
		char md5[33];
		int t2 = clock();
		Md5.GetFileMd5(md5, path);
		//LOGT("getMD5:" << clock() - t2 << "\t" << t2 - t1 << endl;);
		CString re = db_t.findData(md5, 2), fileNew = db_t.source + ("\\" + re);
		if (re[0] == 0 || !PathFileExists(fileNew)){	//��ǰ��δ�������ͼ
			db_t.addRow(md5, path, newName);	//���Ӹ��м�¼
			///����ΪԤ������
			tar_img = loadImg(path, ask, 0, 0, show);
			saveRGB(tar_img);
			controlWhtieNoise(Otsu(tar_img));	//����RGB�����Զ���ֵȥ��
			saveIplImage();						//��RGB���浽ͼ��ָ��
			saveImg(tmpbuf, tar_img);
		}else{
			tar_img = loadImg(fileNew, ask, 0, 0, show);
			saveRGB(tar_img);
		}
		//LOGT("�������ݿ⣺" << clock() - t1 << endl);
	}
	else{
		tar_img = loadImg(path, ask, 0, 0, show);
		saveRGB(tar_img);
		controlWhtieNoise(Otsu(tar_img));	//����RGB�����Զ���ֵȥ��
		saveIplImage();						//��RGB���浽ͼ��ָ��
	}
    int i,j;
	//�ҵ���߽�
    for(i=2; i<tar_img->width-2 && x<0; i++)
        for(j=2; j<tar_img->height-3; j++)
            if(isTargetPoint(j,i) && isTargetPoint(j+1,i)) {
                x = i;
                break;
            }
	//�ҵ��ұ߽�
    for(i=tar_img->width-3; i>0 && w<0; i--)
        for(j=2; j<tar_img->height-3; j++)
            if(isTargetPoint(j,i) && isTargetPoint(j+1,i)) {
                w = i - x + 1;
                break;
            }
	//�ҵ��ϱ߽�
    for(i=2; i<tar_img->height-2 && y<0; i++)
        for(j=2; j<tar_img->width-3; j++)
            if(isTargetPoint(i,j) && isTargetPoint(i,j+1)) {
                y = i;
                break;
            }
	//�ҵ��±߽�
    for(i=tar_img->height-3; i>0 && h<0; i--)
        for(j=2; j<tar_img->width-3; j++)
            if(isTargetPoint(i,j) && isTargetPoint(i,j+1)) {
                h = i - y + 1;
                break;
            }

	ww = w, hh = h;	//Ŀ�����Ч����͸߶�---ȥ���˿հ��кͿհ���
	//����߽��������ұ߽�
	for(int i=x,j; i<x+w; i++)
	{
		for(j=y; j<y+h; j++)
			if(isTargetPoint(j,i))
				break;
		if(j==y+h)
			ww--;
	}
	//���ϱ߽��������±߽�
	for(int j=y,i; j<y+h; j++)
	{
		for(i=x; i<x+w; i++)
			if(isTargetPoint(j,i))
				break;
		if(i==x+w)
			hh--;
	}

	//�������������ͶӰ
    projectionUV();
	//�õ���Ϣ��---�����ȼ�����Ϣ�غ��ٲ�����������ֹ������Ϣ��ʱ���뼴Ϊ����
	IplImage *dst = cvCreateImage(cvGetSize(tar_img),tar_img->depth,tar_img->nChannels);
    if(ask!=-2) {
        ///int ttt = clock();
        Hilditch(tar_img,dst,150,10);
        entropy = Entropy(dst,150,ww,hh);
        //LOGT("Hilditch:\t"<<clock()-ttt<<endl);
    }
    saveRGB(dst);
    Bias(R);
    saveRGB(tar_img);
    releaseImg(&dst);
	//��������
    contour = ::findContour(tar_img,0);
}
#ifdef __AFXWIN_H__
void Target::getTargetInfo(CString& path,int ask,int show){
	getTargetInfo((LPSTR)(LPCTSTR)path,ask,show);
}
#endif
// ���ļ��л�ȡĿ��ͶӰ��Ϣ
void Target::getUVFromFile(cchar* filein) {
    strcpy(fileName,filein);
    FILE * fp = fopen(filein,"r");
    if(fp) {
        x = y = 0;
        fscanf(fp,"%d%d",&h,&w);
        int i;
        for(i=0; i<h; i++)
            fscanf(fp,"%lf",&p_u[i]);
        for(i=0; i<w; i++)
            fscanf(fp,"%lf",&p_v[i]);
        fclose(fp);
    } else
#ifndef __AFXWIN_H__
        cout<<"���ļ���ȡUVͶӰʧ��: �ļ�"<<filein<<"��ʧ��"<<endl;
#else
		sprintf(info,"%s���ļ���ȡUVͶӰʧ��: �ļ�%s��ʧ��\r\n",info,filein);
#endif
    contour = 0;
}
// �Ƚ�����Ŀ������ƶ�
double Target::compare(Target &mod,cchar *saveError,int same,int re,double *ratio,int ww,int hh) {
	int ttt = clock();
	if(re!=-1){
		p_model = &mod;
#ifndef __AFXWIN_H__
		cout<<fileName<<"��"<<mod.fileName<<"ƥ��������:\n"<<endl;
#else
		sprintf(info,"%s\"%s\"��\"%s\"ƥ��������:\r\n",info,fileName,mod.fileName);
#endif
		matchWidthHeight();	//1ms
		if(ww==0 && 0==hh) {
			ww = w < mod.w ? w : mod.w;
			hh = h < mod.h ? h : mod.h;
		}
		Normalize(hh,ww);
		mod.Normalize(hh,ww);
		matchProjection();	//0ms
		matchContours();	//0ms
		surfError = find_obj(tar_img,mod.tar_img);	//60ms
		//LOGT("find_obj:\t"<<clock()-ttt<<endl);ttt = clock();
		Sleep(1);
		matchWeight(tar_img, mod.tar_img, weightError);	//10ms
		//LOGT("matchWeight:\t"<<clock()-ttt<<endl);
		entrError = 1-sqrt(fabs(entropy-mod.entropy));
		biasError = matchBias();//�õ���б������ֵ
		Error = ratio[0]*whError + ratio[1]/2*(comError[0] + comError[1]) + ratio[2]*huError
			+ ratio[3]*surfError + ratio[4]/4*(weightError[0]+weightError[1]+weightError[2]+weightError[3])
			+ ratio[5]*entrError + ratio[6]*biasError;
#ifndef __AFXWIN_H__
		cout<<"ϸ����Ǽ����Ƹ���Ϊ:\t"<<entrError<<endl;
		cout<<"�Ǽ���б�������Ƹ���Ϊ:\t"<<biasError<<endl;
		cout<<"\n�ۺ����Ƹ���Ϊ: \t\t"<<Error<<endl;
#else
		sprintf(info,"%sϸ����Ǽ����Ƹ���Ϊ:\t%g\r\n",info,entrError);
		sprintf(info,"%s�Ǽ���б�������Ƹ���Ϊ :%g\r\n",info,biasError);
		sprintf(info,"%s\r\n�ۺ����Ƹ���Ϊ :\t%g\r\n",info,Error);
#endif
		if(re>0)
			return Error;
	}
    if(saveError && saveError[0]) {
        FILE *fp1 = fopen(saveError,"a+");
		if(!fp1)
		{
			MessageBox(0,"�޷���ָ��λ�ô����ļ���������������Ŀ¼�����ԣ�","������ֹ��ʾ",0);
			abort();
		}
		double error[Ch_Num] = {whError,comError[0],comError[1],huError,surfError,weightError[0],weightError[1],weightError[2],weightError[3],entrError,biasError};
		for(int i=0;i<Ch_Num;i++)
			fprintf(fp1,"%-.3f\t",error[i]);
		if(same!=-1)
			//fprintf(fp1,"%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%d\n",whError,comError[0],comError[1],huError,surfError,weightError[0],weightError[1],weightError[2],weightError[3],entrError,same);
			fprintf(fp1,"%d\n",same);
        else
			fprintf(fp1,"\n");
		fclose(fp1);
    }
	return 0;
}
// ��Ŀ��ͶӰ��Ϣ���浽�ļ�
void Target::saveUVToFile(cchar* fileout,cchar* ps,int hh,int ww) {
    if(hh && ww) {
        if(p_u[0]==0) {
#ifndef __AFXWIN_H__
            cout<<"���·����ڴ�"<<endl;
#else
			sprintf(info,"%s���·����ڴ�\r\n",info);
#endif
            projectionUV();
        }
        Normalize(hh,ww);
    } else if(p_u[0]==0) {
        projectionUV();
        Normalize(h,w);
    }
    FILE *fp = fopen(fileout,"a+");
    if(fp) {
        fprintf(fp,"%d\t%d\n",h,w);
        int i;
        for(i=0; i<h; i++)
            fprintf(fp,"%lf  ",p_u[i]);
        fprintf(fp,"\n\n");
        for(i=0; i<w; i++)
            fprintf(fp,"%lf  ",p_v[i]);
        fprintf(fp,"\n\n");
        if(ps)
            fprintf(fp,"%s\n\n",ps);
        fclose(fp);
    } else
#ifndef __AFXWIN_H__
        cout<<"����ͶӰʧ��: �ļ�"<<fileout<<"��ʧ��"<<endl;
#else
		sprintf(info,"%s����ͶӰʧ��: �ļ�%s��ʧ��\r\n",info,fileout);
#endif
}
