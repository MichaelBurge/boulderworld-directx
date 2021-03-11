// d3d.h: interface for the d3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_D3D_H__5764EB4B_88F0_421A_AA1D_312B1D599F81__INCLUDED_)
#define AFX_D3D_H__5764EB4B_88F0_421A_AA1D_312B1D599F81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "main.h"
#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
struct vertex {
	FLOAT x, y, z, rhw; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
};
class triangle  
{
	IDirect3DVertexBuffer9 *vertexbuffer;
	IDirect3DDevice9 *device;
	void *vertexes;
	debug debugger;
	int pointformat;
	int thingsize;
public:
	triangle(int format,int size,void *data,IDirect3DDevice9 *device);
	int Draw(void);
	virtual ~triangle();

};
class d3d {
	IDirect3D9 *direct3d;
	
	D3DDISPLAYMODE displaymode;
	deque<triangle> triangles;
	int adaptercount;
public:
	IDirect3DVertexBuffer9 *trianglebuffer;
	IDirect3DDevice9 *device;
	void LoadTexture(char *filename);
	void Start(void);
	void End(void);
	void Clear(void);
	void Flip(void);
	void Triangle(vertex vertexes[3]);
	d3d();
	void initialize(HWND hwnd);
	virtual ~d3d();

};
char *GetError(int error2);
#endif // !defined(AFX_D3D_H__5764EB4B_88F0_421A_AA1D_312B1D599F81__INCLUDED_)
