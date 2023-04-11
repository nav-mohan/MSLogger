Implement Meyers Singleton - for threadsafe constructor
Uses C++17 `<filesystem>` for measuring filesize (rotating log files)


Inherit std::streambuf
`xsputn()` : For filling up buffer.\n 
`sync()` : For flushing full buffer\n
`overflow()` : Not required if `xsputn` handles all cases but basically a 
combination of `xsputn(n=1)` and `sync()`

Use locks when filling/flushing buffer

The strength of this library is that it's a single header file.
It does not provide the flexiblity of something like Boost Logger i.e it does not allow you to define sinks, sources, and filters. 
As of now, logs to rotating textfiles and stdout. No support for database. Might change in the future. 
Boost Logger implements the Observer Design Pattern. Hence, the source and sink are not as tightly coupled. Thats what gives you the flexbility to log to a textfile, the stdout, or a database. 


The class ms_logger is templated on the default LOGLEVEL. 
ms_logger<WARN>::get_instance() will return a separate instance from ms_logger<INFO>::get_instance() or ms_logger<WARN>::get_instance(). 

Default buffersize is 1024
A static methods presize_buffer(std::size_t) can be called before instantaion to increase/decrease buffersize
A non-static mthods set_bufferSize(std::size_t) can be called after instantiation to increase buffersize