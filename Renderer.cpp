
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


void PutPixel(const IntPoint InPt)
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
	SetColor(255, 0, 0);

	// Draw a circle with radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	int nradius = (int)radius;

	Matrix2 scaleMat;
	scaleMat.SetScale(2.0f, 0.5f);

	Matrix2 rotMat;
	rotMat.SetRotation(30.0f);

	Matrix2 SRMat = scaleMat*rotMat;
	Matrix2 RSMat = rotMat*scaleMat;

	Vector2 startVec(radius, 0.0f);
	Vector2 startVec1(radius, 0.0f);
	Vector2 startVec2(radius, 0.0f);

	static float degree = 0;
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix2 rotMat1;
	rotMat1.SetRotation(degree);
	

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
			PutPixel(Vector2(i, j)*rotMat1);
		}
	}


	for (int i = 0; i < 360; i++)
	{
		//Matrix2 rotMat;
		//rotMat.SetRotation(float(i));
		//PutPixel(startVec*rotMat);
	}

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
		
			IntPoint pt(i, j);//ÇÈ¼¿ÀÇÁÂÇ¥
			Vector2 ptVec = pt.ToVector2();
			if (Vector2::DistSquared(center, ptVec) <= radius*radius)
			{
				//IntPoint scaledPt(ptVec*scaleMat);
				//PutPixel(scaledPt);

				//PutPixel(pt);

				//IntPoint rotatedPt(ptVec*rotMat);
				//PutPixel(rotatedPt);

				//IntPoint RSPT(ptVec*RSMat);
				//PutPixel(RSPT);
				
			}
		}
	}
	

	// Buffer Swap 
	BufferSwap();
}
