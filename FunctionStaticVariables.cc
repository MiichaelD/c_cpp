/**
 * Test class for Function static variables.
 * 
 * These variables are initialized only once, regardless of being called from
 * different instances (since they are static).
 * 
 * These variables are alive since their initialization and destroyed at program
 * exit.
 * 
*/

#include <iostream>

class Config {
  public:
  Config() {
    std::cout << "Config created" << std::endl;
  }

  ~Config() {
    std::cout << "Config destroyed" << std::endl;
  }
};

class ConfigLoader {
  public:
  ConfigLoader() {
    std::cout << "ConfigLoader created" << std::endl;
  }

  ~ConfigLoader() {
    std::cout << "ConfigLoader destroyed" << std::endl;
  }

  void loadConfig() {
    static Config config;
    std::cout << "ConfigLoader loading config ..." << std::endl;
  }
};

class Consumer {
  public:
  Consumer() {
    std::cout << "Consumer created" << std::endl;
  }

  ~Consumer() {
    std::cout << "Consumer destroyed" << std::endl;
  }
  void consume() {
    static ConfigLoader configLoader;
    configLoader.loadConfig();
  }
};

int main() { 
  {
    std::cout << "1 Consumer - consuming once " << std::endl;
    Consumer consumer1;
    consumer1.consume();
  }
  {
    std::cout << "1 Consumer - consuming twice " << std::endl;
    Consumer consumer1;
    consumer1.consume();
    consumer1.consume();
  }
  {
    std::cout << "2 Consumers - consuming once " << std::endl;
    Consumer consumer1;
    consumer1.consume();
    Consumer consumer2;
    consumer2.consume();
  }
}