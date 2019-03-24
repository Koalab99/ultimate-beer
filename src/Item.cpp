#include <Item.h>

Item::Item() {
	m_id = 0;
}

Item::Item(int id) {
	m_id = id;
}

Item::~Item() {
	
}

int Item::getId() const {
	return m_id;
}
