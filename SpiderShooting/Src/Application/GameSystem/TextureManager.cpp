#include "TextureManager.h"

// 完成！(unique_ptrにすることにより解決)


KdTexture* TextureManager::GetTexture(TextureType type, std::string fileName)
{

	std::string name = fileName;

	// fileNameに拡張子が無ければ.pngを付ける
	if (name.find('.') == std::string::npos)
	{
		name += ".png";
	}

	// ファイルパスの頭の部分を合成
	std::string fullPath = GetBasePath(type) + name;

	auto it = m_textureCache.find(fullPath);
	if (it != m_textureCache.end())
	{
		return it->second.get();
	}

	// キャッシュに無ければ新規でロード
	auto tex = std::make_unique<KdTexture>();
	if (!tex->Load(fullPath))
	{
		return nullptr;
	}

	// コピー/代入禁止でも emplaceとmoveでマップクラスの仲で直接構築
	auto result = m_textureCache.emplace(fullPath, std::move(tex));
	// ↑↑ ここあんまり理解できないから要勉強


	return result.first->second.get();
}

// テクスチャタイプによって頭につけるファイルパスを返す
std::string TextureManager::GetBasePath(TextureType type) const
{
	std::string Base = "Texture/";

	// タイプによってパスを変える
	switch (type)
	{
	case TextureType::Player:	return Base + "Chara/Player/";			break;
	case TextureType::Enemy:	return Base + "Chara/Enemy/";			break;
	case TextureType::Weapon:	return Base + "Weapon/";				break;
	case TextureType::Effect:	return Base + "Effect/";				break;
	case TextureType::Map:		return Base + "Map/";					break;
	case TextureType::Picture:	return Base + "UI/Picture/";			break;
	case TextureType::Button:	return Base + "UI/Button/";				break;
	default: break;
	}

	return " ";
}
