# cj process monitor

## Dbus generation from XML

1. Create xml interface
2. Generate C++ code from xml definition

### sdbus
```
sdbus-c++-xml2cpp interface.xml \
--adaptor=server-adaptor.h \
--proxy=client-proxy.h
```

### qdbus

```
qdbusxml2cpp -p device_interface interface.xml
```


### monitor debus

```
dbus-monitor --session "type='signal',interface='com.example.Interface'"
``