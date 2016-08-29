#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
//#include<conio.h>
using namespace cv;
using namespace std;
Mat img(400,400,CV_8U,Scalar(120,120,120));//global for mouse callback
Point L=Point(133,136);//initialize eyeball at socket centre
Point R=Point(266,136);//get scaled black circle centres from mouse loc
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if ( event == EVENT_LBUTTONDOWN )
     {
       circle(img,Point(x,y),5,Scalar(255,255,255),1);//global Mat is never refreshed after 1st imread
       cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	

     }
	  if ( event == EVENT_MOUSEMOVE )
     {

       
		
	  L=Point((3*133+x)/4,(3*136+y)/4);
	  R=Point((3*266+x)/4,(3*136+y)/4);//move in 3/4th of the ellipse region, with y same for both

	 if(x>200)

	{
		L.x=(3*133+200)/4;//so the eyeball isn't sucked into the socket
	}
	 if(x<200)

	{
		R.x=(3*266+200)/4;//so the eyeball isn't sucked into the socket
	}
	 if(y>275)

	{
		L.y=((3*136+275)/4);
		R.y=((3*136+275)/4);//so the eyeball isn't sucked into the socket
	}			
				
			
		

     }
	 }

int main()
{
	Mat face(400,400,CV_8U,Scalar(120,120,120));//local
	Mat eye_th;//extract white cut ellipse
	namedWindow("eyes");//for mousecallback
        int event;
	
	for(;;)
		{
			//ellipse(img,Point(133,L.y/10),Size(2,15),90,0,360,Scalar(252),30);
			//ellipse(face,Point(133,L.y/10),Size(20,15),90,0,360,Scalar(200),30);
			ellipse(face,Point(133,136),Size(40,20),90,0,360,Scalar(0),46,8);//black space for eye sockets
			ellipse(face,Point(266,136),Size(40,20),90,0,360,Scalar(0),46,8);			
			
			ellipse(img,Point(133,136),Size(40,20),90,0,360,Scalar(255),46,8);//white eye sockets
			ellipse(img,Point(266,136),Size(40,20),90,0,360,Scalar(255),46,8);//redraw sockets to erase old eyeball
			//waitKey(1);
			
			ellipse(img,L,Size(20,15),90,0,360,Scalar(0),30);//draw black eyeball on global point
			ellipse(img,R,Size(20,15),90,0,360,Scalar(0),30);
			setMouseCallback("eyes", CallBackFunc, NULL);
			threshold(img,eye_th,250,255,THRESH_BINARY);//extract white part
			addWeighted(eye_th,1,face,1,0,face);//add white part to blank eye sockets
			img=face.clone();//apply result image on img
			int brow_y=L.y/4+20;
			if(L.y>133)
			{
				brow_y=54;				
			}
			//ellipse(img,Point(133,L.y/4-50),Size(6,30),90,0,360,Scalar(90),30);//to erase old eyebrow
			ellipse(img,Point(133,brow_y),Size(1,30),90,0,360,Scalar(30),30);//left eyebrow
			line(img,Point(83,brow_y+10),Point(183,brow_y+10),Scalar(120),15);//underside of new eyebrow
			ellipse(img,Point(266,brow_y),Size(1,30),90,0,360,Scalar(30),30);//right eyebrow
			line(img,Point(216,brow_y+10),Point(316,brow_y+10),Scalar(120),15);//underside of right eyebrow
	
			line(img,Point(216,brow_y+20),Point(316,brow_y+20),Scalar(120),25);//right eyelid
			line(img,Point(83,brow_y+20),Point(183,brow_y+20),Scalar(120),25);//right eyelid
			line(img,Point(250,300),Point(150,300),Scalar(0),15);//mouth
			line(img,Point(240,291),Point(160,291),Scalar(200),10);//teeth
			line(img,Point(240,311),Point(160,311),Scalar(200),10);//teeth
			ellipse(img,Point(200,300),Size(1.5*L.y/10,70),90,0,360,Scalar(80),20);//lips
			ellipse(img,Point(200,210),Size(4,1),90,0,360,Scalar(150),50);//nose
			ellipse(img,Point(200,200),Size(320,220),90,0,360,Scalar(80),90);//large face border
			imshow("eyes",img);
			//imshow("eyes",img);
			
			char c=waitKey(10);
			if(c=='b')
				{
					break;
				}
		}
	
	return 1;
}
