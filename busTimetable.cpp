/*
	C++ 8 lab
	Program for timetable bus creation timetable.
	-- For windows only --
	Ed_Os 2017
*/
 
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <windows.h>
#include <map>
using namespace std;


typedef vector<string>::iterator itString;

struct trip
{
	string route;
	int departureTime, arrivalTime;
	string busType, destination;
	trip():route("666"), departureTime(0), arrivalTime(2017), destination("HELL"), busType("KIROV"){};
	trip(string route, int departureTime, int arrivalTime, string busType, string destination):
		route(route), departureTime(departureTime), arrivalTime(arrivalTime), busType(busType), destination(destination){};
	
	void outputTrip()
	{
		string output = "BUS ROUTE -  ";
		for(int i = 0; i < 10 - route.size(); i++)
			output.push_back(' ');
		output += route;
		output += "| Type";
		for(int i = 0; i < 9 - busType.size(); i++)
			output.push_back(' ');
		output += busType;
		output += "| Destiantion - ";
		for(int i = 0; i < 10 - destination.size(); i++)
			output.push_back(' ');
		output += destination;
		output += "| Departure - ";
		output += (char)(departureTime/36000 + '0');
		output += (char)((departureTime/3600) % 10 + '0');
		output += ':';
		output += (char)((departureTime%3600)/ 600 + '0');
		output += (char)(((departureTime%3600)/ 600 ) % 10 + '0');
		output += "| Arrival - ";
		output += (char)(arrivalTime/36000 + '0');
		output += (char)((arrivalTime/3600) % 10 + '0');
		output += ':';
		output += (char)((arrivalTime%3600)/ 600 + '0');
		output += (char)(((arrivalTime%3600)/ 600 ) % 10 + '0');
		cout << output;
	};
};	

vector<trip*> timetable;
map<string, string> helpDescription;
map<string, void(*)(itString, itString)> functions; 


int toSeconds(string s)
{
	if(s.size() < 4 || s.size() > 5)
		return -1;
	if(s.size() < 5)
		s.insert(s.begin(),'0');
	if((s[0] < '0' || s[0] > '9') || (s[1] < '0' || s[1] > '9') || s[2] != ':'
	 || (s[3] < '0' || s[3] > '9') || (s[4] < '0' || s[4] > '9'))
		return -1;
	if(atoi((s.substr(0, 2)).c_str()) > 23 || atoi((s.substr(3, 2)).c_str()) > 59)
		return -1;
	return atoi((s.substr(0, 2)).c_str()) * 3600 + atoi((s.substr(3, 2)).c_str()) * 60;
}

void addToTimeTable(vector<trip*> &g, trip *x)
{
	g.push_back(x);
}

void outputTimetable(vector<trip*> &g)
{
	system("cls");
	cout << "|---------------------------------------------  Timetable ---------------------------------------------| " << endl;
	for(trip* x: g)
	{
		cout << "| ";
		x->outputTrip();
		cout << " |\n";
	}
	cout << "|------------------------------------------------------------------------------------------------------| " << endl;
}

void outputCommandList()
{
	for(pair<string, string> s: helpDescription)
		cout << s.first << " -- " << s.second << "\n\n";
}
void gaben(itString	begin, itString end);

void helpFunction(itString begin, itString end)
{
	if(begin != end)
	{
		cout << "RLY? Try somthing else\n";
		return;
	}
	outputCommandList();
}
bool comp1(trip a, trip b)
{
	return a.route < b.route;
}

bool comp2(trip a, trip b)
{
	return a.arrivalTime < b.arrivalTime;
}

bool comp3(trip a, trip b)
{
	return a.departureTime < b.departureTime;
}

void sortTrips(vector<trip*> &g, bool (*comprasion)(trip, trip))
{
	for(int i = 0;i < g.size() - 1; i++)
	{
		int minIndex = i;
		for(int j = i + 1; j < g.size(); j++)
			if((*comprasion)(*g[j], *g[minIndex]))
				minIndex = j;
		//cout << i << " " << minIndex << endl;
		swap(g[i], g[minIndex]);
	}
}

void sortFullTimetable(itString begin, itString end)
{
	if(begin == end)
	{
		cout << "Invalid arrgs\n";
		return;
	}
	
	if(*begin != "by")
	{
		cout << "Invalid arrgs\n";
		return;
	}
	begin++;
	if(begin == end)
	{
		cout << "Invalid arrgs\n";
		return;
	}
	
	if(*begin == "route")
	{
		begin++;
		if(begin != end)
		{
			cout << "Invalid arrgs\n";
			return;
		}
		sortTrips(timetable, comp1);
		return;
	}
	
	if(*begin == "arrival")
	{
		begin++;
		if(begin != end)
		{
			cout << "Invalid arrgs\n";
			return;
		}
		sortTrips(timetable, comp2);
		return;
	}
	
	if(*begin == "departure")
	{
		begin++;
		if(begin != end)
		{
			cout << "Invalid arrgs\n";
			return;
		}
		sortTrips(timetable, comp3);
		return;
	}
	cout << "Invalid arrgs\n";
}
void findTrips(itString begin, itString end)
{
	string destination, timeChecker;
	int beforeThatTime;
	
	if(begin == end)
	{
		cout << " Destination ? --> ";
		getline(cin, destination);
		cout << " Before ? --> ";
		getline(cin, timeChecker);
		beforeThatTime = toSeconds(timeChecker);
		if(beforeThatTime == -1)
		{
			cout << "Invalid arrgs\n";
			return;
		}	
	}
	else
	{
		beforeThatTime = toSeconds(*begin);
		if(beforeThatTime == -1)
		{
			cout << "Invalid arrgs\n";
			return;
		}
		begin++;
		if(begin == end)
		{
			cout << "Invalid arrgs\n";
			return;
		}
		destination = *begin;
	}
	
	vector<trip*> tempTimetable; 
	
	for(trip* x: timetable)
		if(x->destination == destination && x->departureTime <= beforeThatTime)
			tempTimetable.push_back(x);
			
	if(tempTimetable.empty())
	{
		cout << " Nothing found!\n";
		return;
	}
	sortTrips(tempTimetable, comp3);
	outputTimetable(tempTimetable);
}

void addTrip(itString begin, itString end)
{
	trip *t = new trip();
	string timeChecker;
	cout << " Route ? --> ";
	cin >> t->route;
	cout << " Bus type ? --> ";
	cin >> t->busType;
	while(true)
	{
		cout << " Departure time? --> ";
		cin >> timeChecker;
		t->departureTime = toSeconds(timeChecker);
		if(t->departureTime == -1)
		{
			cout << "Incorrect time. Try again\n";
			continue;
		}
		break;
	}
	
	while(true)
	{
		cout << " Arrival time? --> ";
		cin >> timeChecker;
		t->arrivalTime = toSeconds(timeChecker);
		if(t->arrivalTime == -1)
		{
			cout << "Incorrect time. Try again\n";
			continue;
		}
		break;
	}
	cout << " Destination ? --> ";
	cin >> t->destination;
	addToTimeTable(timetable, t);
	getline(cin, timeChecker);
}

void print(itString begin, itString end)
{
	if(begin == end)
	{
		cout << "NOTHING TO PRINT\n";
		return;
	}
	if(*begin == "all")
	{
		begin++;
		if(begin != end)
		{
			cout << "INVALID ARRGS\n";
			return;
		}
		outputTimetable(timetable);
		return;
	}
}
	
void parse(string s, vector<string> &g)
{
	g.clear();
	string x = "";
	for(char a: s)
		if(a != ' ')
			x.push_back(a);
		else
		{
			if(!x.empty())
				g.push_back(x);
			x.clear();
		}
	if(!x.empty())
		g.push_back(x);
} 

void mainCycle()
{
	vector<string> command;
	while(true)
	{
		cout << " --> ";
		string inputString;
		getline(cin, inputString);
		parse(inputString, command);
		
		if(command.empty())
		{
			cout << "EMPTY COMMAND\n";
			continue;
		}
		if(*command.begin() == "exit")
			return;
		if(functions[*command.begin()] == nullptr)
		{
			cout << "INVALID COMMAND\n";
			continue;
		}
		
		(*functions[*command.begin()])(command.begin() + 1, command.end());	
	}
}

void initializing()
{
	system("color 2");
	system("cls");
	addToTimeTable(timetable, new trip("66", 10000, 15000, "Shiti", "Mogilev"));
	addToTimeTable(timetable, new trip("17a", 9000, 17000, "Slow", "Grodno"));
	cout << "$$$$$ INTERACTIVE BUS TIMETABLE AlPHA 0.0.5 $$$$$ \n\n\n";
	cout << "--------------------\nThis is interactive bus timetable(IBT)\nUse it for creating timetable, watching and editing it.\n--------------------\n";
	cout << "Print \"help\" for information" << endl;
	//Help 
	helpDescription["help"] = " help HERE";
	functions["help"] = &helpFunction;
	//Add
	helpDescription["add"] = " Add's trip to timetale. Add trips one by one. Print exit to end it.\nArrgs:\n NO ARRGS - Full discribe of a trip";
	functions["add"] = &addTrip;
	//Print
	helpDescription["print"] = " Print timetable.\n Arrgs:\n NO ARRGS - NOTHING\n all - print full timetable";
	functions["print"] = &print;
	//Sort
	helpDescription["sort"] = " Sort timetable i think.\n Arrgs:\n NO ARRGS - NOTHING\n by departure - sorts by departure time\n by arrival - sorts by arrival time\n by destination - sorts by destination";
	functions["sort"] = &sortFullTimetable;
	//Found
	helpDescription["find"] = " Displaying all routes with fixed destination.\n Arrgs:\n NO ARRGS - will ask you \n time(HH::MM) + place - will simply find what you want.";
	functions["find"] = &findTrips;
	//???
	functions["gaben"] = &gaben;
}

int main()
{
	//freopen("input","r",stdin);
	initializing();
	mainCycle();
	return 0;
}


void gaben(itString	begin, itString end)
{
	system("cls");
	system("color 3");
	cout << "$ Here your cookies my friend.\n$ You have found me. Who are you?\n";
	string name;
	getline(cin, name);
	system("color 7");
	cout << "$ Hmm rare name.\n$ But i think you still have got a lot of questions\n$ C'mon ask me about anything!\n";
	string something;
	getline(cin, something);
	system("color 12");
	cout << "$ Ohh i forgot\n$ Old memory you know.\n$ It's demo version.\n$ You can buy it just for 0.99$\n$ Bye!\n";
	string wtf;
	getline(cin, wtf);
}
