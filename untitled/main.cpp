#include <iostream>
#include<opencv2/opencv.hpp> //引入头文件

using namespace cv;//命名空间
using namespace std;

//opencv机器视觉库 C/C++编写出来 提供了很多功能 都是以函数的形式提供 调用

int main()
{

    Mat frame;//保存每一帧的摄像头图片

    VideoCapture capture(0);//参数为0的时候，表示调用电脑默认摄像头

    while(capture.read(frame))
    {
        Mat backImg = imread("d:/background.png");//记住背景

        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);//将frame转化为从BGR转化为HSV

        Mat mask,mask1;
        inRange(hsv,Scalar(0,120,100),Scalar(10,255,255),mask);
        inRange(hsv,Scalar(170,120,100),Scalar(180,255,255),mask1);//来提取HSV图像中的红色区域，红色区域呈现白色


        mask = mask + mask1;//合并红色区域

        //4.取反操作 ->获得红布区域以外的抠图模板
        Mat uMask;//红布区域以外的抠图模板
        bitwise_not(mask,uMask);        //现在是非红色区域呈现白色
        imshow("umask",uMask);

        Mat finalImg;
        bitwise_and(backImg, backImg, finalImg, mask); //将 backImg 中 mask 指定的区域复制到 finalImg，也就是红色区域后的初始背景
        Mat foreground;
        bitwise_and(frame, frame, foreground, uMask); // 将frame中mask指定的相反的地方复制到，也就是红色区域外的实时画面
        add(finalImg, foreground, finalImg);


        namedWindow("Invisibility Cloak", WINDOW_NORMAL);
        resizeWindow("Invisibility Cloak", 2000, 1000);  // 设置窗口大小
        imshow("Invisibility Cloak", finalImg);





        waitKey(30);//参数为0的时候 表示等待用户按下任意键  参数>0 30表示休眠30毫秒 1000毫秒=1秒
    }


        return 0;//程序正常结束
}


/*
    //1.显示2张图片
    Mat backImg = imread("d:/background.jpg");//背景图片
    Mat hideImg = imread("d:/hide.jpg");//人物拿着红布图片

    imshow("back",backImg);
    imshow("hide",hideImg);

    //2.图片转hsv格式
    Mat hsv;
    cvtColor(hideImg,hsv,COLOR_BGR2HSV);//颜色处理函数
    imshow("hsv",hsv);

    //3.识别出红色区域   注意：红色有2个hsv的区域
    Mat mask,mask1;
    inRange(hsv,Scalar(0,120,100),Scalar(10,255,255),mask);
    inRange(hsv,Scalar(170,120,100),Scalar(180,255,255),mask1);
//    imshow("mask",mask);
//    imshow("mask1",mask1);
    mask = mask + mask1;
    imshow("mask",mask);//此时mask就是完整的红布区域抠图模板

    //4.取反操作 ->获得红布区域以外的抠图模板
    Mat uMask;//红布区域以外的抠图模板
    bitwise_not(mask,uMask);
    imshow("uMask",uMask);

    //5.  背景图片 mask扣1  uMask扣2
    Mat bkMask;
    bitwise_and(backImg,backImg,bkMask,mask);
    imshow("bkMask",bkMask);

    Mat bkUmask;
    bitwise_and(hideImg,hideImg,bkUmask,uMask);
    imshow("bkUmask",bkUmask);

    //6.2个图片 像素相融合
    Mat finalImg;
//    add(bkMask,bkUmask,finalImg);// +可以吗？  add函数有什么存在的意义？
    finalImg = bkMask + bkUmask;
    imshow("final",finalImg);



//1.显示图片
    Mat image = imread("d:/test.png");
    imshow("1",image);

    //2.图片转hsv格式
    Mat hsv;
    cvtColor(image,hsv,COLOR_BGR2HSV);//颜色处理函数
    imshow("2",hsv);

    //3.截取颜色区域范围 inRang  在hsv取值范围内 呈白色的模板  ，不在范围内 呈黑色
    Mat mask;//抠图模版
    inRange(hsv,Scalar(100,43,46),Scalar(124,255,255),mask);
    imshow("3",mask);

    //4.现在可以抠背景图了，但其实我们想抠的是人像
    //取反操作
    bitwise_not(mask,mask);
    imshow("4",mask);//此时的mask已经是人像抠图模板了

    //5.生成一张红色背景图  大小？类型？ 参考原始图片
                  // ：：是C++作用域分解运算符  调用Mat对象里面的成员函数
                //zeros() 创建一个指定行数、列数  类型 的矩阵  所有像素都为0
    Mat redBack = Mat::zeros(image.size(),image.type());
    redBack = Scalar(40,40,200);//BGR       RGB 210 67 115
    imshow("5",redBack);

    //6.实现图片的拷贝操作
    image.copyTo(redBack,mask);
    imshow("6",redBack);



//1.显示一张图片     路径不写\  得写/  转义符  imread读取一张图片
    Mat img = imread("d:/niu0.jpg");//定义一个Mat类型的变量  图片对象类型 / 容器对象类型
    imshow("title",img); //imshow显示一张图片

    //2.图片转模糊图片
    Mat blurImg;//模糊图片对象
    blur(img,blurImg,Size(50,50));//模糊处理函数  size(横向模糊尺寸，纵向模糊尺寸)
    imshow("blur",blurImg);

    //3.图片做灰度处理             (数据量减少3倍，未来业务跟颜色无关，都可以先灰色处理)
    Mat grayImg;//灰色图片对象
    cvtColor(img,grayImg,COLOR_BGR2GRAY);//颜色处理函数
    imshow("gray",grayImg);

    //4.图片做二值化处理
    Mat threImg;//二值化图片
    threshold(grayImg,threImg,170,255,THRESH_BINARY);//二值化处理
    imshow("thre",threImg);


*/



