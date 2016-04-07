#pragma once

#include "Assist/Common.h"

#include "Assist/String.h"
#include "Assist/Mutex.h"

#include <ostream>

#define LOGGER_MAX_INSET_SIZE 256

class Logger
{
public:

	DECLARE_SINGLETON_HEADER(Logger);

public:

	// enum for log level description
	typedef enum LogLevelEnum {
		DETAIL_LEVEL = 0,
		DEBUG_LEVEL = 1,
		INFO_LEVEL = 2,
		WARN_LEVEL = 3,
		ERROR_LEVEL = 4,
		FATAL_LEVEL = 5,
		NO_LOGGING = 6
	} LogLevelEnum;

	// constructors / destructor
	virtual ~Logger();

	// logging functions
	void detail(const String& msg);
	void debug(const String& msg);
	void info(const String& msg);
	void warn(const String& msg);
	void error(const String& msg);
	void fatal(const String& msg);

	// getters/setters
	void setLogLevel(LogLevelEnum logLvl);
	void setTimestampedLogging(bool timestamped);
	void setStream(LogLevelEnum level, std::ostream* stream);

	void addInset(unsigned int numSpaces);
	void removeInset(unsigned int numSpaces);

	void flush(LogLevelEnum level);

protected:

	Mutex mLock;

	LogLevelEnum mLogLevel;
	bool mIsTimestamped;

	// log message labels
	String mLabels[6];

	// output streams to log into
	std::ostream* mStreams[6];

	unsigned char mInsetString[LOGGER_MAX_INSET_SIZE];
	unsigned int mCurrentInsetSize;

	// protected constructor
	Logger();

	String timestamp();
	void print(LogLevelEnum level, const String& msg);

}; /* class Logger */

#if BDE_GLOBAL_LOGLEVEL < 2
#define LOGDEBUG(msg) for(;;) { Logger::getInstance()->debug(msg); break; }
#define LOGINFO(msg)  for(;;) { Logger::getInstance()->info(msg);  break; }
#define LOGERROR(msg) for(;;) { Logger::getInstance()->error(msg); break; }
#elif BDE_GLOBAL_LOGLEVEL < 4
#define LOGDEBUG(msg) 
#define LOGINFO(msg)  for(;;) { Logger::getInstance()->info(msg);  break; }
#define LOGERROR(msg) for(;;) { Logger::getInstance()->error(msg); break; }
#elif BDE_GLOBAL_LOGLEVEL < 6 */
#define LOGDEBUG(msg) 
#define LOGINFO(msg)  
#define LOGERROR(msg) for(;;) { Logger::getInstance()->error(msg); break; }
#else /* BDE_GLOBAL_LOGLEVEL >= 6 */
#define LOGDEBUG(msg) 
#define LOGINFO(msg)  
#define LOGERROR(msg) 
#endif
