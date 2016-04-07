// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)
#define REPORT_SORTING showMeResultOfSorting(mapOfSex)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);
void showMeResultOfSorting (map <_sex, vector <Slav *> >);

void containers(Slav *, int);
void adapters(Slav *, int);
void sorting(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sorting(slavs, n);
	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	srand(time(NULL));
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	vectorOfSlavs.push_back(slavs);

	// Umieść Słowian w losowej kolejności w wektorze.
	for (int i = 1; i < n; i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin() + rand()%vectorOfSlavs.size(),slavs+i);


	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze

	for (vector<Slav *>::iterator itr = vectorOfSlavs.begin(); itr != vectorOfSlavs.end(); itr++)
		cout << (*itr)->description() << endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.

	for (int i = 0; !vectorOfSlavs.empty(); i++)
	{
		setOfSlavs.insert(vectorOfSlavs[i]);
		vectorOfSlavs.pop_back();
	}
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór

	for (set<Slav *>::iterator itr = setOfSlavs.begin(); !setOfSlavs.empty() ;)
	{
		mapOfSlavs[*itr++]=*itr--;
		setOfSlavs.erase(itr++);
		setOfSlavs.erase(itr++);
	}

	// Wykorzystując iterator, wyświetl wszystkie pary Słowian

	for (map<Slav *, Slav *>::iterator itr = mapOfSlavs.begin(); itr != mapOfSlavs.end() ; itr++)
	{
		cout << (*itr).first->description() <<"\t\ti\t"<< (*itr).second->description() << endl;
	}

	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	
	for (int i = 0; i < n; i++)
	{
		queueOfSlavs.push(slavs++);	
	}

	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.

	while (!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	while (!stackOfSlavs.empty())
	{
		cout << (stackOfSlavs.top())->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void sorting (Slav * slavs, int n)
{
	map <_sex, vector <Slav *> > mapOfSex;
	printf("# Sorting\n");
	for (int i = 0; i < n; i++)
	{
		(slavs+i)->sex()==male?
			mapOfSex[male].push_back(slavs+i):
			mapOfSex[female].push_back(slavs+i);
	}

	REPORT_SORTING;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav *> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}

void showMeResultOfSorting(map <_sex, vector <Slav *> > mapOfSex)
{
	cout << "men: " << endl;
	for (vector<Slav *>::iterator itr = mapOfSex[male].begin(); itr != mapOfSex[male].end(); itr++)
		cout << (*itr)->description() << endl;
	
	cout << "women: " << endl;
	for (vector<Slav *>::iterator itr = mapOfSex[female].begin(); itr != mapOfSex[female].end(); itr++)
		cout << (*itr)->description() << endl;
}