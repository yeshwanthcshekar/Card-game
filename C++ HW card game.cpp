//Yeshwanth Chandrashekaraiah
//645047527

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
using namespace std;


class game {
public:
	vector<string> deck;
	ofstream odata;
	int n;
	game(int i) { n = i; }
	vector<list<string>*> setup_game(void);
	int compare(vector<string>V);
	void casino(vector<list<string>*>& P);
	int help(vector<list<string>*>& P);
};
vector<string>C;
vector<list<string>*> game::setup_game(void) {
	vector<list<string>*>V;
	list<string>* p;
	int k = 1, l = 1;		//change k to change the dealer
	string s;
	deck = { "KC", "QC", "JC", "10C", "9C", "8C", "7C", "6C", "5C", "4C", "3C", "2C", "AC", "KD", "QD", "JD", "10D", "9D", "8D", "7D", "6D", "5D", "4D", "3D", "2D", "AD", "KH", "QH", "JH", "10H", "9H", "8H", "7H", "6H", "5H", "4H", "3H", "2H", "AH", "KS", "QS", "JS", "10S", "9S", "8S", "7S", "6S", "5S", "4S", "3S", "2S", "AS" };
	odata << endl << " ************** initial deck of cards before shuffle ************** " << endl << endl;
	for (string i : deck) {
		odata << i << " ";
	}
	odata << endl << endl;
	random_shuffle(deck.begin(), deck.end());
	odata << " ************** after shuffle ************** " << endl << endl;
	for (string i : deck) {
		odata << i << " ";
	}
	odata << endl << endl;
	for (int i = 1; i <= n; i++) {
		list<string>* j = new list<string>;
		V.push_back(j);
	}
	//initially player 1 is the dealer and hence the card dealing starts from player 2. 
	//We can decide who gets the first card from 'k'

	for (int i = 1; i <= 52; i++) {
		s = deck.back();
		deck.pop_back();
		p = V[k];
		p->push_back(s);
		k++;
		if (k >= n)k = 0;
	}
	for (auto i : V) {
		odata << "Cards for Player " << l << endl;
		auto k = i->begin();
		while (k != i->end()) {
			odata << *k << "  ";
			k++;
		}
		l++;
		odata << endl << endl;
	}
	return V;
}

void game::casino(vector<list<string>*>& P) {
	vector<string> table, copy;
	string s;
	int count = 0, size = 0, index = 0, m = 1, k = 0, j = 0, equal = 0;
	bool stop = true;
	size = P.size();
	auto it = P.begin();
	while (stop != false) {

		for (auto p : P) {
			auto k = p->begin();
			odata << "Hand " << m << endl;
			while (k != p->end()) {
				odata << *k << " ";
				k++;
			}
			m++;
			odata << endl;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}
		for (auto pt : P) {
			if (pt->size() != 0) {
				s = pt->front();
				pt->pop_front();
				table.push_back(s);
			}
			else if (pt->size() == 0) {
				s = "00";
				table.push_back(s);
			}
			odata << "Table " << m << endl;
			if (pt->size() != 0)odata << s << endl << endl;
			else odata << "  " << endl;
			m++;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}
		index = compare(table);

		auto ite = table.begin();
		for (int z = 0; z < table.size();) {
			string s1 = table[z];
			string s2 = "00";
			int c = s1.compare(s2);
			if (c == 0) {
				table.erase(ite);
				z = 0;
				ite = table.begin();
			}
			else { ite++; z++; }
		}
		if (index != -1) {
			for (auto v : table) {
				P[index]->push_back(v);
				//random_shuffle(P[index]->begin(), P[index]->end());
			}
		}
		else if (index == -1) {
			for (auto i : table) {
				C.push_back(i);
			}
			index = help(P);
		}
		table.clear();
		if (index != -1) {
			auto x = P[index];
			int i = 0;
			list<string>::iterator it = x->begin();
			while (it != x->end()) {
				copy.push_back(*it);
				it++;
				i++;
			}
			random_shuffle(copy.begin(), copy.end());
			it = x->begin();
			i = 0;
			auto vec = copy.begin();
			while (vec != copy.end()) {
				*it = copy[i];
				vec++;
				i++;
				it++;
			}
			copy.clear();
		}
		else equal++;
		for (auto sze : P) {
			k = sze->size();
			if (k == 0) {
				count++;
			}
			if (count == (size - 2)) {
				for (auto o : P) {
					j = o->size();
					if ((j != 0) && (j <= 5)) {
						stop = false;
					}
				}
			}
		}
		count = 0;
	}
	for (auto p : P) {
		auto k = p->begin();
		odata << "Hand " << m << endl;
		while (k != p->end()) {
			odata << *k << " ";
			k++;
		}
		m++;
		odata << endl;
		if (m > size) {
			m = 1;
			odata << endl << endl;
		}
	}
	int winner = -1;
	for (auto i : P) {
		size = i->size();
		winner++;
		if (size > 5)break;
	}
	odata << "Game Over!!  The winner is player " << winner + 1 << endl << endl;
	int runner = -1;
	for (auto i : P)
	{
		runner++;
		size = i->size();
		if (size == 5)break;
	}
	auto pj = P[winner];
	auto kj = P[runner];
	auto lk = kj->begin();
	while (lk != kj->end()) {
		pj->push_back(*lk);
		lk++;
	}
	int kj_size = kj->size();
	while (kj_size != 0) {
		kj->pop_back();
		kj_size = kj->size();
	}

	size = P.size();
	for (auto p : P) {
		auto k = p->begin();
		odata << "Final Hand " << m << endl;
		while (k != p->end()) {
			odata << *k << " ";
			k++;
		}
		m++;
		odata << endl;
		if (m > size) {
			m = 1;
			odata << endl << endl;
		}
	}
}

int game::help(vector<list<string>*>& P) {
	string s1, s2;
	vector<int> index;
	vector<string> copy, N;
	int num = 1, ind1 = 999, ind2 = 999, l = 999, f_k = 999, m = 1;
	char temp, comp;
	int size = 0, a = 0, b = 0;
	size = P.size();
	for (auto p : P) {
		auto k = p->begin();
		odata << "Hand " << m << endl;
		while (k != p->end()) {
			odata << *k << " ";
			k++;
		}
		m++;
		odata << endl;
		if (m > size) {
			m = 1;
			odata << endl << endl;
		}
	}
	for (int i = 0; i < C.size(); i++) {
		s1 = C[i];
		s1 = s1[0];
		for (int j = i + 1; j < C.size(); j++) {
			s2 = C[j];
			s2 = s2[0];
			num = s1.compare(s2);
			if (num == 0) {
				s1 = C[i];
				s2 = C[j];
				index.push_back(i);
				index.push_back(j);
				copy.push_back(s1);
				copy.push_back(s2);
			}
		}
	}
	if (copy.size() > 2) {
		s1 = copy[1];
		temp = s1[0];
		s2 = copy[2];
		comp = s2[0];
		if (temp == '1') {
			if (s1[1] == '0') {
				a = 10;
			}
		}
		if (comp == '1') {
			if (s2[1] == '0') {
				b = 10;
			}
		}
		if ((temp == 'A') || (temp == 'K') || (temp == 'Q') || (temp == 'J')) {
			if (temp == 'A') a = 1;
			else if (temp == 'K') a = 13;
			else if (temp == 'Q') a = 12;
			else if (temp == 'J') a = 11;
		}
		else if (a != 10)a = temp - 48;
		if ((comp == 'A') || (comp == 'K') || (comp == 'Q') || (comp == 'J')) {
			if (comp == 'A') b = 1;
			else if (comp == 'K') b = 13;
			else if (comp == 'Q') b = 12;
			else if (comp == 'J') b = 11;
		}
		else if (b != 10)b = comp - 48;
		if (a < b) {
			l = 0;
		}
		else  if (a > b)l = 2;

		if (l == 0) f_k = index[0];
		else if (l == 2)f_k = index[2];
		auto it = P[f_k];
		ind1 = f_k;
		if (it->size() < 2) {
			if (l == 0)f_k = index[1];
			else if (l == 2)f_k = index[3];
			ind2 = f_k;
			it = P[ind2];
			for (auto i : N) {
				it->push_back(i);
			}for (auto j : C) {
				it->push_back(j);
			}
			C.clear();
			N.clear();
			if (l == 0)f_k = index[1];
			else if (l == 2)f_k = index[3];
			ind2 = f_k;
			return ind2;
		}
		auto x = it->begin();
		N.push_back(*x);
		x++;
		N.push_back(*x);
		it->pop_front();
		it->pop_front();
		if (l == 0)f_k = index[1];
		else if (l == 2)f_k = index[3];
		it = P[f_k];
		if (it->size() < 2) {
			it = P[ind1];						//card in ind1 is the winner
			for (auto i : N) {
				it->push_back(i);
			}
			for (auto j : C) {
				it->push_back(j);
			}
			C.clear();
			N.clear();
			return ind1;
		}

		ind2 = f_k;
		x = it->begin();
		N.push_back(*x);
		x++;
		N.push_back(*x);
		it->pop_front();
		it->pop_front();

		for (int i = 0; i < C.size(); i++) {
			if ((i != ind1) && (i != ind2)) {
				odata << "Table " << m << endl;
				s1 = C[i];
				odata << s1 << endl;
			}
			else if (i == ind1) {
				odata << "Table " << m << endl;
				for (int j = 0; j < 2; j++) {
					s1 = N[j];
					odata << s1 << " ";
				}
				s1 = C[i];
				odata << s1 << endl;
			}
			else if (i == ind2) {
				odata << "Table " << m << endl;
				for (int j = 2; j < 4; j++) {
					s1 = N[j];
					odata << s1 << " ";
				}
				s1 = C[i];
				odata << s1 << endl;
			}
			m++;
			odata << endl;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}

		for (auto p : P) {								//after popping the tie cards from the list of ties players 
			auto k = p->begin();
			odata << "Hand " << m << endl;
			while (k != p->end()) {
				odata << *k << " ";
				k++;
			}
			m++;
			odata << endl;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}
		s1 = N[1];
		s2 = N[3];
		temp = s1[0];
		comp = s2[0];
		if (temp == '1') {
			if (s1[1] == '0') {
				a = 10;
			}
		}
		if (comp == '1') {
			if (s2[1] == '0') {
				b = 10;
			}
		}
		if ((temp == 'A') || (temp == 'K') || (temp == 'Q') || (temp == 'J')) {
			if (temp == 'A') a = 1;
			else if (temp == 'K') a = 13;
			else if (temp == 'Q') a = 12;
			else if (temp == 'J') a = 11;
		}
		else if (a != 10)a = temp - 48;
		if ((comp == 'A') || (comp == 'K') || (comp == 'Q') || (comp == 'J')) {
			if (comp == 'A') b = 1;
			else if (comp == 'K') b = 13;
			else if (comp == 'Q') b = 12;
			else if (comp == 'J') b = 11;
		}
		else if (b != 10)b = comp - 48;
		if (a < b) {
			it = P[ind1];						//card in ind1 is the winner
			for (auto i : N) {
				it->push_back(i);
			}
			for (auto j : C) {
				it->push_back(j);
			}
		}
		else  if (a > b) {					//card in ind2 is the winner
			it = P[ind2];
			for (auto i : N) {
				it->push_back(i);
			}for (auto j : C) {
				it->push_back(j);
			}

		}
		else if (a == b) {
			int g = P[ind1]->size();
			int f = P[ind2]->size();
			if (g > f) {
				it = P[ind1];						//card in ind1 is the winner
				for (auto i : N) {
					it->push_back(i);
				}
				for (auto j : C) {
					it->push_back(j);
				}
			}
			else if (f > g) {
				it = P[ind2];
				for (auto i : N) {
					it->push_back(i);
				}for (auto j : C) {
					it->push_back(j);
				}
			}
		}
		C.clear();
		N.clear();
		if (a < b)return ind1;
		else return ind2;
	}
	else if (copy.size() == 2) {
		f_k = index[0];
		auto it = P[f_k];
		ind1 = f_k;
		if (it->size() < 2) {
			f_k = index[1];
			ind2 = f_k;
			it = P[ind2];
			for (auto i : N) {
				it->push_back(i);
			}for (auto j : C) {
				it->push_back(j);
			}
			C.clear();
			N.clear();
			f_k = index[1];
			ind2 = f_k;
			return ind2;
		}
		auto x = it->begin();
		N.push_back(*x);
		x++;
		N.push_back(*x);
		it->pop_front();
		it->pop_front();
		f_k = index[1];
		it = P[f_k];
		if (it->size() < 2) {
			it = P[ind1];						//card in ind1 is the winner
			for (auto i : N) {
				it->push_back(i);
			}
			for (auto j : C) {
				it->push_back(j);
			}
			C.clear();
			N.clear();
			return ind1;
		}
		ind2 = f_k;
		x = it->begin();
		N.push_back(*x);
		x++;
		N.push_back(*x);
		it->pop_front();
		it->pop_front();

		for (int i = 0; i < C.size(); i++) {
			if ((i != ind1) && (i != ind2)) {
				odata << "Table " << m << endl;
				s1 = C[i];
				odata << s1 << endl;
			}
			else if (i == ind1) {
				odata << "Table " << m << endl;
				for (int j = 0; j < 2; j++) {
					s1 = N[j];
					odata << s1 << " ";
				}
				s1 = C[i];
				odata << s1 << endl;
			}
			else if (i == ind2) {
				odata << "Table " << m << endl;
				for (int j = 2; j < 4; j++) {
					s1 = N[j];
					odata << s1 << " ";
				}
				s1 = C[i];
				odata << s1 << endl;
			}
			m++;
			odata << endl;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}

		for (auto p : P) {								//after popping the tie cards from the list of ties players 
			auto k = p->begin();
			odata << "Hand " << m << endl;
			while (k != p->end()) {
				odata << *k << " ";
				k++;
			}
			m++;
			odata << endl;
			if (m > size) {
				m = 1;
				odata << endl << endl;
			}
		}
		s1 = N[1];
		s2 = N[3];
		temp = s1[0];
		comp = s2[0];
		if (temp == '1') {
			if (s1[1] == '0') {
				a = 10;
			}
		}
		if (comp == '1') {
			if (s2[1] == '0') {
				b = 10;
			}
		}
		if ((temp == 'A') || (temp == 'K') || (temp == 'Q') || (temp == 'J')) {
			if (temp == 'A') a = 1;
			else if (temp == 'K') a = 13;
			else if (temp == 'Q') a = 12;
			else if (temp == 'J') a = 11;
		}
		else if (a != 10)a = temp - 48;
		if ((comp == 'A') || (comp == 'K') || (comp == 'Q') || (comp == 'J')) {
			if (comp == 'A') b = 1;
			else if (comp == 'K') b = 13;
			else if (comp == 'Q') b = 12;
			else if (comp == 'J') b = 11;
		}
		else if (b != 10)b = comp - 48;
		if (a < b) {
			it = P[ind1];						//card in ind1 is the winner
			for (auto i : N) {
				it->push_back(i);
			}
			for (auto j : C) {
				it->push_back(j);
			}
		}
		else  if (a > b) {					//card in ind2 is the winner
			it = P[ind2];
			for (auto i : N) {
				it->push_back(i);
			}for (auto j : C) {
				it->push_back(j);
			}

		}
		else if (a == b) {
			int g = P[ind1]->size();
			int f = P[ind2]->size();
			if (g > f) {
				it = P[ind1];						//card in ind1 is the winner
				for (auto i : N) {
					it->push_back(i);
				}
				for (auto j : C) {
					it->push_back(j);
				}
			}
			else if (f > g) {
				it = P[ind2];
				for (auto i : N) {
					it->push_back(i);
				}for (auto j : C) {
					it->push_back(j);
				}
			}
		}
		C.clear();
		N.clear();
		if (a < b)return ind1;
		else return ind2;
	}
}


int game::compare(vector<string>V) {
	int i = 0, index = 0;
	string s1, s2;
	int a = 0, b = 0, compare = 1;
	bool deleted = true;
	vector<string>::iterator it;
	char temp, comp;
	vector <string> copy;
	copy = V;
	if (V.size() == 2) {			//if only 2 cards are played and those two cards are equal. 
		s1 = V[i];
		s2 = V[i + 1];
		temp = s1[0];
		comp = s2[0];
		if (temp == comp) {
			return -1;
		}
	}
	auto ite = V.begin();
	for (int z = 0; z < V.size();) {
		s1 = V[z];
		s2 = "00";
		int c = s1.compare(s2);
		if (c == 0) {
			V.erase(ite);
			z = 0;
			ite = V.begin();
		}
		else { ite++; z++; }
	}

	while (V.size() > 1) {
		a = 0, b = 0;
		if (deleted) {
			it = V.begin();
			i = 0;
		}
		s1 = V[i];
		if ((i + 1) >= V.size()) { return -1; }
		s2 = V[i + 1];
		temp = s1[0];
		if (temp == '1') {
			if (s1[1] == '0') {
				a = 10;
			}
		}
		comp = s2[0];
		if (comp == '1') {
			if (s2[1] == '0') {
				b = 10;
			}
		}
		if ((temp == 'A') || (temp == 'K') || (temp == 'Q') || (temp == 'J')) {
			if (temp == 'A') a = 1;
			else if (temp == 'K') a = 13;
			else if (temp == 'Q') a = 12;
			else if (temp == 'J') a = 11;
		}
		else if (a != 10)a = temp - 48;
		if ((comp == 'A') || (comp == 'K') || (comp == 'Q') || (comp == 'J')) {
			if (comp == 'A') b = 1;
			else if (comp == 'K') b = 13;
			else if (comp == 'Q') b = 12;
			else if (comp == 'J') b = 11;
		}
		else if (b != 10)b = comp - 48;

		if (a < b) {
			V.erase(it + 1);
			deleted = true;
		}
		else if (a > b) {
			V.erase(it);
			deleted = true;
		}
		else if (a == b) {
			i++;
			it++;
			deleted = false;
		}
	}
	s1 = V[0];

	for (int i = 0; i < copy.size(); i++) {		//compares the result after comparing and returns the index of the card in vector
		string s3 = copy[i];
		compare = s3.compare(s1);
		if (compare == 0) {
			index = i;
			break;
		}
	}

	return index;
}

int main()
{

	game G(4);		//change here for number of players.
	G.odata.open("data.txt");
	if (!G.odata) {
		cout << "Error opening file" << endl;
	}
	vector<list<string>*>Q = G.setup_game();
	G.casino(Q);
}

