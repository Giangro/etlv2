delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1    and 250  and (atype='M' OR atype='D') and dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 251  and 500  and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 501  and 750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 751  and 1000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1001 and 1250 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1251 and 1500 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1501 and 1750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1751 and 2000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2001 and 2250 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2251 and 2500 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2501 and 2750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
delete from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2751 and 3000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1  and 250  and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 251  and 500  and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 501  and 750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 751  and 1000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1001 and 1250 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1251 and 1500 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1501 and 1750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 1751 and 2000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2001 and 2250 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2251 and 2500 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2501 and 2750 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');
select count (*) from KPI_FE_UNICO_STORICO_PREAGG_2_0 where combo between 2751 and 3000 and and (atype='M' OR atype='D') dday >= to_date('2016-03-01', 'yyyy-MM-dd');