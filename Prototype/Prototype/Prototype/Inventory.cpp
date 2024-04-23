#include "Inventory.h"

Inventory::Inventory() {
	if (!texture.loadFromFile("./assets/images/inventory.png")) {
		std::cout << "could not load inventory image." << std::endl;
	}

	for (int i = 0; i < SIZE; i++) {
		Slot slot(texture);

		slot.setPosition(sf::Vector2f((i * Grid::width), 0.f));

		slots.push_back(slot);
	}
}

void Inventory::setActiveSlot(int slot) {
	if (slot < SIZE && slot > -1) {
		activeSlot = slot;
	}
}

void Inventory::addItem(Block* block) {
	Item* item = new Item(block->sprite.getTexture(), 4, Item::ItemType::block, block->getId());

	for (auto& slot : slots) {
		if (slot.getItem() != nullptr && slot.getItem()->type == item->type && slot.getItem()->getId() == item->getId()) {
			slot.addItem();
			return;
		}
	}

	if (currSize < SIZE) {
		for (auto& slot : slots) {
			if (slot.getItem() == nullptr) {
				slot.addItem(item);
				currSize++;
				return;
			}
		}
	}
}

void Inventory::addItem(Item item) {
	for (auto& slot : slots) {
		if (slot.getItem() != nullptr && slot.getItem()->type == item.type && slot.getItem()->getId() == item.getId()) {
			slot.addItem();
			return;
		}
	}

	if (currSize < SIZE) {
		for (auto& slot : slots) {
			if (slot.getItem() == nullptr) {
				slot.addItem(&item);
				currSize++;
				return;
			}
		}
	}
}

void Inventory::removeItem(Item item) {
	for (auto& slot : slots) {
		if (slot.getItem() != nullptr && slot.getItem()->type == item.type && slot.getItem()->getId() == item.getId()) {
			slot.removeItem();
			if (slot.getItem() == nullptr) {
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