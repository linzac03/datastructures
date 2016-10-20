#include <list>
#include <iostream>

using namespace std;

list<int> genPlayers(int n) {
	list<int> ret;
	for (int i = 1; i <= n; i++) {
		ret.push_back(i);
	}
	return ret;
}

void play(list<int> ps, list<int> rs, int m, int n) {
	list<int>::iterator itr;
	list<int>::iterator potato = ps.begin();
	while (ps.size() > 1) {
		for (int i = 0; i < m; i++){ 
			if (potato != --ps.end()) {
				potato++;
			} else {
				potato = ps.begin();
			}
		}
		rs.push_back(*potato);
		itr = potato;
		++potato;
		ps.remove(*itr);
	  	
	}
	cout << "Removed: ";
	for (itr = rs.begin(); itr != rs.end(); itr++) {
		cout << *itr << ' ';	
	}
	cout << endl;
	cout << "Winner: " << ps.front() << endl;
}

int main (int argc, char **argv) {
	int m;
	int n;
	list<int> players;
	list<int> removed;
	if (argc != 3) {
		cout << 
			"Requires only two arguments: number of passes and number of players"
		<< endl;
		return -1;
	}
	m = isdigit(argv[1][0]) ? atoi(argv[1]) : -1;
	n = isdigit(argv[2][0]) ? atoi(argv[2]) : -1;
	if (m == -1 || n == -1) {
		cout << 
			"Error: an argument wasn't a number"
		<< endl;
		return -1;
	}
	players = genPlayers(n);
	play(players, removed, m, n);
	return 0;
}
