// d3d.cpp: implementation of the d3d class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern draw drawing;
extern debug debugger;
#define errorcheck(blah,message) if (FAILED(h=blah)) {char *error=GetError(h);debugger.logdata(message);debugger.logdata(error);}
char *GetError(int error2) {
	char *error;
	switch (error2) {
		case D3DERR_INVALIDCALL: error="Invalid call";break;
		case D3DERR_NOTAVAILABLE:error="Your comp sucks too much to run D3D";break;
		case D3DERR_OUTOFVIDEOMEMORY:error="Out of video memory";break;
		default:error="Unknown Error";break;
	}
	return error;
}
d3d::d3d()
{
	direct3d=NULL;
	device=NULL;
	adaptercount=0;
}

d3d::~d3d()
{
	if (trianglebuffer!=NULL)
		trianglebuffer->Release();
	if (device!=NULL)
		device->Release();
	if( direct3d != NULL)
        direct3d->Release();
}

void d3d::initialize(HWND hwnd) {
	int error =  0;
	
	bool running=true;
	char *message = NULL;
	if (NULL == (direct3d = Direct3DCreate9(D3D_SDK_VERSION))) {//Creates D3D object
		MessageBox(NULL,"Couldn't create D3D","Error",0);
		running = false;//Program can't work if D3D isn't working
	}
	if (running) {

		if (FAILED(direct3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&displaymode))) {
			MessageBox(NULL,"Couldn't get info on your display mode adapter.","Environment = teh screwed",0);
			running = false;
		}
		D3DPRESENT_PARAMETERS d3dpp; //Get parameters working
		ZeroMemory( &d3dpp, sizeof(d3dpp) );
		d3dpp.Windowed = FALSE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		d3dpp.BackBufferFormat = displaymode.Format;
		d3dpp.BackBufferWidth = 640;
		d3dpp.BackBufferHeight = 480;
		d3dpp.BackBufferCount = 3;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


		if (running) {
			//Test if we can make a HAL device
			if (SUCCEEDED(error = direct3d->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,displaymode.Format,displaymode.Format,TRUE))) {
				if( FAILED( error = direct3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,//Make device for D3D
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &device ) ) ) //Continuing...
					//D3D sets backbuffercount value in paramaters to what is possible, and fails. Try again with new count...
					if( FAILED( error = direct3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,//Make device for D3D
						D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &device ) ) ) {
					message = GetError(error);
					debugger.logdata("D3D device initialization failed");
					debugger.logdata(message);
					running = false;
				}
			} else {
				message = GetError(error);
				debugger.logdata("Hardware Abstraction Layer device can't be made on your comp");
				debugger.logdata(message);
				running = false;
			}
		}
	}
	
	
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	device->SetRenderState( D3DRS_LIGHTING, FALSE );
	
}
void d3d::Clear(void) {
	HRESULT h;
	if (FAILED(h=device->Clear(NULL,NULL,D3DCLEAR_TARGET,D3DCOLOR_ARGB(0,0,0,0),1.0f,NULL))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't clear screen:");
		debugger.logdata(error);
	}
}

void d3d::Flip(void) {
	HRESULT h;
	if (FAILED(h=device->Present(NULL,NULL,NULL,NULL))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't present screen:");
		debugger.logdata(error);
	}
}

void d3d::Triangle(vertex vertexes[3]) {

	HRESULT h;
	if (FAILED(h=device->SetStreamSource( 0, trianglebuffer, 0, sizeof(vertex) ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't set stream source");
		debugger.logdata(error);
	}
	if (FAILED(h=device->SetFVF( D3DFVF_VERTEX ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't set FVF");
		debugger.logdata(error);
	}
	if (FAILED(h=device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't draw triangle");
		debugger.logdata(error);
	}
}

void d3d::Start(void) {
	HRESULT h;
	if (FAILED(h=device->BeginScene())) {
		char *error = GetError(h);
		debugger.logdata("Couldn't start scene to be rendered");
		debugger.logdata(error);
	}
}
void d3d::End(void) {
	HRESULT h;
	if (FAILED(h=device->EndScene())) {
		char *error = GetError(h);
		debugger.logdata("Couldn't end scene rendering");
		debugger.logdata(error);
	}
}
/*
void d3d::SetMatrixes(void) {
	// For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

    // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
    // every 1000 ms. To avoid the loss of precision inherent in very high 
    // floating point numbers, the system time is modulated by the rotation 
    // period before conversion to a radian angle.
    UINT  iTime  = timeGetTime() % 1000;
    FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
    D3DXMatrixRotationY( &matWorld, fAngle );
    device->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    device->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    device->SetTransform( D3DTS_PROJECTION, &matProj );
}*/