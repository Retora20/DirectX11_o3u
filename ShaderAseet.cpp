#include "main.h"
#include <io.h>
#include "Renderer.h"
#include "ShaderAseet.h"

void VS_Asset::Load(std::string filename)
{

	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_vs);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	D3DDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		&m_VertexLayout);

	delete[] buffer;
}





void GS_Asset::Load(std::string filename)
{
	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateGeometryShader(buffer, fsize, NULL, &m_gs);
	delete[] buffer;
}




void PS_Asset::Load(std::string filename)
{




	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreatePixelShader(buffer, fsize, NULL, &m_ps);
	delete[] buffer;
}

void VSSKIN_Asset::Load(std::string filename)
{
	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_vs);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 4*12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4*16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	D3DDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		&m_VertexLayout);

	delete[] buffer;
}

void VSPosition_Asset::Load(std::string filename)
{
	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateVertexShader(buffer, fsize, NULL, &m_vs);

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	D3DDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		&m_VertexLayout);

	delete[] buffer;
}

void HS_Asset::Load(std::string filename)
{
	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateHullShader(buffer, fsize, NULL, &m_hs);
	delete[] buffer;
}

void DS_Asset::Load(std::string filename)
{
	FILE* file;
	long int fsize;
	ID3D11Device* D3DDevice = Renderer::GetDevice();

	file = fopen(filename.data(), "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	D3DDevice->CreateDomainShader(buffer, fsize, NULL, &m_ds);
	delete[] buffer;
}
