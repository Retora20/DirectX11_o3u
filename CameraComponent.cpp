#include "CameraComponent.h"
#include "Renderer.h"
#include "input.h"
CameraComponent::CameraComponent()
{
}

void CameraComponent::Init()
{
}

void CameraComponent::UnInit()
{
}

void CameraComponent::Update()
{
	Renderer::SetProjectionMatrix(&GetProjectionMatrix());
	Renderer::SetViewMatrix(&GetViewMatrix());
}

D3DXMATRIX CameraComponent::GetProjectionMatrix()
{
	//プロジェクション
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, m_fov, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_near, m_far);
	return projectionMatrix;
}

D3DXMATRIX CameraComponent::GetViewMatrix()
{
	D3DXMATRIX viewMatrix;

	auto gameobject = GetOwnGameObject();

	D3DXMatrixLookAtLH(&viewMatrix, 
		&gameobject->GetPosition(),
		&(gameobject->GetPosition() + gameobject->GetFrontVector()), 
		&gameobject->GetUpVector());

	return viewMatrix;
}

std::pair<D3DXVECTOR3, D3DXVECTOR3> CameraComponent::GetMouseVector()
{
	//逆行
	D3DXMATRIX invvp;
	invvp = GetViewMatrix() * GetProjectionMatrix();
	D3DXMatrixInverse(&invvp, NULL, &invvp);

	D3DXVECTOR3 start, end;
	{
		POINT mousepos = Input::GetMousePos();
		float x, y;
		float w = SCREEN_WIDTH - 10;
		float h = SCREEN_HEIGHT - 10;
		x = (mousepos.x * 2 - w) / float(w);
		y = (mousepos.y * 2 - h) / float(h);

		start.x = x;
		start.y = -y;
		start.z = 0;

		end.x = x;
		end.y = -y;
		end.z = 1;
	}

	D3DXVec3TransformCoord(&start, &start, &invvp);
	D3DXVec3TransformCoord(&end, &end, &invvp);

	end = end - start;
	D3DXVec3Normalize(&end, &end);

	return std::pair<D3DXVECTOR3, D3DXVECTOR3>(start, end);
}
