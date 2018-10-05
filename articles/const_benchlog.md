106G    /data/users/hwzhang/index/data/indexed/1535972718/indexed_db
9.1G    new_index3/
corpus : one shard baike docs.
term count : 11314832
Use the same test query.(disable random shuffle)

==========================================================================================
# second test time (with page cache): 
## chert
spye@spi-cdb-52:~$ ./db_bench_main --db_path /data/users/hwzhang/index/data/indexed/1535972718/indexed_db --term_file terms.random --test_query_num 10000
### single query.
 performance : total  10000 queries, 1964.25 queries/sec.Total matches:2059342, use time(Ms) : 5091
mean : 508, p50 : 31, p90 : 164, p98 : 3130, max : 196774

### OOV query.
 performance : total  10000 queries, 91743.1 queries/sec.Total matches:0, use time(Ms) : 109
mean : 10, p50 : 10, p90 : 12, p98 : 17, max : 76

### q1 AND q2.
 performance : total  10000 queries, 28985.5 queries/sec.Total matches:23, use time(Ms) : 345
mean : 34, p50 : 32, p90 : 44, p98 : 56, max : 1035

### q1 OR q2.
 performance : total  10000 queries, 844.167 queries/sec.Total matches:4718740, use time(Ms) : 11846
mean : 1184, p50 : 80, p90 : 654, p98 : 12552, max : 237985

## const format
spye@spi-cdb-52:~$ ./db_bench_main --db_path new_index3/ --term_file terms.random --test_query_num 10000

### single query.
 performance : total  10000 queries, 21141.6 queries/sec.Total matches:2059342, use time(Ms) : 473
mean : 47, p50 : 9, p90 : 16, p98 : 235, max : 22211

### OOV query.
 performance : total  10000 queries, 400000 queries/sec.Total matches:0, use time(Ms) : 25
mean : 2, p50 : 2, p90 : 3, p98 : 4, max : 22

### q1 AND q2.
 performance : total  10000 queries, 82644.6 queries/sec.Total matches:23, use time(Ms) : 121
mean : 11, p50 : 9, p90 : 11, p98 : 30, max : 4273

### q1 OR q2.
 performance : total  10000 queries, 10235.4 queries/sec.Total matches:4718740, use time(Ms) : 977
mean : 97, p50 : 7, p90 : 38, p98 : 873, max : 39104

==========================================================================================
# first test time (without cache)

## chert format
spye@spi-cdb-52:~$ ./db_bench_main --db_path /data/users/hwzhang/index/data/indexed/1535972718/indexed_db --term_file terms.random --query_offset 100000 --test_query_num 10000

### single query.
 performance : total  10000 queries, 99.9081 queries/sec.Total matches:4352104, use time(Ms) : 100092
mean : 10008, p50 : 6680, p90 : 20067, p98 : 39933, max : 700193

### OOV query.
 performance : total  10000 queries, 135.142 queries/sec.Total matches:2, use time(Ms) : 73996
mean : 7399, p50 : 1063, p90 : 18590, p98 : 28911, max : 313295

### q1 AND q2.
 performance : total  10000 queries, 68.5363 queries/sec.Total matches:111, use time(Ms) : 145908
mean : 14590, p50 : 11921, p90 : 30572, p98 : 57874, max : 545734

### q1 OR q2.
 performance : total  10000 queries, 70.1745 queries/sec.Total matches:4557791, use time(Ms) : 142502
mean : 14249, p50 : 10483, p90 : 30344, p98 : 66662, max : 792642

## const format
$ ./db_bench_main --db_path new_index3/ --term_file terms.random --query_offset 100000 --test_query_num 10000
### single query.
 performance : total  10000 queries, 705.02 queries/sec.Total matches:4352104, use time(Ms) : 14184
mean : 1418, p50 : 11, p90 : 99, p98 : 18834, max : 672850
### OOV query.
 performance : total  10000 queries, 188679 queries/sec.Total matches:2, use time(Ms) : 53
mean : 5, p50 : 4, p90 : 6, p98 : 19, max : 125
### q1 AND q2.
 performance : total  10000 queries, 649.013 queries/sec.Total matches:111, use time(Ms) : 15408
mean : 1540, p50 : 19, p90 : 162, p98 : 20562, max : 364259
### q1 OR q2.
 performance : total  10000 queries, 771.962 queries/sec.Total matches:4557791, use time(Ms) : 12954
mean : 1295, p50 : 16, p90 : 280, p98 : 20545, max : 85903


feature | const(single) | const (OOV) | const (AND) | const (OR) | chert (single) | chert (OOV) | chert (AND) | chert (OR)
------------ | ------| -- | -| -- | -- | --| -- |------------
QPS | 705.02 | 188679 | 649.013 | 771.962 | 99.9081 | 135.142 | 68.5363 | 70.1745
mean | 1418 | 5 | 1540 | 1295 | 10008 | 7399 | 14590 | 14249
p50 | 11 | 4 | 19 | 16 | 6680 | 1063 | 11921 | 10483
p90 | 99 | 6 |162 | 280 | 20067 | 18590 | 30572 | 30344
p98 | 18834 | 19 | 20562 | 20545 | 39933 | 28911 | 57874 | 66662
max | 672850 | 125 | 364259 | 85903 | 700193 | 313295 | 545734 | 792642

<!--stackedit_data:
eyJoaXN0b3J5IjpbLTI0Mjk4OTg0Nl19
-->