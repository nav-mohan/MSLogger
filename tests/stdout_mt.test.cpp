#define BOOST_TEST_MODULE MSLogger MultiThread Logging to STDCLOG
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/thread.hpp>
#include <boost/regex.hpp>

#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <streambuf>
#include "ms_logger.h"
#include <thread>
#include <mutex>

BOOST_AUTO_TEST_CASE(test_logging_to_stdclog_multithread)
{
    std::mutex mut;                 // to verify that all 
    std::condition_variable cond;   // threads are done 
    int counter = 0;                // logging to stdout

    boost::atomic<bool> ready; // to kick-start all threads as simultaneously as possible

    // hijack the std::clog's buffer!
    std::ostringstream original_clog_stream;
    std::streambuf *original_clog_buffer = std::clog.rdbuf(original_clog_stream.rdbuf());

    boost::thread logger1
    (
        [&counter,&ready,&mut,&cond]
        {
            while(!ready.load()){;};
            std::lock_guard<std::mutex> lk(mut);
            ms_logger<INFO>::get_instance().log_to_stdout("Test String 1",TRACE);
            counter++;
            cond.notify_one();
        }
    );
    boost::thread logger2
    (
        [&counter,&ready,&mut,&cond]
        {
            while(!ready.load()){;};
            std::lock_guard<std::mutex> lk(mut);
            ms_logger<WARN>::get_instance().log_to_stdout("Test String 2",ERROR);
            counter++;
            cond.notify_one();
        }
    );
    boost::thread logger3
    (
        [&counter,&ready,&mut,&cond]
        {
            while(!ready.load()){;};
            std::lock_guard<std::mutex> lk(mut);
            ms_logger<INFO>::get_instance().log_to_stdout("Test String 3",DEBUG);
            counter++;
            cond.notify_one();
        }
    );

    boost::thread verifier
    (
        [&counter,&ready,&original_clog_stream,&original_clog_buffer,&cond,&mut]
        {

            ready.store(true);
            std::unique_lock<std::mutex> lk(mut);
            cond.wait(lk,[&counter]{return counter == 3;});
            
            std::vector<std::string> matches;
            boost::regex pattern("\x1b\\[\\d\\d;1m\\[\\w*\\]\x1b\\[\\d\\w\t\\d{4}-\\d{2}-\\d{2}\\s\\d{2}:\\d{2}:\\d{2}\\s:\\sTest\\sString\\s\\d\n");
            std::string s = original_clog_stream.str();
            boost::sregex_iterator iter(s.begin(),s.end(),pattern);
            boost::sregex_iterator end;
            while(iter != end)
            {
                matches.emplace_back(std::move(iter->str()));
                ++iter;
            }

            for(auto m : matches)
            {
                std::cout << "," << m;
            }
            BOOST_TEST(matches.size() == 3);
            std::clog.rdbuf(original_clog_buffer);
        }
    );

    logger1.join();
    logger2.join();
    logger3.join();
    verifier.join();
}
