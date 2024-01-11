# (Parallel) FilterKruskal

This is my implementation of the FilterKruskal MST Algortihm [https://algo2.iti.kit.edu/documents/fkruskal.pdf]. Compile with 
```
g++ -O3 --std=c++17 -march=native filterKruskal.cpp -o filterKruskal -ltbb -fopenmp
```

Example output of the `./filterKruskal` programm:

```
Run 1: Minimum Spanning Tree Weight: 243401
Run 2: Minimum Spanning Tree Weight: 246514
Run 3: Minimum Spanning Tree Weight: 234202
Run 4: Minimum Spanning Tree Weight: 238512
Run 5: Minimum Spanning Tree Weight: 238659
Average Execution Time with i = 1 : 0.00127847 seconds
Run 1: Minimum Spanning Tree Weight: 467892
Run 2: Minimum Spanning Tree Weight: 484452
Run 3: Minimum Spanning Tree Weight: 479263
Run 4: Minimum Spanning Tree Weight: 463594
Run 5: Minimum Spanning Tree Weight: 470628
Average Execution Time with i = 2 : 0.00286128 seconds
Run 1: Minimum Spanning Tree Weight: 962112
Run 2: Minimum Spanning Tree Weight: 965211
Run 3: Minimum Spanning Tree Weight: 941270
Run 4: Minimum Spanning Tree Weight: 944989
Run 5: Minimum Spanning Tree Weight: 950066
Average Execution Time with i = 3 : 0.00552371 seconds
Run 1: Minimum Spanning Tree Weight: 1921288
Run 2: Minimum Spanning Tree Weight: 1894377
Run 3: Minimum Spanning Tree Weight: 1887088
Run 4: Minimum Spanning Tree Weight: 1894058
Run 5: Minimum Spanning Tree Weight: 1927235
Average Execution Time with i = 4 : 0.00952085 seconds
Run 1: Minimum Spanning Tree Weight: 3805277
Run 2: Minimum Spanning Tree Weight: 3840833
Run 3: Minimum Spanning Tree Weight: 3850463
Run 4: Minimum Spanning Tree Weight: 3831994
Run 5: Minimum Spanning Tree Weight: 3786928
Average Execution Time with i = 5 : 0.0165049 seconds
Run 1: Minimum Spanning Tree Weight: 7694275
Run 2: Minimum Spanning Tree Weight: 7730059
Run 3: Minimum Spanning Tree Weight: 7641224
Run 4: Minimum Spanning Tree Weight: 7629138
Run 5: Minimum Spanning Tree Weight: 7658094
Average Execution Time with i = 6 : 0.0283207 seconds
Run 1: Minimum Spanning Tree Weight: 15387335
Run 2: Minimum Spanning Tree Weight: 15329028
Run 3: Minimum Spanning Tree Weight: 15395897
Run 4: Minimum Spanning Tree Weight: 15308682
Run 5: Minimum Spanning Tree Weight: 15293294
Average Execution Time with i = 7 : 0.0518349 seconds
Run 1: Minimum Spanning Tree Weight: 30636711
Run 2: Minimum Spanning Tree Weight: 30514083
Run 3: Minimum Spanning Tree Weight: 30555445
Run 4: Minimum Spanning Tree Weight: 30729887
Run 5: Minimum Spanning Tree Weight: 30535606
Average Execution Time with i = 8 : 0.100456 seconds
Run 1: Minimum Spanning Tree Weight: 61115470
Run 2: Minimum Spanning Tree Weight: 61152538
Run 3: Minimum Spanning Tree Weight: 61305923
Run 4: Minimum Spanning Tree Weight: 61238336
Run 5: Minimum Spanning Tree Weight: 61193052
Average Execution Time with i = 9 : 0.214043 seconds
Run 1: Minimum Spanning Tree Weight: 122417220
Run 2: Minimum Spanning Tree Weight: 122553290
Run 3: Minimum Spanning Tree Weight: 122594260
Run 4: Minimum Spanning Tree Weight: 122326392
Run 5: Minimum Spanning Tree Weight: 122618739
Average Execution Time with i = 10 : 0.509476 seconds
```
