#ifndef ITEM_H
#define ITEM_H

class Item {
private:
	int m_id;
public:
	Item();
	Item(int id);
	~Item();
	int getId() const;
};

#endif
