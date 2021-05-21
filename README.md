# linktimeplugin
Compile time plugin registration. Credit to Wolfram Roesler
https://lnkd.in/ef_Y_Jw

Your Plugins are subclasses of some
```cpp
class Plugin {
public:
  typedef Plugin type; // allows the proxy to return this type
  virtual ret_t func(args) = 0;
};
```
Plugin implementations:
```cpp
class Plugin1 : public Plugin {
public:
  ret_t func(args) { ... }
};

PluginProxy<Plugin1> plugin1;  // static object registers on creation
```
usage:
```cpp
typedef RegisteredPluginProxy<Plugin> Plugins;
for (Plugins::iterator it = Plugins::begin(); it != Plugins::end(); ++it)
  (*it)->plugin()->func();
```
