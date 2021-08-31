#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include "FUNCTIONS.h"
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

void addMenues(HWND);
HMENU hMenu;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+2;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

struct my_point
{
    int x;
    int y;

};

struct edge_entry
{
    int xmax = -3666;
    int xmin = 3666;
    int y = 0;
};
PAINTSTRUCT ps;
edge_entry et[10000];


vector<my_point>vertix_list;

void draw_scan_line (HDC hdc)
{
    for (int i=0; i <10000; i++)
    {
        if(et[i].y!=0)
        {
            for(int j=et[i].xmin; j<et[i].xmax ; j++)
            {
                SetPixel(hdc,j,et[i].y,RGB(255,0,0));
            saveVec.push_back(j);
            saveVec.push_back(et[i].y);
            colorVec.push_back(RGB(255,0,0));

            }

    }
}
}

void scan_edge (HDC hdc)
{
    my_point v1 = vertix_list[vertix_list.size()-1];
    for (int i=0; i< vertix_list.size(); i++)
    {
        my_point v2= vertix_list[i];

        if (v1.y > v2.y)
        {
            SWAP(v1.y, v2.y);
            SWAP(v1.x, v2.x);
        }
        int y = v1.y;
        double x = v1.x;

        double m_inv = (double)(v2.x-v1.x)/(double)(v2.y-v1.y);
        while (y < v2.y)
        {
            if (x < et[y].xmin)
            {
                et[y].xmin = ceil(x);
                et[y].y = y;
            }
            if (x > et[y].xmax)
            {
                et[y].xmax = floor(x);
                et[y].y = y;

            }
            y++;
            x+=m_inv;
        }

        v1 = vertix_list[i];
    }
    draw_scan_line (hdc);
}


HDC hdc;
int x1,x2,y1,y2;

/*  This function is called by the Windows function DispatchMessage()  */
bool ready = false;
my_point V;
string check="";

#define LINE_PARAMETRIC 1
#define LINE_DDA 2
#define ELLIPSE_Cartesian 3
#define ELLIPSE_DIRECT_POLAR 4
#define ELLIPSE_MIDPOINT 5
#define CONVEX 6
#define CLIPING 7
#define LINE_BRES 8
#define save 9
#define load 10
#define points 11


int xc1,xc2,yc1,yc2;



LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_COMMAND:
        switch(wParam)
        {
        case points:
            {
                   for(int i=0;i<ptsIN.size();i+=2)
               {
                   cout<<" points inside circle :"<<ptsIN[i]<<" "<<ptsIN[i+1]<<endl;
               }

                for(int i=0;i<ptsOUT.size();i+=2)
               {
                   cout<<" points outside circle : "<<ptsOUT[i]<<" "<<ptsOUT[i+1]<<endl;
               }

            }
            break;
            case save: //case line
        {
            MessageBeep(MB_OK);
            saveFun();

        }
        break;

        case load: //case line
        {
            MessageBeep(MB_OK);
            hdc = GetDC(hwnd);
            loadFun(hdc);

        }
        break;


        case LINE_DDA: //case line
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            check="lineDda";

        }
        break;

        case LINE_PARAMETRIC: //case line
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            check="lineParametric";

        }
        break;

           case LINE_BRES: //case line
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            check="lineBres";

        }
        break;

        case ELLIPSE_DIRECT_POLAR: //case line
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            check="ellipseDirect";

        }
        break;
        case ELLIPSE_Cartesian: //case line
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            check="ellipseCartesian";

        }
        break;

        case ELLIPSE_MIDPOINT:
            {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
                check="ellipseMidPoint";
            }
break;
        case CONVEX:
        {
            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;
            vertix_list.clear();
            for(int i=0; i<10000; i++)
            {
                et[i].xmax = -3666;
                et[i].xmin = 3666;
                et[i].y = 0;
            }

            check="convex";

        }
        break;
        case CLIPING:
        {

            MessageBeep(MB_OK);
            x1=0;
            x2=0;
            y1=0;
            y2=0;

             xc1=x1;
             yc1=y1;
             xc2=x2;
             yc2=y2;

            /*
            int x11=300;
            int y11=420;
            int x22=500;
            int y22=500;
            int r=sqrt(pow(x22-x11,2.0)+pow(y22-y11,2.0));
            HDC hdc = GetDC(hwnd);

            drawCircle3(hdc,x11,y11,r,RGB(0,200,150));
            ReleaseDC(hwnd,hdc);
            */
            check="clip";
        }
        }

    case WM_CREATE:
        addMenues(hwnd);
        break;

    case WM_LBUTTONDOWN :
    {
        x1=LOWORD(lParam);
        y1=HIWORD(lParam);

        V.x=LOWORD(lParam);
        V.y=HIWORD(lParam);

        vertix_list.push_back(V);

    }
    break;
    case WM_KEYDOWN:
    {
        if(check=="convex")
        {
            hdc = GetDC(hwnd);
            scan_edge(hdc);
            ReleaseDC(hwnd, hdc);
            check="";

        }
    }
    case WM_LBUTTONUP:
    {
        x2=LOWORD(lParam);
        y2=HIWORD(lParam);

        if(check=="lineBres")
        {
            hdc = GetDC(hwnd);
            brsenhamLine(hdc,x1,y1,x2,y2,RGB(0,255,0));
            ReleaseDC(hwnd, hdc);
            check="";
        }

        if(check=="lineDda")
        {
            hdc = GetDC(hwnd);
            drawLineDDA(hdc,x1,x2,y1,y2,RGB(255,255,0));
            ReleaseDC(hwnd, hdc);
            check="";
        }
        if(check=="lineParametric")
        {
            hdc = GetDC(hwnd);
            drawLineParam(hdc,x1,y1,x2,y2,RGB(255,0,0));
            ReleaseDC(hwnd, hdc);
            check="";
        }

        if(check=="clip")
        {
            HDC hdc = GetDC(hwnd);

            int r=sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0));

             xc1=x1;
             yc1=y1;
             xc2=x2;
             yc2=y2;


            drawCircle3(hdc,x1,y1,r,RGB(0,200,150));
            ReleaseDC(hwnd,hdc);
           x1=0;
           x2=0;
           y1=0;
           y2=0;
            check="clipLine";
        }

            if(check=="clipLine")
        {
            HDC hdc = GetDC(hwnd);

            drawLine2(hdc,x1,y1,x2,y2,xc1,yc1,xc2,yc2,RGB(0,200,150));
            ReleaseDC(hwnd,hdc);
            check="clipLine";
        }


    }
    break;

      case WM_RBUTTONDOWN:
    {
    int x3 = LOWORD(lParam);
    int y3 = HIWORD(lParam);
    int Ry=sqrt(pow(x3-x1,2.0)+pow(y3-y1,2.0));
    int Rx =sqrt(pow(x2-x1,2.0)+pow(y2-y1,2.0));
        if(check=="ellipseDirect")
       {
           hdc=GetDC(hwnd);

        drawEllipsebyUsingDirectPolar(hdc,x1,y1,Rx,Ry,RGB(255,255,255) );
        ReleaseDC(hwnd,hdc);
        check="";
       }
       if(check=="ellipseCartesian")
       {
           hdc=GetDC(hwnd);

       drawEllipsebyUsingCartesian(hdc, x1,y1,Rx,Ry,RGB(255,255,100));
        ReleaseDC(hwnd,hdc);
        check="";
       }
       if(check=="ellipseMidPoint")
       {
           hdc=GetDC(hwnd);

       drawEllipsebyUsingMidpoint(hdc, x1,y1,Rx,Ry,RGB(255,150,255));
        ReleaseDC(hwnd,hdc);
        check="";
       }
        //drawEllipsebyUsingIterativePolar(hdc, x1,y1,Rx,Ry,RGB(255,0,0));
        //drawEllipsebyUsingMidpoint(hdc, x1, y1,Rx,  Ry, RGB(255,0,0));

    }
    break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    //return 0;
}

void addMenues(HWND hwnd)
{
    hMenu = CreateMenu();
    HMENU hfLINE = CreateMenu();
    HMENU hfELLIPSE = CreateMenu();

    AppendMenu(hfLINE,MF_STRING,LINE_BRES,"LINE BRESENHAM");
    AppendMenu(hfLINE,MF_STRING,LINE_DDA,"LINE DDA");
    AppendMenu(hfLINE,MF_STRING,LINE_PARAMETRIC,"LINE PARAMETRIC");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hfLINE,"LINE");


    AppendMenu(hfELLIPSE,MF_STRING,ELLIPSE_MIDPOINT,"ELLIPSE MIDPOINT");
    AppendMenu(hfELLIPSE,MF_STRING,ELLIPSE_Cartesian,"ELLIPSE Cartesian ");
    AppendMenu(hfELLIPSE,MF_STRING,ELLIPSE_DIRECT_POLAR,"ELLIPSE DIRECT POLAR");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hfELLIPSE,"ELLIPSE");


    AppendMenu(hMenu,MF_STRING,CONVEX,"CONVEX FILLING");
    AppendMenu(hMenu,MF_STRING,CLIPING,"Line Clipping");
    AppendMenu(hMenu,MF_STRING,save,"save");
    AppendMenu(hMenu,MF_STRING,load,"load");
    AppendMenu(hMenu,MF_STRING,points,"POINTS IN AND OUT");

    SetMenu(hwnd,hMenu);
}
