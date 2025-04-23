# Benchmark Results (windows-2022) 
 
Generated on: Wed 04/23/2025 at 18:15:57.21 
 
## System Info 
CPU: AMD EPYC 7763 64-Core Processor                 
OS: Microsoft Windows Server 2022 Datacenter 
OS Version: 10.0.20348 N/A Build 20348 
 
## SSE 4.2 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.56 |                1.54 |   5.32% |     7840255 | Store float (reference 'no-op')
|                3.43 |                3.40 |   4.96% |     3564401 | Pull (1) Random Float And Store (reference 'no-op')
|                6.78 |                6.79 |   4.96% |     1712836 | Pull (2) Random Float And Store (reference 'no-op')
|               10.18 |               10.27 |   4.78% |     1165511 | Pull (3) Random Float And Store (reference 'no-op')
|               14.15 |               13.62 |   4.33% |      887463 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.79 |                6.80 |   5.07% |     1707277 | two float const ref
|                6.79 |                6.80 |   5.38% |     1710514 | one float const ref
|                6.79 |                6.80 |   5.87% |     1704925 | four float const
|                6.79 |                6.80 |   5.78% |     1707357 | four float const ref
|                6.84 |                6.79 |   5.66% |     1711839 | one float const
|               10.33 |               10.34 |   5.46% |     1155756 | eight float const
|               15.74 |               15.73 |   5.88% |      768341 | two float const
|               18.12 |               18.12 |   5.32% |      664170 | 16 float const
|               18.59 |               18.15 |   4.87% |      667327 | 16 float const ref
|               25.47 |               25.49 |   5.67% |      473554 | eight float const ref

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.57 |   5.69% |      891892 | glm
|               13.56 |               13.59 |   5.30% |      891130 | SimpleMath
|               13.57 |               13.61 |   5.04% |      887023 | LAB
|               13.92 |               13.60 |   4.73% |      890464 | move (float)
|               14.02 |               13.61 |   5.56% |      889127 | DirectX

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.34 |               21.28 |   3.90% |      591772 | SimpleMath
|               20.35 |               20.37 |   5.46% |      593401 | DirectX
|               20.36 |               20.36 |   5.41% |      594350 | glm
|               20.36 |               20.38 |   5.67% |      594474 | move (float)
|               21.72 |               20.48 |   4.80% |      584082 | LAB

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.16 |   5.54% |      445779 | SimpleMath
|               27.13 |               27.17 |   5.68% |      445278 | DXM
|               27.15 |               27.14 |   5.41% |      445909 | glm
|               27.15 |               27.18 |   5.16% |      443723 | LAB
|               27.15 |               27.17 |   5.93% |      445459 | move (float)
|               27.45 |               27.18 |   5.03% |      445522 | rtm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.86 |                5.00 |   7.47% |     2456943 | DXM w/out loads
|               61.04 |               61.14 |   5.45% |      197914 | DXM
|               61.04 |               61.07 |   5.47% |      198223 | glm
|               61.05 |               61.14 |   5.22% |      197611 | LAB
|               61.08 |               61.37 |   4.18% |      198022 | move (float)
|               61.21 |               61.17 |   5.29% |      198057 | SimpleMath

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.95 |                1.96 |   5.98% |     5783242 | DXM w/out loads
|               40.69 |               40.75 |   5.79% |      296819 | LAB
|               40.69 |               40.71 |   5.48% |      297263 | glm
|               40.69 |               40.79 |   5.46% |      297208 | move::math (float)
|               40.69 |               40.73 |   5.81% |      297169 | SimpleMath
|               40.72 |               40.77 |   5.46% |      295193 | DXM

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.65 |                1.56 |   4.62% |     7748207 | DXM w/out loads
|               54.25 |               54.77 |   4.43% |      217753 | SimpleMath
|               54.29 |               54.48 |   5.50% |      222289 | LAB
|               54.29 |               54.29 |   5.41% |      222878 | move::math(float)
|               54.30 |               54.53 |   4.92% |      221008 | glm
|               54.30 |               54.41 |   5.21% |      221541 | rtm
|               55.42 |               54.38 |   4.86% |      222758 | DXM

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.56 |   4.16% |     7789948 | rtm::qvvf (~transformation matrix)
|                7.24 |                7.19 |   5.77% |     1631284 | rtm::matrix3x4f
|                8.25 |                8.30 |   4.37% |     1420723 | move::math (builtin, float)
|                8.59 |                8.59 |   5.58% |     1369581 | rtm::matrix4x4f
|               17.71 |               17.38 |   4.75% |      698515 | LAB (~transformation matrix)
|               45.50 |               45.53 |   5.41% |      265459 | DXM (builtin)
|               52.89 |               53.06 |   5.44% |      228644 | DXM (manual)
|               53.19 |               53.32 |   5.71% |      226664 | SimpleMath
|              137.98 |              138.51 |   5.38% |       86643 | move::math (manual, float)
|              182.01 |              181.70 |   5.94% |       66755 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.12 |                8.16 |   6.44% |     1423676 | move::math (float)
|               17.93 |               17.98 |   5.61% |      672970 | rtm::matrix4x4f
|               18.80 |               18.59 |   5.62% |      646465 | glm
|               20.05 |               20.10 |   5.50% |      599821 | LAB
|               22.17 |               22.24 |   5.48% |      541758 | SimpleMath
|               22.17 |               22.18 |   5.47% |      545736 | DXM

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                9.15 |                9.48 |   6.09% |     1280960 | move::math (float)
|                9.24 |                9.28 |   6.13% |     1298220 | rtm::matrix4x4f
|                9.26 |                9.28 |   4.93% |     1281326 | glm
|               10.51 |               10.57 |   5.47% |     1139087 | LAB
|               14.52 |               14.53 |   4.96% |      825575 | DXM
|               17.56 |               17.01 |   4.01% |      708654 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.55 |   5.57% |     7755072 | LAB
|                1.57 |                1.55 |   4.42% |     7835904 | move::math (float)
|                1.85 |                1.87 |   5.54% |     6495183 | SimpleMath
|                1.85 |                1.85 |   5.41% |     6489797 | rtm::matrix4x4f
|                2.16 |                2.17 |   5.40% |     5553678 | DXM
|                8.60 |                8.47 |   5.83% |     1376810 | glm

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.16 |                2.20 |   5.06% |     5314874 | rtm::matrix4x4f
|                3.79 |                3.80 |   5.39% |     3178024 | rtm::qvvf
|                7.95 |                7.96 |   4.67% |     1474974 | DXM
|                9.07 |                9.07 |   5.06% |     1306569 | move::math (float)
|               12.67 |               12.68 |   5.79% |      940945 | SimpleMath
|               14.64 |               14.67 |   5.59% |      823773 | glm
|               22.18 |               22.27 |   5.49% |      538385 | LAB

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.39 |                4.42 |   6.02% |     2737653 | rtm::matrix4x4f
|                4.46 |                4.43 |   5.21% |     2724655 | move::math (float)
|                4.63 |                4.65 |   5.39% |     2599471 | SimpleMath
|                4.81 |                4.82 |   5.42% |     2509083 | DXM
|                6.51 |                6.52 |   5.62% |     1857589 | LAB
|                8.03 |                8.04 |   4.84% |     1461754 | rtm::qvvf
|               21.43 |               20.83 |   4.52% |      578993 | glm
 
## AVX 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.54 |   5.40% |     7844704 | Store float (reference 'no-op')
|                3.39 |                3.39 |   5.77% |     3568316 | Pull (1) Random Float And Store (reference 'no-op')
|                6.78 |                6.79 |   4.68% |     1709711 | Pull (2) Random Float And Store (reference 'no-op')
|               10.18 |               10.19 |   5.85% |     1188420 | Pull (3) Random Float And Store (reference 'no-op')
|               13.79 |               13.59 |   4.83% |      891518 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.78 |                6.79 |   4.98% |     1708958 | one float const ref
|                6.79 |                6.79 |   5.26% |     1711896 | one float const
|                6.79 |                6.89 |   5.48% |     1710041 | four float const
|                6.79 |                6.82 |   5.68% |     1707099 | two float const ref
|                6.80 |                6.88 |   5.78% |     1657554 | four float const ref
|               10.84 |               10.88 |   5.48% |     1098809 | eight float const
|               10.92 |               10.91 |   6.13% |     1110167 | eight float const ref
|               15.89 |               15.92 |   5.44% |      759737 | two float const
|               18.81 |               18.83 |   5.47% |      642882 | 16 float const ref
|               19.08 |               18.97 |   4.99% |      637720 | 16 float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.59 |   5.84% |      891274 | LAB
|               13.56 |               13.58 |   5.53% |      889062 | glm
|               13.57 |               13.58 |   5.46% |      888682 | SimpleMath
|               13.57 |               13.57 |   5.40% |      891270 | move (float)
|               13.74 |               13.59 |   4.96% |      891134 | DirectX

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.35 |               20.38 |   5.75% |      593982 | LAB
|               20.38 |               20.38 |   5.33% |      593818 | glm
|               20.38 |               20.41 |   5.52% |      591106 | SimpleMath
|               20.42 |               20.36 |   5.13% |      594404 | move (float)
|               20.93 |               20.41 |   4.35% |      594125 | DirectX

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.98 |   5.17% |      432147 | glm
|               27.15 |               27.14 |   5.41% |      444435 | SimpleMath
|               27.15 |               27.23 |   5.35% |      440401 | LAB
|               27.23 |               27.39 |   5.13% |      445967 | move (float)
|               28.51 |               27.27 |   4.11% |      445162 | DXM
|               28.85 |               27.35 |   4.03% |      435233 | rtm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.10 |                7.10 |   5.11% |     1639830 | DXM w/out loads
|               61.04 |               61.30 |   5.42% |      197482 | glm
|               61.09 |               61.44 |   5.29% |      196584 | SimpleMath
|               61.14 |               61.14 |   5.37% |      197427 | move (float)
|               63.51 |               61.30 |   3.65% |      197797 | LAB
|               66.34 |               61.53 |   3.37% |      197959 | DXM

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.16 |                2.18 |   5.28% |     5371142 | DXM w/out loads
|               40.69 |               40.75 |   5.71% |      296892 | move::math (float)
|               40.69 |               40.83 |   5.53% |      296669 | glm
|               40.72 |               40.72 |   5.47% |      297075 | DXM
|               40.72 |               42.25 |   4.71% |      286573 | SimpleMath
|               41.20 |               40.76 |   4.64% |      297144 | LAB

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.86 |   5.17% |     6468196 | DXM w/out loads
|               54.25 |               54.34 |   5.76% |      222818 | glm
|               54.25 |               54.27 |   5.55% |      223005 | DXM
|               54.26 |               54.36 |   5.44% |      222700 | SimpleMath
|               54.26 |               54.33 |   5.38% |      223023 | LAB
|               54.26 |               54.43 |   5.87% |      222249 | rtm
|               56.82 |               54.50 |   3.94% |      221932 | move::math(float)

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.02 |                7.09 |   5.54% |     1617796 | rtm::matrix3x4f
|                7.03 |                7.04 |   4.92% |     1655723 | rtm::matrix4x4f
|                7.25 |                7.29 |   4.99% |     1588086 | rtm::qvvf (~transformation matrix)
|               10.21 |               10.21 |   5.40% |     1185479 | move::math (builtin, float)
|               19.67 |               20.52 |   4.48% |      592942 | LAB (~transformation matrix)
|               74.26 |               74.35 |   5.73% |      158700 | DXM (builtin)
|               76.67 |               76.84 |   5.69% |      152184 | DXM (manual)
|               87.59 |               87.62 |   5.52% |      135189 | SimpleMath
|              101.65 |              104.91 |   5.40% |      117811 | move::math (manual, float)
|              169.91 |              169.89 |   5.59% |       71201 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.03 |                8.03 |   4.94% |     1462277 | rtm::matrix4x4f
|                8.33 |                8.44 |   5.94% |     1408291 | move::math (float)
|               14.09 |               14.10 |   5.73% |      853246 | DXM
|               17.90 |               17.90 |   5.34% |      669827 | glm
|               19.75 |               19.78 |   5.75% |      605727 | LAB
|               58.28 |               58.29 |   5.46% |      207658 | SimpleMath

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.71 |                7.73 |   5.37% |     1512006 | rtm::matrix4x4f
|                8.02 |                8.03 |   5.54% |     1460540 | move::math (float)
|                8.73 |                8.82 |   4.54% |     1337101 | glm
|               11.48 |               11.51 |   5.49% |     1044291 | DXM
|               12.48 |               11.80 |   4.37% |     1020480 | LAB
|               16.14 |               16.19 |   4.86% |      743890 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.09 |                7.24 |   7.72% |     1630417 | rtm::matrix4x4f
|                7.09 |                7.10 |   4.95% |     1640667 | LAB
|                7.40 |                7.42 |   4.83% |     1574435 | move::math (float)
|                7.82 |                7.81 |   5.03% |     1501157 | SimpleMath
|                8.78 |                8.81 |   4.44% |     1343578 | glm
|                9.25 |                9.26 |   6.04% |     1278179 | DXM

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.16 |                2.16 |   5.47% |     5558364 | rtm::matrix4x4f
|                3.57 |                3.57 |   5.39% |     3382933 | rtm::qvvf
|                7.96 |                7.96 |   4.76% |     1475022 | DXM
|                9.26 |                9.27 |   5.52% |     1280576 | move::math (float)
|                9.36 |                9.58 |   5.54% |     1268486 | SimpleMath
|               10.28 |               10.28 |   5.46% |     1174883 | LAB
|               12.24 |               12.20 |   5.26% |      991729 | glm

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.80 |                8.11 |   4.93% |     1441821 | rtm::qvvf
|                8.23 |                8.24 |   5.74% |     1447018 | DXM
|                8.67 |                8.70 |   6.04% |     1347293 | move::math (float)
|                8.67 |                8.70 |   4.47% |     1359720 | rtm::matrix4x4f
|                8.70 |                8.92 |   6.33% |     1321380 | LAB
|               13.08 |               13.12 |   5.47% |      913797 | SimpleMath
|               20.22 |               19.92 |   5.86% |      610261 | glm
 
## AVX2 

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.54 |                1.55 |   5.60% |     7843699 | Store float (reference 'no-op')
|                3.39 |                3.39 |   5.55% |     3563147 | Pull (1) Random Float And Store (reference 'no-op')
|                6.78 |                6.93 |   5.52% |     1664319 | Pull (2) Random Float And Store (reference 'no-op')
|               10.20 |               10.19 |   6.01% |     1187067 | Pull (3) Random Float And Store (reference 'no-op')
|               13.90 |               13.60 |   3.83% |      891108 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.79 |                6.85 |   5.26% |     1711946 | one float const
|                6.79 |                6.79 |   4.98% |     1710967 | four float const ref
|                6.80 |                6.85 |   6.39% |     1695039 | two float const ref
|                7.14 |                6.86 |   4.21% |     1689645 | four float const
|                7.89 |                7.61 |   7.40% |     1498640 | one float const ref
|               10.86 |               10.92 |   5.40% |     1088497 | eight float const
|               11.04 |               11.07 |   5.80% |     1083345 | eight float const ref
|               15.88 |               16.31 |   6.00% |      728030 | two float const
|               18.79 |               18.80 |   5.61% |      640435 | 16 float const ref
|               19.70 |               18.93 |   4.91% |      636913 | 16 float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.56 |               13.86 |   6.26% |      882954 | LAB
|               13.57 |               13.57 |   5.47% |      874058 | SimpleMath
|               14.00 |               13.80 |   4.70% |      888303 | DirectX
|               14.38 |               13.65 |   3.75% |      885161 | glm
|               14.55 |               13.99 |   4.77% |      857348 | move (float)

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.35 |               20.39 |   5.42% |      591576 | glm
|               20.36 |               20.39 |   5.81% |      594431 | move (float)
|               20.36 |               20.38 |   5.76% |      593916 | LAB
|               20.59 |               20.38 |   4.96% |      593979 | DirectX
|               20.87 |               20.93 |   4.79% |      576911 | SimpleMath

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.13 |               27.23 |   5.52% |      443596 | glm
|               27.13 |               27.14 |   5.48% |      445742 | rtm
|               27.13 |               27.17 |   5.80% |      445861 | DXM
|               27.15 |               27.15 |   5.74% |      445714 | SimpleMath
|               27.15 |               27.19 |   5.70% |      445897 | move (float)
|               27.15 |               27.18 |   5.46% |      445159 | LAB

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.10 |                7.10 |   5.75% |     1637942 | DXM w/out loads
|               61.04 |               61.11 |   5.46% |      198016 | glm
|               61.09 |               61.18 |   5.15% |      197431 | SimpleMath
|               61.63 |               61.13 |   4.67% |      198074 | DXM
|               63.15 |               61.24 |   4.14% |      197949 | LAB
|               63.50 |               67.62 |   5.18% |      156779 | move (float)

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.16 |                2.21 |   5.86% |     5147223 | DXM w/out loads
|               40.69 |               40.80 |   5.37% |      296465 | move::math (float)
|               40.69 |               40.76 |   5.47% |      297145 | glm
|               40.69 |               40.71 |   5.57% |      297330 | DXM
|               41.01 |               41.07 |   5.43% |      294618 | SimpleMath
|               42.42 |               40.86 |   4.98% |      297169 | LAB

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.86 |   5.58% |     6458571 | DXM w/out loads
|               54.26 |               54.48 |   5.63% |      222477 | SimpleMath
|               54.26 |               54.40 |   5.43% |      222508 | move::math(float)
|               54.35 |               54.26 |   5.32% |      222995 | DXM
|               55.58 |               54.41 |   4.83% |      222643 | rtm
|               55.59 |               54.48 |   5.50% |      222901 | LAB
|               55.74 |               54.42 |   4.09% |      222850 | glm

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.55 |                6.80 |   4.94% |     1774067 | rtm::matrix3x4f
|                6.82 |                6.93 |   4.07% |     1683778 | rtm::matrix4x4f
|                7.24 |                7.26 |   6.26% |     1603040 | rtm::qvvf (~transformation matrix)
|               10.23 |               10.24 |   5.65% |     1164197 | move::math (builtin, float)
|               17.61 |               17.69 |   4.91% |      675811 | LAB (~transformation matrix)
|               63.53 |               76.94 |  11.93% |      185155 | DXM (builtin)
|               68.51 |               68.37 |   5.51% |      170688 | DXM (manual)
|               86.26 |               86.06 |   5.29% |      137349 | SimpleMath
|              103.53 |              103.42 |   4.32% |      114429 | move::math (manual, float)
|              173.17 |              173.06 |   5.57% |       69620 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                8.03 |                8.12 |   5.33% |     1461418 | rtm::matrix4x4f
|                8.03 |                8.05 |   4.50% |     1460432 | move::math (float)
|               17.89 |               17.88 |   5.42% |      671518 | glm
|               19.75 |               19.91 |   5.62% |      592795 | LAB
|               23.02 |               23.61 |   5.69% |      511106 | DXM
|               23.49 |               23.52 |   5.34% |      515028 | SimpleMath

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.73 |                7.72 |   5.07% |     1517360 | rtm::matrix4x4f
|                8.83 |                8.84 |   5.29% |     1334911 | move::math (float)
|                8.95 |                8.96 |   5.15% |     1318516 | glm
|               11.33 |               11.36 |   5.67% |     1056425 | DXM
|               11.73 |               11.76 |   5.43% |     1021657 | LAB
|               16.18 |               16.15 |   5.23% |      748249 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                7.09 |                7.11 |   4.54% |     1638841 | rtm::matrix4x4f
|                7.10 |                7.12 |   5.13% |     1640838 | LAB
|                7.42 |                7.42 |   4.96% |     1573543 | move::math (float)
|                8.16 |                8.14 |   5.33% |     1451904 | SimpleMath
|                8.41 |                8.39 |   4.24% |     1402059 | DXM
|                9.56 |                9.62 |   4.71% |     1239136 | glm

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.85 |                1.86 |   5.38% |     6481865 | rtm::matrix4x4f
|                3.76 |                3.76 |   5.40% |     3211988 | rtm::qvvf
|                8.09 |                8.11 |   4.71% |     1448563 | DXM
|                9.26 |                9.27 |   4.92% |     1280600 | move::math (float)
|                9.92 |                9.94 |   4.95% |     1201967 | SimpleMath
|               10.30 |               10.33 |   5.05% |     1159440 | LAB
|               12.21 |               12.21 |   5.45% |      991166 | glm

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.50 |                4.51 |   5.42% |     2682310 | DXM
|                8.04 |                8.02 |   5.03% |     1483889 | rtm::qvvf
|                8.64 |                8.65 |   4.69% |     1364833 | move::math (float)
|                8.64 |                8.65 |   4.76% |     1364487 | rtm::matrix4x4f
|                8.96 |                8.94 |   5.13% |     1322409 | LAB
|               12.09 |               12.12 |   5.69% |      987363 | SimpleMath
|               20.71 |               19.76 |   3.84% |      609627 | glm
