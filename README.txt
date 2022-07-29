I.  Task 3 tables

==> 1.1.    Trace : page-simpleloop.ref       Memory Size : 50         Swap file size : 4000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  22.6025 |    766    |     2623   |          2573          |          47          |         2526         |
|    FIFO    |  22.7206 |    770    |     2619   |          2569          |          45          |         2524         |
|    CLOCK   |  25.3762 |    860    |     2529   |          2479          |          0           |         2479         |
|    LRU     |  25.4352 |    862    |     2527   |          2477          |          0           |         2477         |
|    MRU     |  1.4163  |    48     |     3341   |          3291          |          410         |         2881         |


==> 1.2.    Trace : page-simpleloop.ref       Memory Size : 100          Swap file size : 4000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  24.1074 |    817    |     2572   |          2472          |          23          |         2449         |
|    FIFO    |  24.0189 |    814    |     2575   |          2475          |          23          |         2452         |
|    CLOCK   |  25.3172 |    858    |     2531   |          2431          |          1           |         2430         |
|    LRU     |  25.4352 |    862    |     2527   |          2427          |          0           |         2427         |
|    MRU     |  1.9475  |    66     |     3323   |          3223          |          401         |         2822         |




==> 2.1.    Trace : page-repeatloop.ref       Memory Size : 50         Swap file size : 600

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  54.4014 |    309    |     259    |          209           |          121         |         88           |
|    FIFO    |  33.4507 |    190    |     378    |          328           |          241         |         87           |
|    CLOCK   |  34.3310 |    195    |     373    |          323           |          236         |         87           |
|    LRU     |  34.5070 |    196    |     372    |          322           |          236         |         86           |
|    MRU     |  49.2958 |    280    |     288    |          238           |          164         |         74           |


==> 2.2.    Trace : page-repeatloop.ref       Memory Size : 100          Swap file size : 600

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  82.7465 |    470    |     98     |          0             |          0           |         0            |
|    FIFO    |  82.7465 |    470    |     98     |          0             |          0           |         0            |
|    CLOCK   |  82.7465 |    470    |     98     |          0             |          0           |         0            |
|    LRU     |  82.7465 |    470    |     98     |          0             |          0           |         0            |
|    MRU     |  82.7465 |    470    |     98     |          0             |          0           |         0            |




==> 3.1.    Trace : page-matmul.ref       Memory Size : 50         Swap file size : 1000000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  58.5619 |  1358850  |   961515   |        961465          |        960452        |        1013          |
|    FIFO    |  52.4492 |  1217013  |   1103352  |        1103302         |        1102309       |        993           |
|    CLOCK   |  55.1394 |  1279436  |   1040929  |        1040879         |        1039918       |        961           |
|    LRU     |  55.1396 |  1279440  |   1040925  |        1040875         |        1039914       |        961           |
|    MRU     |  15.9283 |  369595   |   1950770  |        1950720         |        1931220       |       19500          |


==> 3.2.    Trace : page-matmul.ref       Memory Size : 100          Swap file size : 1000000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  86.6919 |  2011569  |   308796   |        308696          |        307714        |        982           |
|    FIFO    |  53.7949 |  1248239  |   1072126  |        1072026         |        1071052       |        974           |
|    CLOCK   |  55.1721 |  1280194  |   1040171  |        1040071         |        1039111       |        960           |
|    LRU     |  56.6329 |  1314090  |   1006275  |        1006175         |        1005215       |        960           |
|    MRU     |  22.3449 |  518483   |   1801882  |        1801782         |        1783832       |       17950          |




==> 4.1.    Trace : page-blocked.ref       Memory Size : 50         Swap file size : 2000000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  99.6067 |  1938017  |    7652    |         7602           |         6565         |        1037          |
|    FIFO    |  99.6911 |  1939658  |    6011    |         5961           |         4946         |        1015          |
|    CLOCK   |  99.7491 |  1940787  |    4882    |         4832           |         3848         |         984          |
|    LRU     |  99.7477 |  1940760  |    4909    |         4859           |         3875         |         984          |
|    MRU     |  13.1380 |  255622   |  1690047   |       1689997          |       1632627        |       57370          |


==> 4.2.    Trace : page-blocked.ref       Memory Size : 100          Swap file size : 2000000

|  Algorithm | Hit rate | Hit count | Miss count | Overall eviction count | Clean eviction count | Dirty eviction count |
|------------|----------|-----------|------------|------------------------|----------------------|----------------------|
|    RAND    |  99.7451 |  1940709  |    4960    |         4860           |         3851         |        1009          |
|    FIFO    |  99.7881 |  1941547  |    4122    |         4022           |         3025         |         997          |
|    CLOCK   |  99.8015 |  1941806  |    3863    |         3763           |         2792         |         971          |
|    LRU     |  99.8141 |  1942052  |    3617    |         3517           |         2569         |         948          |
|    MRU     |  21.6730 |  421684   |  1523985   |       1523885          |       1471265        |       52620          |




II.     Summary of tables from above

Among the 4 implemented algorithms (FIFO, CLOCK, LRU, MRU), overall CLOCK and LRU has the highest hit rate because
in both algorithms, essentially the less recently-used a page is, the more likely it will be evicted, and this assumption
aligns with most of the use cases both in the provided traces programs and in practice. FIFO, instead, does not consider
whether a page has been recently referenced or not, it simply evicts pages based on the order they are stored in physical
memory. MRU tends to have a lower hit rate compared to others with the provided traces programs because in those traces,
pages that are recently referenced are seen to have a higher possibility of being referenced again so those pages keep
being stored and pushed out in physical frames repeatedly.





III.    Tables for my designed short traces on LRU, FIFO, CLOCK, OPT

==> 1.    Trace : trace1.ref       Memory Size : 8          Swap file size : 40        Total References : 36
          Requirement:
          1. each of LRU, FIFO, CLOCK have a different hit rate
          2. none of LRU, FIFO, CLOCK have the optimal hit rate
          3. none of LRU, FIFO, CLOCK have a hit rate of 0


|  Algorithm | Hit rate | Hit count |  Miss Rate | Miss count |
|------------|----------|-----------|------------|------------|
|    OPT     |  58.3333 |     21    |   41.6666  |     15     |
|    FIFO    |  47.2222 |     17    |   52.7778  |     19     |
|    CLOCK   |  33.3333 |     12    |   66.6667  |     24     |
|    LRU     |  19.4444 |     7     |   80.5556  |     29     |




==> 2.    Trace : trace2.ref       Memory Size : 8          Swap file size : 40        Total References : 33
          Requirement:
          1. at least 1 of LRU, FIFO, CLOCK have the optimal hit rate
          3. none of LRU, FIFO, CLOCK have a hit rate of 0

|  Algorithm | Hit rate | Hit count |  Miss Rate | Miss count |
|------------|----------|-----------|------------|------------|
|    OPT     |  57.5758 |     19    |   42.4242  |     14     |
|    FIFO    |  57.5758 |     19    |   42.4242  |     14     |
|    CLOCK   |  57.5758 |     19    |   42.4242  |     14     |
|    LRU     |  57.5758 |     19    |   42.4242  |     14     |




==> 3.    Trace : trace3.ref       Memory Size : 8          Swap file size : 40        Total References : 33
          Requirement:
          1. each of LRU, FIFO, CLOCK have a hit rate of 0
          2. each page is referenced at least 3 times
          3. the OPT algorithm has a hit rate higher than 0

|  Algorithm | Hit rate | Hit count |  Miss Rate | Miss count |
|------------|----------|-----------|------------|------------|
|    OPT     |  48.4848 |     16    |   51.5151  |     17     |
|    FIFO    |   0.0000 |     0     |  100.0000  |     33     |
|    CLOCK   |   0.0000 |     0     |  100.0000  |     33     |
|    LRU     |   0.0000 |     0     |  100.0000  |     33     |
