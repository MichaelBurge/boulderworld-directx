// triangle.cpp: implementation of the triangle class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
triangle::triangle(int format,int size,void *data,IDirect3DDevice9 *thedevice) {
	HRESULT h;
	pointformat=format;
	thingsize=size;
	debugger.SetFile("triangle.txt");
	vertexes = new char[size*3];
	memcpy((char*)vertexes,data,size*3);
	device=thedevice;
	if (FAILED(h=device->CreateVertexBuffer(3*size,0,format,D3DPOOL_DEFAULT,&vertexbuffer,0))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't create vertex buffer in Triangle function");
		debugger.logdata(error);
	}
	void* pVertices;
	if( FAILED(h= vertexbuffer->Lock( 0, size*3, (void**)&pVertices, 0 ) ) ) {
		char *error = GetError(h);
		debugger.logdata("Couldn't create lock vertex buffer in triangle function");
		debugger.logdata(error);
	}
	
	memcpy( pVertices, vertexes, 3*size );
	if (FAILED(h=vertexbuffer->Unlock())) {
		char *error = GetError(h);
		debugger.logdata("Couldn't unlock vertex buffer");
		debugger.logdata(error);
	}
}
int triangle::Draw(void) {
	HRESULT h;
	if (FAILED(h=device->SetStreamSource( 0, vertexbuffer, 0, thingsize*3 ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't set stream source");
		debugger.logdata(error);
	}
	else if (FAILED(h=device->SetFVF( pointformat ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't set FVF");
		debugger.logdata(error);
	}
	else if (FAILED(h=device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 ))) {
		char *error = GetError(h);
		debugger.logdata("Couldn't draw triangle");
		debugger.logdata(error);
	}
	return h;
}
triangle::~triangle()
{
	vertexbuffer->Release();
}
