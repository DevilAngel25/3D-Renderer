// 3DRenderer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3DRenderer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

BOOL WINAPI ChooseColour();

int clientWidth = 0;
int clientHeight = 0;

bool loading = true;						//load a model if on startup
bool rotate = true;							//is the mesh rotating
bool fill = true;							//does the mesh have a fill color


float rotateX = 0.0f;						//rotation vars
float rotateY = 0.0f;
float rotateZ = 0.0f;

COLORREF Colour;							//Colour varibles
int wr = 0;
int wg = 0;
int wb = 0;

int fr = 0;
int fg = 0;
int fb = 0;

Mesh originalModel, newModel;			//create two meshes one for loading models and one to manipulate

Matrix4 mTW, vM, worldViewProjection;	//modeltoworld, viewmatrix, object-world-view-viewport matrix

Matrix4 tM;								//translation matrix
Matrix4 rxM, ryM, rzM;					//rotation matrixes
Matrix4 sxM, syM, szM, sM;				//scale matrixes

Matrix4 projection(	5.0,0.0,0.0,0.0,	//projection matrix
					0.0,5.0,0.0,0.0, 
					0.0,0.0,0.0,0.0, 
					0.0,0.0,0.0,1.0);

Vector3 view, up, right, eye, at;		//view vectors for view matrix, set later on


void PipeLine(void);					//define custom functions
void DrawMesh(HDC&);
void ResetModel(Mesh&);
void ResetMatrix(void);
void RotateMesh(void);
void FillTriangle(HDC&);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY3DRENDERER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DRENDERER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DRENDERER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY3DRENDERER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// Create a Color Dialog
BOOL ChooseColour(HWND hWnd)
{
	CHOOSECOLOR cc;
	static COLORREF CustCol[16];
	static DWORD rgbCurrent;

	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD) CustCol;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT | CC_SOLIDCOLOR;
 
	if (ChooseColor(&cc) == TRUE) 
	{	
		rgbCurrent = cc.rgbResult;
	}

	return rgbCurrent; //return color selected
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_LOADOBJECT_LOAD_CUBE:				//select to load a cube
			ResetModel(originalModel);				//reset the original model mesh so the new mesh  is clean
			LoadObj("Cube", originalModel);			//load the cube from an object file
			InvalidateRect(hWnd,NULL,true);			//refresh the screen
			break;
		case ID_LOADOBJECT_LOAD_DIAMOND:
			ResetModel(originalModel);
			LoadObj("Diamond", originalModel);
			InvalidateRect(hWnd,NULL,true);
			break;
		case ID_LOADOBJECT_LOAD_DODECA:
			ResetModel(originalModel);
			LoadObj("Dodeca", originalModel);
			InvalidateRect(hWnd,NULL,true);
			break;
		case ID_LOADOBJECT_LOAD_ICOSA:
			ResetModel(originalModel);
			LoadObj("Icosa", originalModel);
			InvalidateRect(hWnd,NULL,true);
			break;
		case ID_LOADOBJECT_LOAD_OCTA:
			ResetModel(originalModel);
			LoadObj("Octa", originalModel);
			InvalidateRect(hWnd,NULL,true);
			break;
		case ID_LOADOBJECT_LOAD_HUMANOID:
			ResetModel(originalModel);
			LoadObj("Humanoid", originalModel);
			InvalidateRect(hWnd,NULL,true);
			break;
		case ID_COLOUR_OBJECTCOLOUR:
			rotate = false;						//stop rotating the mesh (else an error is created)
			Colour = ChooseColour(hWnd);		//Open the color dialog to pick a border color.
			
			wr = GetRValue(Colour);				//set wireframe and fill colour
			wg = GetGValue(Colour);
			wb = GetBValue(Colour);

			fr = GetRValue(Colour);
			fg = GetGValue(Colour);
			fb = GetBValue(Colour);

			rotate = true;						//begin rotating the mesh again.
			break;
		case ID_RENDERTYPE_WIREFRAME:
			fill = false;						//if wireframe, don't fill
			break;
		case ID_RENDERTYPE_FILLCOLOR:
			fill = true;						//if not wireframe fill mesh
			break;
		case ID_FILE_ROTATE:

			if(rotate)
			{
				rotate = false;
			}
			else
			{
				rotate = true;
			}
						//Starts and Stops the rotation
			break;
		case IDM_ABOUT:
			rotate = false;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			rotate = true;
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			//get client.
			RECT client;
			GetClientRect(hWnd, &client);

			//Find width/height.
			clientWidth = client.right - client.left;
			clientHeight = client.bottom + client.left;

			//create buffer
			HDC bdc = CreateCompatibleDC(hdc);
			HBITMAP backbuff = CreateCompatibleBitmap(hdc, clientWidth, clientHeight);
			HGDIOBJ oldobj = SelectObject(bdc, backbuff);

			//draw rect around client area
			Rectangle(bdc, client.left, client.top, client.right, client.bottom);

			if(loading)								//load the startup mesh
			{
				LoadObj("Cube", originalModel);
				loading = false;					//now a mesh is in the system we'll never need to load it again (untill the next start-up)
			}

			PipeLine();								//take the mesh and run it through the pipeline.
			DrawMesh(bdc);							//draw the mesh

			if(fill)								//if not wireframe
			{
				FillTriangle(bdc);					//Fill triangles
			}

			//copy content from bdc to hdc
			BitBlt(hdc, 0, 0, clientWidth, clientHeight, bdc, 0, 0, SRCCOPY);

			// select and delete objects
			SelectObject(bdc, oldobj);
			DeleteObject(backbuff);
			DeleteDC(bdc);
			ReleaseDC(hWnd, hdc);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	//rotate the mesh 
	if(rotate)
	{
		InvalidateRect(hWnd,NULL,true); //redraw the mesh/update the screen
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//create a pipeline the mesh needs to go through before drawing.
void PipeLine()
{
	ResetMatrix();				//reset matrices (mainly for scale as they increase everytime they are set)
	newModel = originalModel;	//use the newmodel for drawing the mesh so theres no need to reload the object to retrieve the original values.
	RotateMesh();				//rotate the mesh

	tM.Translation(120,-80,0);	//translate the mesh
	rxM.RotationX(rotateX);		//rotate in X
	ryM.RotationY(rotateY);		//rotate in Y
	rzM.RotationZ(rotateZ);		//rotate in Z
	sxM.ScaleX(1);				//Scale in X
	syM.ScaleY(1);				//Scale in Y
	szM.ScaleZ(1);				//Scale in Z
	sM.Scale(1);				//Scale in all (XYZ)

	mTW = tM * rxM * ryM * rzM * sxM * syM * szM * sM; //create modeltoworld matrix

	view.SetX(0.0f);		//set view values
	view.SetY(0.0f);
	view.SetZ(1.0f); 

	up.SetX(0.0f);			//set up values
	up.SetY(1.0f);
	up.SetZ(0.0f);

	right.SetX(1.0f);		//set right values
	right.SetY(0.0f);
	right.SetZ(0.0f);

	eye.SetX(0.0f);			//set eye values
	eye.SetY(0.0f);
	eye.SetZ(0.0f);

	at.SetX(0.0f);			//set at values
	at.SetY(0.0f);
	at.SetZ(-1.0f);

	view = view.Normalise(at - eye);					//normalise view
	right = right.Normalise(view.crossProduct(up));		//normalise right via cross product of view and up
	up = up.Normalise(right.crossProduct(view));		//normalise up via cross product of right and view

	vM.View(view,up,right,eye);					//create view matrix values
	vM = vM.Invert(vM);							//invert view matrix

	// create one total matrix
	worldViewProjection = projection * vM * mTW;

	Edge updateEdge0, updateEdge1, updateEdge2;			//create edges to update mesh values

	//turn object x,y,z into viewport x,y,z, update the vertices and edges. (then DeHomogise the Vertex (when drawing mesh))
	for(int i = 0; i < newModel.GetTCount(); i++)
	{
		newModel.SetV0P(i, worldViewProjection * newModel.GetV0(i).GetP());		//create new vertex values
		newModel.SetV1P(i, worldViewProjection * newModel.GetV1(i).GetP());
		newModel.SetV2P(i, worldViewProjection * newModel.GetV2(i).GetP());

		for(int j = 0; j < newModel.GetTCount(); j++)
		{
			updateEdge0.SetV0(newModel.GetV0(j));					//update the edges.
			updateEdge0.SetV1(newModel.GetV1(j));					//without this the mesh will not draw correctly
																	//as the edges are used in drawing and the edges
			updateEdge1.SetV0(newModel.GetV1(j));					//are not updated when the vertices are.
			updateEdge1.SetV1(newModel.GetV2(j));

			updateEdge2.SetV0(newModel.GetV2(j));
			updateEdge2.SetV1(newModel.GetV0(j));

			newModel.SetE0(j, updateEdge0);
			newModel.SetE1(j, updateEdge1);
			newModel.SetE2(j, updateEdge2);

			newModel.SetTColour(j,Colour);
		}

	}
}

void DrawMesh(HDC& bdc)
{
	Edge e0, e1, e2;

	//get the edges and draw the mesh
	for(int i = 0; i < newModel.GetTCount(); i++)
	{
		e0 = newModel.GetE0(i);
		e1 = newModel.GetE1(i);
		e2 = newModel.GetE2(i);

		Draw_Line(bdc, e0, fill, Colour);
		Draw_Line(bdc, e1, fill, Colour);
		Draw_Line(bdc, e2, fill, Colour);
	}

}

//reset mesh values for new .obj models
void ResetModel(Mesh& m)
{
	Vertex v0(0,0,0), v1(0,0,0);
	Edge e0(v0,v1);

	for(int i = 0; i < m.GetTCount(); i++)
	{
		m.SetV0(i, v0);
		m.SetV1(i, v0);
		m.SetV2(i, v0);

		m.SetE0(i, e0);
		m.SetE1(i, e0);
		m.SetE2(i, e0);
	}

	m.SetTCount(0);
}

// I reset the Matrices back to the default as
// changes to the type of model affect the scaling ect.
void ResetMatrix()
{
	sxM.ResetMatrix();
	syM.ResetMatrix();
	szM.ResetMatrix();
	sM.ResetMatrix();
	mTW.ResetMatrix();
	vM.ResetMatrix();
	worldViewProjection.ResetMatrix();
}

//rotates the mesh in all planes xyz
void RotateMesh()
{
	if(rotateX <= 360)
	{
		rotateX += 1;
	}
	else
	{
		rotateX = 0;
	}

	if(rotateY <= 360)
	{
		rotateY += 1;
	}
	else
	{
		rotateY = 0;
	}

	if(rotateZ <= 360)
	{
		rotateZ += 1;
	}
	else
	{
		rotateZ = 0;
	}
}

//Get the X and Y for each triangle, find all possible places to set a colour and set the colour
void FillTriangle(HDC& bdc)
{
	Vertex v0,v1,v2;
	float x0, x1, y0, y1;
	float v0x, v0y, v1x, v1y, v2x, v2y;
	float x[3], y[3]; 
	float high,
		  low,
		  left = 10000, 
		  right = 0;

	//Get each Triangle and try to fill it in with a solid colour
	for(int i = 0; i < newModel.GetTCount(); i++)
	{
		v0 = newModel.GetV0(i);
		v1 = newModel.GetV1(i);
		v2 = newModel.GetV2(i);

		v0x = v0.GetPX(), v0y = v0.GetPY();
		v1x = v1.GetPX(), v1y = v1.GetPY();
		v2x = v2.GetPX(), v2y = v2.GetPY();

		x[0] = v0x, x[1] = v1x, x[2] = v2x;		
		y[0] = v0y, y[1] = v1y, y[2] = v2y;

		high = right;
		low = left;

		for(int i = 0; i < 3;i ++)
		{
			if (high < y[i]) { high = y[i]; }
			if (low > y[i]) { low = y[i]; }
			if (left > x[i]) {left = x[i]; }
			if (right < x[i]) { right = x[i]; }
		}

		left-=1;

		for (float y0 = low; y0 < high; y0++)
		{
			for (float x0 = left; x0 < right; x0++)
			{

			int j = 2;
			bool odd = false;

				for (int i = 0; i < 3; i++)
				{
					if (y[i] < y0 && y[j] >= y0 || y[j] < y0 && y[i] >= y0)
					{
						if (x[i] + (y0 - y[i]) / (y[j] - y[i]) * (x[j] - x[i]) < x0) 
						{
							odd = !odd; //when theres an intersection odd becomes true or false
						}
					}

					j = i; 
				}

				if (odd)
				{
					SetPixel(bdc,x0,y0,Colour); //Fill Triangle If Possible
				}
			}
		}
	}
}
