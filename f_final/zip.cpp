#include <testList.h>
#include <Pair.h>

template <typename Object> 
List<Pair<Object>> zip (const List<Object> & l1, const List<Object> & l2) {
	List<Pair<Object>> out = new List();
	List<Object>::iterator ins = out.begin();
	List<Object>::iterator itr1 = l1.begin();
	List<Object>::iterator itr2 = l2.begin();

	while(itr1 != l1.end() || itr2 != l2.end())	{
		if (itr1 != l1.end() && itr2 != l2.end()) {		
			out.insert(ins++, new Pair(*itr1, *itr2));
			++itr1;
			++itr2;	
		} else if (itr1 != l1.end()) {
			out.insert(ins++, new Pair(*itr1, NULL));
			++itr1;
		} else {	
			out.insert(ins++, new Pair(NULL, *itr2));
			++itr2;	
		} //its not the most elegant code	
	}
	
	return out;
}

template <typename Object> 
Pair<List<Object>> unzip (const List<Pair<Object>> l) {
	List<Object> o1;
	List<Object> o2;
	List<Object>::iterator ins1 = o1.begin();
	List<Object>::iterator ins2 = o2.begin();
	List<Pair<Object>>::iterator itr1 = l.begin();

	while(itr1 != l.end()) {
		o1.insert(ins1++, itr1->first());
		o2.insert(ins2++, itr1->second());
	}

	return new Pair(o1, o2);	
}

