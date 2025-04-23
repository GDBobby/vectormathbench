# Benchmark Results (ubuntu-latest)

Generated on: 2025-04-23 18:16:52
CPU: AMD EPYC 7763 64-Core Processor
OS: Ubuntu 24.04.2 LTS
OS Version: 24.04

## SSE 4.2

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.31 |                0.31 |   4.97% |    38214978 | Store float (reference 'no-op')
|                3.57 |                3.44 |   4.57% |     3519420 | Pull (1) Random Float And Store (reference 'no-op')
|                6.84 |                6.85 |   5.22% |     1694892 | Pull (2) Random Float And Store (reference 'no-op')
|               10.25 |               10.26 |   6.01% |     1179692 | Pull (3) Random Float And Store (reference 'no-op')
|               13.67 |               13.69 |   5.39% |      884070 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.83 |                6.83 |   4.52% |     1701514 | eight float const
|                6.83 |                6.84 |   5.68% |     1697788 | eight float const ref
|                6.83 |                6.90 |   4.89% |     1681270 | two float const
|                6.83 |                6.85 |   5.84% |     1697860 | one float const ref
|                6.83 |                6.84 |   5.44% |     1696686 | one float const
|                6.83 |                6.84 |   5.56% |     1694281 | two float const ref
|                6.83 |                6.84 |   4.76% |     1700371 | 16 float const ref
|                6.83 |                6.87 |   5.53% |     1696743 | 16 float const
|                6.84 |                6.85 |   6.08% |     1691539 | four float const ref
|                6.87 |                6.83 |   5.39% |     1699104 | four float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.65 |               13.67 |   5.57% |      884180 | LAB
|               13.65 |               13.67 |   5.89% |      885047 | move (float)
|               13.68 |               13.73 |   5.60% |      880215 | glm
|               13.69 |               13.76 |   5.43% |      883784 | DirectX
|               13.73 |               13.80 |   5.79% |      871129 | SimpleMath

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.48 |               20.51 |   5.46% |      590024 | LAB
|               20.49 |               20.59 |   5.16% |      589166 | glm
|               20.49 |               20.52 |   5.40% |      587472 | move (float)
|               20.49 |               20.51 |   5.49% |      589778 | DirectX
|               21.44 |               20.62 |   3.75% |      588014 | SimpleMath

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.54 |               27.77 |   5.22% |      436215 | move (float)
|               27.70 |               27.74 |   5.61% |      437654 | LAB
|               27.73 |               27.79 |   5.12% |      436257 | DXM
|               27.75 |               27.92 |   5.61% |      436683 | rtm
|               27.77 |               27.52 |   5.25% |      440720 | SimpleMath
|               27.85 |               27.51 |   5.92% |      442012 | glm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.86 |                4.85 |   4.95% |     2491601 | DXM w/out loads
|               61.43 |               61.52 |   5.88% |      196621 | DXM
|               61.47 |               61.58 |   5.36% |      196282 | LAB
|               61.73 |               61.82 |   5.62% |      195386 | glm
|               61.75 |               62.51 |   5.86% |      193052 | SimpleMath
|               64.89 |               62.18 |   4.76% |      192192 | move (float)

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.51 |                2.60 |   2.94% |     4581623 | DXM w/out loads
|               40.95 |               41.02 |   5.77% |      294583 | LAB
|               40.95 |               41.00 |   5.39% |      295194 | move::math (float)
|               40.98 |               41.03 |   5.41% |      295024 | glm
|               40.98 |               41.05 |   5.27% |      294330 | SimpleMath
|               41.02 |               41.04 |   5.34% |      294903 | DXM

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.43 |                1.43 |   5.87% |     8317235 | DXM w/out loads
|               54.63 |               54.66 |   5.35% |      221155 | SimpleMath
|               54.72 |               54.68 |   5.28% |      221379 | rtm
|               54.83 |               55.58 |   5.60% |      210034 | DXM
|               54.85 |               54.69 |   5.05% |      221293 | LAB
|               54.90 |               54.70 |   5.11% |      221230 | move::math(float)
|               54.99 |               54.66 |   4.75% |      221307 | glm

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.25 |                1.24 |   5.81% |     9602755 | LAB (~transformation matrix)
|                1.34 |                1.38 |   3.91% |     8672692 | move::math (builtin, float)
|                3.03 |                3.04 |   5.42% |     3989196 | rtm::qvvf (~transformation matrix)
|                3.73 |                3.73 |   5.56% |     3240171 | DXM (builtin)
|                3.76 |                3.76 |   5.19% |     3219355 | rtm::matrix4x4f
|                4.17 |                4.26 |   5.91% |     2866523 | rtm::matrix3x4f
|               44.22 |               44.01 |   5.15% |      274137 | DXM (manual)
|               66.94 |               67.34 |   5.71% |      171934 | SimpleMath
|               83.24 |               80.70 |   5.55% |      148001 | move::math (manual, float)
|               93.19 |               91.93 |   5.84% |      128488 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.85% |     9463019 | move::math (float)
|                3.73 |                3.74 |   5.57% |     3233925 | rtm::matrix4x4f
|                3.73 |                3.73 |   5.40% |     3226148 | DXM
|                3.74 |                3.78 |   5.44% |     3183473 | glm
|                3.77 |                3.75 |   4.60% |     3194404 | SimpleMath
|               18.70 |               18.81 |   5.79% |      634703 | LAB

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.25 |                1.25 |   5.11% |     9631292 | move::math (float)
|                3.73 |                3.74 |   5.90% |     3204733 | rtm::matrix4x4f
|                3.73 |                3.73 |   5.87% |     3227314 | DXM
|                3.73 |                3.74 |   5.19% |     3192628 | SimpleMath
|               23.59 |               23.62 |   5.45% |      507412 | LAB
|               27.98 |               27.82 |   6.10% |      431013 | glm

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   6.00% |     9542095 | LAB
|                1.25 |                1.27 |   5.75% |     9365627 | move::math (float)
|                3.73 |                3.73 |   5.49% |     3209723 | SimpleMath
|                3.73 |                3.73 |   5.62% |     3224542 | DXM
|                3.73 |                3.74 |   6.07% |     3201274 | rtm::matrix4x4f
|                3.75 |                3.74 |   4.80% |     3202436 | glm

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.38 |                1.39 |   4.75% |     8494597 | rtm::matrix4x4f
|                5.11 |                5.10 |   6.08% |     2353768 | rtm::qvvf
|                7.41 |                7.43 |   5.81% |     1568786 | move::math (float)
|                7.41 |                7.42 |   4.53% |     1574678 | LAB
|               10.04 |               10.04 |   4.52% |     1193243 | DXM
|               14.40 |               14.41 |   5.59% |      837504 | glm
|               15.45 |               15.48 |   5.48% |      780268 | SimpleMath

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.66 |                4.67 |   5.51% |     2563948 | move::math (float)
|                4.71 |                4.71 |   5.43% |     2542019 | SimpleMath
|                4.74 |                4.73 |   5.89% |     2512121 | DXM
|                4.97 |                5.05 |   6.21% |     2378829 | rtm::matrix4x4f
|                5.19 |                5.19 |   5.97% |     2312721 | LAB
|                6.59 |                6.67 |   5.83% |     1725112 | rtm::qvvf
|                6.98 |                7.01 |   6.09% |     1634183 | glm

## AVX

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.31 |                0.31 |   5.48% |    38875456 | Store float (reference 'no-op')
|                3.63 |                3.45 |   5.11% |     3480154 | Pull (1) Random Float And Store (reference 'no-op')
|                6.84 |                6.84 |   4.56% |     1699752 | Pull (2) Random Float And Store (reference 'no-op')
|               10.25 |               10.25 |   5.27% |     1179547 | Pull (3) Random Float And Store (reference 'no-op')
|               13.65 |               13.67 |   5.39% |      878863 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.82 |                6.83 |   5.78% |     1698596 | two float const ref
|                6.83 |                6.83 |   4.54% |     1701523 | eight float const ref
|                6.83 |                6.85 |   5.43% |     1693629 | 16 float const
|                6.83 |                6.84 |   5.44% |     1697321 | four float const ref
|                6.83 |                6.84 |   5.61% |     1694945 | one float const ref
|                6.83 |                6.84 |   4.60% |     1701582 | one float const
|                6.83 |                6.84 |   5.19% |     1697013 | two float const
|                6.83 |                6.84 |   5.85% |     1696760 | 16 float const ref
|                6.84 |                6.83 |   4.72% |     1702310 | four float const
|                6.84 |                6.84 |   5.76% |     1697435 | eight float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.65 |               13.67 |   5.76% |      885035 | DirectX
|               13.65 |               13.69 |   5.21% |      881158 | LAB
|               13.65 |               13.67 |   5.88% |      884760 | move (float)
|               13.65 |               13.67 |   5.59% |      884414 | glm
|               13.68 |               13.67 |   5.86% |      884324 | SimpleMath

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.48 |               20.51 |   5.69% |      589724 | SimpleMath
|               20.49 |               20.51 |   5.87% |      589875 | LAB
|               20.53 |               20.52 |   5.34% |      589176 | DirectX
|               20.62 |               20.50 |   4.85% |      588064 | glm
|               20.63 |               20.50 |   4.71% |      588066 | move (float)

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.30 |               27.34 |   5.54% |      442447 | rtm
|               27.30 |               27.35 |   5.47% |      442539 | move (float)
|               27.33 |               27.36 |   5.48% |      442050 | DXM
|               27.34 |               27.64 |   5.20% |      441986 | glm
|               27.36 |               27.35 |   5.50% |      442420 | SimpleMath
|               27.37 |               27.36 |   6.11% |      442302 | LAB

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.52 |                6.55 |   5.98% |     1756406 | DXM w/out loads
|               61.47 |               61.52 |   5.89% |      196643 | LAB
|               61.51 |               61.50 |   6.07% |      196611 | move (float)
|               61.51 |               61.52 |   5.31% |      196585 | DXM
|               61.54 |               61.53 |   5.91% |      196477 | glm
|               61.59 |               61.54 |   5.24% |      196642 | SimpleMath

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.60 |                2.63 |   6.29% |     4554245 | DXM w/out loads
|               40.94 |               41.00 |   5.57% |      294709 | SimpleMath
|               40.95 |               41.03 |   5.39% |      294869 | move::math (float)
|               40.95 |               41.04 |   5.49% |      294908 | glm
|               41.03 |               41.04 |   5.35% |      294699 | DXM
|               41.20 |               40.99 |   5.03% |      294901 | LAB

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.48 |                1.45 |   6.33% |     8167419 | DXM w/out loads
|               54.59 |               54.65 |   5.57% |      221368 | glm
|               54.60 |               54.67 |   5.91% |      221269 | move::math(float)
|               54.60 |               54.71 |   5.89% |      220687 | DXM
|               54.63 |               54.71 |   5.26% |      221040 | rtm
|               54.64 |               54.69 |   5.86% |      221216 | SimpleMath
|               54.65 |               54.66 |   5.41% |      221432 | LAB

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.62 |   5.41% |    19405974 | LAB (~transformation matrix)
|                1.24 |                1.25 |   5.21% |     9649983 | move::math (builtin, float)
|                7.46 |                7.46 |   4.69% |     1566419 | rtm::qvvf (~transformation matrix)
|               12.73 |               12.76 |   5.42% |      945991 | rtm::matrix3x4f
|               13.14 |               13.05 |   4.64% |      924188 | rtm::matrix4x4f
|               36.90 |               36.99 |   5.35% |      325123 | DXM (builtin)
|               38.12 |               38.18 |   5.47% |      315144 | DXM (manual)
|               63.86 |               64.09 |   5.41% |      188821 | SimpleMath
|               89.45 |               90.33 |   5.04% |      131364 | move::math (manual, float)
|              136.14 |              136.31 |   5.64% |       87486 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   5.57% |     9618236 | move::math (float)
|                2.80 |                2.80 |   5.32% |     4302333 | glm
|                7.76 |                7.78 |   5.88% |     1500690 | rtm::matrix4x4f
|               13.13 |               13.06 |   4.79% |      923365 | LAB
|               15.00 |               15.02 |   5.69% |      805669 | SimpleMath
|               15.21 |               15.23 |   5.44% |      795831 | DXM

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   5.45% |     9591520 | move::math (float)
|               12.74 |               12.76 |   5.34% |      940791 | rtm::matrix4x4f
|               12.85 |               12.75 |   5.02% |      945604 | LAB
|               14.79 |               14.80 |   5.91% |      817415 | DXM
|               15.32 |               15.35 |   5.33% |      788161 | SimpleMath
|               15.43 |               15.13 |   5.14% |      798811 | glm

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.63 |                0.62 |   4.99% |    19406240 | LAB
|                1.24 |                1.24 |   5.43% |     9596810 | move::math (float)
|                2.80 |                2.80 |   5.57% |     4303143 | glm
|               12.75 |               12.74 |   5.21% |      946391 | rtm::matrix4x4f
|               15.20 |               15.23 |   5.41% |      796205 | DXM
|               15.63 |               15.65 |   5.23% |      769124 | SimpleMath

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.69 |                1.71 |   5.09% |     7007587 | rtm::matrix4x4f
|                5.23 |                5.10 |   5.06% |     2337523 | rtm::qvvf
|                6.76 |                6.78 |   4.36% |     1713998 | LAB
|                6.78 |                6.78 |   4.76% |     1715721 | move::math (float)
|                9.27 |                9.27 |   4.81% |     1282089 | glm
|                9.36 |                9.18 |   6.68% |     1319064 | DXM
|                9.64 |                9.66 |   5.49% |     1248423 | SimpleMath

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                3.11 |                3.11 |   5.73% |     3835421 | LAB
|                3.35 |                3.24 |   3.01% |     3732464 | move::math (float)
|                6.48 |                6.49 |   6.07% |     1774811 | rtm::qvvf
|               14.40 |               14.32 |   4.82% |      842997 | rtm::matrix4x4f
|               14.91 |               14.93 |   5.61% |      805748 | DXM
|               17.39 |               17.44 |   5.90% |      694119 | SimpleMath
|               18.45 |               18.29 |   4.22% |      651658 | glm

## AVX2

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.31 |                0.31 |   4.96% |    38734010 | Store float (reference 'no-op')
|                3.61 |                3.44 |   4.84% |     3488679 | Pull (1) Random Float And Store (reference 'no-op')
|                6.84 |                6.84 |   6.01% |     1696376 | Pull (2) Random Float And Store (reference 'no-op')
|               10.24 |               10.25 |   5.97% |     1179766 | Pull (3) Random Float And Store (reference 'no-op')
|               13.65 |               13.68 |   5.47% |      884107 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.83 |                6.84 |   5.23% |     1696886 | one float const
|                6.83 |                6.84 |   5.49% |     1697209 | four float const ref
|                6.83 |                6.92 |   5.90% |     1694353 | eight float const ref
|                6.83 |                6.84 |   5.87% |     1695816 | one float const ref
|                6.83 |                6.84 |   5.20% |     1696239 | two float const ref
|                6.83 |                6.84 |   4.55% |     1699715 | two float const
|                6.83 |                6.84 |   4.41% |     1701071 | eight float const
|                6.83 |                6.84 |   5.64% |     1697656 | 16 float const ref
|                6.87 |                6.84 |   5.49% |     1697116 | 16 float const
|                6.88 |                6.84 |   5.47% |     1696605 | four float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.65 |               13.67 |   5.44% |      882637 | LAB
|               13.66 |               13.68 |   5.90% |      884240 | SimpleMath
|               13.68 |               13.73 |   4.60% |      878762 | move (float)
|               13.70 |               13.68 |   5.66% |      883465 | glm
|               14.16 |               13.80 |   4.66% |      877140 | DirectX

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.47 |               20.52 |   5.25% |      588967 | move (float)
|               20.47 |               20.52 |   5.42% |      589688 | glm
|               20.49 |               20.52 |   5.48% |      589570 | SimpleMath
|               20.50 |               20.53 |   5.38% |      589054 | DirectX
|               20.52 |               20.50 |   6.04% |      590049 | LAB

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.30 |               27.34 |   6.03% |      441417 | LAB
|               27.30 |               27.36 |   5.38% |      442285 | DXM
|               27.31 |               27.34 |   5.84% |      442615 | glm
|               27.33 |               27.37 |   5.31% |      440996 | move (float)
|               27.34 |               27.34 |   5.33% |      442687 | SimpleMath
|               27.39 |               27.34 |   5.60% |      442750 | rtm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.23 |                6.22 |   5.74% |     1934569 | DXM w/out loads
|               61.43 |               61.50 |   5.33% |      196659 | glm
|               61.49 |               61.61 |   5.30% |      196661 | move (float)
|               61.53 |               61.53 |   5.97% |      196693 | SimpleMath
|               61.59 |               61.68 |   5.49% |      196181 | LAB
|               61.72 |               61.63 |   5.33% |      196507 | DXM

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.59 |                2.56 |   5.23% |     4614262 | DXM w/out loads
|               40.95 |               41.02 |   5.88% |      295058 | glm
|               40.95 |               41.00 |   5.44% |      294925 | LAB
|               40.99 |               41.02 |   5.63% |      294933 | move::math (float)
|               41.03 |               41.03 |   5.32% |      294872 | DXM
|               41.05 |               41.01 |   5.19% |      294949 | SimpleMath

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.40 |                1.40 |   5.38% |     8639494 | DXM w/out loads
|               54.60 |               54.67 |   5.51% |      221143 | move::math(float)
|               54.60 |               54.68 |   5.41% |      221267 | glm
|               54.70 |               54.69 |   5.49% |      221261 | rtm
|               54.81 |               54.76 |   5.52% |      220922 | LAB
|               54.94 |               54.71 |   5.77% |      221140 | SimpleMath
|               55.16 |               54.74 |   5.22% |      220938 | DXM

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.63 |   6.27% |    17907754 | LAB (~transformation matrix)
|                1.25 |                1.27 |   5.56% |     9260700 | move::math (builtin, float)
|                7.45 |                7.47 |   5.57% |     1558840 | rtm::qvvf (~transformation matrix)
|               13.04 |               13.07 |   5.97% |      919838 | rtm::matrix4x4f
|               13.70 |               13.71 |   5.80% |      881939 | rtm::matrix3x4f
|               15.21 |               15.22 |   5.63% |      795696 | DXM (builtin)
|               41.39 |               41.45 |   5.46% |      288974 | DXM (manual)
|               72.52 |               72.83 |   5.70% |      159043 | SimpleMath
|               75.06 |               75.51 |   6.46% |      153357 | move::math (manual, float)
|              122.05 |              122.62 |   5.98% |       96545 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.32% |     9488732 | move::math (float)
|                2.79 |                2.80 |   5.44% |     4248006 | glm
|               12.73 |               12.75 |   5.39% |      942479 | rtm::matrix4x4f
|               13.35 |               13.11 |   5.46% |      916663 | LAB
|               13.35 |               13.37 |   5.33% |      893955 | SimpleMath
|               14.80 |               14.84 |   4.17% |      807067 | DXM

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.99% |     9516860 | move::math (float)
|               12.72 |               12.75 |   5.60% |      936841 | LAB
|               12.73 |               12.75 |   5.87% |      943137 | rtm::matrix4x4f
|               14.80 |               14.83 |   5.41% |      808181 | SimpleMath
|               15.04 |               15.07 |   5.59% |      786689 | glm
|               15.11 |               15.22 |   4.93% |      795304 | DXM

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.63 |   5.79% |    18045076 | LAB
|                1.24 |                1.25 |   5.38% |     9490021 | move::math (float)
|                2.80 |                2.80 |   5.22% |     4245473 | glm
|               13.72 |               13.00 |   4.01% |      918617 | rtm::matrix4x4f
|               15.24 |               15.22 |   5.21% |      795617 | DXM
|               15.62 |               15.63 |   5.49% |      769860 | SimpleMath

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.78 |                1.75 |   5.27% |     7082979 | rtm::matrix4x4f
|                6.12 |                6.09 |   5.07% |     1991045 | rtm::qvvf
|                7.45 |                7.46 |   5.89% |     1564219 | move::math (float)
|                7.67 |                7.48 |   5.52% |     1561452 | LAB
|                9.34 |                9.30 |   5.01% |     1281363 | glm
|                9.73 |                9.73 |   5.03% |     1224372 | DXM
|               10.71 |               10.73 |   5.98% |     1126967 | SimpleMath

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                3.25 |                3.17 |   5.84% |     3832660 | move::math (float)
|                3.43 |                3.34 |   5.08% |     3603028 | LAB
|                6.19 |                6.18 |   5.79% |     1952135 | rtm::qvvf
|               14.18 |               14.02 |   4.80% |      861961 | rtm::matrix4x4f
|               14.92 |               14.93 |   5.98% |      807706 | SimpleMath
|               14.96 |               14.89 |   5.21% |      801602 | glm
|               16.46 |               16.47 |   5.35% |      735047 | DXM
