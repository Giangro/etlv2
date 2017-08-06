#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

#include "etl.h"
#include "utils.h"
#include "database.h"
#include "csv.h"
#include "md5sum.h"
#include "simplelog.h"

const char combo_column[][32] = {
    "DATA","POLO", "SILOS", "ISOLA", "REGIONE", "DOMINIO", "NETWORK", "FAMIGLIA", "PIATTAFORMA", "VENDOR"
    //"DATA","POLO", "SILOS", "ISOLA", "REGIONE", "DOMINIO", "NETWORK", "FAMIGLIA"
};

const char kpi_column[][256] = {
    "SUM(ACK) as ACK"
    ,"SUM(ACK_TT) as ACK_TT"
    ,"SUM(ACK_PARK) as ACK_PARK"
    ,"SUM(CORRELATO) as CORRELATO"
    ,"SUM(PARKSISTEMA) as PARKSISTEMA"
    ,"SUM(OUTAGE) as OUTAGE"
    ,"SUM(NON_GESTITI_NOTE) as NON_GESTITI_NOTE"
    ,"SUM(NON_GESTITI_MIN_60) as NON_GESTITI_MIN_60"
    ,"SUM(NON_GESTITI_MAG_60) as NON_GESTITI_MAG_60"
    ,"SUM(ACK+ACK_TT+CORRELATO+PARKSISTEMA+OUTAGE+NON_GESTITI_NOTE+NON_GESTITI_MIN_60+NON_GESTITI_MAG_60) as VAI"
    ,"SUM(ACK+ACK_TT+NON_GESTITI_NOTE+NON_GESTITI_MIN_60+NON_GESTITI_MAG_60+PARKSISTEMA) as VAP"
    ,"SUM(ACK+ACK_TT+PARKSISTEMA) as VAG"
};

extern char line[LINE_MAX+1];
const char table_name[] = "KPI_FE_CRUSCOTTO";
int nrow;
map<string, string> colmap;
map<string, string> extracolmap;

/*
 *  callback
 *
 */
int callback(void *data, int argc, char **argv, char **azColName) {
    const size_t csv_column_size = sizeof (csv_column) / sizeof (csv_column[0]);
    int i;
    char md5sum[33];

    colmap.erase("DATA");

    colmap["VAI"]="-1";
    colmap["VAP"]="-1";
    colmap["VAG"]="-1";
    colmap["VNTT"]="-1";
    colmap["VCTT"]="-1";
    colmap["DA"]="-1";
    colmap["IGA"]="-1";
    colmap["ICRNTT"]="-1";
    colmap["IRRNTT"]="-1";
    colmap["IDNTT"]="-1";
    colmap["IDNTTWR"]="-1";
    colmap["ICONTT"]="-1";
    colmap["ITNTT"]="-1";
    colmap["NTTRSLA"]="-1";
    colmap["NTTDSLA"]="-1";
    colmap["TTRR"]="-1";
    colmap["IRNTTD"]="-1";
    colmap["DTI"]="-1";

    for (i = 0; i < argc; i++) {
        string colname = azColName[i];
        to_upper(colname);
        colmap[colname] = argv[i];
    } // for

    for (map<string,string>::iterator it = colmap.begin();it!=colmap.end();it++) {
        snprintf (line,sizeof(line),"%s = %s",it->first.c_str(),it->second.c_str());
        LOGWRITE(NULL, (_LOG_DEBUG, line));
        //cout << it->first << " = " <<it->second <<endl;
    } // for

    // PATCH: da gestire settimana e mese
    // INIZIO
    if (colmap.find("DATA") == colmap.end()) {
        //colmap["DATA"]="2015-10-01";
        //colmap["DATA"]="2015-11-01";
        //colmap["DATA"]="2015-12-01";
        colmap["DATA"]="2016-01-01";
        colmap["ATYPE"]='M';
    }
    else {
        colmap["ATYPE"]='D';
    }
    // FINE

    string sum;

    if (colmap.find("POLO") != colmap.end())
        sum.append(colmap["POLO"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("SILOS") != colmap.end())
        sum.append(colmap["SILOS"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("ISOLA") != colmap.end())
        sum.append(colmap["ISOLA"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("REGIONE") != colmap.end())
        sum.append(colmap["REGIONE"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("DOMINIO") != colmap.end())
        sum.append(colmap["DOMINIO"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("NETWORK") != colmap.end())
        sum.append(colmap["NETWORK"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("FAMIGLIA") != colmap.end())
        sum.append(colmap["FAMIGLIA"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("PIATTAFORMA") != colmap.end())
        sum.append(colmap["PIATTAFORMA"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("VENDOR") != colmap.end())
        sum.append(colmap["VENDOR"]).append("|");
    else
        sum.append("*|");

    if (colmap.find("SLOGAN") != colmap.end())
        sum.append(colmap["SLOGAN"]);
    else
        sum.append("*");

    md5hash(sum.c_str(),md5sum);

    snprintf (line,sizeof(line),"md5 sum of %s is %s",sum.c_str(),md5sum);
    LOGWRITE(NULL, (_LOG_DEBUG, line));

    colmap["MD5SUM"] = md5sum;
    string csvrow;

    if (colmap.find(csv_column[0]) != colmap.end())
        csvrow.append(colmap[csv_column[0]]);
    else
        csvrow.append(" ");

    for (i = 1; i < csv_column_size; i++) {
        csvrow.append(";");
        if (colmap.find(csv_column[i]) != colmap.end())
            csvrow.append(colmap[csv_column[i]]);
        else
            csvrow.append(" ");
    } // for

    snprintf (line,sizeof(line),"row #%d = %s",++nrow,csvrow.c_str());
    LOGWRITE(NULL, (_LOG_DEBUG, line));

    cout<<csvrow<<endl;

    snprintf (line,sizeof(line),"----------------------------------");
    LOGWRITE(NULL, (_LOG_DEBUG, line));

    return 0;
}

/*
 *  load_data
 *
 */
void load_data() {

    const size_t combo_column_size = sizeof (combo_column) / sizeof (combo_column[0]);
    const size_t kpi_column_size = sizeof (kpi_column) / sizeof (kpi_column[0]);
    const int combinazioni = 1 << combo_column_size;
    //const int combinazioni = pow(2, arraysize);

    if (openDatabase() == -1) {
        return;
    }

    snprintf (line,sizeof(line),"loading data...");
    LOGWRITE(NULL, (_LOG_INFO, line));

    nrow=0;

    for (int i = 1; i < combinazioni; i++) {

        int combo = i;
        vector<string> groupby_vector;

        for (int j = 0; combo > 0; j++) {

            if ((combo % 2) == 1) {
                groupby_vector.push_back(combo_column[j]);
            } // if

            combo >>= 1;

        } // for

        string sqlselect;

        sqlselect.append("SELECT ");

        //        BOOST_FOREACH(string col, groupby_vector) {
        //            sqlselect
        //                .append (col)
        //                .append(",");
        //        }

        string colset;

        colset.append(groupby_vector[0]);

        for (int j = 1; j < groupby_vector.size(); j++)
            colset.append(",").append(groupby_vector[j]);

        sqlselect.append(colset).append(",");
        sqlselect.append(kpi_column[0]);

        for (int j = 1; j < kpi_column_size; j++)
            sqlselect.append(",").append(kpi_column[j]);

        sqlselect.append(" FROM ").append(table_name);
        //sqlselect.append(" WHERE DOMINIO='CX'");
        sqlselect.append(" GROUP BY ").append(colset);

        snprintf (line,sizeof(line),"binary combo(%d) = %d - selecting cols = %s",i,decimal_to_binary(i),colset.c_str());
        LOGWRITE(NULL, (_LOG_DEBUG, line));

        //cout << "colset = " << colset << endl;
        //snprintf (line,sizeof(line),"binary combo(%d) = %d",i,decimal_to_binary(i));
        //LOGWRITE(NULL, (_LOG_DEBUG, line));

        //cout << "binary combo (" << i << ")" << "=" << decimal_to_binary(i) << endl;
        colmap.clear();

        colmap["COMBO"]=string(lexical_cast<std::string>(i));
        executeSql(sqlselect.c_str());

    } // for

    closeDatabase();

}
