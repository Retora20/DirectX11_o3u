#include "TextureAsset.h"
#include "Renderer.h"
void TextureAsset::Load(std::string filename)
{
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		filename.data(),
		NULL,
		NULL,
		&m_texture,
		NULL);

	assert(m_texture);
}

void TextureAsset::Unload()
{
	m_texture->Release();
}
