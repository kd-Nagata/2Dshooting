#pragma once

#include "../Enum/TextureType.h"

class TextureManager
{
public:

	// テクスチャのアドレスを返す関数
	KdTexture* GetTexture(TextureType type, std::string fileName);

private:

	std::string GetBasePath(TextureType type)const;

private:

	// 画像のリスト
	std::unordered_map<std::string, KdTexture> m_textureCache;

};