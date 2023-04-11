#include "ms_logger.h"
#include <stdio.h>

int main()
{
    ms_logger<INFO>::presize_buffer(512);
    
    ms_logger<WARN>::presize_buffer(1024);
    ms_logger<WARN>::get_instance();
    // ms_logger<WARN>::get_instance().log_to_stdout("Default logging level");
    ms_logger<INFO>::get_instance().log_to_stdout("INFO logger logging ERROR",ERROR);

    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 1");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 2");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 3");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 4");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 5");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 6");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 7");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 8");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 9");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 10");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 11");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 12");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 13");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 14");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 15");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 16");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 17");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 18");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 19");
    ms_logger<INFO>::get_instance().log_to_file("msl1 Goodbye Cruel World 20");
    
    return 0;
}