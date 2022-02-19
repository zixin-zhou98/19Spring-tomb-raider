#ifndef LINKNODE
#define LINKNODE

template<class Elem> class Link {
public:
	Elem element;
	Link* next;
	Link(Link* nextval = nullptr)
	{
		next = nextval;
	}
	Link(Elem elemval, Link* nextval = nullptr)
	{
		element = elemval;
		next = nextval;
	}
};

#endif
