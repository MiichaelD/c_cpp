//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

struct Entity {
	string email_address;
	vector<const Entity*> entities;

	void addEntity(Entity *entity) {
		entities.push_back(entity);
	}
};

unordered_map<string, Entity> data_store;

// --------------------- AUXILIAR FUNCTIONS --------------------- // 

// Register the entity into the structure we are using to store our entities
Entity *registerEntity(const Entity &entity) {
	if (data_store.find(entity.email_address) == data_store.end()) {
		auto entry = data_store.emplace(entity.email_address, entity);
		return &entry.first->second;
	}
	//update entity's contained entities;
	data_store[entity.email_address].entities = entity.entities;
	return &data_store[entity.email_address];
}

// news and registers a new entity from a list of emails composing that entity.
Entity *newEntityFromEmails(const string &email, const vector<string> &emails) {
	Entity entity;
	entity.email_address = email;
	for (const string &em : emails) {
		if (data_store.find(em) == data_store.end()) {
			Entity aux;
			aux.email_address = em;
			entity.addEntity(registerEntity(aux)); // include it in this entity's vector
		}
		else {
			entity.addEntity(&data_store[em]);
		}
	}
	return registerEntity(entity);
}

// news and registers a new entity from a list of entities (which are going to be registered too)
// composing that entity.
Entity *newEntityFromEntities(const string &email, const vector<Entity> &entities) {
	Entity entity;
	entity.email_address = email;
	for (const Entity &ent : entities) {
		entity.addEntity(registerEntity(ent));
	}
	return registerEntity(entity);
}

// news and registers a new entity from a list of already registered entities
// composing that entity.
Entity *newEntityFromRegisteredEntities(const string &email, const vector<Entity*> &entities) {
	Entity entity;
	entity.email_address = email;
	for (Entity *ent : entities) {
		if (data_store.find(ent->email_address) == data_store.end()) {
			throw "Tried to add an unregistered entity to a new entity. Use newEntityFromEntities instead.";
		}
		entity.addEntity(ent);
	}
	return registerEntity(entity);
}


// --------------------- SOLUTION FUNCTIONS --------------------- // 

void loadData() {
	vector<string> engEmails = { "michael@gmail.com", "yanny@gmail.com", "matt@gmail.com", "dan@gmail.com","casey@gmail.com" };
	vector<string> hrEmails = { "s2@gmail.com", "rebecca@gmail" };
	vector<string> roomEmails = { "michael@gmail.com", "josh@gmail.com", "espy@gmail.com", "christiane@gmail.com" };


	Entity *eng = newEntityFromEmails("eng@email.com", engEmails);
	Entity *hr = newEntityFromEmails("hr@gmail.com", hrEmails);
	data_store[engEmails[0]].addEntity(newEntityFromEmails("test@gmail.com", {})); // add a new entity to michael@gmail.com
	Entity *roomies = newEntityFromEmails("roomies@gmail.com", roomEmails);

	Entity *company = newEntityFromRegisteredEntities("company@gmail.com", { eng, hr });
	newEntityFromRegisteredEntities("all@gmail.com", { company, roomies });
}

set<string> getAllEmails(const Entity *entity, int depth = 0, bool skipRepeated = true, set<string> &seenEntities = set<string>()) {
	if (seenEntities.find(entity->email_address) != seenEntities.end() && skipRepeated) {
		//this entity was already printed, skip!
		return seenEntities;
	}

	for (int i = 0; i < depth; ++i) {
		cout << "\t";
	}

	cout << entity->email_address << endl;
	seenEntities.insert(entity->email_address);
	++depth;

	for (const Entity *ent : entity->entities) {
		getAllEmails(ent, depth, skipRepeated, seenEntities);
	}
	return seenEntities;
}

void printEmailSet(const set<string> &emails) {
	cout << "\nEmails on entity: ";
	auto it = emails.begin();
	while (it != emails.end()) {
		cout << *it;
		++it;
		if (it != emails.end()) {
			cout << ", ";
		}
	}
	cout << endl;
}

int main() {
	loadData();

	auto &entity = data_store["all@gmail.com"];
	auto emails = getAllEmails(&entity);
	printEmailSet(emails);

	return EXIT_SUCCESS;
}

