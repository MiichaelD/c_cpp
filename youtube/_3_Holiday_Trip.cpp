/*
	Description:	Given the function: bool isPossible(int numCities, int numDays){  }
					validate if you can make trip visiting all the cities within the total 
					number of days.

	Rules:			- You have to be at least a day in a city.
					- Cities are ordered from city 0 to N-1. You can only visit them in order,
					  that is, you can only visit city 2 right after city 1.
					- Once you leave one city you can't come back to it.
					- You can only stay/visit a city when it is sunny, and you can use the function:
					  bool isSunny(int city, int day) to check what the weather will be like at given
					  city and given day.
	
	Example:		City:    Weather per day: (Sunny o Rainy)
					  -		0 	1 	2 	3	4	5
					  0		S 	S 	S 	S 	S 	S
					  1		R 	S 	R 	S 	R 	R
					  2             S 	R 	R 	R 	S 	R
					  3             S 	S 	S 	S 	S 	S

	Programmer:		Michael Duarte

	Date:			Sep 12, 2016.	
*/

#include <iostream>
#include <vector>

using namespace std;

vector<vector<bool>>weather;

void initWeather(int cities, int days){
	// start all days as sunny;
	bool sunny = true;
	weather.clear();
	weather.reserve(cities);
	for(int i = 0; i < cities; ++i){
		weather.emplace_back(days, sunny);
	}

	weather[1][0] = false;
	weather[1][2] = false;
	weather[1][4] = false;
	weather[1][5] = false;

	weather[2][1] = false;
	weather[2][2] = false;
	weather[2][3] = false;
	weather[2][5] = false;

	// weather[3][5] = false;
}

bool isSunny(int city, int day){
	return weather[city][day];
}

bool canTravel(int city, int day, int lastCity, int lastDay, vector<vector<bool>> &cache){
	// for (int i = 0 ; i < day; ++i) cout << "  ";
	if (isSunny(city, day)){
		// cout << "Staying in city: " << city << " for the day: " << day << endl;
		if (city == lastCity) return true; // we completed all the cities!!
		if (day == lastDay) return false; // we ran out of days
		if (cache[city][day]) return false; // we already checked this city in this day
		int pendingCities = lastCity - city;
		int remainingDays = lastDay - day;
		if (remainingDays < pendingCities) return false; // we will run out of days eventually


		bool res = canTravel(city+1, day+1, lastCity, lastDay, cache);
		return res ? res : canTravel(city, day+1, lastCity, lastDay, cache);
	}
	// else {
	// 	cout << "CANNOT stay in city: " << city << " for the day: " << day << endl;
	// }

	// never check again this city and day again, we know it is not possible
	cache[city][day] = true; 
	return false;
}

bool isPossible(int cities, int days){
	vector<vector<bool>> cache(cities, vector<bool>(days,false));
	return canTravel(0, 0, cities-1, days-1, cache);
}

int main(){
	int cities = 4, days = 6;
	initWeather(cities, days);

	bool possible = isPossible(cities, days);
	cout << (possible? "Trip can be completed" : "Trip is impossible to be completed") << endl;
	return EXIT_SUCCESS;
}
