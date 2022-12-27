#ifndef flightticket_h
#define flightticket_h

//#ifndef FLIGHT_TICKET_H
//#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
private:
	string companyName;
	string flightNumber;
	string country_of_origin;
	string country_of_destination;
	string stopOver;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;

public:
	Flight_Ticket();
	Flight_Ticket(string companyName, string flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
	// Please add additional methods, contructor if needed
	void set_companyName(string company);
	void set_flightNumber(string num);
	void set_country_of_origin(string  origin);
	void set_country_of_destination(string destination);
	void set_stopOver(string stopover);
	void set_price(string price);
	void set_time_of_departure(string departure);
	void set_time_of_arrival(string arrival);
	void set_date(string date);

	string get_companyName();
	string get_flightNumber();
	string get_country_of_origin();
	string get_country_of_destination();
	string get_stopOver();

	string get_price();
	string get_time_of_departure();
	string get_time_of_arrival();
	string get_date();
};

Flight_Ticket::Flight_Ticket() {

}
Flight_Ticket::Flight_Ticket(string companyName, string flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date) {
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
}
// sets companyName
void Flight_Ticket::set_companyName(string company) {
	companyName = company;
}
// sets flight number
void Flight_Ticket::set_flightNumber(string num) {
	flightNumber = num;
}
// sets country of origin 
void Flight_Ticket::set_country_of_origin(string  origin) {
	country_of_origin = origin;
}
// sets country of destination 
void Flight_Ticket::set_country_of_destination(string destination) {
	country_of_destination = destination;
}
// sets stop over
void Flight_Ticket::set_stopOver(string stopover) {
	stopOver = stopover;
}
// sets price
void Flight_Ticket::set_price(string price) {
	this->price = price;
}
// sets time of departure
void Flight_Ticket::set_time_of_departure(string departure) {
	time_of_departure = departure;
}
// sets time of arrival 
void Flight_Ticket::set_time_of_arrival(string arrival) {
	time_of_arrival = arrival;
}
// sets date
void Flight_Ticket::set_date(string date) {
	this->date = date;
}
// returns company name 
string Flight_Ticket::get_companyName() {
	return companyName;
}
// returns flight number
string Flight_Ticket::get_flightNumber() {
	return flightNumber;
}
// returns country of origin 
string Flight_Ticket::get_country_of_origin() {
	return  country_of_origin;
}
// returns country of destination 
string Flight_Ticket::get_country_of_destination() {
	return country_of_destination;
}
// returns stop over
string Flight_Ticket::get_stopOver() {
	return stopOver;
}
// returns price
string Flight_Ticket::get_price() {
	return price;
}
// returns time of departure
string Flight_Ticket::get_time_of_departure() {
	return time_of_departure;
}
// returns time of arrival 
string Flight_Ticket::get_time_of_arrival() {
	return time_of_arrival;
}
// returns date
string Flight_Ticket::get_date() {
	return date;
}

#endif
