#include "Inventory.h"

Inventory::Inventory() {
	sf::Texture* texture = ResourceLoader::loadTexture(TextureInfo::inventoryTextureLocation);
	sprite.setTexture(*texture);

	for (int i = 0; i < SIZE; i++) {
		Slot slot;

		slot.setPosition(sf::Vector2f((i * Grid::width), 0.f));

		slots.push_back(slot);
	}
}

void Inventory::setActiveSlot(int slot) {
	if (slot < SIZE && slot > -1) {
		activeSlot = slot;
	}
}

void Inventory::addItem(Block& block) {
	Item item(Item::ItemType::block, block.getId());

	for (auto& slot : slots) {
		if (slot.getAmount() != 0 && slot.getItem().type == item.type && slot.getItem().getId() == item.getId()) {
			slot.addItem();
			return;
		}
	}

	if (currSize < SIZE) {
		for (auto& slot : slots) {
			if (slot.getAmount() == 0) {
				slot.addItem(item);
				currSize++;
				return;
			}
		}
	}
}

void Inventory::addItem(Item& item) {
	for (auto& slot : slots) {
		if (slot.getAmount() != 0 && slot.getItem().type == item.type && slot.getItem().getId() == item.getId()) {
			slot.addItem();
			return;
		}
	}

	if (currSize < SIZE) {
		for (auto& slot : slots) {
			if (slot.getAmount() == 0) {
				slot.addItem(item);
				currSize++;
				return;
			}
		}
	}
}

void Inventory::addItem(Item::ItemType type, int id) {
	for (auto& slot : slots) {
		if (slot.getAmount() != 0 && slot.getItem().type == type && slot.getItem().getId() == id) {
			slot.addItem();
			return;
		}
	}

	if (currSize < SIZE) {
		for (auto& slot : slots) {
			if (slot.getAmount() == 0) {
				Item newItem(type, id);
				slot.addItem(newItem);
				currSize++;
				return;
			}
		}
	}
}

void Inventory::removeItem(Item& item) {
	for (auto& slot : slots) {
		if (slot.getAmount() != 0 && slot.getItem().type == item.type && slot.getItem().getId() == item.getId()) {
			slot.removeItem();
			if (slot.getAmount() == 0) {
				currSize--;
			}
			return;
		}
	}
}

void Inventory::draw(sf::RenderWindow& window) {
	for (auto& slot : slots) {
		slot.draw(window);
	}
}