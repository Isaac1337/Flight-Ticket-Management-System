
#ifndef flighthashtable_h
#define flighthashtable_h


//#ifndef FlightHASHTABLE_H
//#define FlightHASHTABLE_H

#include<iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "flightticket.h"
#include "Mylist.h"
// include additional header files if needed

using namespace std;
using namespace std::chrono;

class HashNode
{
private:
	string key; // key = companyName+flightNumber
	Flight_Ticket value;
public:
	HashNode() {

	}
	HashNode(string key, Flight_Ticket value)
	{
		this->key = key;
		this->value = value;
	}
	// Gets key of hashNode
	string getkey() {
		return this->key;
	}
	// Get value of hashnode
	Flight_Ticket getval() {
		return this->value;
	}
	friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
private:
	Mylist <HashNode>* buckets;				//List of Buckets, Please create your own List Class called MyList
	int size;					    //Current Size of HashTable
	int capacity;				    // Total Capacity of HashTable
	int probes;
	// add more attributes needed
public:
	FlightHASHTABLE();
	FlightHASHTABLE(int capacity);						//constructor
	//~FlightHASHTABLE();						//destructor
	long hashCode(string key); 						//implement and test different hash functions 
	int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
	int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
	int count_collisions();					//return the number of collisions on the HashTable
	int add(Flight_Ticket* data);			//add new flight to the HashTable
	void removeRecord(string companyName, string flightNumber);	//Delete a record with key from the hashtable
	void find(string companyName, string flightNumber);		//Find and Display records with same key entered 
	void allinday(string date);  					//Find and Display records with same day entered
	void printASC(string companyName, string flightNumber);  		//display the collisions for the entered key in an ascending order 

	//Add more methods and contructors, destructors if needed	
};






//constructor
FlightHASHTABLE::FlightHASHTABLE()
{
}
//constructor
FlightHASHTABLE::FlightHASHTABLE(int capacity)
{// creating bucket of linked list
	buckets = new Mylist<HashNode>[capacity];	  //Array of a list/chain
	this->capacity = capacity;
	this->size = 0;
	this->probes = 0;
}
// Generating the hasHcode
long FlightHASHTABLE::hashCode(string key)
{
	/*
	int seed = 131;
	unsigned long b = 0;
	for (int i = 0; i < key.length(); i++)
	{
		b = (b * seed) + key[i];
	}
	return (3 * b + 8) % capacity;
	*/

	/*
	stringstream dan(key);
	int a = 0;
	dan >> a;
	return( 5 * a + 12 ) % capacity;
	
	*/
	unsigned int index = 0;
	for (int i = 0; i < key.size();++i) {
		index = (index << 5) | (index >> 27);
		index += (unsigned int)key[i];
	}
	// returning hashCode
	return ((3 * index + 4) % capacity);
}

//add new flight to the HashTable
int FlightHASHTABLE::add(Flight_Ticket* data) {
	//TODO
	string key = data->get_companyName() + data->get_flightNumber();
	long h = hashCode(key);
	// Creating new Hashnode
	HashNode newNode = HashNode(key, *data);
	if (buckets[h].size() > 0) {
		probes++;
	}
	// Adding flight into the hashTable 
	buckets[h].addBack(newNode);
	// Increasing size of hashNode
	++size;
	return 1;
}
//Load all the flight-tickets from the CSV file to the HashTable
int FlightHASHTABLE::importCSV(string path) {
	// Counter of imported flight tickets
	int count = 0;
	ifstream rl;
	// Openning CSV file to be read from
	rl.open(path);
	// Condition for when file fails to open
	if (rl.fail()) {
		cerr << "Error file does not exist" << endl;
		exit(-1);
	}
	while (!rl.eof()) {
		string line;
		string CN, FN, CO, CD, SO, P, TD, TA, D, key;
		// getting data on a line in th CSV file
		while (getline(rl, line)) {
			// Reading the data into their respective attributes
			stringstream ss(line);
			getline(ss, CN, ',');
			getline(ss, FN, ',');
			getline(ss, CO, ',');
			getline(ss, CD, ',');
			getline(ss, SO, ',');
			getline(ss, P, ',');
			getline(ss, TD, ',');
			getline(ss, TA, ',');
			getline(ss, D, ',');
			if (count >= 1) {
				key = CN + FN;
				// Creating new flight ticket
				Flight_Ticket* T = new Flight_Ticket(CN, FN, CO, CD, SO, P, TD, TA, D);
				// Inserting flight ticket into the hashtable
				add(T);
			}
			break;
		}
		++count;
	}
	// Closing the file 
	rl.close();
	return count - 1;
}
//Find and Display records with same key entered 
void FlightHASHTABLE::find(string companyName, string flightNumber) //search(string key)
{
	//TODO
	string key = companyName + flightNumber;
	// creating hashCode
	long index = hashCode(key);
	int i =0;
	int j = 0;
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		if (it.operator*().getkey() == key) {
			++j;
		}
	}
	// Printing number of records found
	cout << j << " record(s) found" << endl;
	auto start = high_resolution_clock::now();
	// Traversing through the bucket of the key
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		if (it.operator*().getkey() == key) {
			++i;
			// Printing out the details of the matched key
			cout << i << ". " << "Country Name: " << it.operator*().getval().get_companyName() << endl;
			cout << "   Flight Number: " << it.operator*().getval().get_flightNumber() << endl;
			cout << "   Country of Origin: " << it.operator*().getval().get_country_of_origin() << endl;
			cout << "   Country of Destination: " << it.operator*().getval().get_country_of_destination() << endl;
			cout << "   Stop Over: " << it.operator*().getval().get_stopOver() << endl;
			cout << "   Price: " << it.operator*().getval().get_price() << endl;
			cout << "   Time of Departure: " << it.operator*().getval().get_time_of_departure() << endl;
			cout << "   Time of Arrival: " << it.operator*().getval().get_time_of_arrival() << endl;
			cout << "   Date: " << it.operator*().getval().get_date() << endl;
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Find function took: " << duration.count() << " milliseconds" << endl;
}


//Delete a record with key from the hashtable
void FlightHASHTABLE::removeRecord(string companyName, string flightNumber) {
	//TODO
	string key = companyName + flightNumber;
	string s;
	int p = 1;
	int index = hashCode(key);	//Get the index of the bucket
	// Finding the records in the buckek
	int i = 0;
	int k = 0;
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		if (it.operator*().getkey() == key) {
			++k;
		}
	}
	// Printing number of records found
	cout << k<< " record(s) found" << endl;
	// Traversing through the bucket of the key
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		if (it.operator*().getkey() == key) {
			++i;
			// Printing out the details of the matched key
			cout << i << ". " << it.operator*().getval().get_companyName() << "," << it.operator*().getval().get_flightNumber() << "," << it.operator*().getval().get_country_of_origin() << "," << it.operator*().getval().get_country_of_destination() << "," << it.operator*().getval().get_stopOver() << "," << it.operator*().getval().get_price()<< "," << it.operator*().getval().get_time_of_departure() << "," << it.operator*().getval().get_time_of_arrival() << "," << it.operator*().getval().get_date() << endl;
		}
	}
	cout << "Please select the record you want to delete: ";
	cin >> s;
	stringstream num(s);
// Converting the user input into a string
	int x = 0;
	num >> x;
	// Traversing through the bucket
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it)
	{
		if (it.operator*().getkey() == key) {
			if (p == x) {
				buckets[index].remove(it.key());
				return;
			}
			++p;
		}
	}
	cout << "Cant delete....Record Not Found...!" << endl;
}
//Find and Display records with same day entered
void FlightHASHTABLE::allinday(string date) {
	// Travering through the hashTable 
	int cnt = 0;
	for (int i = 0; i < 150001; ++i) {
		for (HashNode it : buckets[i])
		{   // Checking for matched date
			if (it.getval().get_date() == date)
			{
				//Printing the data of the matched date
				cout << ++cnt << ". " << it.getval().get_companyName() << "," << it.getval().get_flightNumber() << "," << it.getval().get_country_of_origin() << "," << it.getval().get_country_of_destination() << "," << it.getval().get_stopOver() << "," << it.getval().get_price() << "," << it.getval().get_time_of_departure() << "," << it.getval().get_time_of_arrival() << "," << it.getval().get_date() << endl;
			}
		}
	}
	if (cnt == 0) {
		cout << "No matched date found" << endl;
	}
	
}
//display the collisions for the entered key in an ascending order 
void FlightHASHTABLE::printASC(string companyName, string flightNumber)
{
	int i = 0;
	int l = 0;
	string key = companyName + flightNumber;
	long index = hashCode(key);
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		if (it.operator*().getkey() == key) {
			++l;
		}
	}
	cout <<l<< " records found" << endl;
	// Creating new array to hold the nodes of flight ticket
	HashNode* flight = new HashNode[l]; //buckets[index].size()
	// Traversing through the bucket
	for (Mylist<HashNode>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
		// Checking for matched key
		if (it.operator*().getkey() == key) {
			// Inserting the nodes into the array
			flight[i] = it.operator*();
			++i;
		}
	}
	// Implementation of the sorting of the array 
	int m;
	HashNode hold;
	for (int k = 0; k <= l - 2; ++k) {
		m = k;
		for (int j = k + 1; j <= l - 1; ++j) {
			if (flight[j].getval().get_country_of_destination() < flight[m].getval().get_country_of_destination()) {
				m = j;
			}
			// Swaping nodes
			hold = flight[m];
			flight[m] = flight[k]; 
			flight[k] = hold;
		}
	}
	// Printing the nodes info in ascending order
	for (int h = 0; h < l; ++h) {
		cout << flight[h].getval().get_companyName() << "," << flight[h].getval().get_flightNumber() << "," << flight[h].getval().get_country_of_origin() << "," << flight[h].getval().get_country_of_destination() << "," << flight[h].getval().get_stopOver() << "," << flight[h].getval().get_price() << "," << flight[h].getval().get_time_of_departure() << "," << flight[h].getval().get_time_of_arrival() << "," << flight[h].getval().get_date() << endl;
	}
}


//Export all the flight-tickets from the HashTable to a CSV file in an ascending order	
int FlightHASHTABLE::exportCSV(string path) {
	int count = 0;
	ofstream wrt;
	// Opening up a new file 
	wrt.open(path);
	if (!wrt) {
		cout << "Can not open the file!" << endl;
		return -1;
	}
	// Traversing the hashtable
	for (int i = 0;i < capacity;i++) {
		if (buckets[i].size() > 0) {
			for (Mylist<HashNode>::iterator p = buckets[i].begin(); p != buckets[i].end(); ++p) {
				++count;
				// writing the flight details into the csv file 
				wrt << p.operator*().getval().get_companyName() << "," << p.operator*().getval().get_flightNumber() << "," << p.operator*().getval().get_country_of_origin() << "," << p.operator*().getval().get_country_of_destination() << "," << p.operator*().getval().get_stopOver() << "," << p.operator*().getval().get_price() << "," << p.operator*().getval().get_time_of_departure() << "," << p.operator*().getval().get_time_of_arrival() << "," << p.operator*().getval().get_date() << endl;
			}
		}
	}
	wrt.close();
	return count;
}





//return the number of collisions on the HashTable
int FlightHASHTABLE::count_collisions() {
	int count = 0;
	// Traversing the hashTable 
	for (int i = 0; i < 150001; ++i) {
		// Checking for collisions 
		if (buckets[i].size() > 1) {
			count += buckets[i].size() - 1;
		}
	}
	//returning number of collision 
	return count;
}



#endif
