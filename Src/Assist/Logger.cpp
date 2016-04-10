#include "Logger.h"

#include "Assist/MathCommon.h"

#include <iostream>
//#include <ctime>
#include <sstream> 
#include <chrono>
#include <iomanip>


DEFINE_SINGLETON_IMPL(Logger);

Logger::Logger() {

	mLogLevel = DETAIL_LEVEL;
	mIsTimestamped = true;

	mStreams[DETAIL_LEVEL] = &std::cout;
	mStreams[DEBUG_LEVEL]  = &std::cout;
	mStreams[INFO_LEVEL]   = &std::cout;
	mStreams[WARN_LEVEL]   = &std::cout;
	mStreams[ERROR_LEVEL]  = &std::cerr;
	mStreams[FATAL_LEVEL]  = &std::cerr;

	mLabels[DETAIL_LEVEL] = String("[DETAIL] ");
	mLabels[DEBUG_LEVEL]  = String("[ DEBUG] ");
	mLabels[INFO_LEVEL]   = String("[  INFO] ");
	mLabels[WARN_LEVEL]   = String("[  WARN] ");
	mLabels[ERROR_LEVEL]  = String("[ ERROR] ");
	mLabels[FATAL_LEVEL]  = String("[ FATAL] ");

	mCurrentInsetSize = 0;
	for (unsigned int i = 0; i < LOGGER_MAX_INSET_SIZE; ++i) {
		mInsetString[i] = ' ';
	}
	mInsetString[mCurrentInsetSize] = '\0';
}

Logger::~Logger() {
}

void Logger::detail(const String& msg) {
	mLock.lock();
	if (mLogLevel <= DETAIL_LEVEL) {
		print(DETAIL_LEVEL, msg);
	}
	mLock.release();
}

void Logger::debug(const String& msg) {
	mLock.lock();
	if (mLogLevel <= DEBUG_LEVEL) {
		print(DEBUG_LEVEL, msg);
	}
	mLock.release();
}

void Logger::info(const String& msg) {
	mLock.lock();
	if (mLogLevel <= INFO_LEVEL) {
		print(INFO_LEVEL, msg);
	}
	mLock.release();
}

void Logger::warn(const String& msg) {
	mLock.lock();
	if (mLogLevel <= WARN_LEVEL) {
		print(WARN_LEVEL, msg);
	}
	mLock.release();
}

void Logger::error(const String& msg) {
	mLock.lock();
	if (mLogLevel <= ERROR_LEVEL) {
		print(ERROR_LEVEL, msg);
	}
	mLock.release();
}

void Logger::fatal(const String& msg) {
	mLock.lock();
	if (mLogLevel <= FATAL_LEVEL) {
		print(FATAL_LEVEL, msg);
	}
	mLock.release();
}

void Logger::setLogLevel(LogLevelEnum logLvl) {
	mLock.lock();
	mLogLevel = logLvl;
	mLock.release();
}

void Logger::setTimestampedLogging(bool timestamped) {
	mLock.lock();
	mIsTimestamped = timestamped;
	mLock.release();
}

void Logger::setStream(LogLevelEnum level, std::ostream* stream) {
	mLock.lock();
	mStreams[level] = stream;
	mLock.release();
}

void Logger::addInset(unsigned int numSpaces) {
	mLock.lock();
	mInsetString[mCurrentInsetSize] = ' ';
	mCurrentInsetSize = Math::Min(mCurrentInsetSize + numSpaces, LOGGER_MAX_INSET_SIZE - 1U);
	mInsetString[mCurrentInsetSize] = '\0';
	mLock.release();
}

void Logger::removeInset(unsigned int numSpaces) {
	mLock.lock();
	mInsetString[mCurrentInsetSize] = ' ';
	mCurrentInsetSize = Math::Max(mCurrentInsetSize - numSpaces, 0U);
	mInsetString[mCurrentInsetSize] = '\0';
	mLock.release();
}

void Logger::flush(LogLevelEnum level) {
	mLock.lock();
	mStreams[level]->flush();
	mLock.release();
}

String Logger::timestamp() {
	char buf[64];
	std::time_t ti1 = std::time(NULL);
	std::tm ti2;
	localtime_s(&ti2, &ti1);
	std::strftime(buf, 64, "[%Y-%m-%d, %H:%M:%S] ", &ti2);
	return String(buf);
}

void Logger::print(LogLevelEnum level, const String& msg) {
	(*mStreams[level]) << (mIsTimestamped ? timestamp().cstr() : String("").cstr()) << mLabels[level].cstr() << mInsetString << msg.cstr() << "\n";
	mStreams[level]->flush();
}


