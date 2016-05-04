//
//  main.cpp
//
//  Created by Michael Duarte on 4/25/16.
//  Copyright © 2016 Michael Duarte. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// mapa de comandos, con un mapa de posibles entradas (chars). Cada entrada tiene un vector de acciones, cada accion es un par
// de subcomando con parametro.
unordered_map<string, unordered_map<char,vector<pair<string, string>>>> m_commands;
string m_lastCommand;
char m_lastInputchar;
bool m_stoleNewLine = false;

pair<int, char> getSpaceCount(){
    int i = 0;
    char c;
    while ((c=getchar()) == ' ')
        ++i;
    
    return {i, c};
}

void moveOutputToLeft(stringstream &output){
    long pos = output.tellp();
    output.seekp(pos-1); // return to previous input position
}

void moveOutputToRight(stringstream &output, bool needSpace){
    long pos = output.tellp();
    output.seekp(pos+1);
    if (needSpace){
        output << ' '; // add an empty space
        moveOutputToLeft(output);
    }
}


string processInput(const string &inputStr){
    stringstream output;
    for (int i = 0; i < inputStr.length()-1; ++i){
        output << inputStr[i];
    }
    
    output.seekp(static_cast<long>(output.tellp()) - (inputStr.length()-1));
//    output.seekg(0, output.beg); // move to begining of string;
    string currentOutput;
    char inputChar;
    string state = "start";
    int index = 0;
    while(true){
        currentOutput = output.str();
        inputChar = currentOutput[index];
        auto &vec = m_commands[state][inputChar];
        
        if (vec.empty() || state == "end"){
            break;
        }
        
        for (const auto &curPair : vec){
            inputChar = currentOutput[index];
            if (curPair.first == "move"){
                if (curPair.second == "right"){
                    moveOutputToRight(output, ++index == currentOutput.length());
                } else {
                    --index;
                    moveOutputToLeft(output);
                }
                
            } else if (curPair.first == "write"){
                output << curPair.second;
                moveOutputToLeft(output);
            } else if (curPair.first == "state"){
                state = curPair.second;
            }
        }
//        cout << "input: " << output.str() << endl;
    }
    return output.str();
}

bool processTapes(char previousChar){
    if (previousChar == '.') // ...
        return false;
    
    
    int caseN = previousChar - '0';
    while(true){
        char c = getchar();
        if (c == ':'){
            getchar();getchar();
            string input;
            getline(cin, input);
            cout << "Tape #"<<caseN<<": " <<processInput(input) << endl;
            
            return true;
        } else {
            caseN*= 10;
            caseN+= c-'0';
        }
    }
}

void addToken(char firstChar){
    string line;
    getline(cin, line);
    string command(1, firstChar);
    command.reserve(line.length());
    command+=line.substr(0,line.length()-1);
    m_lastCommand = command;
    
    m_commands.insert( {std::move(command), unordered_map<char,vector<pair<string,string>>>()} );
}

void addInputChar(){
    auto prevCommand = m_commands[m_lastCommand];
    char c = getchar();
    m_lastInputchar = c;
    prevCommand.insert({c, vector<pair<string, string>>()});
    getchar();// '
    getchar();// :
    getchar();// \n
}

string getParameter(){
    char c;
    stringstream ss;
    while ((c= getchar())){
        if (c == '\'' || c == '\n'){
            string param = ss.str();
            if (param.length() > 0){
                if (c == '\'')
                    getchar(); // consume \n
                return param;
            }
        } else {
            ss << c;
        }
    }
    return string();
}

void addSubcommand(char firstChar){
    auto &subcommandVector = m_commands[m_lastCommand][m_lastInputchar];
    stringstream stream;
    stream << firstChar;
    while(true){
        char c = getchar();
        if (c == ':'){
            getchar();
            string param = getParameter();
            subcommandVector.push_back({std::move(stream.str()), std::move(param)} );
            return;
        } else{
            stream << c;
        }
    }
}


int main(){
    string line;
    bool processingTapes = false;
    getline(cin, line); // ---
    getline(cin, line); // code:
    while(true){
        auto spaceOut = getSpaceCount();
        switch(spaceOut.first){
            case 0: // tapes:
                if (spaceOut.second == '.')
                    return 0;
                getline(cin, line);
                processingTapes = true;
                spaceOut = getSpaceCount();
                if (!processTapes(spaceOut.second))
                    return 0;
                break;
            case 2: // state:
                if (processingTapes){
                    if (!processTapes(spaceOut.second))
                        return 0;
                } else {
                    addToken(spaceOut.second);
                }
                break;
            case 4: // input_chars:
                addInputChar();
                break;
            case 6: // commands: param
                addSubcommand(spaceOut.second);
                break;
        }
    }
}
