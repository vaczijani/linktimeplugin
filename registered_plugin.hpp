#pragma once
#include <vector>

template<class T>
class RegisteredPluginProxy {
public:
	RegisteredPluginProxy() {
		plugins().push_back(this);
	}
	virtual T* plugin() = 0;
	typedef std::vector<RegisteredPluginProxy*> PluginColl;
	typedef typename PluginColl::iterator iterator;
	static iterator begin() { return plugins().begin(); }
	static iterator end() { return plugins().end(); }
private:
	static PluginColl& plugins() {
		static PluginColl plugins_;
		return plugins_;
	}	
};

// Proxy converts back to the correct type
template<class T>
class PluginProxy : public RegisteredPluginProxy<typename T::type> {
public:
	T* plugin() { return &x; }
private:
	T x;
};

// Below is the simple to use but unsafe implementation!
// Subclass must make sure to correctly use the type
// because any other subclass type can be used which
// unfortunately is the most likely mistake to do:
// class PrinterPlugin : public UnSafeRegisteredPlugin<PrinterPlugin> {...};
//
// creating new plugin with copy-paste and forgetting the type
//
// class StringPlugin : public UnSafeRegisteredPlugin<PrinterPlugin> BOOM! Runtime error!
template<class T>
class RegisteredPlugin {
public:
	RegisteredPlugin() {
		plugins().push_back(static_cast<T*>(this)); // downcasting
	}
	typedef std::vector<T*> PluginColl;
	typedef typename PluginColl::iterator iterator;
	static iterator begin() { return plugins().begin(); }
	static iterator end() { return plugins().end(); }
private:
	static PluginColl& plugins() {
		static PluginColl plugins_;
		return plugins_;
	}	
};