#ifndef LLIST
#define LLIST
#include"LinkNode.h"
template<class Elem> class LList :public Link<Elem> {
	//LList<Elem>();
public:
	Link<Elem>* head;
	Link<Elem>* tail;
	Link<Elem>* fence;
	int leftcnt;
	int rightcnt;
	void init();
	void removeall();
	bool insert(const Elem& item);
	bool setPos(int pos);
	bool getValue(Elem*& it);
	bool append(const Elem& item);
	bool remove(Elem& it);
	void setStart();
	void setEnd();
	void prev();
	void next();
	bool swap();
	bool findNdel(Elem value);
	void print() const;
	
};

template<class Elem> void LList<Elem>::init()
{
	head = tail = fence = new Link<Elem>;
	leftcnt = rightcnt = 0;
}
template<class Elem> void LList<Elem>::removeall()
{
	while (head != nullptr)
	{
		fence = head;
		head = head->next;
		delete fence;
	}
}
template<class Elem> bool LList<Elem>::insert(const Elem& item)
{
	//new 是开辟出一段新的地址空间, temp指向这个地址空间（新别墅），fence->next就是定位器
	//定义定位器的下一个别墅为temp指向的新别墅，即temp号别墅
	//	Link<Elem>* temp=new Link<Elem>(item, fence->next);
	//	fence->next = temp;
	//直接指定定位器fence的下一间房为新别墅
	fence->next = new Link<Elem>(item, fence->next);
	if (fence == tail)
		tail = fence->next;
	rightcnt++;
	return true;
}
template<class Elem>bool LList<Elem>::setPos(int pos)
{
	if ((pos < 0) && (pos > leftcnt + rightcnt))
		return false;
	fence = head;
	for (int i = 0; i < pos; i++)
	{
		fence = fence->next;
	}
	rightcnt = leftcnt + rightcnt - pos;
	leftcnt = pos;
	return true;
}
template<class Elem> bool LList<Elem>::getValue(Elem*& it)
{
	if (rightcnt == 0)
		return false;
	*&it = &fence->next->element;
	return true;
}
template<class Elem> bool LList<Elem>::append(const Elem& item)
{
	tail->next = new Link<Elem>(item, nullptr);
	rightcnt++;
	tail = tail->next;
	return true;
}
template<class Elem> bool LList<Elem>::remove(Elem& it)
{
	if (fence->next == nullptr)
		return false;
	it = fence->next->element;
	Link<Elem>* temp = fence->next;
	fence->next = fence->next->next;
	if (tail == temp)
		tail = fence;
	delete temp;
	rightcnt--;
	return true;
}
template<class Elem>void LList<Elem>::setStart()
{
	fence = head;
	rightcnt = leftcnt + rightcnt;
	leftcnt = 0;
}
template<class Elem>void LList<Elem>::setEnd()
{
	fence = tail;
	rightcnt = 0;
	leftcnt = leftcnt + rightcnt;
}
template<class Elem>void LList<Elem>::prev()
{
	Link<Elem>* temp = head;
	if (fence == head)
		return;
	while (temp->next != fence)
		temp = temp->next;
	rightcnt++;
	leftcnt--;
}
template<class Elem>void LList<Elem>::next()
{
	if (fence == tail)
		return;
	fence = fence->next;
	rightcnt--;
	leftcnt++;
}
template<class Elem>bool LList<Elem>::swap()
{
	if ((fence == tail) || (fence->next = tail))
		return false;

	Link<Elem>* temp = fence->next;


	fence->next = temp->next;
	temp->next = fence->next->next;
	fence->next->next = temp;
	if (fence->next == tail)
		tail = tail->next;
}

template<class Elem> bool LList<Elem>::findNdel(Elem value)
{
	//if (leftcnt == 0)
	if (head == tail)
		return false;

	Link<Elem>* temp;
	Link<Elem>* ptr = head;
	bool beforeFence = true;
	while (ptr!=tail)
	{
		if (ptr->next->element == value)
		{
			if (ptr == fence->next)
				beforeFence = false;
			if (ptr->next == tail)
			{
				tail = ptr;
			}
			if (ptr->next == fence)
			{
				fence = ptr;
			}
			temp = ptr->next;
			ptr->next = ptr->next->next;
			delete temp;
			if (beforeFence)
				leftcnt--;
			else
				rightcnt--;
		}
		else
			ptr = ptr->next;
	}
	return true;
}
template<class Elem> void LList<Elem>::print() const
{
	Link<Elem>* temp = head;
	cout << '<';
	while (temp != fence)
	{
		cout << temp->next->element << " ";
		temp = temp->next;
	}
	cout << '|';
	while (temp->next != nullptr)
	{
		cout << temp->next->element << " ";
		temp = temp->next;
	}
	cout << '\n';
}
#endif
