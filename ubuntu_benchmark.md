# Benchmark Results (ubuntu-latest)

Generated on: 2025-04-23 18:09:23
CPU: AMD EPYC 7763 64-Core Processor
OS: Ubuntu 24.04.2 LTS
OS Version: 24.04

## SSE 4.2

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.32 |                0.32 |   3.99% |    37244246 | Store float (reference 'no-op')
|                3.41 |                3.42 |   5.25% |     3534546 | Pull (1) Random Float And Store (reference 'no-op')
|                6.83 |                6.85 |   5.17% |     1693679 | Pull (2) Random Float And Store (reference 'no-op')
|               10.25 |               10.27 |   5.35% |     1176684 | Pull (3) Random Float And Store (reference 'no-op')
|               13.66 |               13.69 |   5.21% |      882919 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.82 |                6.83 |   5.54% |     1699810 | two float const
|                6.83 |                6.83 |   5.37% |     1698894 | two float const ref
|                6.83 |                6.83 |   4.60% |     1701614 | four float const
|                6.83 |                6.83 |   4.56% |     1702713 | one float const
|                6.83 |                6.84 |   5.39% |     1698949 | one float const ref
|                6.84 |                6.84 |   5.61% |     1698791 | four float const ref

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.66 |               13.68 |   5.84% |      878934 | LAB
|               13.67 |               13.69 |   5.75% |      884347 | move (float)
|               13.68 |               13.68 |   5.86% |      882985 | DirectX
|               13.70 |               13.67 |   5.13% |      885249 | SimpleMath
|               13.92 |               13.72 |   5.55% |      882906 | glm

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.47 |               20.50 |   5.86% |      590340 | move (float)
|               20.47 |               20.52 |   5.42% |      588849 | LAB
|               20.48 |               20.51 |   5.49% |      590136 | SimpleMath
|               20.48 |               20.52 |   5.13% |      588834 | DirectX
|               20.51 |               20.56 |   5.61% |      588232 | glm

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.29 |               27.33 |   5.51% |      442650 | move (float)
|               27.31 |               27.34 |   5.46% |      442517 | rtm
|               27.32 |               27.33 |   5.91% |      442872 | LAB
|               27.33 |               27.37 |   5.64% |      441954 | DXM
|               27.33 |               27.35 |   5.67% |      442415 | SimpleMath
|               27.47 |               27.35 |   4.89% |      440563 | glm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.81 |                4.81 |   5.46% |     2500978 | DXM w/out loads
|               61.91 |               61.54 |   4.83% |      196558 | DXM
|               61.95 |               61.74 |   4.60% |      195663 | move (float)
|               62.14 |               62.29 |   5.53% |      194990 | SimpleMath
|               62.71 |               62.43 |   5.50% |      193974 | glm
|               62.81 |               62.00 |   5.68% |      194627 | LAB

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.63 |                2.59 |   6.09% |     4604686 | DXM w/out loads
|               40.94 |               41.01 |   5.85% |      294757 | LAB
|               41.01 |               41.00 |   5.37% |      295151 | move::math (float)
|               41.04 |               41.15 |   4.77% |      292771 | glm
|               41.06 |               41.01 |   5.23% |      295058 | DXM
|               41.24 |               41.02 |   5.61% |      294835 | SimpleMath

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.43 |                1.44 |   5.64% |     8170207 | DXM w/out loads
|               54.59 |               54.68 |   5.54% |      221111 | rtm
|               54.59 |               54.80 |   5.78% |      221316 | move::math(float)
|               54.63 |               54.68 |   5.36% |      221289 | DXM
|               54.63 |               54.68 |   6.02% |      220968 | SimpleMath
|               54.63 |               54.72 |   5.45% |      221173 | LAB
|               55.03 |               54.67 |   4.77% |      221260 | glm

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.25 |                1.25 |   4.84% |     9553741 | LAB (~transformation matrix)
|                1.25 |                1.25 |   5.08% |     9511149 | move::math (builtin, float)
|                2.84 |                2.81 |   4.48% |     4268533 | rtm::qvvf (~transformation matrix)
|                3.74 |                3.74 |   5.07% |     3205091 | rtm::matrix3x4f
|                3.75 |                3.74 |   5.23% |     3219130 | DXM (builtin)
|                3.75 |                3.74 |   5.63% |     3228369 | rtm::matrix4x4f
|               43.91 |               44.09 |   5.49% |      272765 | DXM (manual)
|               67.74 |               67.26 |   5.48% |      172372 | SimpleMath
|               79.07 |               78.93 |   5.22% |      148345 | move::math (manual, float)
|               89.78 |               90.21 |   6.13% |      130648 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.26 |                1.25 |   5.18% |     9599685 | move::math (float)
|                3.73 |                3.88 |   6.36% |     3177693 | glm
|                3.73 |                3.73 |   5.48% |     3221774 | SimpleMath
|                3.73 |                3.73 |   6.02% |     3227776 | DXM
|                3.74 |                3.74 |   5.01% |     3241234 | rtm::matrix4x4f
|               18.73 |               18.75 |   5.22% |      643242 | LAB

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   5.32% |     9558561 | move::math (float)
|                3.73 |                3.73 |   5.96% |     3231025 | SimpleMath
|                3.73 |                3.73 |   5.80% |     3238582 | rtm::matrix4x4f
|                3.73 |                3.74 |   5.26% |     3239629 | DXM
|               23.59 |               23.61 |   5.99% |      511249 | LAB
|               27.82 |               27.68 |   4.75% |      436944 | glm

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.99% |     9441491 | move::math (float)
|                1.26 |                1.28 |   5.29% |     9481736 | LAB
|                3.73 |                3.74 |   5.95% |     3207971 | rtm::matrix4x4f
|                3.73 |                3.73 |   5.87% |     3229569 | SimpleMath
|                3.75 |                3.75 |   5.83% |     3200676 | DXM
|                3.82 |                3.74 |   4.04% |     3231495 | glm

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.39 |                1.39 |   4.55% |     8707853 | rtm::matrix4x4f
|                5.02 |                5.15 |   6.05% |     2336127 | rtm::qvvf
|                7.42 |                7.44 |   5.85% |     1564877 | move::math (float)
|                7.44 |                7.43 |   5.50% |     1566486 | LAB
|               10.04 |               10.02 |   6.32% |     1201231 | DXM
|               14.28 |               14.30 |   5.85% |      842548 | glm
|               15.39 |               15.46 |   5.17% |      775328 | SimpleMath

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                4.66 |                4.67 |   4.87% |     2565762 | move::math (float)
|                4.74 |                4.71 |   5.06% |     2533421 | SimpleMath
|                4.97 |                4.98 |   5.49% |     2398912 | DXM
|                4.97 |                4.99 |   5.31% |     2395379 | rtm::matrix4x4f
|                5.04 |                5.06 |   7.19% |     2361890 | LAB
|                6.45 |                6.82 |   4.70% |     1609955 | glm
|                6.82 |                6.83 |   5.51% |     1682375 | rtm::qvvf

## AVX

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.31 |                0.31 |   5.73% |    38677174 | Store float (reference 'no-op')
|                3.41 |                3.52 |   4.99% |     3492039 | Pull (1) Random Float And Store (reference 'no-op')
|                6.84 |                6.83 |   4.83% |     1701954 | Pull (2) Random Float And Store (reference 'no-op')
|               10.24 |               10.26 |   5.39% |     1176938 | Pull (3) Random Float And Store (reference 'no-op')
|               13.69 |               13.67 |   5.85% |      885802 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.82 |                6.83 |   4.62% |     1700748 | one float const ref
|                6.83 |                6.85 |   5.70% |     1696677 | two float const ref
|                6.83 |                6.85 |   4.91% |     1696630 | two float const
|                6.84 |                6.84 |   5.60% |     1698742 | four float const
|                6.92 |                6.88 |   6.00% |     1687767 | one float const
|                6.92 |                6.93 |   4.43% |     1683584 | four float const ref

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.72 |               13.81 |   5.32% |      876168 | move (float)
|               13.83 |               13.87 |   5.30% |      858651 | SimpleMath
|               13.89 |               13.88 |   4.85% |      873973 | LAB
|               13.93 |               13.89 |   5.03% |      871899 | DirectX
|               14.02 |               13.92 |   4.85% |      870231 | glm

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.48 |               20.52 |   5.28% |      588440 | glm
|               20.48 |               20.52 |   5.91% |      589036 | DirectX
|               20.50 |               20.50 |   6.00% |      589892 | LAB
|               20.56 |               20.62 |   5.85% |      586594 | SimpleMath
|               20.58 |               20.74 |   5.50% |      583194 | move (float)

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.30 |               27.37 |   5.81% |      441793 | glm
|               27.30 |               27.43 |   5.37% |      441554 | DXM
|               27.32 |               27.35 |   5.82% |      442613 | rtm
|               27.34 |               27.33 |   5.54% |      441750 | move (float)
|               27.47 |               27.33 |   4.93% |      440897 | LAB
|               28.04 |               27.49 |   4.85% |      440444 | SimpleMath

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.61 |                6.56 |   5.74% |     1749552 | DXM w/out loads
|               61.41 |               61.50 |   5.51% |      196686 | move (float)
|               61.42 |               61.53 |   5.72% |      196712 | LAB
|               61.45 |               61.53 |   5.95% |      196558 | SimpleMath
|               61.46 |               61.50 |   5.45% |      196835 | DXM
|               61.47 |               61.49 |   5.36% |      196761 | glm

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.75 |                2.65 |   4.17% |     4513007 | DXM w/out loads
|               40.94 |               41.00 |   5.80% |      294834 | move::math (float)
|               40.95 |               41.00 |   6.02% |      294739 | glm
|               40.97 |               41.01 |   5.97% |      294384 | DXM
|               40.98 |               41.03 |   5.79% |      295001 | SimpleMath
|               41.00 |               41.01 |   5.54% |      295108 | LAB

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.59 |                1.59 |   6.04% |     7503006 | DXM w/out loads
|               54.59 |               54.69 |   5.67% |      221119 | LAB
|               54.59 |               54.71 |   5.30% |      221069 | move::math(float)
|               54.63 |               54.66 |   5.46% |      221500 | rtm
|               54.63 |               54.66 |   5.47% |      221414 | glm
|               55.29 |               54.69 |   4.91% |      221313 | DXM
|               55.34 |               54.78 |   5.24% |      221319 | SimpleMath

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.63 |                0.63 |   5.38% |    18205051 | LAB (~transformation matrix)
|                1.24 |                1.24 |   5.59% |     9708557 | move::math (builtin, float)
|                7.45 |                7.46 |   5.74% |     1564972 | rtm::qvvf (~transformation matrix)
|               13.04 |               13.05 |   5.58% |      924467 | rtm::matrix4x4f
|               17.37 |               17.40 |   5.87% |      693854 | rtm::matrix3x4f
|               37.07 |               36.99 |   4.91% |      327169 | DXM (builtin)
|               37.90 |               37.95 |   5.63% |      317275 | DXM (manual)
|               63.76 |               63.84 |   5.87% |      188940 | SimpleMath
|               90.11 |               90.40 |   5.36% |      130769 | move::math (manual, float)
|              136.81 |              136.99 |   5.30% |       87246 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.38% |     9613750 | move::math (float)
|                7.76 |                7.81 |   6.45% |     1484730 | rtm::matrix4x4f
|               10.00 |                9.95 |   5.00% |     1209984 | glm
|               13.04 |               13.05 |   5.77% |      923488 | LAB
|               16.55 |               16.57 |   5.50% |      727744 | SimpleMath
|               17.91 |               17.72 |   4.88% |      680054 | DXM

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   5.36% |     9605702 | move::math (float)
|               12.72 |               12.74 |   5.89% |      947228 | LAB
|               13.10 |               12.82 |   5.19% |      937299 | rtm::matrix4x4f
|               17.69 |               17.71 |   5.34% |      679958 | DXM
|               20.62 |               20.56 |   5.28% |      588180 | SimpleMath
|               22.58 |               22.68 |   5.11% |      532321 | glm

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.63 |   5.99% |    17488592 | LAB
|                1.24 |                1.24 |   5.61% |     9603394 | move::math (float)
|                9.93 |                9.94 |   5.54% |     1212675 | glm
|               12.72 |               12.74 |   5.95% |      946901 | rtm::matrix4x4f
|               17.70 |               17.71 |   4.58% |      683752 | DXM
|               20.66 |               20.67 |   5.49% |      585307 | SimpleMath

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.68 |                1.70 |   4.64% |     6917392 | rtm::matrix4x4f
|                5.26 |                5.16 |   6.29% |     2327779 | rtm::qvvf
|                6.79 |                6.80 |   5.44% |     1709773 | LAB
|                6.79 |                6.79 |   4.59% |     1712481 | move::math (float)
|                9.38 |                9.38 |   4.73% |     1269089 | DXM
|                9.70 |                9.70 |   5.28% |     1228111 | SimpleMath
|                9.75 |                9.76 |   4.48% |     1222546 | glm

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                3.11 |                3.11 |   5.51% |     3852076 | LAB
|                3.19 |                3.23 |   5.28% |     3678949 | move::math (float)
|                9.42 |                8.20 |  14.75% |     1613386 | rtm::qvvf
|               15.81 |               15.84 |   4.63% |      762897 | rtm::matrix4x4f
|               17.41 |               17.44 |   5.08% |      692249 | SimpleMath
|               20.79 |               20.78 |   5.37% |      575149 | glm
|               21.77 |               21.76 |   5.46% |      554425 | DXM

## AVX2

| no-op
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.31 |                0.32 |   3.94% |    37696658 | Store float (reference 'no-op')
|                3.46 |                3.42 |   4.99% |     3523815 | Pull (1) Random Float And Store (reference 'no-op')
|                6.84 |                6.83 |   4.86% |     1700773 | Pull (2) Random Float And Store (reference 'no-op')
|               10.24 |               10.25 |   5.36% |     1171041 | Pull (3) Random Float And Store (reference 'no-op')
|               13.65 |               13.66 |   5.98% |      885270 | Pull (4) Random Float And Store (reference 'no-op')

| testing const& param vs const param
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.82 |                6.84 |   5.56% |     1698032 | two float const ref
|                6.82 |                6.84 |   5.35% |     1697364 | one float const
|                6.83 |                6.83 |   4.40% |     1701381 | one float const ref
|                6.83 |                6.83 |   4.78% |     1700687 | four float const
|                6.83 |                6.83 |   4.66% |     1702009 | four float const ref
|                6.84 |                6.84 |   5.14% |     1696252 | two float const

| vec2 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               13.65 |               13.69 |   5.43% |      884572 | LAB
|               13.65 |               13.67 |   5.42% |      884762 | SimpleMath
|               13.66 |               13.68 |   5.40% |      879977 | glm
|               13.67 |               13.70 |   5.94% |      882350 | DirectX
|               13.77 |               13.74 |   5.48% |      879489 | move (float)

| vec3 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               20.47 |               20.52 |   5.42% |      586476 | LAB
|               20.48 |               20.59 |   5.02% |      583381 | move (float)
|               20.49 |               20.52 |   5.47% |      589893 | DirectX
|               20.49 |               20.51 |   5.40% |      589797 | glm
|               20.64 |               20.60 |   5.15% |      588302 | SimpleMath

| vec4 add
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|               27.29 |               27.33 |   5.42% |      442466 | LAB
|               27.29 |               27.37 |   5.67% |      442071 | glm
|               27.30 |               27.35 |   5.65% |      442660 | move (float)
|               27.31 |               27.34 |   5.71% |      440498 | SimpleMath
|               27.32 |               27.35 |   5.30% |      442201 | DXM
|               27.46 |               27.33 |   4.97% |      440815 | rtm

| dot and cross
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                6.25 |                6.22 |   4.89% |     1935568 | DXM w/out loads
|               61.42 |               61.52 |   5.42% |      196769 | SimpleMath
|               61.45 |               61.55 |   5.44% |      196721 | glm
|               61.47 |               61.55 |   5.89% |      196478 | DXM
|               61.56 |               61.57 |   5.27% |      196524 | move (float)
|               61.78 |               61.82 |   5.90% |      195395 | LAB

| add sub multi cross vec3
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                2.55 |                2.55 |   6.07% |     4696584 | DXM w/out loads
|               40.94 |               41.04 |   5.81% |      294131 | DXM
|               40.95 |               41.00 |   5.39% |      294622 | glm
|               40.95 |               41.01 |   5.81% |      295164 | SimpleMath
|               40.97 |               41.00 |   5.36% |      295158 | LAB
|               41.26 |               41.05 |   5.64% |      294825 | move::math (float)

| add sub multi vec4
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.67 |                1.66 |   5.91% |     7268447 | DXM w/out loads
|               54.59 |               54.65 |   5.85% |      221292 | LAB
|               54.59 |               54.68 |   5.36% |      221386 | move::math(float)
|               54.59 |               54.68 |   5.43% |      221218 | rtm
|               54.60 |               54.69 |   5.34% |      221197 | glm
|               54.61 |               54.71 |   5.53% |      221139 | DXM
|               55.13 |               54.76 |   4.96% |      221015 | SimpleMath

| model matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.63 |   6.41% |    18171551 | LAB (~transformation matrix)
|                1.24 |                1.25 |   5.32% |     9691038 | move::math (builtin, float)
|                7.45 |                7.45 |   4.66% |     1567565 | rtm::qvvf (~transformation matrix)
|               12.94 |               13.24 |   3.25% |      916101 | rtm::matrix3x4f
|               13.18 |               13.09 |   5.20% |      923156 | rtm::matrix4x4f
|               15.21 |               15.26 |   5.03% |      791636 | DXM (builtin)
|               41.27 |               41.31 |   5.39% |      291498 | DXM (manual)
|               72.53 |               72.60 |   4.74% |      160512 | SimpleMath
|               74.59 |               74.75 |   5.60% |      156009 | move::math (manual, float)
|              122.22 |              122.38 |   5.53% |       97678 | glm

| view matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.25 |   5.35% |     9672557 | move::math (float)
|                2.80 |                2.80 |   5.36% |     4302117 | glm
|               12.72 |               12.77 |   5.37% |      940609 | rtm::matrix4x4f
|               13.39 |               13.39 |   5.51% |      897544 | SimpleMath
|               13.60 |               13.53 |   5.07% |      890638 | LAB
|               14.31 |               14.30 |   5.62% |      842621 | DXM

| perspective matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                1.24 |                1.24 |   5.32% |     9619172 | move::math (float)
|               12.72 |               12.74 |   5.97% |      947750 | rtm::matrix4x4f
|               13.89 |               13.49 |   6.16% |      904288 | LAB
|               15.06 |               15.07 |   6.03% |      798775 | glm
|               15.21 |               15.25 |   5.10% |      795265 | DXM
|               15.33 |               15.32 |   5.33% |      783572 | SimpleMath

| ortho matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                0.62 |                0.62 |   6.46% |    18302736 | LAB
|                1.24 |                1.24 |   5.20% |     9524692 | move::math (float)
|                2.80 |                2.80 |   5.45% |     4283066 | glm
|               13.62 |               12.90 |   3.87% |      928506 | rtm::matrix4x4f
|               15.28 |               15.24 |   4.72% |      794176 | DXM
|               15.62 |               15.63 |   5.39% |      773828 | SimpleMath

| matrix * vector
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                3.54 |                3.54 |   5.18% |     3410551 | rtm::matrix4x4f
|                7.24 |                7.36 |   6.10% |     1555998 | rtm::qvvf
|                7.44 |                7.46 |   5.08% |     1564491 | LAB
|                7.46 |                7.46 |   5.56% |     1565662 | move::math (float)
|                9.36 |                9.33 |   5.45% |     1271175 | glm
|               10.89 |               10.88 |   5.28% |     1112977 | DXM
|               11.51 |               11.51 |   6.04% |     1050549 | SimpleMath

| matrix * matrix
|      ns/op (median) |      ns/op(average) |    err% |  iterations | library
|--------------------:|--------------------:|--------:|------------:|:----------
|                3.13 |                3.13 |   5.19% |     3837171 | move::math (float)
|                3.26 |                3.30 |   5.31% |     3631559 | LAB
|                6.16 |                6.17 |   5.98% |     1950427 | rtm::qvvf
|               13.97 |               13.99 |   5.41% |      862700 | rtm::matrix4x4f
|               14.83 |               14.84 |   5.50% |      802951 | glm
|               15.01 |               15.03 |   6.07% |      803033 | SimpleMath
|               16.46 |               16.47 |   5.35% |      735473 | DXM
