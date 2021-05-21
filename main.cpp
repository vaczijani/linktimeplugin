#include <iostream>
#include <string>
#include <algorithm>
#include "registered_plugin.hpp"

class PrintPlugin : public RegisteredPlugin<PrintPlugin> {
public:
	typedef PrintPlugin type;
	virtual void print() = 0;
};

class MyDog : public PrintPlugin {
public:
	void print() { std::cout << "woof\n"; }
};

PluginProxy<MyDog> myDog;

class MyCat : public PrintPlugin {
public:
	void print() { std::cout << "meow\n"; }
};

PluginProxy<MyCat> myCat;

class StringPlugin : public RegisteredPlugin<StringPlugin> {
//class StringPlugin : public RegisteredPlugin<PrintPlugin> {  // use this for a runtime error
public:
	typedef StringPlugin type;
	virtual std::string string() = 0;
};


class Name : public StringPlugin {
public:
	std::string string() { return "Name"; }
};

PluginProxy<Name> myName;

class Town : public StringPlugin {
public:
	std::string string() { return "Town"; }
};

PluginProxy<Town> myTown;

int main() {	
	std::cout << "Plugins with safe type proxy\n";
	typedef RegisteredPluginProxy<PrintPlugin> Plugins;
	for (Plugins::iterator it = Plugins::begin(); it != Plugins::end(); ++it) {
		(*it)->plugin()->print();
	}

	typedef RegisteredPluginProxy<StringPlugin> StrPlugins;
	for (StrPlugins::iterator it = StrPlugins::begin(); it != StrPlugins::end(); ++it) {
		std::cout << (*it)->plugin()->string() << std::endl;;
	}
	std::cout << "Plugins with unsafe downcasting\n";
	typedef RegisteredPlugin<PrintPlugin> UnSafePlugins;
	for (UnSafePlugins::iterator it = UnSafePlugins::begin(); it != UnSafePlugins::end(); ++it) {
		(*it)->print();
	}

	typedef RegisteredPlugin<StringPlugin> UnSafeStrPlugins;
	for (UnSafeStrPlugins::iterator it = UnSafeStrPlugins::begin(); it != UnSafeStrPlugins::end(); ++it) {
		std::cout << (*it)->string() << std::endl;
	}
}
