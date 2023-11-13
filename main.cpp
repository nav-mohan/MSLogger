#include "ms_logger.h"
#include <stdio.h>

int main()
{
    MsLogger<INFO>::presize_buffer(512);
    
    MsLogger<WARN>::presize_buffer(1024);
    MsLogger<WARN>::get_instance();
    // MsLogger<WARN>::get_instance().log_to_stdout("Default logging level");
    MsLogger<INFO>::get_instance().log_to_stdout("INFO logger logging ERROR",ERROR);

    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 1");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 2");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 3");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 4");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 5");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 6");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 7");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 8");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 9");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 10");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 11");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 12");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 13");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 14");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 15");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 16");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 17");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 18");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 19");
    MsLogger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 20");
    
    return 0;
}