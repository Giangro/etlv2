/*
 * File:   global.cpp
 * Author: Alex
 *
 * Created on 08 marzo 2016, 11.43
 */

#include "database.h"
#include "global.h"

const char *logFilename = LOG_FILE_NAME;
const char *databaseFilename = DATABASE_FILE_NAME;
const char *kpiFeFilename = KPI_FE_FILE_NAME;
const char *aggregationType = AGGREGATION_TYPE;
const char *tableName = TABLE_NAME;
const char *dateRef = DEFAULT_DATE;

// from http://stackoverflow.com/questions/7904730/boost-simple-human-readable-date-time-of-now
void formatDateTime(
        std::string const& format,
        boost::posix_time::ptime const& date_time,
        std::string& result) {
    boost::posix_time::time_facet * facet =
            new boost::posix_time::time_facet(format.c_str());
    std::ostringstream stream;
    stream.imbue(std::locale(stream.getloc(), facet));
    stream << date_time;
    result = stream.str();
}
