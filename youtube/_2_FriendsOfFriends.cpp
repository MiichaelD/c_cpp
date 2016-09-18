/*
	Description:	Given a userID, Return a list of suggested friends of friends from a 
					social network.

	Extra:			Sort the friends of friends array in descending order based on the
					amount of friends in common. 

	Programmer:		Michael Duarte

	Date:			Sep 12, 2016.	
*/

#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

typedef unordered_map<string,vector<string>> SocialNetwork; 

bool sortByFriendsInCommon(const pair<string, int> &p1, const pair<string, int> &p2){
	return p2.second < p1.second;
}

unordered_map<string, int> getSuggestedFriends(const string &userID, SocialNetwork &sn){
	unordered_set<string> ignoreList;
	unordered_map<string, int> ffMap;
	ignoreList.insert(userID);

	const vector<string> &myFriends = sn[userID];
	ignoreList.insert(myFriends.begin(), myFriends.end());

	for (const string &myFriend : myFriends){
		const vector<string> &ffriends = sn[myFriend];
		for(const string &myFf : ffriends){
			if(ignoreList.find(myFf) == ignoreList.end()){
				++ffMap[myFf];
			}
		}
	}
	return ffMap;
}

vector<pair<string, int>> getSuggestedFriendsSorted(const string &userID, SocialNetwork &sn){
	auto ffMap = getSuggestedFriends(userID, sn);
	vector<pair<string, int>> ffVec(ffMap.begin(), ffMap.end());
	sort(ffVec.begin(), ffVec.end(), sortByFriendsInCommon);
	return ffVec;
}

void print(const unordered_map<string, int> &ffMap){
	for(const auto &ff : ffMap){
		cout << ff.first << " - " << ff.second << endl; 
	}
}

void print(const vector<pair<string, int>> &ffVec){
	for(const auto &ff : ffVec){
		cout << ff.first << " - " << ff.second << endl; 
	}
}



int main(){
	string me = "Michael";
	string f1 = "f1";
	string f2 = "f2";
	string f3 = "f3";
	string f4 = "f4";
	string f5 = "f5";
	string ff1 = "ff1";
	string ff2 = "ff2";
	string ff3 = "ff3";
	string ff4 = "ff4";
	string ff5 = "ff5";
	string ff6 = "ff6";
	string ff7 = "ff7";
	string ff8 = "ff8";
	string ff9 = "ff9";
	string ff10 = "ff10";

	vector<string> myFriends = {f1, f2, f3, f4, f5};
	vector<string> f1Friends = {me, f2, ff1, ff2, ff3};
	vector<string> f2Friends = {me, ff1, ff3};
	vector<string> f3Friends = {me, f2, ff1, ff4, ff5, ff6, ff7, ff8, ff9, ff10};
	vector<string> f4Friends = {me, f2, ff1, ff5, ff3};
	vector<string> f5Friends = {me, f2, ff1, ff2, ff3, ff10};


	SocialNetwork sn1;
	sn1[me] = myFriends;
	sn1[f1] = f1Friends;
	sn1[f2] = f2Friends;
	sn1[f3] = f3Friends;
	sn1[f4] = f4Friends;
	sn1[f5] = f5Friends;

	// auto ffResult = getSuggestedFriends(me, sn1);
	// print(ffResult);
	auto ffResult2 = getSuggestedFriendsSorted(me, sn1);
	print(ffResult2);
	return EXIT_SUCCESS;
}