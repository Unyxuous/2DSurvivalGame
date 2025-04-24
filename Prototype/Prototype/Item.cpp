#include "Item.h"

// copy constructor just calls constructor with other item's info
Item::Item(const Item& other) : Item(other.type, other.id) {

}

Item::Item(ItemType type, int id){
	this->type = type;
	this->id = id;

	if (id != 0) {
		if (type == ItemType::block) {
			sprite.setTexture(*ResourceLoader::loadTexture(TextureInfo::blockTextureLocation));
			id--;
			sprite.setTextureRect(sf::IntRect((id % TextureInfo::blockImagesPerLine) * TextureInfo::blockImageWidth, (id / TextureInfo::blockImagesPerLine) * TextureInfo::blockImageHeight, TextureInfo::blockImageWidth, TextureInfo::blockImageHeight));
		}
		else {
			sprite.setTexture(*ResourceLoader::loadTexture(TextureInfo::toolTextureLocation));
			id--;
			sprite.setTextureRect(sf::IntRect((id % TextureInfo::toolImagesPerLine) * TextureInfo::toolImageWidth, (id / TextureInfo::toolImagesPerLine) * TextureInfo::toolImageHeight, TextureInfo::toolImageWidth, TextureInfo::toolImageHeight));
		}
	}
}

void Item::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Item::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}