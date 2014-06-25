#ifndef PAIR_H
#define PAIR_H
class Pair
{
public:
	Path* primary;
	Path* back;

	Pair(Path* p,Path* b)
	{
		primary=p;
		back=b;
	}
};


#endif /* GROUP_H */
