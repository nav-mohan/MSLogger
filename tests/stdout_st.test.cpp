#define BOOST_TEST_MODULE MSLogger SingleThreaded Logging to STDCLOG
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/regex.hpp>

#include <ostream>
#include <iostream>
#include <string>
#include <vector>

#include "ms_logger.h"


//verifying that our string is formatted correctly
BOOST_AUTO_TEST_CASE(test_logging_to_stdclog_singlethread)
{
    // Hijack the std::clog!
    std::ostringstream original_clog_stream;
    std::streambuf *original_buffer = std::clog.rdbuf(original_clog_stream.rdbuf());
    
    ms_logger<INFO>& msl = ms_logger<INFO>::get_instance();
    msl.log_to_stdout("Test String 1");
    msl.log_to_stdout("Test String 2",WARN);
    msl.log_to_stdout("Test String 3",ERROR);
    boost::regex pattern("\x1b\\[\\d\\d;1m\\[\\w*\\]\x1b\\[\\d\\w\t\\d{4}-\\d{2}-\\d{2}\\s\\d{2}:\\d{2}:\\d{2}\\s:\\sTest\\sString\\s\\d\n");

    std::vector<std::string> matches;
    std::string s = original_clog_stream.str();
    boost::sregex_iterator iter(s.begin(),s.end(),pattern);
    boost::sregex_iterator end;
    while(iter != end)
    {
        matches.emplace_back(std::move(iter->str()));
        ++iter;
    }

    // Restore the std::clog's streambuffer
    std::clog.rdbuf(original_buffer);

    for(auto m : matches)
    {
        std::cout << "," << m;
    }
    BOOST_TEST(matches.size() == 3);
}

