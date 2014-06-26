#ifndef VM_H
#define VM_H
class VM
{
public:
	bool marked;

	void mark()
	{
		marked=true;
	}

	VM()
	{
		marked=false;
	}
};


#endif /* GROUP_H */
