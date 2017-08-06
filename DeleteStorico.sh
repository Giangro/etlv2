#!/bin/bash

#DELAY="7200"
SQLITE_PATH=/usr/bin
PATH_SCRIPT=/home/hadoop/dev/etlv2

#while true
#do

cd $PATH_SCRIPT

echo $(date +%F-%T) >> $PATH_SCRIPT/delete_log
echo "start script DeleteStorico.sh" >> $PATH_SCRIPT/delete_log

/usr/phoenix/phoenix-4.6.0-HBase-1.1-bin/bin/psql.py localhost:2181:/hbase-unsecure DeleteStorico.sql

echo $(date +%F-%T) >> $PATH_SCRIPT/delete_log
echo "End script DeleteStorico.sh" >> $PATH_SCRIPT/delete_log

#sleep $DELAY
#done

