#include <vector>
#include<fstream>
#include<iostream>
using namespace std;

vector<int>saveVec;
vector<int> loadVec;
vector<COLORREF>colorVec;
vector<COLORREF> loadColor;

vector<int>ptsIN;
vector<int>ptsOUT;



void saveFun()
{

ofstream out;
ofstream outColor;

out.open("saveFile.txt");
outColor.open("colorFile.txt");
for(int i=0 ; i < saveVec.size()-1 ; i+=2)
{
    out<<saveVec[i]<<endl;
    out<<saveVec[i+1]<<endl;
}

for(int i=0 ; i < colorVec.size() ; i++)
{
outColor<<colorVec[i]<<endl;
}

out.close();

}
void loadFun(HDC hdc)
{
    ifstream infile;
    ifstream inColor;

  infile.open("saveFile.txt");
  inColor.open("colorFile.txt");
  if(infile.fail())
  {
      cout<<"error in opening the file "<<endl;
  exit(1);
  }
int x=0;
COLORREF c;

  while(!infile.eof())
  {
      infile>>x;
      loadVec.push_back(x);
  }
  while(!inColor.eof())
  {
      inColor>>c;
      loadColor.push_back(c);
  }

int j=0;

for(int i=0 ; i < loadVec.size()-1 ; i+=2 )
{

    SetPixel(hdc , loadVec[i] , loadVec[i+1] ,loadColor[j] );
j++;
}

infile.close();
inColor.close();
remove("saveFile.txt");
remove("colorFile.txt");

}

void SWAP(int &x1,int &x2)
{
    int temp;
    temp=x1;
    x1=x2;
    x2=temp;
}

int Round(double x)
{
    return (x+0.5);
}

void draw8Pts(HDC hdc ,int xc,int yc,int x , int y ,COLORREF c)
{
    SetPixel(hdc, xc +x , yc+y , c);
 saveVec.push_back(xc +x);
 saveVec.push_back(yc+y);
colorVec.push_back(c);

    SetPixel(hdc, xc -x , yc+y , c);
saveVec.push_back(xc -x);
 saveVec.push_back(yc+y);
colorVec.push_back(c);

    SetPixel(hdc, xc -x , yc-y , c);
saveVec.push_back(xc -x);
 saveVec.push_back(yc-y);
colorVec.push_back(c);

    SetPixel(hdc, xc +x , yc-y , c);
saveVec.push_back(xc +x);
 saveVec.push_back(yc-y);
colorVec.push_back(c);

    SetPixel(hdc, xc +y , yc+x , c);
saveVec.push_back(xc +y);
 saveVec.push_back(yc+x);
colorVec.push_back(c);

    SetPixel(hdc, xc -y , yc+x , c);
saveVec.push_back(xc - y );
 saveVec.push_back(yc+x);
colorVec.push_back(c);

    SetPixel(hdc, xc -y , yc-x , c);
saveVec.push_back(xc - y);
 saveVec.push_back(yc-x);
colorVec.push_back(c);

    SetPixel(hdc, xc +y , yc-x , c);
saveVec.push_back(xc +y);
 saveVec.push_back(yc-x);
colorVec.push_back(c);
}

void drawCircle3(HDC hdc,int xc,int yc,int r ,COLORREF c)
{
    double xStart=0;
    double yStart=r;

    draw8Pts(hdc,xc,yc,xStart,yStart,c);
    while(xStart<yStart)
    {
        xStart+=1;
        yStart=Round(sqrt((r*r)-(xStart*xStart)));

        draw8Pts(hdc,xc,yc,xStart,yStart,c);

    }}

bool InCircle(int x , int y , int x11,int y11 , int x22,int y22)
{
    /*
int x11=300;
int y11=420;
int x22=500;
int y22=500;*/
int r=sqrt(pow(x22-x11,2.0)+pow(y22-y11,2.0));
int rTest=sqrt(pow(x-x11,2.0)+pow(y-y11,2.0));

if(rTest <=r)
{
    return true;
}
return false;
}
void drawLine2(HDC hdc,int xs ,int ys,int xe,int ye, int x11,int y11 , int x22,int y22 ,COLORREF c) //direct use of parametric equation
//x=x1+t*(x2-x1)      y=y1+t*(y2-y1)
{
    double x,y;

    double dt=1.0/max(abs(xe-xs),abs(ye-ys));

    for(double t=0.0;t<=1;t+=dt)
    {
        x=xs+t*(xe-xs);
        y=ys+t*(ye-ys);

        if(InCircle((int)x , (int)y ,x11, y11 , x22, y22))
        {
        SetPixel(hdc,Round(x),Round(y),c);
        saveVec.push_back(Round(x));
        saveVec.push_back(Round(y));
        colorVec.push_back(c);

        ptsIN.push_back(Round(x));

        ptsIN.push_back(Round(y));

        }
        else
        {
     SetPixel(hdc,Round(x),Round(y),RGB(255,255,255));
            saveVec.push_back(Round(x));
            saveVec.push_back(Round(y));
    colorVec.push_back(RGB(255,255,255));
            ptsOUT.push_back(Round(x));
            ptsOUT.push_back(Round(y));
        }

    }
}
////////////////////  LINE   /////////////////////

void  drawLineDDA(HDC hdc,int xs,int xe,int ys,int ye,COLORREF color)
{
    double dx,dy;
    dx=(double)(xe-xs);
    dy=(double)(ye-ys);

    double slope = dy/dx;
    double slope_inv = dx/dy;

    if(abs(dx)>=abs(dy))
    {
        //double y=ys;
        if(xs>xe)
        {
            SWAP(xs,xe);
            SWAP(ys,ye);
    /*double temp;
    temp=ys;
    ys=ye;
    ye=temp;
      */  }
        int x=xs;
        double y=ys;
        SetPixel(hdc,x,Round(y),color);
saveVec.push_back(x );
 saveVec.push_back(Round(y));
 colorVec.push_back(color);

        while(x<xe)
        {
            x++;
            //y=slope*(x-xs)+ys;
            y+=slope;
            SetPixel(hdc,x,Round(y),color);
saveVec.push_back(x);
 saveVec.push_back(Round(y));
 colorVec.push_back(color);

        }
    }
     else{
        //double x=xs;

        if(ys>ye)
        {
/*    double temp;
    temp=xs;
    xs=xe;
    xe=temp;
  */
 SWAP(xs,xe);
SWAP(ys,ye);
        }
         int y=ys;
        double x=xs;

        SetPixel(hdc,Round(x),y,color);
saveVec.push_back(Round(x) );
 saveVec.push_back(y);
 colorVec.push_back(color);

        while(y<ye)
        {
            y++;
            x+=slope_inv;
            //x=slope_inv*(y-ys)+xs;
            SetPixel(hdc,Round(x),y,color);
        saveVec.push_back(Round(x));
 saveVec.push_back(y);
         colorVec.push_back(color);

        }

        }
}



void drawLineParam(HDC hdc,int xs ,int ys,int xe,int ye,COLORREF c)
{
    double x,y;

    double dt=1.0/max(abs(xe-xs),abs(ye-ys));

    for(double t=0.0;t<=1;t+=dt)
{
        x=xs+t*(xe-xs);
        y=ys+t*(ye-ys);
        SetPixel(hdc,Round(x),Round(y),c);
saveVec.push_back(Round(x));
saveVec.push_back(Round(y));
 colorVec.push_back(c);

}
}

void brsenhamLine(HDC hdc ,int xs,int ys,int xe,int ye,COLORREF c)
{
    double dy=ye-ys;
    double dx=xe-xs;

    int x=xs;
    int y=ys;

    double d=0.0    ;


    if(abs(dx) > abs(dy))
    {
  if(dx<0)
  {
SWAP(xs,xe);
SWAP(ys,ye);
dy=-dy;
dx=-dx;
  }

 x=xs;
y=ys;
    SetPixel(hdc,x,y,c);
saveVec.push_back(x);
saveVec.push_back(y);
 colorVec.push_back(c);

  if(dy>0)
  {
        d=dx-2*dy;
        int d1=2*dx-2*dy;
        int d2= -2*dy;
    while(x<xe)
    {
    //    d=(y+0.5-ys)*dx - (x+1-xs)*dy; //f(x,y)= y dx -x dy ==  (y+1/2 -ys )*dx - (x+1-xs )*dy
        if( d <= 0 )
        {   d+=d1;
            y++;
            x++;
        }
        else{
                d+=d2;
            x++;
        }

        SetPixel(hdc,x,y,c);
    saveVec.push_back(x);
    saveVec.push_back(y);
 colorVec.push_back(c);

    }
    }
    else{ //dx>dy , dy<0 , dx<0 or dx>0  ---> 4th quad and 3rd quad
        d=dx+2*dy;
        int d1=2*dx+2*dy;
        int d2= 2*dy;

//   dy=-dy;

    while(x<xe)
    {
        if( d <= 0 )
        {
            d+=d1;
            y--;
            x++;
        }
        else{
            d+=d2;
            x++;
        }

        SetPixel(hdc,x,y,c);
    saveVec.push_back(x);
    saveVec.push_back(y);
 colorVec.push_back(c);

    }
    }
    }
    else{ //dy > dx

if(dy<0)
    {
            SWAP(xs,xe);
            SWAP(ys,ye);
dy=-dy;
dx=-dx;

    }
x=xs;
y=ys;
    SetPixel(hdc,x,y,c);
saveVec.push_back(x);
saveVec.push_back(y);
 colorVec.push_back(c);

    if(dx>0) //1st quad but dy>dx
    {

        d=-2*dx+dy;
        int d1=-2*dx+2*dy;
        int d2= -2*dx;

    while(y<ye)
    {
        if( d <= 0 )
        {d+=d1;
            y++;
            x++;
        }
        else{
                d+=d2;
            y++;
        }

        SetPixel(hdc,x,y,c);
    saveVec.push_back(x);
        saveVec.push_back(y);
 colorVec.push_back(c);
    }
    }
    else{ //3Rd quad AND 2nd quad
    d=2*dx+dy;
    int d1=2*dx+2*dy;
    int d2= 2*dx;

    while(y<ye)
    {
        if( d <= 0 )
        {
            d+=d1;
            y++;
            x--;
        }
        else{
            d+=d2;
            y++;
        }

        SetPixel(hdc,x,y,c);
    saveVec.push_back(x);
        saveVec.push_back(y);
     colorVec.push_back(c);

    }


    }
}

}

//////////////////////   ELLIPSE    ////////////////////////////////////


int Max(int x,int y)
{
    if(x>y)
        return x;
    else
        return y;
}

void drawEllipsebyUsingDirectPolar(HDC hdc, int xc, int yc, int Rx, int Ry, COLORREF c)
{
    double dtheta=1.0/Max(Rx,Ry);
    for(double theta=0; theta<=6.28 ; theta+=dtheta )
    {
            double x=xc+Rx*cos(theta);
           double y=yc+Ry*sin(theta);
           SetPixel(hdc,Round(x),Round(y),c);
    saveVec.push_back(Round(x));
    saveVec.push_back(Round(y));
 colorVec.push_back(c);

    }
}


void Draw4points(HDC hdc,int x,int y,int xc,int yc,COLORREF c)
{
    SetPixel(hdc,(xc+x),(yc+y),c);
    saveVec.push_back(xc+x);
        saveVec.push_back(yc+y);
 colorVec.push_back(c);

    SetPixel(hdc,(xc-x),(yc+y),c);
    saveVec.push_back(xc-x);
        saveVec.push_back(yc+y);
 colorVec.push_back(c);

    SetPixel(hdc,(xc+x),(yc-y),c);
    saveVec.push_back(xc+x);
        saveVec.push_back(yc-y);
 colorVec.push_back(c);

    SetPixel(hdc,(xc-x),(yc-y),c);
saveVec.push_back(xc-x);
        saveVec.push_back(yc-y);
 colorVec.push_back(c);

}

void drawEllipsebyUsingCartesian(HDC hdc,int xc,int yc,int Rx,int Ry,COLORREF c)
{
    double x = Rx;
    int y = 0;
    Draw4points(hdc,x,0,xc,yc,c);
    double dt=1.0/Max(Rx,Ry);
    while(x >=0)
    {
       x-=dt;
        //x-=0.01;
        y=abs(Ry*sqrt(1-(pow(x,2.0)/pow(Rx,2.0))));

        Draw4points(hdc,Round(x),Round(y),xc,yc,c);
    }

}


void drawEllipsebyUsingMidpoint(HDC hdc ,int xc, int yc , int rx, int ry, COLORREF c)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
  Draw4points( hdc ,  x ,  y ,  xc ,  yc , c );
    // Initial decision parameter of region 1
    d1 = pow(ry,2) - (pow(rx,2) * ry) + (0.25 * pow(rx,2));
    dx = 2 *pow(ry,2) * x;
    dy = 2 * pow(rx,2) * y;

    while (dx < dy)
    {

        if (d1 < 0)
        {
            x++;
            dx += (2 * pow(ry,2));
            d1 += dx + pow(ry,2);
        }
        else
        {
            x++;
            y--;
            dx+=(2 * pow(ry,2));
            dy-= (2 * pow(rx,2));
            d1 += dx - dy + pow(ry,2);
        }
        Draw4points ( hdc ,  x ,  y ,  xc ,  yc , c );
    }

    // Decision parameter of region 2
    d2 = (pow(ry,2) * ((x + 0.5) * (x + 0.5))) +
         (pow(rx,2) * ((y - 1) * (y - 1))) -
          (pow(rx,2)* pow(ry,2));

    //  points of region 2
    while (y >= 0)
    {

        if (d2 > 0)
        {
            y--;
            dy -= (2 * pow(rx,2));
            d2 += pow(rx,2) - dy;
        }
        else
        {
            y--;
            x++;
            dx += (2 * pow(ry,2));
            dy -= (2 * pow(rx,2));
            d2 += dx - dy + pow(rx,2);
        }
        Draw4points ( hdc ,  x ,  y ,  xc ,  yc , c );
}
}



/////////////////////               /////////////////
