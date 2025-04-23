# Benchmark Results (windows-2022) 
 
Generated on: Wed 04/23/2025 at 18:09:02.25 
 
## System Info 
CPU: AMD EPYC 7763 64-Core Processor                 
OS: Microsoft Windows Server 2022 Datacenter 
OS Version: 10.0.20348 N/A Build 20348 
 
## SSE 4.2 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.60 |                1.55 |   5.30% |     7843216 | Store float (reference 'no-op')
|                3.39 |                3.39 |   5.47% |     3567545 | Pull (1) Random Float And Store (reference 'no-op')
|                6.79 |                6.79 |   5.28% |     1709313 | Pull (2) Random Float And Store (reference 'no-op')
|               10.17 |               10.19 |   5.78% |     1187613 | Pull (3) Random Float And Store (reference 'no-op')
|               13.69 |               13.58 |   4.77% |      891437 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.78 |                6.78 |   4.93% |     1712634 | one float const
|                6.78 |                6.79 |   5.01% |     1709896 | one float const ref
|                6.79 |                6.80 |   5.78% |     1710663 | two float const ref
|                6.79 |                6.79 |   4.90% |     1710929 | four float const ref
|                6.79 |                6.81 |   4.99% |     1710740 | four float const
|               15.91 |               15.89 |   5.28% |      760691 | two float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.57 |   5.48% |      891798 | DirectX
|               13.56 |               13.58 |   5.47% |      890651 | SimpleMath
|               13.56 |               13.85 |   5.75% |      841955 | move (float)
|               13.60 |               13.79 |   5.79% |      883831 | glm
|               13.86 |               13.59 |   4.15% |      891573 | LAB

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.35 |               20.35 |   5.47% |      594458 | DirectX
|               20.35 |               20.40 |   5.13% |      590396 | move (float)
|               20.35 |               20.38 |   5.45% |      593609 | SimpleMath
|               20.59 |               20.37 |   4.93% |      594429 | LAB
|               20.65 |               20.38 |   5.39% |      594204 | glm

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.17 |   5.78% |      445565 | glm
|               27.13 |               27.17 |   5.46% |      445549 | SimpleMath
|               27.13 |               27.14 |   5.47% |      444577 | move (float)
|               27.15 |               27.16 |   5.64% |      445514 | rtm
|               27.21 |               27.15 |   5.25% |      445946 | DXM
|               27.41 |               27.17 |   4.66% |      445790 | LAB

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.86 |                4.86 |   5.14% |     2476799 | DXM w/out loads
|               61.04 |               61.16 |   5.52% |      197856 | move (float)
|               61.04 |               61.24 |   5.37% |      197364 | glm
|               61.04 |               61.05 |   5.47% |      198227 | DXM
|               61.04 |               61.14 |   5.60% |      198201 | LAB
|               61.05 |               61.34 |   5.40% |      197589 | SimpleMath

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.88 |   6.64% |     6189800 | DXM w/out loads
|               40.69 |               40.79 |   5.82% |      296797 | move::math (float)
|               40.69 |               40.80 |   5.62% |      296920 | SimpleMath
|               40.69 |               40.75 |   5.78% |      297355 | LAB
|               40.72 |               40.72 |   5.63% |      297275 | DXM
|               41.27 |               40.77 |   5.05% |      297145 | glm

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.89 |                1.88 |   5.84% |     6095692 | DXM w/out loads
|               54.25 |               55.50 |   5.59% |      221608 | SimpleMath
|               54.26 |               54.43 |   5.62% |      222586 | move::math(float)
|               54.26 |               58.00 |   6.45% |      222391 | glm
|               54.29 |               54.30 |   5.40% |      222923 | LAB
|               54.30 |               54.29 |   5.41% |      222189 | DXM
|               55.74 |               54.41 |   4.17% |      222917 | rtm

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.55 |   5.10% |     7759170 | rtm::qvvf (~transformation matrix)
|                7.23 |                7.32 |   5.54% |     1613603 | rtm::matrix3x4f
|                8.27 |                8.23 |   5.56% |     1445547 | move::math (builtin, float)
|                8.49 |                8.82 |   5.78% |     1392342 | rtm::matrix4x4f
|               17.02 |               17.12 |   5.87% |      699429 | LAB (~transformation matrix)
|               46.78 |               46.47 |   5.25% |      260581 | DXM (builtin)
|               53.21 |               54.24 |   5.35% |      224288 | DXM (manual)
|               53.30 |               53.39 |   5.35% |      227150 | SimpleMath
|              138.90 |              141.53 |   5.20% |       86884 | move::math (manual, float)
|              184.40 |              182.64 |   6.08% |       65971 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.11 |                8.13 |   4.82% |     1447384 | move::math (float)
|               17.93 |               17.94 |   5.47% |      674097 | rtm::matrix4x4f
|               18.57 |               18.58 |   5.48% |      645781 | glm
|               20.81 |               20.84 |   5.85% |      577427 | LAB
|               22.17 |               22.19 |   5.60% |      542472 | DXM
|               22.18 |               22.27 |   5.42% |      545527 | SimpleMath

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.99 |                9.00 |   5.29% |     1316624 | glm
|                9.17 |                9.15 |   5.35% |     1310344 | move::math (float)
|                9.23 |                9.26 |   5.42% |     1285754 | rtm::matrix4x4f
|               11.67 |               11.56 |   5.64% |     1041590 | LAB
|               14.63 |               14.51 |   4.65% |      827579 | DXM
|               16.95 |               16.95 |   5.70% |      711000 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.85 |   5.47% |     6468561 | DXM
|                1.85 |                1.86 |   5.27% |     6485031 | LAB
|                1.85 |                1.85 |   5.46% |     6470037 | SimpleMath
|                1.85 |                1.85 |   5.17% |     6479059 | move::math (float)
|                1.85 |                1.86 |   5.44% |     6480122 | rtm::matrix4x4f
|                9.13 |                9.13 |   3.80% |     1302595 | glm

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.88 |   5.86% |     6272441 | rtm::matrix4x4f
|                3.79 |                3.80 |   5.66% |     3181554 | rtm::qvvf
|                7.95 |                7.96 |   4.68% |     1473785 | DXM
|                9.06 |                9.08 |   5.06% |     1304802 | move::math (float)
|               12.67 |               12.71 |   5.78% |      952933 | SimpleMath
|               14.64 |               14.66 |   5.44% |      826223 | glm
|               22.19 |               22.20 |   5.46% |      545012 | LAB

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.40 |                4.49 |   5.76% |     2725799 | move::math (float)
|                4.51 |                4.43 |   3.91% |     2730259 | rtm::matrix4x4f
|                4.63 |                4.65 |   5.92% |     2603934 | DXM
|                4.63 |                4.64 |   5.47% |     2601127 | SimpleMath
|                6.45 |                6.47 |   5.63% |     1866441 | LAB
|                8.02 |                8.04 |   5.86% |     1458212 | rtm::qvvf
|               20.78 |               20.87 |   5.19% |      573221 | glm
 
## AVX 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.55 |   5.51% |     7832312 | Store float (reference 'no-op')
|                3.40 |                3.40 |   5.90% |     3566624 | Pull (1) Random Float And Store (reference 'no-op')
|                6.78 |                6.81 |   4.91% |     1712674 | Pull (2) Random Float And Store (reference 'no-op')
|               10.18 |               10.18 |   5.40% |     1188126 | Pull (3) Random Float And Store (reference 'no-op')
|               13.56 |               13.58 |   5.84% |      890867 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.79 |                6.79 |   5.25% |     1709888 | one float const
|                6.79 |                6.80 |   5.82% |     1700304 | two float const ref
|                6.79 |                7.16 |   4.06% |     1635169 | four float const
|                6.80 |                6.89 |   6.42% |     1709022 | one float const ref
|                6.81 |                6.89 |   6.20% |     1702700 | four float const ref
|               15.88 |               15.88 |   5.63% |      761828 | two float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.57 |   5.48% |      891989 | glm
|               13.56 |               13.58 |   5.46% |      890944 | DirectX
|               13.56 |               13.59 |   5.73% |      891685 | move (float)
|               13.57 |               13.59 |   5.71% |      892013 | SimpleMath
|               13.57 |               13.58 |   5.21% |      890134 | LAB

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.35 |               20.37 |   5.90% |      594489 | move (float)
|               20.35 |               20.36 |   5.47% |      594552 | glm
|               20.35 |               20.37 |   5.70% |      594207 | DirectX
|               20.35 |               20.39 |   5.48% |      594310 | SimpleMath
|               21.70 |               20.50 |   4.79% |      592742 | LAB

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.24 |   5.84% |      445188 | move (float)
|               27.15 |               27.18 |   5.41% |      445852 | SimpleMath
|               27.15 |               27.17 |   5.38% |      445445 | DXM
|               27.15 |               27.15 |   5.40% |      445403 | glm
|               27.15 |               27.16 |   5.31% |      445338 | LAB
|               27.24 |               27.18 |   5.02% |      445811 | rtm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.41 |                7.46 |   4.39% |     1567634 | DXM w/out loads
|               61.04 |               61.11 |   5.53% |      197732 | glm
|               61.04 |               61.86 |   5.68% |      196558 | DXM
|               61.04 |               61.10 |   5.46% |      197928 | LAB
|               61.04 |               61.08 |   5.67% |      198157 | SimpleMath
|               61.30 |               61.32 |   5.07% |      198273 | move (float)

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.26 |                2.21 |   6.30% |     5188361 | DXM w/out loads
|               40.69 |               40.80 |   5.14% |      295877 | glm
|               40.69 |               40.71 |   5.48% |      297120 | move::math (float)
|               40.69 |               40.92 |   5.38% |      295965 | LAB
|               40.69 |               40.71 |   5.67% |      297359 | SimpleMath
|               41.50 |               40.78 |   4.90% |      296976 | DXM

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.86 |                1.88 |   6.20% |     6235659 | DXM w/out loads
|               54.25 |               54.28 |   5.73% |      222956 | move::math(float)
|               54.26 |               54.41 |   5.13% |      221843 | rtm
|               54.26 |               54.42 |   5.57% |      222622 | LAB
|               54.26 |               54.41 |   5.12% |      221148 | SimpleMath
|               54.26 |               54.41 |   5.43% |      222431 | glm
|               54.26 |               54.60 |   5.65% |      222530 | DXM

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.16 |                7.03 |   4.48% |     1655570 | rtm::matrix4x4f
|                7.37 |                7.03 |   5.45% |     1646757 | rtm::matrix3x4f
|                7.55 |                7.55 |   5.16% |     1546894 | rtm::qvvf (~transformation matrix)
|               11.71 |               10.64 |   2.60% |     1133766 | move::math (builtin, float)
|               19.03 |               19.12 |   5.12% |      633890 | LAB (~transformation matrix)
|               74.37 |               76.46 |   5.40% |      153098 | DXM (builtin)
|               75.74 |               75.77 |   4.94% |      154313 | DXM (manual)
|               90.49 |               88.73 |   5.15% |      133271 | SimpleMath
|              102.78 |              103.33 |   5.58% |      116005 | move::math (manual, float)
|              172.10 |              173.19 |   6.03% |       69912 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.02 |                8.07 |   4.37% |     1457480 | move::math (float)
|                8.39 |                8.40 |   4.94% |     1403747 | rtm::matrix4x4f
|               14.07 |               14.11 |   5.25% |      850677 | DXM
|               17.98 |               18.04 |   5.56% |      668178 | glm
|               20.04 |               20.03 |   5.20% |      598642 | LAB
|               56.12 |               56.14 |   5.81% |      215922 | SimpleMath

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.71 |                7.73 |   4.98% |     1517864 | move::math (float)
|                8.02 |                8.03 |   5.02% |     1462943 | rtm::matrix4x4f
|                8.33 |                8.51 |   5.31% |     1322904 | glm
|               11.54 |               11.59 |   5.81% |     1039460 | DXM
|               12.03 |               12.26 |   5.21% |      965335 | LAB
|               15.93 |               16.22 |   6.47% |      699435 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.09 |                7.10 |   5.32% |     1640545 | DXM
|                7.45 |                7.14 |   4.99% |     1623245 | move::math (float)
|                8.34 |                8.34 |   5.07% |     1411338 | glm
|                8.51 |                8.51 |   5.12% |     1386766 | LAB
|                8.52 |                8.33 |   5.23% |     1413838 | rtm::matrix4x4f
|                9.72 |                9.73 |   5.66% |     1238543 | SimpleMath

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.88 |   5.63% |     6279573 | rtm::matrix4x4f
|                3.57 |                3.57 |   5.44% |     3380405 | rtm::qvvf
|                7.95 |                7.96 |   4.60% |     1474298 | DXM
|                9.25 |                9.27 |   4.70% |     1280472 | move::math (float)
|                9.36 |                9.37 |   5.47% |     1268095 | SimpleMath
|               10.30 |               10.27 |   5.25% |     1177493 | LAB
|               12.26 |               12.24 |   5.39% |      993867 | glm

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.78 |                7.81 |   5.64% |     1495403 | rtm::qvvf
|                8.24 |                8.26 |   4.74% |     1425458 | DXM
|                8.92 |                8.88 |   5.50% |     1331071 | rtm::matrix4x4f
|                9.49 |                9.48 |   5.28% |     1253869 | move::math (float)
|                9.67 |                9.68 |   4.74% |     1230264 | LAB
|               11.60 |               11.61 |   5.78% |     1031574 | SimpleMath
|               20.06 |               20.30 |   5.33% |      581809 | glm
 
## AVX2 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.55 |   3.72% |     7836835 | Store float (reference 'no-op')
|                3.41 |                3.41 |   5.09% |     3566348 | Pull (1) Random Float And Store (reference 'no-op')
|                6.78 |                6.79 |   4.89% |     1712192 | Pull (2) Random Float And Store (reference 'no-op')
|               10.17 |               10.20 |   5.53% |     1183545 | Pull (3) Random Float And Store (reference 'no-op')
|               13.56 |               13.62 |   5.49% |      889483 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.78 |                6.90 |   6.61% |     1707969 | one float const
|                6.78 |                6.78 |   4.93% |     1712377 | one float const ref
|                6.79 |                6.80 |   5.78% |     1709649 | four float const
|                6.79 |                6.80 |   4.82% |     1709254 | two float const ref
|                6.88 |                6.94 |   5.23% |     1684240 | four float const ref
|               15.89 |               15.93 |   5.13% |      755179 | two float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.58 |   5.69% |      891169 | DirectX
|               13.56 |               13.57 |   5.48% |      891872 | SimpleMath
|               13.56 |               13.58 |   5.84% |      891238 | LAB
|               13.56 |               13.64 |   5.62% |      884919 | glm
|               13.56 |               13.58 |   5.47% |      891600 | move (float)

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.34 |               20.37 |   5.81% |      593749 | glm
|               20.35 |               20.38 |   5.77% |      594246 | DirectX
|               20.35 |               20.37 |   5.48% |      594298 | move (float)
|               20.35 |               20.36 |   5.48% |      594373 | SimpleMath
|               20.36 |               20.37 |   5.83% |      594199 | LAB

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.13 |   5.48% |      445970 | rtm
|               27.13 |               27.18 |   5.67% |      445245 | DXM
|               27.13 |               27.13 |   5.74% |      446110 | SimpleMath
|               27.13 |               27.17 |   5.34% |      445153 | glm
|               27.15 |               27.32 |   5.72% |      443814 | LAB
|               27.15 |               27.16 |   5.41% |      445991 | move (float)

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.41 |                7.41 |   4.93% |     1575721 | DXM w/out loads
|               61.04 |               61.18 |   5.64% |      198023 | DXM
|               61.04 |               61.06 |   5.47% |      198162 | move (float)
|               61.04 |               61.15 |   5.25% |      197422 | SimpleMath
|               61.13 |               61.12 |   5.52% |      198038 | glm
|               62.44 |               61.80 |   5.53% |      196738 | LAB

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.17 |                2.21 |   5.50% |     5134821 | DXM w/out loads
|               40.69 |               40.78 |   5.17% |      296212 | move::math (float)
|               40.69 |               40.79 |   5.42% |      296835 | glm
|               40.69 |               40.79 |   5.52% |      297030 | LAB
|               40.78 |               40.78 |   5.13% |      297364 | DXM
|               40.99 |               41.14 |   5.46% |      293811 | SimpleMath

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.89 |   6.74% |     5996453 | DXM w/out loads
|               54.25 |               55.25 |   3.97% |      219652 | SimpleMath
|               54.25 |               54.27 |   5.47% |      223022 | DXM
|               54.26 |               54.30 |   5.67% |      222983 | glm
|               54.90 |               54.33 |   4.90% |      222998 | LAB
|               57.04 |               54.53 |   3.84% |      221832 | move::math(float)
|               57.10 |               55.37 |   4.68% |      220401 | rtm

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.54 |                6.57 |   5.44% |     1842221 | rtm::matrix3x4f
|                6.82 |                6.86 |   5.50% |     1697948 | rtm::matrix4x4f
|                7.25 |                7.28 |   4.96% |     1591579 | rtm::qvvf (~transformation matrix)
|               10.21 |               10.21 |   5.48% |     1169614 | move::math (builtin, float)
|               19.19 |               19.27 |   5.35% |      619360 | LAB (~transformation matrix)
|               64.70 |               63.25 |   4.77% |      191383 | DXM (builtin)
|               68.63 |               68.81 |   4.49% |      168800 | DXM (manual)
|               85.68 |               86.19 |   5.54% |      137448 | SimpleMath
|              103.04 |              102.34 |   4.71% |      117638 | move::math (manual, float)
|              173.49 |              174.04 |   5.52% |       69054 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.03 |                8.05 |   5.06% |     1462893 | rtm::matrix4x4f
|                8.36 |                8.40 |   5.10% |     1388317 | move::math (float)
|               17.93 |               17.93 |   5.46% |      669854 | glm
|               19.74 |               19.82 |   5.38% |      603436 | LAB
|               22.93 |               23.00 |   5.44% |      524155 | DXM
|               25.20 |               23.82 |   4.62% |      514551 | SimpleMath

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.71 |                7.72 |   5.82% |     1511831 | rtm::matrix4x4f
|                8.03 |                8.03 |   4.99% |     1463314 | move::math (float)
|                9.13 |                8.78 |   5.24% |     1342328 | glm
|               11.68 |               11.37 |   4.53% |     1057313 | DXM
|               11.73 |               11.76 |   5.64% |     1020997 | LAB
|               16.04 |               16.03 |   5.57% |      751155 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.09 |                7.12 |   4.40% |     1638307 | rtm::matrix4x4f
|                7.09 |                7.10 |   5.07% |     1640781 | LAB
|                7.43 |                7.41 |   5.23% |     1575201 | move::math (float)
|                7.82 |                7.82 |   4.86% |     1498167 | SimpleMath
|                8.82 |                8.93 |   5.95% |     1334830 | glm
|                9.25 |                9.25 |   5.26% |     1281770 | DXM

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.16 |                2.27 |   5.37% |     5459507 | rtm::matrix4x4f
|                3.65 |                3.64 |   6.40% |     3327530 | rtm::qvvf
|                8.09 |                8.16 |   5.35% |     1441072 | DXM
|                9.26 |                9.27 |   5.46% |     1281055 | move::math (float)
|                9.92 |                9.94 |   4.92% |     1202025 | SimpleMath
|               10.30 |               10.32 |   5.10% |     1164181 | LAB
|               12.23 |               12.19 |   5.40% |      992036 | glm

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.48 |                4.49 |   5.37% |     2697250 | DXM
|                7.79 |                7.84 |   5.14% |     1484468 | rtm::qvvf
|                8.64 |                8.64 |   5.04% |     1365534 | move::math (float)
|                8.64 |                8.65 |   4.65% |     1364689 | LAB
|                8.66 |                8.68 |   4.56% |     1361424 | rtm::matrix4x4f
|               11.30 |               11.29 |   5.46% |     1055548 | SimpleMath
|               19.60 |               19.87 |   5.30% |      605831 | glm
