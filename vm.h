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

	void unmark()
	{
		marked=false;
	}


	VM()
	{
		marked=false;
	}
};


#endif /* GROUP_H */
