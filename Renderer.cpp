
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& InPt)
{
	PutPixel(InPt.X, InPt.Y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	

	// Draw a filled circle with radius 100
	Vector3 center(0.0f, 0.0f);
	float radius = 30.0f;
	int nradius = (int)radius;

	float radius2 = 10.0f;
	int nradius2 = (int)radius2;

	static float degree = 0;
	degree += 1;
	degree = fmodf(degree, 360.0f);

	Matrix3 rotMat;
	rotMat.SetRotation(degree);
	rotMat.Transpose();

	float maxScale = 1;
	float scale = ((sinf(Deg2Rad(degree * 2)) + 2) * 0.5) * maxScale;
	if (scale < 0.5f) scale = 0.5f;

	Matrix3 scaleMat;
	scaleMat.SetScale(scale, scale, scale);

	float maxPos = 150;
	float pos = sinf(Deg2Rad(degree)) * maxPos;

	Matrix3 translationMat;
	translationMat.SetTranslation(pos, pos);

	
	Matrix3 SR = scaleMat * rotMat;
	Matrix3 TRS = translationMat * rotMat * scaleMat;


	Matrix3 mat1;
	mat1.SetTranslation( 200, 0 );

	Matrix3 mat2;
	mat2.SetTranslation( 100, 0 );
	
	static float num1 = 0.0f;
	num1 += 1.0f;
	num1 = fmodf( num1, 360 );

	static float num2 = 360.0f;
	num2 -= 1.5f;
	num2 = fmodf( num2, 360 );

	Matrix3 aa; 
	aa.SetRotation( num1 );
	Matrix3 bb;
	bb.SetRotation( num2 );

	static int r;
	static int g;
	static int b;

	static float count;

	count += 0.1f;
	
	if( count >= 10.0f ) {
		r += 10;
		if( r > 255 )
			r = 20;
		g += 20;
		if( g > 255 )
			g = 10;
		b += 30;
		if( b > 255 )
			b = 50;
	}

	SetColor( r, g, b );

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
			PutPixel(Vector3((float)i, (float)j) *SR );
		}
	}

	if( count >= 10.0f ) {
		r += 10;
		if( r > 255 )
			r = 0;
		g += 20;
		if( g > 255 )
			g = 0;
		b += 30;
		if( b > 255 )
			b = 0;
	}

	SetColor( g, b, r );

	for( int i = -nradius; i <= nradius; i++ ) {
		for( int j = -nradius; j <= nradius; j++ ) {
			Vector3 vertex( i, j );
			if( Vector3::Dist( center, vertex ) <= radius )
				PutPixel( Vector3( i, j ) *mat1*aa);
		}
	}

	if( count >= 10.0f ) {
		r += 10;
		if( r > 255 )
			r = 0;
		g += 20;
		if( g > 255 )
			g = 0;
		b += 30;
		if( b > 255 )
			b = 0;
	}

	SetColor( b, r, g );

	for( int i = -nradius2; i <= nradius2; i++ ) {
		for( int j = -nradius2; j <= nradius2; j++ ) {
			Vector3 vertex( i, j );
			if( Vector3::Dist( center, vertex ) <= radius2 )
				PutPixel( Vector3( i, j ) *mat2*bb );
		}
	}

	if( count >= 10.0f )
		count = 0;
	// Buffer Swap 
	BufferSwap();
}
