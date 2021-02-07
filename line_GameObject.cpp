#include "line_GameObject.h"
#include "LineDrawer.h"
#include "MapAsset.h"
#include "Time.h"
#include <algorithm>
void TitleLine_GameObject::Init()
{
	D3DXCOLOR col[7] =
	{
		{1,0,0,1} ,
		{0,1,0,1} ,
		{0,0,1,1} ,
		{1,1,0,1} ,
		{0,1,1,1} ,
		{1,0,1,1} ,
		{1,1,1,1}
	};


	for (size_t i = 0; i < 14; i++)
	{
		m_Lines.push_back(AddCompoent<LineDrawer>());
		auto cp = m_Lines[i]->GetCP();
		cp->CP_Num = 63;
		float rad = D3DX_PI * 2 / m_Lines.size() * i;
		for (size_t j = 0; j < cp->CP_Num; j++)
		{
			cp->CP[j] = D3DXVECTOR4(sinf(rad), sinf(rad), cosf(rad), 1.0f);
			cp->CP[j] *=30;
		}
		m_Lines[i]->Setcolor(col[i % 7]); 
	}
	float clrcol[4]{0.1,0.1,0.1,1};
	Renderer::SetClearColor(clrcol);

}

void TitleLine_GameObject::Update()
{
	static float r = 0;
	r += Time::GetDeltaTime() * 1.;
	m_scale = (D3DXVECTOR3(1, 1, 1) * ((sinf(Time::GetTime() * 0.5f) * 3) * 2 + 2.0));
	D3DXQuaternionRotationYawPitchRoll(&m_rotation, r, r, 0);

	for (size_t i = 0; i < m_Lines.size(); i++)
	{
		auto cp = m_Lines[i]->GetCP();

		{
			for (int j = cp->CP_Num - 1; j >= 1; j--)
			{
				cp->CP[j] = cp->CP[j - 1];
			}
		}

		float rad = D3DX_PI * 2 / m_Lines.size() * i * (Time::GetTime() * 1.0f);
		cp->CP[0] = D3DXVECTOR4(sinf(rad), sinf(rad*1.1), cosf(rad*1.3), 1.0f);
		cp->CP[0] *= 1 + i / 30;
	}

	ComponentsUpdate();
}

void TitleLine_GameObject::Uninit()
{
	Renderer::SetBlendStateDefault();
}