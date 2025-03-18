# Benchmark Results (windows-2022) 
 
## System Info 
CPU: AMD EPYC 7763 64-Core Processor                 
OS: Microsoft Windows Server 2022 Datacenter 
OS Version: 10.0.20348 N/A Build 20348 
 
## SSE 4.2 

| no-op
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648290777.44 |   0.00% |      0.00 | Store int (reference 'no-op')

| vector 2
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648779488.04 |   0.00% |      0.00 | glm
|                1.54 |        647773244.21 |   0.00% |      0.00 | Vectormath
|                1.54 |        647744177.31 |   0.00% |      0.00 | DirectX
|                1.54 |        647736352.76 |   0.00% |      0.00 | LAB
|                1.54 |        647702781.56 |   0.00% |      0.00 | SimpleMath
|                1.85 |        540649700.34 |   0.00% |      0.00 | move (float)
|                1.85 |        539773240.66 |   0.00% |      0.00 | move (double)

| vector 3
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648189512.42 |   0.00% |      0.00 | move (double)
|                1.54 |        648175349.20 |   0.00% |      0.00 | SimpleMath
|                1.54 |        647771152.02 |   0.00% |      0.00 | Vectormath
|                1.85 |        540104055.24 |   0.00% |      0.00 | glm
|                1.85 |        539755016.94 |   0.00% |      0.00 | DirectX
|                1.85 |        539737806.60 |   0.00% |      0.00 | move (float)
|                1.85 |        539725683.70 |   0.00% |      0.00 | LAB

| vector 4
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648176985.92 |   0.00% |      0.00 | move::vec4f addition (float)
|                1.54 |        648175449.60 |   0.00% |      0.00 | DirectX::XMFLOAT4 addition without Loads
|                1.54 |        648160286.42 |   0.00% |      0.00 | glm::vec4 addition
|                1.54 |        647781745.34 |   0.00% |      0.00 | rtm::vector4d addition
|                1.54 |        647734125.96 |   0.00% |      0.00 | rtm::vector4f addition
|                1.54 |        647708597.64 |   0.00% |      0.00 | SimpleMath::Vector4 addition
|                1.85 |        540105363.98 |   0.00% |      0.00 | Vectormath::Vector4 addition
|                1.85 |        539780081.95 |   0.00% |      0.00 | move::vec4d addition (double)
|               11.05 |         90537623.95 |   0.00% |      0.00 | LAB::vector4 addition

| complex1
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648197063.17 |   0.00% |      0.00 | Complex operation 1 with move::math::* (float)
|                1.54 |        648179688.81 |   0.00% |      0.00 | Complex operation 1 with glm::vec*
|                1.54 |        648175090.08 |   0.00% |      0.00 | Complex operation 1 with lab::vector
|                1.85 |        540138685.42 |   0.00% |      0.00 | Complex operation 1 with Vectormath
|                2.23 |        447555729.37 |   0.00% |      0.00 | Complex operation 1 with DXM
|                3.40 |        294522153.41 |   0.00% |      0.00 | Complex operation 1 with move::math::* (double)
|                3.50 |        285696981.54 |   0.00% |      0.00 | Complex operation 1 with SimpleMath::Vector*
|                4.85 |        206338210.41 |   0.00% |      0.00 | Complex operation 1 with DXM w/out loads

| complex2 vec3
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        647783482.34 |   0.00% |      0.00 | Complex operation 2 with Vectormath
|                1.54 |        647736579.97 |   0.00% |      0.00 | Complex operation 2 with glm::vec3
|                1.54 |        647735106.78 |   0.00% |      0.00 | Complex operation 2 with move::math (float)
|                1.85 |        539959215.55 |   0.00% |      0.00 | Complex operation 2 with DXM w/out loads
|                1.85 |        539770621.16 |   0.00% |      0.00 | Complex operation 2 with DXM
|                2.16 |        462559663.54 |   0.00% |      0.00 | Complex operation 2 with lab::vec3
|                2.47 |        404734816.80 |   0.00% |      0.00 | Complex operation 2 with move::math (double)
|                3.11 |        321736265.87 |   0.00% |      0.00 | Complex operation 2 with SimpleMath::Vector3

| complex3 vec4
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648199370.96 |   0.00% |      0.00 | Complex operation 3 with rtm::vector4f
|                1.54 |        648184815.62 |   0.00% |      0.00 | Complex operation 3 with move::math (float)
|                1.54 |        648156440.55 |   0.00% |      0.00 | Complex operation 3 with glm::vec4
|                1.54 |        648155281.11 |   0.00% |      0.00 | Complex operation 3 with Vectormath
|                1.54 |        647756242.36 |   0.00% |      0.00 | Complex operation 3 with SimpleMath::Vector4
|                1.54 |        647726641.19 |   0.00% |      0.00 | Complex operation 3 with DXM
|                1.85 |        540092911.22 |   0.00% |      0.00 | Complex operation 3 with DXM w/out loads
|                1.85 |        539724971.45 |   0.00% |      0.00 | Complex operation 3 with rtm::vector4d
|                2.16 |        462912929.75 |   0.00% |      0.00 | Complex operation 3 with move::math (double)
|               12.08 |         82793119.92 |   0.00% |      0.00 | Complex operation 3 with lab::vec4

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |        648326670.47 |   0.00% |      0.00 | Construct model matrix move::math (builtin, double)
|                1.54 |        647711174.24 |   0.00% |      0.00 | Construct rtm::qvvf (~transformation matrix)
|                1.85 |        539648655.61 |   0.00% |      0.00 | Construct rtm::qvvd (~transformation matrix)
|                7.24 |        138046389.50 |   0.00% |      0.00 | Construct model matrix rtm::matrix3x4f
|                8.27 |        120923076.92 |   0.00% |      0.00 | Construct model matrix move::math (builtin, float)
|                8.76 |        114182163.19 |   0.02% |      0.00 | Construct model matrix rtm::matrix4x4f
|               12.49 |         80080062.66 |   0.01% |      0.00 | Construct model matrix rtm::matrix3x4d
|               12.81 |         78071490.85 |   0.00% |      0.00 | Construct model matrix rtm::matrix4x4d
|               17.88 |         55921942.76 |   0.00% |      0.00 | Construct model matrix LAB (~transformation matrix)
|               23.29 |         42928819.44 |   0.00% |      0.00 | Construct model matrix Vectormath
|               45.48 |         21989366.84 |   0.00% |      0.00 | Construct model matrix DXM (builtin)
|               53.10 |         18833085.86 |   0.00% |      0.00 | Construct model matrix SimpleMath
|               53.10 |         18832268.09 |   0.00% |      0.00 | Construct model matrix DXM (manual)
|              121.61 |          8222720.22 |   0.00% |      0.00 | Construct model matrix move::math (manual, double)
|              138.16 |          7237968.42 |   0.00% |      0.00 | Construct model matrix move::math (manual, float)
|              168.55 |          5933112.32 |   0.00% |      0.00 | Construct model matrix glm

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                8.11 |        123268496.98 |   0.00% |      0.00 | Construct view matrix move::math (float)
|               17.94 |         55736325.39 |   0.00% |      0.00 | Construct view matrix rtm::matrix4x4f
|               18.63 |         53670167.47 |   0.00% |      0.00 | Construct view matrix glm
|               22.19 |         45072944.88 |   0.00% |      0.00 | Construct view matrix DXM
|               22.69 |         44063161.61 |   0.02% |      0.00 | Construct view matrix SimpleMath
|               40.45 |         24724626.65 |   0.00% |      0.00 | Construct view matrix Vectormath
|               44.11 |         22671215.13 |   0.00% |      0.00 | Construct view matrix LAB
|               55.93 |         17878762.54 |   0.00% |      0.00 | Construct view matrix rtm::matrix4x4d
|               58.37 |         17131789.77 |   0.00% |      0.00 | Construct view matrix move::math (double)

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                2.47 |        404993678.89 |   0.00% |      0.00 | Construct perspective matrix rtm::matrix4x4d
|                2.47 |        404979514.34 |   0.00% |      0.00 | Construct perspective matrix move::math (double)
|                9.00 |        111148441.14 |   0.00% |      0.00 | Construct perspective matrix glm
|                9.13 |        109507494.65 |   0.00% |      0.00 | Construct perspective matrix move::math (float)
|                9.13 |        109486491.02 |   0.00% |      0.00 | Construct perspective matrix rtm::matrix4x4f
|               10.80 |         92618897.78 |   0.00% |      0.00 | Construct perspective matrix LAB
|               12.34 |         81029350.28 |   0.00% |      0.00 | Construct perspective matrix Vectormath
|               12.89 |         77573823.59 |   0.00% |      0.00 | Construct perspective matrix SimpleMath
|               13.47 |         74246586.96 |   0.00% |      0.00 | Construct perspective matrix DXM

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.85 |        540115260.05 |   0.00% |      0.00 | Construct ortho matrix lab
|                1.85 |        540088271.28 |   0.00% |      0.00 | Construct ortho matrix SimpleMath
|                1.85 |        539751435.83 |   0.00% |      0.00 | Construct ortho matrix rtm::matrix4x4f
|                1.85 |        539746953.20 |   0.00% |      0.00 | Construct ortho matrix move::math (float)
|                2.16 |        462644326.76 |   0.00% |      0.00 | Construct ortho matrix DXM
|                2.47 |        404989152.13 |   0.00% |      0.00 | Construct ortho matrix move::math (double)
|                2.47 |        404741286.38 |   0.00% |      0.00 | Construct ortho matrix rtm::matrix4x4d
|                9.22 |        108512847.13 |   0.01% |      0.00 | Construct ortho matrix glm
|               21.51 |         46482201.91 |   0.00% |      0.00 | Construct ortho matrix Vectormath

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.85 |        540049858.16 |   0.00% |      0.00 | Vector matrix multiply rtm::matrix4x4f
|                3.71 |        269230536.81 |   0.00% |      0.00 | Point QVV multiply rtm::qvvf
|                7.03 |        142249738.40 |   0.00% |      0.00 | Vector matrix multiply Vectormath
|                7.95 |        125785695.29 |   0.00% |      0.00 | Vector matrix multiply DXM
|                9.07 |        110253351.91 |   0.00% |      0.00 | Vector matrix multiply move::math (float)
|               11.36 |         88063104.99 |   0.00% |      0.00 | Point QVV multiply rtm::qvvd
|               11.42 |         87563125.30 |   0.00% |      0.00 | Vector matrix multiply rtm::matrix4x4d
|               12.30 |         81332002.78 |   0.00% |      0.00 | Vector matrix multiply glm
|               12.97 |         77094224.92 |   0.00% |      0.00 | Vector matrix multiply move::math (double)
|               12.99 |         76955408.39 |   0.00% |      0.00 | Vector matrix multiply SimpleMath
|               44.47 |         22485563.65 |   0.00% |      0.00 | Vector matrix multiply lab

| model matrix
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                4.42 |        226335571.72 |   0.00% |      0.00 | Matrix matrix multiply rtm::matrix4x4f
|                4.45 |        224591436.44 |   0.01% |      0.00 | Matrix matrix multiply move::math (float)
|                4.63 |        215985666.42 |   0.00% |      0.00 | Matrix matrix multiply SimpleMath
|                4.82 |        207651599.80 |   0.00% |      0.00 | Matrix matrix multiply DXM
|                4.82 |        207462769.92 |   0.00% |      0.00 | Matrix matrix multiply Vectormath
|                8.03 |        124601449.28 |   0.00% |      0.00 | QVV QVV multiply rtm::qvvf
|               20.61 |         48522698.77 |   0.00% |      0.00 | Matrix matrix multiply glm
|               20.80 |         48081143.38 |   0.00% |      0.00 | QVV QVV multiply rtm::qvvd
|               30.09 |         33230223.54 |   0.03% |      0.00 | Matrix matrix multiply LAB
|               41.98 |         23821152.34 |   0.00% |      0.00 | Matrix matrix multiply move::math (double)
|               42.00 |         23807339.45 |   0.00% |      0.00 | Matrix matrix multiply rtm::matrix4x4d
 
## AVX 

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |      648,735,554.70 |    0.0% |      0.01 | `Store int (reference 'no-op')`
|                1.54 |      648,147,858.40 |    0.0% |      0.01 | `SimpleMath`
|                1.54 |      648,742,503.57 |    0.0% |      0.01 | `glm`
|                1.54 |      648,175,267.77 |    0.0% |      0.01 | `LAB`
|                1.85 |      539,733,321.75 |    0.0% |      0.01 | `DirectX`
|                1.54 |      647,711,729.27 |    0.1% |      0.01 | `Vectormath`
|                1.85 |      539,729,220.39 |    0.1% |      0.01 | `move (float)`
|                1.54 |      647,708,597.64 |    0.0% |      0.01 | `move (double)`
|                1.54 |      647,736,162.04 |    0.1% |      0.01 | `SimpleMath`
|                1.54 |      648,175,878.97 |    0.0% |      0.01 | `glm`
|                1.85 |      539,720,985.96 |    0.1% |      0.01 | `LAB`
|                1.85 |      540,279,285.59 |    0.1% |      0.01 | `DirectX`
|                1.54 |      648,202,258.13 |    0.0% |      0.01 | `Vectormath`
|                1.54 |      647,740,459.50 |    0.1% |      0.01 | `move (float)`
|                1.54 |      647,825,758.85 |    0.1% |      0.01 | `move (double)`
|                1.54 |      647,757,017.95 |    0.1% |      0.01 | `SimpleMath::Vector4 addition`
|                1.54 |      648,168,210.31 |    0.0% |      0.01 | `glm::vec4 addition`
|                1.85 |      539,717,265.75 |    0.1% |      0.01 | `LAB::vector4 addition`
|                1.54 |      647,781,404.30 |    0.1% |      0.01 | `DirectX::XMFLOAT4 addition without Loads`
|                1.54 |      648,184,154.96 |    0.0% |      0.01 | `Vectormath::Vector4 addition`
|                1.85 |      539,705,539.36 |    0.1% |      0.01 | `move::vec4f addition (float)`
|                1.54 |      648,214,849.92 |    0.0% |      0.01 | `move::vec4d addition (double)`
|                1.54 |      647,751,325.05 |    0.1% |      0.01 | `rtm::vector4f addition`
|                7.17 |      139,498,086.29 |    0.1% |      0.01 | `rtm::vector4d addition`
|               12.96 |       77,177,825.08 |    0.1% |      0.01 | `Complex operation 1 with SimpleMath::Vector*`
|                1.54 |      647,757,872.90 |    0.1% |      0.01 | `Complex operation 1 with glm::vec*`
|                1.85 |      539,747,301.48 |    0.1% |      0.01 | `Complex operation 1 with lab::vector`
|                2.16 |      462,826,813.45 |    0.0% |      0.01 | `Complex operation 1 with DXM`
|                7.10 |      140,774,709.73 |    0.1% |      0.01 | `Complex operation 1 with DXM w/out loads`
|                1.54 |      647,766,981.79 |    0.1% |      0.01 | `Complex operation 1 with Vectormath`
|                1.54 |      648,180,423.74 |    0.0% |      0.01 | `Complex operation 1 with move::math::* (float)`
|                3.11 |      321,646,323.60 |    0.5% |      0.01 | `Complex operation 1 with move::math::* (double)`
|               34.46 |       29,020,001.67 |    0.0% |      0.01 | `Complex operation 2 with SimpleMath::Vector3`
|                1.85 |      539,759,804.35 |    0.0% |      0.01 | `Complex operation 2 with glm::vec3`
|                1.85 |      540,059,862.61 |    0.0% |      0.01 | `Complex operation 2 with lab::vec3`
|                1.85 |      540,095,890.41 |    0.0% |      0.01 | `Complex operation 2 with DXM`
|                2.16 |      462,679,173.51 |    0.0% |      0.01 | `Complex operation 2 with DXM w/out loads`
|                1.54 |      647,754,389.03 |    0.0% |      0.01 | `Complex operation 2 with Vectormath`
|                1.85 |      539,756,245.66 |    0.1% |      0.01 | `Complex operation 2 with move::math (float)`
|                1.91 |      522,498,036.14 |    0.0% |      0.01 | `Complex operation 2 with move::math (double)`
|                1.85 |      540,112,742.53 |    0.0% |      0.01 | `Complex operation 3 with SimpleMath::Vector4`
|                1.54 |      648,179,937.95 |    0.0% |      0.01 | `Complex operation 3 with glm::vec4`
|                2.16 |      462,894,211.58 |    0.0% |      0.01 | `Complex operation 3 with lab::vec4`
|                1.54 |      647,788,751.26 |    0.1% |      0.01 | `Complex operation 3 with DXM`
|                1.85 |      539,732,797.14 |    0.1% |      0.01 | `Complex operation 3 with DXM w/out loads`
|                1.54 |      647,737,192.10 |    0.0% |      0.01 | `Complex operation 3 with Vectormath`
|                1.54 |      647,737,746.53 |    0.0% |      0.01 | `Complex operation 3 with move::math (float)`
|                1.85 |      539,696,161.13 |    0.0% |      0.01 | `Complex operation 3 with move::math (double)`
|                1.54 |      647,756,263.19 |    0.0% |      0.01 | `Complex operation 3 with rtm::vector4f`
|                8.95 |      111,775,875.90 |    0.1% |      0.01 | `Complex operation 3 with rtm::vector4d`
|               87.14 |       11,475,831.65 |    0.0% |      0.01 | `Construct model matrix SimpleMath`
|              173.51 |        5,763,320.53 |    0.2% |      0.01 | `Construct model matrix glm`
|               17.93 |       55,775,229.36 |    0.1% |      0.01 | `Construct model matrix LAB (~transformation matrix)`
|               76.38 |       13,091,867.62 |    0.0% |      0.01 | `Construct model matrix DXM (manual)`
|               74.37 |       13,447,070.73 |    0.1% |      0.01 | `Construct model matrix DXM (builtin)`
|               21.97 |       45,507,713.76 |    0.2% |      0.01 | `Construct model matrix Vectormath`
|              101.67 |        9,835,302.88 |    0.2% |      0.01 | `Construct model matrix move::math (manual, float)`
|               10.21 |       97,953,847.59 |    0.1% |      0.01 | `Construct model matrix move::math (builtin, float)`
|              167.03 |        5,986,904.45 |    1.7% |      0.01 | `Construct model matrix move::math (manual, double)`
|                1.54 |      648,308,694.81 |    0.1% |      0.01 | `Construct model matrix move::math (builtin, double)`
|                7.10 |      140,905,189.23 |    0.0% |      0.01 | `Construct rtm::qvvf (~transformation matrix)`
|                9.39 |      106,541,706.62 |    1.3% |      0.01 | `Construct rtm::qvvd (~transformation matrix)`
|                7.02 |      142,359,069.22 |    0.1% |      0.01 | `Construct model matrix rtm::matrix3x4f`
|               22.41 |       44,629,907.95 |    0.1% |      0.01 | `Construct model matrix rtm::matrix3x4d`
|                7.02 |      142,425,223.02 |    0.1% |      0.01 | `Construct model matrix rtm::matrix4x4f`
|               31.69 |       31,559,318.81 |    0.1% |      0.01 | `Construct model matrix rtm::matrix4x4d`
|               58.19 |       17,183,880.07 |    0.0% |      0.01 | `Construct view matrix SimpleMath`
|               17.84 |       56,068,236.51 |    0.0% |      0.01 | `Construct view matrix glm`
|               47.53 |       21,039,444.73 |    0.1% |      0.01 | `Construct view matrix LAB`
|               14.07 |       71,060,262.01 |    0.0% |      0.01 | `Construct view matrix DXM`
|               20.88 |       47,885,428.35 |    0.1% |      0.01 | `Construct view matrix Vectormath`
|                8.03 |      124,524,596.18 |    0.0% |      0.01 | `Construct view matrix move::math (float)`
|               62.26 |       16,060,818.51 |    0.1% |      0.01 | `Construct view matrix move::math (double)`
|                8.03 |      124,496,637.66 |    0.1% |      0.01 | `Construct view matrix rtm::matrix4x4f`
|               61.72 |       16,203,213.20 |    0.1% |      0.01 | `Construct view matrix rtm::matrix4x4d`
|               11.71 |       85,371,925.03 |    0.1% |      0.01 | `Construct perspective matrix SimpleMath`
|                8.95 |      111,690,704.38 |    0.0% |      0.01 | `Construct perspective matrix glm`
|               10.19 |       98,167,932.27 |    0.1% |      0.01 | `Construct perspective matrix LAB`
|               11.49 |       87,053,173.84 |    0.0% |      0.01 | `Construct perspective matrix DXM`
|                1.85 |      540,089,464.17 |    0.0% |      0.01 | `Construct perspective matrix Vectormath`
|                7.86 |      127,166,174.68 |    0.2% |      0.01 | `Construct perspective matrix move::math (float)`
|                8.91 |      112,269,341.54 |    1.2% |      0.01 | `Construct perspective matrix move::math (double)`
|                7.88 |      126,913,689.42 |    0.2% |      0.01 | `Construct perspective matrix rtm::matrix4x4f`
|                8.03 |      124,567,798.95 |    0.1% |      0.01 | `Construct perspective matrix rtm::matrix4x4d`
|                8.02 |      124,704,545.45 |    0.0% |      0.01 | `Construct ortho matrix SimpleMath`
|                9.56 |      104,563,505.95 |    0.1% |      0.01 | `Construct ortho matrix glm`
|                7.09 |      140,954,712.36 |    0.0% |      0.01 | `Construct ortho matrix lab`
|                8.36 |      119,564,795.97 |    1.4% |      0.01 | `Construct ortho matrix DXM`
|               11.31 |       88,392,515.23 |    0.4% |      0.01 | `Construct ortho matrix Vectormath`
|                8.34 |      119,945,775.76 |    1.2% |      0.01 | `Construct ortho matrix move::math (float)`
|                8.03 |      124,580,236.72 |    0.1% |      0.01 | `Construct ortho matrix move::math (double)`
|                7.41 |      135,004,613.71 |    0.1% |      0.01 | `Construct ortho matrix rtm::matrix4x4f`
|                8.39 |      119,219,952.49 |    0.2% |      0.01 | `Construct ortho matrix rtm::matrix4x4d`
|                9.37 |      106,759,022.32 |    0.1% |      0.01 | `Vector matrix multiply SimpleMath`
|                9.28 |      107,797,451.11 |    0.2% |      0.01 | `Vector matrix multiply glm`
|               44.44 |       22,499,777.76 |    0.1% |      0.01 | `Vector matrix multiply lab`
|                7.95 |      125,717,493.17 |    0.1% |      0.01 | `Vector matrix multiply DXM`
|                7.03 |      142,192,820.31 |    0.1% |      0.01 | `Vector matrix multiply Vectormath`
|                9.26 |      107,984,748.44 |    0.0% |      0.01 | `Vector matrix multiply move::math (float)`
|               19.09 |       52,377,551.02 |    0.1% |      0.01 | `Vector matrix multiply move::math (double)`
|                1.85 |      539,660,516.61 |    0.0% |      0.01 | `Vector matrix multiply rtm::matrix4x4f`
|               12.05 |       83,010,879.15 |    0.1% |      0.01 | `Vector matrix multiply rtm::matrix4x4d`
|                3.45 |      289,766,827.98 |    0.1% |      0.01 | `Point QVV multiply rtm::qvvf`
|               13.02 |       76,832,449.35 |    0.2% |      0.01 | `Point QVV multiply rtm::qvvd`
|               12.86 |       77,779,585.93 |    0.2% |      0.01 | `Matrix matrix multiply SimpleMath`
|               19.73 |       50,677,606.71 |    0.1% |      0.01 | `Matrix matrix multiply glm`
|               21.40 |       46,732,507.53 |    0.1% |      0.01 | `Matrix matrix multiply LAB`
|                8.18 |      122,195,701.79 |    0.1% |      0.01 | `Matrix matrix multiply DXM`
|                4.70 |      212,972,311.99 |    0.0% |      0.01 | `Matrix matrix multiply Vectormath`
|                8.65 |      115,637,879.36 |    0.1% |      0.01 | `Matrix matrix multiply move::math (float)`
|               50.04 |       19,985,084.37 |    0.1% |      0.01 | `Matrix matrix multiply move::math (double)`
|                7.80 |      128,175,238.83 |    0.1% |      0.01 | `QVV QVV multiply rtm::qvvf`
|               22.86 |       43,747,043.88 |    0.1% |      0.01 | `QVV QVV multiply rtm::qvvd`
|                8.67 |      115,386,691.48 |    0.0% |      0.01 | `Matrix matrix multiply rtm::matrix4x4f`
|               50.04 |       19,985,630.81 |    0.0% |      0.01 | `Matrix matrix multiply rtm::matrix4x4d`
Benchmark complete
 
## AVX2 

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.54 |      648,346,028.29 |    0.1% |      0.01 | `Store int (reference 'no-op')`
|                1.85 |      539,764,649.83 |    0.1% |      0.01 | `SimpleMath`
|                1.54 |      648,318,295.97 |    0.0% |      0.01 | `glm`
|                1.54 |      647,709,562.11 |    0.0% |      0.01 | `LAB`
|                1.85 |      540,115,347.02 |    0.0% |      0.01 | `DirectX`
|                1.54 |      647,697,246.00 |    0.1% |      0.01 | `Vectormath`
|                1.85 |      539,796,805.75 |    0.1% |      0.01 | `move (float)`
|                1.54 |      647,763,387.53 |    0.1% |      0.01 | `move (double)`
|                1.85 |      539,738,555.74 |    0.0% |      0.01 | `SimpleMath`
|                1.54 |      647,790,326.75 |    0.1% |      0.01 | `glm`
|                1.94 |      516,592,877.77 |    1.6% |      0.01 | `LAB`
|                1.85 |      540,274,520.02 |    0.1% |      0.01 | `DirectX`
|                1.85 |      539,765,428.65 |    0.1% |      0.01 | `Vectormath`
|                1.54 |      647,727,941.81 |    0.1% |      0.01 | `move (float)`
|                1.54 |      647,747,982.30 |    0.1% |      0.01 | `move (double)`
|                1.54 |      648,191,692.74 |    0.0% |      0.01 | `SimpleMath::Vector4 addition`
|                1.54 |      647,771,021.54 |    0.1% |      0.01 | `glm::vec4 addition`
|                1.85 |      539,732,727.75 |    0.0% |      0.01 | `LAB::vector4 addition`
|                1.54 |      647,731,322.82 |    0.1% |      0.01 | `DirectX::XMFLOAT4 addition without Loads`
|                1.85 |      540,089,808.67 |    0.0% |      0.01 | `Vectormath::Vector4 addition`
|                1.54 |      647,772,359.22 |    0.1% |      0.01 | `move::vec4f addition (float)`
|                1.54 |      647,766,927.08 |    0.0% |      0.01 | `move::vec4d addition (double)`
|                1.85 |      539,761,446.00 |    0.1% |      0.01 | `rtm::vector4f addition`
|                6.94 |      144,075,455.33 |    0.5% |      0.01 | `rtm::vector4d addition`
|               12.98 |       77,055,723.63 |    0.1% |      0.01 | `Complex operation 1 with SimpleMath::Vector*`
|                1.54 |      647,744,067.01 |    0.0% |      0.01 | `Complex operation 1 with glm::vec*`
|                1.85 |      539,763,278.96 |    0.1% |      0.01 | `Complex operation 1 with lab::vector`
|                2.16 |      462,543,560.43 |    0.0% |      0.01 | `Complex operation 1 with DXM`
|                7.10 |      140,774,193.55 |    0.0% |      0.01 | `Complex operation 1 with DXM w/out loads`
|                1.54 |      647,719,777.54 |    0.1% |      0.01 | `Complex operation 1 with Vectormath`
|                1.54 |      647,761,876.02 |    0.1% |      0.01 | `Complex operation 1 with move::math::* (float)`
|                4.16 |      240,099,318.40 |    0.0% |      0.01 | `Complex operation 1 with move::math::* (double)`
|               34.59 |       28,912,784.77 |    0.1% |      0.01 | `Complex operation 2 with SimpleMath::Vector3`
|                1.85 |      539,755,990.90 |    0.1% |      0.01 | `Complex operation 2 with glm::vec3`
|                1.85 |      539,634,703.20 |    0.0% |      0.01 | `Complex operation 2 with lab::vec3`
|                1.54 |      647,700,209.24 |    0.0% |      0.01 | `Complex operation 2 with DXM`
|                2.17 |      460,584,866.37 |    0.0% |      0.01 | `Complex operation 2 with DXM w/out loads`
|                1.85 |      540,095,660.49 |    0.0% |      0.01 | `Complex operation 2 with Vectormath`
|                1.54 |      647,708,659.24 |    0.1% |      0.01 | `Complex operation 2 with move::math (float)`
|                2.16 |      462,566,162.98 |    0.1% |      0.01 | `Complex operation 2 with move::math (double)`
|                1.54 |      647,785,695.66 |    0.1% |      0.01 | `Complex operation 3 with SimpleMath::Vector4`
|                1.54 |      648,160,320.27 |    0.0% |      0.01 | `Complex operation 3 with glm::vec4`
|                2.16 |      462,584,269.66 |    0.0% |      0.01 | `Complex operation 3 with lab::vec4`
|                1.85 |      539,781,204.24 |    0.1% |      0.01 | `Complex operation 3 with DXM`
|                1.85 |      539,756,832.99 |    0.1% |      0.01 | `Complex operation 3 with DXM w/out loads`
|                1.54 |      647,739,834.37 |    0.1% |      0.01 | `Complex operation 3 with Vectormath`
|                1.54 |      648,149,381.54 |    0.0% |      0.01 | `Complex operation 3 with move::math (float)`
|                1.85 |      540,055,057.28 |    0.0% |      0.01 | `Complex operation 3 with move::math (double)`
|                1.54 |      647,743,897.14 |    0.0% |      0.01 | `Complex operation 3 with rtm::vector4f`
|                6.79 |      147,321,275.58 |    0.1% |      0.01 | `Complex operation 3 with rtm::vector4d`
|               85.83 |       11,650,937.90 |    0.1% |      0.01 | `Construct model matrix SimpleMath`
|              170.83 |        5,853,658.54 |    0.1% |      0.01 | `Construct model matrix glm`
|               18.33 |       54,550,176.40 |    0.0% |      0.01 | `Construct model matrix LAB (~transformation matrix)`
|               66.95 |       14,936,058.99 |    0.1% |      0.01 | `Construct model matrix DXM (manual)`
|               64.10 |       15,600,706.71 |    0.1% |      0.01 | `Construct model matrix DXM (builtin)`
|               30.83 |       32,433,612.86 |    0.0% |      0.01 | `Construct model matrix Vectormath`
|              102.50 |        9,755,716.68 |    0.5% |      0.01 | `Construct model matrix move::math (manual, float)`
|               10.84 |       92,243,319.87 |    0.9% |      0.01 | `Construct model matrix move::math (builtin, float)`
|              163.67 |        6,109,918.82 |    1.4% |      0.01 | `Construct model matrix move::math (manual, double)`
|                1.54 |      648,361,903.17 |    0.1% |      0.01 | `Construct model matrix move::math (builtin, double)`
|                7.40 |      135,047,555.64 |    0.0% |      0.01 | `Construct rtm::qvvf (~transformation matrix)`
|                7.84 |      127,484,764.54 |    0.1% |      0.01 | `Construct rtm::qvvd (~transformation matrix)`
|                6.52 |      153,386,551.78 |    0.0% |      0.01 | `Construct model matrix rtm::matrix3x4f`
|               24.93 |       40,113,470.30 |    0.8% |      0.01 | `Construct model matrix rtm::matrix3x4d`
|                6.82 |      146,583,123.75 |    0.0% |      0.01 | `Construct model matrix rtm::matrix4x4f`
|               30.75 |       32,525,131.03 |    0.0% |      0.01 | `Construct model matrix rtm::matrix4x4d`
|               23.51 |       42,531,378.99 |    0.1% |      0.01 | `Construct view matrix SimpleMath`
|               17.80 |       56,194,492.25 |    0.0% |      0.01 | `Construct view matrix glm`
|               47.53 |       21,037,932.83 |    0.0% |      0.01 | `Construct view matrix LAB`
|               22.95 |       43,574,217.06 |    0.0% |      0.01 | `Construct view matrix DXM`
|               21.10 |       47,394,507.70 |    0.1% |      0.01 | `Construct view matrix Vectormath`
|                8.03 |      124,520,246.85 |    0.0% |      0.01 | `Construct view matrix move::math (float)`
|               63.09 |       15,850,221.08 |    0.0% |      0.01 | `Construct view matrix move::math (double)`
|                8.03 |      124,507,716.35 |    0.0% |      0.01 | `Construct view matrix rtm::matrix4x4f`
|               63.90 |       15,650,644.78 |    0.0% |      0.01 | `Construct view matrix rtm::matrix4x4d`
|               11.60 |       86,171,352.07 |    0.0% |      0.01 | `Construct perspective matrix SimpleMath`
|                8.59 |      116,346,713.21 |    0.1% |      0.01 | `Construct perspective matrix glm`
|                8.34 |      119,964,539.01 |    0.0% |      0.01 | `Construct perspective matrix LAB`
|               11.54 |       86,664,049.55 |    0.2% |      0.01 | `Construct perspective matrix DXM`
|                1.85 |      539,724,574.30 |    0.1% |      0.01 | `Construct perspective matrix Vectormath`
|                7.72 |      129,544,152.12 |    0.0% |      0.01 | `Construct perspective matrix move::math (float)`
|                8.03 |      124,552,650.04 |    0.0% |      0.01 | `Construct perspective matrix move::math (double)`
|                7.72 |      129,531,995.23 |    0.1% |      0.01 | `Construct perspective matrix rtm::matrix4x4f`
|                9.05 |      110,555,288.69 |    0.6% |      0.01 | `Construct perspective matrix rtm::matrix4x4d`
|                9.72 |      102,892,660.55 |    0.1% |      0.01 | `Construct ortho matrix SimpleMath`
|                8.64 |      115,780,942.46 |    0.1% |      0.01 | `Construct ortho matrix glm`
|                8.51 |      117,509,716.28 |    0.1% |      0.01 | `Construct ortho matrix lab`
|                7.10 |      140,869,147.45 |    0.0% |      0.01 | `Construct ortho matrix DXM`
|               14.67 |       68,165,702.91 |    0.1% |      0.01 | `Construct ortho matrix Vectormath`
|                7.09 |      140,973,520.93 |    0.0% |      0.01 | `Construct ortho matrix move::math (float)`
|                8.22 |      121,714,646.96 |    0.5% |      0.01 | `Construct ortho matrix move::math (double)`
|                7.24 |      138,182,772.11 |    0.1% |      0.01 | `Construct ortho matrix rtm::matrix4x4f`
|                8.03 |      124,581,126.83 |    0.1% |      0.01 | `Construct ortho matrix rtm::matrix4x4d`
|                9.92 |      100,839,190.09 |    0.0% |      0.01 | `Vector matrix multiply SimpleMath`
|                9.27 |      107,828,337.29 |    0.1% |      0.01 | `Vector matrix multiply glm`
|               44.47 |       22,485,543.65 |    0.6% |      0.01 | `Vector matrix multiply lab`
|                8.10 |      123,498,483.32 |    0.0% |      0.01 | `Vector matrix multiply DXM`
|                7.03 |      142,309,340.61 |    0.0% |      0.01 | `Vector matrix multiply Vectormath`
|                9.26 |      107,974,276.53 |    0.1% |      0.01 | `Vector matrix multiply move::math (float)`
|               18.68 |       53,532,497.81 |    0.1% |      0.01 | `Vector matrix multiply move::math (double)`
|                2.16 |      462,615,355.34 |    0.1% |      0.01 | `Vector matrix multiply rtm::matrix4x4f`
|               12.05 |       83,013,794.31 |    0.1% |      0.01 | `Vector matrix multiply rtm::matrix4x4d`
|                3.64 |      274,385,518.59 |    0.1% |      0.01 | `Point QVV multiply rtm::qvvf`
|               13.17 |       75,941,914.54 |    0.6% |      0.01 | `Point QVV multiply rtm::qvvd`
|                9.78 |      102,239,034.86 |    0.0% |      0.01 | `Matrix matrix multiply SimpleMath`
|               20.43 |       48,942,270.81 |    1.9% |      0.01 | `Matrix matrix multiply glm`
|               21.77 |       45,942,431.07 |    0.2% |      0.01 | `Matrix matrix multiply LAB`
|                4.53 |      220,695,876.29 |    0.0% |      0.01 | `Matrix matrix multiply DXM`
|                4.36 |      229,213,855.68 |    0.1% |      0.01 | `Matrix matrix multiply Vectormath`
|                8.88 |      112,602,247.61 |    0.2% |      0.01 | `Matrix matrix multiply move::math (float)`
|               46.64 |       21,442,920.78 |    0.1% |      0.01 | `Matrix matrix multiply move::math (double)`
|                7.79 |      128,353,228.08 |    0.1% |      0.01 | `QVV QVV multiply rtm::qvvf`
|               22.31 |       44,818,311.87 |    0.1% |      0.01 | `QVV QVV multiply rtm::qvvd`
|                8.88 |      112,649,117.89 |    0.1% |      0.01 | `Matrix matrix multiply rtm::matrix4x4f`
|               46.64 |       21,442,466.69 |    0.1% |      0.01 | `Matrix matrix multiply rtm::matrix4x4d`
Benchmark complete
