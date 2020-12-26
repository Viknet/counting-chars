# counting-chars
Small and stupid benchmarking of ways of counting a char in a big string.

The results, just for the reference (all times are in milliseconds, Apple clang version 12.0.0 (clang-1200.0.32.28), input file size is about 800 Mb):

| CPU                     | Naive / `-O2` | Naive / `-O3 -march=native` | SSE4.2 | AVX2 | NEON |
|:----------------------- | -------------:| ---------------------------:| ------:| ----:| ----:|
| Core i5 4260U	          |          8312 |                        2354 |   2826 | 1670 |    - |
| M1 Rosetta              |          2384 |                        2384 | 159030 |    - |    - |
| M1 Native               |          2489 |                        2485 |      - |    - |  551 |
