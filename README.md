# counting-chars
Small and stupid benchmarking of ways of counting a char in a big string.

The results, just for the reference (all times are in milliseconds, gcc 9.2, input file size is about 1.8 GB):

| CPU                     | Naive / `-O2` | Naive / `-O3 -march=native` | SSE4.2 | AVX2 | NEON |
|:----------------------- | -------------:| ---------------------------:| ------:| ----:| ----:|
| Core i5 4260U	          |          8312 |                        2354 |   2826 | 1670 |    - |
| M1 Rosetta              |          2384 |                        2384 | 159030 |    - |    - |
| M1 Native               |          2489 |                        2485 |      - |    - |  551 |
