# Benchmark Results (windows-2022) 
 
## System Info 
CPU: AMD EPYC 7763 64-Core Processor                 
OS: Microsoft Windows Server 2022 Datacenter 
OS Version: 10.0.20348 N/A Build 20348 
 
## SSE 4.2 

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.55 |      646,033,158.95 |    0.2% |      0.19 | `Store int (reference 'no-op')`
|                1.86 |      538,523,163.00 |    0.1% |      0.22 | `SimpleMath::Vector2 addition`
|                1.86 |      538,856,873.60 |    0.1% |      0.22 | `SimpleMath::Vector3 addition`
|                1.55 |      646,816,873.76 |    0.1% |      0.19 | `SimpleMath::Vector4 addition`
|                1.86 |      538,546,434.58 |    0.2% |      0.22 | `glm::vec2 addition`
|                1.55 |      647,034,231.34 |    0.1% |      0.19 | `glm::vec3 addition`
|                1.86 |      538,492,458.28 |    0.1% |      0.22 | `glm::vec4 addition`
|                1.85 |      539,334,902.73 |    0.0% |      0.22 | `LAB::vector2 addition`
|                1.86 |      536,273,542.41 |    0.2% |      0.22 | `LAB::vector3 addition`
|               11.07 |       90,348,278.86 |    0.1% |      1.32 | `LAB::vector4 addition`
|                1.55 |      646,040,739.33 |    0.2% |      0.19 | `DirectX::XMFLOAT2 addition`
|                1.86 |      538,869,455.08 |    0.0% |      0.22 | `DirectX::XMFLOAT3 addition`
|                1.55 |      645,518,706.09 |    0.3% |      0.19 | `DirectX::XMFLOAT4 addition without Loads`
|                1.55 |      647,181,382.33 |    0.1% |      0.19 | `Vectormath::Vector2 addition`
|                1.55 |      647,234,755.40 |    0.0% |      0.18 | `Vectormath::Vector3 addition`
|                1.55 |      647,121,803.11 |    0.1% |      0.18 | `Vectormath::Vector4 addition`
|                1.86 |      538,807,523.36 |    0.2% |      0.22 | `move::vec2f addition (float)`
|                1.86 |      538,738,374.80 |    0.1% |      0.22 | `move::vec3f addition (float)`
|                1.55 |      644,923,075.03 |    0.4% |      0.19 | `move::vec4f addition (float)`
|                1.86 |      538,866,359.13 |    0.1% |      0.22 | `move::vec2d addition (double)`
|                1.55 |      646,356,394.91 |    0.1% |      0.19 | `move::vec3d addition (double)`
|                1.86 |      537,262,495.00 |    0.3% |      0.22 | `move::vec4d addition (double)`
|                1.55 |      645,616,233.41 |    0.2% |      0.19 | `rtm::vector4f addition`
|                1.86 |      537,599,280.41 |    0.2% |      0.22 | `rtm::vector4d addition`
|                3.51 |      284,833,643.37 |    0.1% |      0.42 | `Complex operation 1 with SimpleMath::Vector*`
|                1.55 |      644,926,710.69 |    0.3% |      0.19 | `Complex operation 1 with glm::vec*`
|                1.85 |      539,136,674.43 |    0.1% |      0.22 | `Complex operation 1 with lab::vector`
|                2.24 |      446,498,803.75 |    0.2% |      0.27 | `Complex operation 1 with DXM`
|                4.86 |      205,820,079.24 |    0.1% |      0.58 | `Complex operation 1 with DXM w/out loads`
|                1.86 |      538,354,756.46 |    0.1% |      0.22 | `Complex operation 1 with Vectormath`
|                1.55 |      646,328,852.12 |    0.1% |      0.19 | `Complex operation 1 with move::math::* (float)`
|                3.41 |      293,573,591.21 |    0.1% |      0.41 | `Complex operation 1 with move::math::* (double)`
|                3.11 |      321,443,655.29 |    0.1% |      0.37 | `Complex operation 2 with SimpleMath::Vector3`
|                1.55 |      646,081,079.56 |    0.1% |      0.19 | `Complex operation 2 with glm::vec3`
|                1.88 |      532,353,802.34 |    0.4% |      0.22 | `Complex operation 2 with lab::vec3`
|                1.55 |      645,985,499.68 |    0.1% |      0.19 | `Complex operation 2 with DXM`
|                2.17 |      461,682,678.22 |    0.1% |      0.26 | `Complex operation 2 with DXM w/out loads`
|                1.55 |      645,533,148.65 |    0.1% |      0.19 | `Complex operation 2 with Vectormath`
|                1.55 |      645,699,932.48 |    0.2% |      0.19 | `Complex operation 2 with move::math (float)`
|                2.48 |      403,174,059.15 |    0.2% |      0.30 | `Complex operation 2 with move::math (double)`
|                1.55 |      646,383,822.11 |    0.1% |      0.18 | `Complex operation 3 with SimpleMath::Vector4`
|                1.55 |      646,143,165.43 |    0.1% |      0.19 | `Complex operation 3 with glm::vec4`
|               12.11 |       82,603,339.79 |    0.1% |      1.45 | `Complex operation 3 with lab::vec4`
|                1.55 |      646,523,242.74 |    0.0% |      0.19 | `Complex operation 3 with DXM`
|                1.55 |      646,168,341.87 |    0.1% |      0.19 | `Complex operation 3 with DXM w/out loads`
|                1.55 |      646,015,698.18 |    0.2% |      0.20 | `Complex operation 3 with Vectormath`
|                1.55 |      645,431,955.34 |    0.2% |      0.19 | `Complex operation 3 with move::math (float)`
|                1.86 |      538,138,925.09 |    0.1% |      0.22 | `Complex operation 3 with move::math (double)`
|                1.86 |      537,932,295.84 |    0.1% |      0.22 | `Complex operation 3 with rtm::vector4f`
|                1.86 |      538,589,777.77 |    0.1% |      0.22 | `Complex operation 3 with rtm::vector4d`
|               53.13 |       18,823,273.73 |    0.1% |      6.35 | `Construct model matrix SimpleMath`
|              169.97 |        5,883,293.66 |    0.3% |     20.42 | `Construct model matrix glm`
|               18.02 |       55,504,268.27 |    0.1% |      2.15 | `Construct model matrix LAB (~transformation matrix)`
|               53.21 |       18,793,308.00 |    0.1% |      6.35 | `Construct model matrix DXM (manual)`
|               45.69 |       21,885,354.21 |    0.1% |      5.46 | `Construct model matrix DXM (builtin)`
|               23.34 |       42,852,058.65 |    0.2% |      2.79 | `Construct model matrix Vectormath`
|              138.86 |        7,201,550.60 |    0.1% |     16.58 | `Construct model matrix move::math (manual, float)`
|                8.30 |      120,443,249.80 |    0.1% |      0.99 | `Construct model matrix move::math (builtin, float)`
|              125.64 |        7,959,283.44 |    0.1% |     15.01 | `Construct model matrix move::math (manual, double)`
|                1.54 |      648,012,743.85 |    0.0% |      0.18 | `Construct model matrix move::math (builtin, double)`
|                1.54 |      647,407,130.81 |    0.0% |      0.18 | `Construct rtm::qvvf (~transformation matrix)`
|                1.86 |      537,676,340.25 |    0.3% |      0.22 | `Construct rtm::qvvd (~transformation matrix)`
|                7.23 |      138,311,508.18 |    0.2% |      0.86 | `Construct model matrix rtm::matrix3x4f`
|               12.41 |       80,565,975.56 |    0.1% |      1.48 | `Construct model matrix rtm::matrix3x4d`
|                8.72 |      114,708,976.11 |    0.3% |      1.04 | `Construct model matrix rtm::matrix4x4f`
|               12.87 |       77,673,850.23 |    0.2% |      1.54 | `Construct model matrix rtm::matrix4x4d`
|               22.30 |       44,849,644.10 |    0.2% |      2.66 | `Construct view matrix SimpleMath`
|               18.76 |       53,305,775.62 |    0.2% |      2.25 | `Construct view matrix glm`
|               44.29 |       22,580,904.34 |    0.1% |      5.29 | `Construct view matrix LAB`
|               22.29 |       44,870,353.84 |    0.1% |      2.66 | `Construct view matrix DXM`
|               40.56 |       24,655,456.38 |    0.0% |      4.84 | `Construct view matrix Vectormath`
|                8.14 |      122,902,213.46 |    0.1% |      0.97 | `Construct view matrix move::math (float)`
|               51.93 |       19,257,802.60 |    0.1% |      6.20 | `Construct view matrix move::math (double)`
|               17.98 |       55,612,966.30 |    0.1% |      2.15 | `Construct view matrix rtm::matrix4x4f`
|               57.37 |       17,431,929.16 |    0.1% |      6.86 | `Construct view matrix rtm::matrix4x4d`
|               13.02 |       76,825,070.38 |    0.2% |      1.56 | `Construct perspective matrix SimpleMath`
|                9.02 |      110,831,831.66 |    0.1% |      1.08 | `Construct perspective matrix glm`
|               10.83 |       92,328,972.86 |    0.1% |      1.29 | `Construct perspective matrix LAB`
|               13.07 |       76,513,494.30 |    0.4% |      1.56 | `Construct perspective matrix DXM`
|               12.38 |       80,797,763.80 |    0.2% |      1.48 | `Construct perspective matrix Vectormath`
|                9.15 |      109,244,522.88 |    0.1% |      1.09 | `Construct perspective matrix move::math (float)`
|                2.47 |      404,206,497.87 |    0.1% |      0.30 | `Construct perspective matrix move::math (double)`
|                9.18 |      108,905,778.23 |    0.1% |      1.10 | `Construct perspective matrix rtm::matrix4x4f`
|                2.47 |      404,107,167.44 |    0.1% |      0.30 | `Construct perspective matrix rtm::matrix4x4d`
|                1.86 |      537,920,206.39 |    0.1% |      0.22 | `Construct ortho matrix SimpleMath`
|                9.32 |      107,264,851.81 |    0.2% |      1.11 | `Construct ortho matrix glm`
|                1.86 |      538,909,183.72 |    0.1% |      0.22 | `Construct ortho matrix lab`
|                1.86 |      538,983,615.80 |    0.1% |      0.22 | `Construct ortho matrix DXM`
|               21.58 |       46,342,090.38 |    0.1% |      2.58 | `Construct ortho matrix Vectormath`
|                1.86 |      539,051,883.77 |    0.1% |      0.22 | `Construct ortho matrix move::math (float)`
|                2.47 |      404,404,708.01 |    0.1% |      0.30 | `Construct ortho matrix move::math (double)`
|                1.85 |      539,190,082.82 |    0.0% |      0.22 | `Construct ortho matrix rtm::matrix4x4f`
|                2.47 |      404,285,558.79 |    0.1% |      0.30 | `Construct ortho matrix rtm::matrix4x4d`
|               13.03 |       76,773,394.77 |    0.1% |      1.55 | `Vector matrix multiply SimpleMath`
|               12.31 |       81,210,011.28 |    0.1% |      1.47 | `Vector matrix multiply glm`
|               41.97 |       23,827,490.87 |    0.5% |      5.02 | `Vector matrix multiply lab`
|                7.98 |      125,341,581.62 |    0.1% |      0.95 | `Vector matrix multiply DXM`
|                7.04 |      142,064,448.43 |    0.1% |      0.84 | `Vector matrix multiply Vectormath`
|                9.10 |      109,901,667.10 |    0.1% |      1.09 | `Vector matrix multiply move::math (float)`
|               11.82 |       84,633,776.08 |    0.4% |      1.42 | `Vector matrix multiply move::math (double)`
|                1.85 |      539,087,903.82 |    0.1% |      0.22 | `Vector matrix multiply rtm::matrix4x4f`
|               11.81 |       84,703,041.18 |    0.4% |      1.41 | `Vector matrix multiply rtm::matrix4x4d`
|                3.72 |      268,737,741.15 |    0.2% |      0.44 | `Point QVV multiply rtm::qvvf`
|               11.40 |       87,697,403.35 |    0.2% |      1.36 | `Point QVV multiply rtm::qvvd`
|                4.65 |      215,215,753.79 |    0.1% |      0.56 | `Matrix matrix multiply SimpleMath`
|               20.80 |       48,087,234.09 |    0.1% |      2.48 | `Matrix matrix multiply glm`
|               22.32 |       44,807,575.67 |    0.3% |      2.67 | `Matrix matrix multiply LAB`
|                4.65 |      215,263,483.57 |    0.2% |      0.56 | `Matrix matrix multiply DXM`
|                4.64 |      215,338,499.47 |    0.1% |      0.56 | `Matrix matrix multiply Vectormath`
|                4.69 |      213,330,044.80 |    0.6% |      0.56 | `Matrix matrix multiply move::math (float)`
|               43.65 |       22,911,737.34 |    0.4% |      5.21 | `Matrix matrix multiply move::math (double)`
|                8.36 |      119,572,558.25 |    0.1% |      1.00 | `QVV QVV multiply rtm::qvvf`
|               20.86 |       47,944,509.33 |    0.1% |      2.49 | `QVV QVV multiply rtm::qvvd`
|                4.44 |      225,049,545.92 |    0.3% |      0.53 | `Matrix matrix multiply rtm::matrix4x4f`
|               43.50 |       22,990,878.29 |    0.2% |      5.19 | `Matrix matrix multiply rtm::matrix4x4d`
Benchmark complete
 
## AVX 

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.55 |      647,201,883.27 |    0.1% |      0.18 | `Store int (reference 'no-op')`
|                1.55 |      646,825,633.48 |    0.1% |      0.18 | `SimpleMath::Vector2 addition`
|                1.55 |      645,972,104.38 |    0.2% |      0.19 | `SimpleMath::Vector3 addition`
|                1.55 |      647,177,606.77 |    0.0% |      0.18 | `SimpleMath::Vector4 addition`
|                1.54 |      647,718,734.62 |    0.0% |      0.18 | `glm::vec2 addition`
|                1.55 |      646,315,252.15 |    0.1% |      0.19 | `glm::vec3 addition`
|                1.55 |      646,808,513.26 |    0.0% |      0.18 | `glm::vec4 addition`
|                1.55 |      646,347,052.75 |    0.1% |      0.18 | `LAB::vector2 addition`
|                1.86 |      538,282,324.96 |    0.2% |      0.22 | `LAB::vector3 addition`
|                1.86 |      538,584,739.30 |    0.2% |      0.22 | `LAB::vector4 addition`
|                1.55 |      645,636,174.28 |    0.2% |      0.19 | `DirectX::XMFLOAT2 addition`
|                1.54 |      647,346,886.10 |    0.1% |      0.18 | `DirectX::XMFLOAT3 addition`
|                1.55 |      647,067,330.36 |    0.1% |      0.18 | `DirectX::XMFLOAT4 addition without Loads`
|                1.55 |      646,570,959.24 |    0.1% |      0.19 | `Vectormath::Vector2 addition`
|                1.86 |      538,828,217.68 |    0.1% |      0.22 | `Vectormath::Vector3 addition`
|                1.86 |      538,959,627.33 |    0.2% |      0.22 | `Vectormath::Vector4 addition`
|                1.55 |      646,704,412.89 |    0.1% |      0.19 | `move::vec2f addition (float)`
|                1.55 |      646,404,157.86 |    0.1% |      0.19 | `move::vec3f addition (float)`
|                1.55 |      646,348,004.34 |    0.1% |      0.19 | `move::vec4f addition (float)`
|                1.55 |      645,651,357.06 |    0.2% |      0.19 | `move::vec2d addition (double)`
|                1.55 |      647,035,606.37 |    0.1% |      0.19 | `move::vec3d addition (double)`
|                1.55 |      646,203,974.72 |    0.2% |      0.19 | `move::vec4d addition (double)`
|                1.55 |      646,077,801.79 |    0.1% |      0.19 | `rtm::vector4f addition`
|                7.19 |      139,156,682.92 |    0.1% |      0.86 | `rtm::vector4d addition`
|               12.99 |       76,983,843.31 |    0.2% |      1.55 | `Complex operation 1 with SimpleMath::Vector*`
|                1.55 |      645,843,477.01 |    0.2% |      0.19 | `Complex operation 1 with glm::vec*`
|                1.55 |      646,864,251.33 |    0.1% |      0.19 | `Complex operation 1 with lab::vector`
|                2.16 |      462,009,175.30 |    0.1% |      0.26 | `Complex operation 1 with DXM`
|                7.13 |      140,265,990.69 |    0.1% |      0.85 | `Complex operation 1 with DXM w/out loads`
|                1.55 |      645,889,335.15 |    0.2% |      0.19 | `Complex operation 1 with Vectormath`
|                1.55 |      646,992,505.80 |    0.1% |      0.18 | `Complex operation 1 with move::math::* (float)`
|                3.09 |      323,645,543.40 |    0.1% |      0.37 | `Complex operation 1 with move::math::* (double)`
|               34.56 |       28,935,147.89 |    0.0% |      4.13 | `Complex operation 2 with SimpleMath::Vector3`
|                1.55 |      647,020,128.05 |    0.1% |      0.19 | `Complex operation 2 with glm::vec3`
|                2.17 |      461,572,645.82 |    0.2% |      0.26 | `Complex operation 2 with lab::vec3`
|                1.86 |      538,888,021.22 |    0.1% |      0.22 | `Complex operation 2 with DXM`
|                2.17 |      461,375,915.25 |    0.1% |      0.26 | `Complex operation 2 with DXM w/out loads`
|                1.55 |      646,776,144.31 |    0.1% |      0.19 | `Complex operation 2 with Vectormath`
|                1.55 |      647,198,346.76 |    0.0% |      0.19 | `Complex operation 2 with move::math (float)`
|                2.17 |      461,582,489.41 |    0.2% |      0.26 | `Complex operation 2 with move::math (double)`
|                1.55 |      645,797,810.54 |    0.1% |      0.19 | `Complex operation 3 with SimpleMath::Vector4`
|                1.55 |      646,290,019.06 |    0.1% |      0.19 | `Complex operation 3 with glm::vec4`
|                1.86 |      538,582,278.12 |    0.1% |      0.22 | `Complex operation 3 with lab::vec4`
|                1.55 |      646,629,771.11 |    0.1% |      0.18 | `Complex operation 3 with DXM`
|                1.86 |      538,589,971.45 |    0.1% |      0.22 | `Complex operation 3 with DXM w/out loads`
|                1.55 |      644,258,853.97 |    0.3% |      0.19 | `Complex operation 3 with Vectormath`
|                1.55 |      646,368,570.87 |    0.1% |      0.18 | `Complex operation 3 with move::math (float)`
|                1.86 |      538,098,661.08 |    0.1% |      0.22 | `Complex operation 3 with move::math (double)`
|                1.86 |      538,317,435.03 |    0.2% |      0.22 | `Complex operation 3 with rtm::vector4f`
|                8.96 |      111,569,998.44 |    0.1% |      1.07 | `Complex operation 3 with rtm::vector4d`
|               87.75 |       11,396,457.66 |    0.0% |     10.48 | `Construct model matrix SimpleMath`
|              171.73 |        5,823,179.39 |    0.1% |     20.51 | `Construct model matrix glm`
|               18.03 |       55,471,904.01 |    0.1% |      2.15 | `Construct model matrix LAB (~transformation matrix)`
|               76.83 |       13,015,245.91 |    0.1% |      9.18 | `Construct model matrix DXM (manual)`
|               75.06 |       13,323,217.36 |    0.2% |      8.97 | `Construct model matrix DXM (builtin)`
|               22.09 |       45,268,867.81 |    0.2% |      2.64 | `Construct model matrix Vectormath`
|              102.81 |        9,726,998.28 |    0.0% |     12.27 | `Construct model matrix move::math (manual, float)`
|               10.33 |       96,766,678.03 |    0.7% |      1.24 | `Construct model matrix move::math (builtin, float)`
|              172.22 |        5,806,423.70 |    0.2% |     20.55 | `Construct model matrix move::math (manual, double)`
|                1.54 |      647,588,915.68 |    0.1% |      0.18 | `Construct model matrix move::math (builtin, double)`
|                7.11 |      140,559,367.38 |    0.2% |      0.85 | `Construct rtm::qvvf (~transformation matrix)`
|                9.33 |      107,184,276.10 |    0.4% |      1.11 | `Construct rtm::qvvd (~transformation matrix)`
|                6.99 |      143,126,274.44 |    0.1% |      0.84 | `Construct model matrix rtm::matrix3x4f`
|               23.01 |       43,453,662.32 |    0.2% |      2.75 | `Construct model matrix rtm::matrix3x4d`
|                7.03 |      142,173,732.11 |    0.0% |      0.84 | `Construct model matrix rtm::matrix4x4f`
|               31.54 |       31,709,004.31 |    0.1% |      3.77 | `Construct model matrix rtm::matrix4x4d`
|               56.17 |       17,801,582.67 |    0.0% |      6.71 | `Construct view matrix SimpleMath`
|               17.95 |       55,704,529.03 |    0.3% |      2.14 | `Construct view matrix glm`
|               47.69 |       20,968,357.65 |    0.1% |      5.70 | `Construct view matrix LAB`
|               14.13 |       70,775,437.92 |    0.1% |      1.69 | `Construct view matrix DXM`
|               20.97 |       47,696,380.91 |    0.1% |      2.50 | `Construct view matrix Vectormath`
|                8.04 |      124,319,305.91 |    0.1% |      0.96 | `Construct view matrix move::math (float)`
|               65.40 |       15,291,348.38 |    0.1% |      7.81 | `Construct view matrix move::math (double)`
|                8.04 |      124,300,873.41 |    0.1% |      0.96 | `Construct view matrix rtm::matrix4x4f`
|               60.62 |       16,496,181.38 |    0.5% |      7.25 | `Construct view matrix rtm::matrix4x4d`
|               11.78 |       84,862,944.33 |    0.1% |      1.42 | `Construct perspective matrix SimpleMath`
|                8.64 |      115,718,641.69 |    0.3% |      1.03 | `Construct perspective matrix glm`
|                8.35 |      119,696,325.31 |    0.1% |      1.00 | `Construct perspective matrix LAB`
|               11.59 |       86,249,350.07 |    0.3% |      1.38 | `Construct perspective matrix DXM`
|                1.86 |      538,187,217.00 |    0.2% |      0.22 | `Construct perspective matrix Vectormath`
|                7.75 |      129,025,498.95 |    0.3% |      0.93 | `Construct perspective matrix move::math (float)`
|                8.08 |      123,784,345.22 |    0.3% |      0.97 | `Construct perspective matrix move::math (double)`
|                7.78 |      128,583,758.71 |    0.4% |      0.93 | `Construct perspective matrix rtm::matrix4x4f`
|                8.06 |      124,054,545.35 |    0.3% |      0.96 | `Construct perspective matrix rtm::matrix4x4d`
|                9.83 |      101,759,971.67 |    0.7% |      1.17 | `Construct ortho matrix SimpleMath`
|                8.66 |      115,480,502.78 |    0.1% |      1.03 | `Construct ortho matrix glm`
|                8.52 |      117,406,706.06 |    0.2% |      1.02 | `Construct ortho matrix lab`
|                7.11 |      140,598,937.42 |    0.1% |      0.85 | `Construct ortho matrix DXM`
|               12.74 |       78,469,196.96 |    2.4% |      1.50 | `Construct ortho matrix Vectormath`
|                7.11 |      140,605,910.00 |    0.1% |      0.85 | `Construct ortho matrix move::math (float)`
|                8.21 |      121,756,774.10 |    1.2% |      0.98 | `Construct ortho matrix move::math (double)`
|                7.26 |      137,768,252.17 |    0.1% |      0.87 | `Construct ortho matrix rtm::matrix4x4f`
|                8.48 |      117,935,692.06 |    0.8% |      1.01 | `Construct ortho matrix rtm::matrix4x4d`
|                9.39 |      106,515,491.88 |    0.1% |      1.12 | `Vector matrix multiply SimpleMath`
|                9.28 |      107,787,868.89 |    0.1% |      1.11 | `Vector matrix multiply glm`
|               47.17 |       21,197,801.01 |    1.8% |      5.59 | `Vector matrix multiply lab`
|                7.96 |      125,610,234.33 |    0.0% |      0.95 | `Vector matrix multiply DXM`
|                7.04 |      141,958,953.78 |    0.1% |      0.84 | `Vector matrix multiply Vectormath`
|                9.27 |      107,829,124.62 |    0.1% |      1.11 | `Vector matrix multiply move::math (float)`
|               18.62 |       53,704,331.10 |    0.1% |      2.23 | `Vector matrix multiply move::math (double)`
|                2.17 |      461,320,082.69 |    0.1% |      0.26 | `Vector matrix multiply rtm::matrix4x4f`
|               11.83 |       84,548,994.47 |    0.3% |      1.41 | `Vector matrix multiply rtm::matrix4x4d`
|                3.63 |      275,602,895.02 |    0.1% |      0.43 | `Point QVV multiply rtm::qvvf`
|               13.17 |       75,942,394.71 |    0.4% |      1.57 | `Point QVV multiply rtm::qvvd`
|               11.76 |       85,019,518.86 |    0.2% |      1.41 | `Matrix matrix multiply SimpleMath`
|               20.29 |       49,287,402.73 |    0.4% |      2.42 | `Matrix matrix multiply glm`
|               22.19 |       45,058,274.33 |    0.3% |      2.65 | `Matrix matrix multiply LAB`
|                8.24 |      121,405,391.94 |    0.3% |      0.99 | `Matrix matrix multiply DXM`
|                4.43 |      225,849,615.22 |    0.4% |      0.53 | `Matrix matrix multiply Vectormath`
|                9.06 |      110,371,356.82 |    1.1% |      1.09 | `Matrix matrix multiply move::math (float)`
|               51.76 |       19,318,530.05 |    0.2% |      6.18 | `Matrix matrix multiply move::math (double)`
|                7.83 |      127,756,995.03 |    0.1% |      0.94 | `QVV QVV multiply rtm::qvvf`
|               22.89 |       43,686,013.81 |    0.2% |      2.73 | `QVV QVV multiply rtm::qvvd`
|                9.07 |      110,272,255.04 |    1.0% |      1.08 | `Matrix matrix multiply rtm::matrix4x4f`
|               51.67 |       19,352,241.76 |    0.6% |      6.18 | `Matrix matrix multiply rtm::matrix4x4d`
Benchmark complete
 
## AVX2 

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|                1.85 |      539,295,359.88 |    0.1% |      0.22 | `Store int (reference 'no-op')`
|                1.86 |      538,234,796.43 |    0.1% |      0.22 | `SimpleMath::Vector2 addition`
|                1.55 |      646,625,441.48 |    0.0% |      0.18 | `SimpleMath::Vector3 addition`
|                1.55 |      646,191,026.99 |    0.1% |      0.19 | `SimpleMath::Vector4 addition`
|                1.55 |      646,970,473.38 |    0.1% |      0.18 | `glm::vec2 addition`
|                1.55 |      646,041,204.95 |    0.2% |      0.19 | `glm::vec3 addition`
|                1.56 |      642,769,493.84 |    0.7% |      0.19 | `glm::vec4 addition`
|                1.55 |      645,484,507.36 |    0.1% |      0.19 | `LAB::vector2 addition`
|                1.86 |      538,740,484.68 |    0.1% |      0.22 | `LAB::vector3 addition`
|                1.86 |      538,626,637.79 |    0.2% |      0.22 | `LAB::vector4 addition`
|                1.85 |      539,102,311.69 |    0.1% |      0.22 | `DirectX::XMFLOAT2 addition`
|                1.54 |      647,829,623.21 |    0.1% |      0.18 | `DirectX::XMFLOAT3 addition`
|                1.86 |      537,787,935.50 |    0.2% |      0.22 | `DirectX::XMFLOAT4 addition without Loads`
|                1.86 |      538,654,359.78 |    0.1% |      0.22 | `Vectormath::Vector2 addition`
|                1.55 |      646,223,980.59 |    0.2% |      0.18 | `Vectormath::Vector3 addition`
|                1.55 |      646,422,027.10 |    0.1% |      0.19 | `Vectormath::Vector4 addition`
|                1.55 |      646,833,812.75 |    0.1% |      0.18 | `move::vec2f addition (float)`
|                1.86 |      538,500,551.05 |    0.1% |      0.22 | `move::vec3f addition (float)`
|                1.55 |      646,726,176.45 |    0.0% |      0.18 | `move::vec4f addition (float)`
|                1.55 |      646,153,448.52 |    0.1% |      0.19 | `move::vec2d addition (double)`
|                1.55 |      646,172,809.13 |    0.2% |      0.19 | `move::vec3d addition (double)`
|                1.54 |      647,452,868.21 |    0.0% |      0.18 | `move::vec4d addition (double)`
|                1.55 |      647,147,070.96 |    0.0% |      0.18 | `rtm::vector4f addition`
|                7.26 |      137,653,130.81 |    0.2% |      0.87 | `rtm::vector4d addition`
|               13.01 |       76,857,916.27 |    0.1% |      1.55 | `Complex operation 1 with SimpleMath::Vector*`
|                1.55 |      646,572,496.44 |    0.1% |      0.19 | `Complex operation 1 with glm::vec*`
|                1.55 |      646,537,790.13 |    0.1% |      0.18 | `Complex operation 1 with lab::vector`
|                2.17 |      461,490,232.41 |    0.0% |      0.26 | `Complex operation 1 with DXM`
|                7.12 |      140,389,584.22 |    0.1% |      0.85 | `Complex operation 1 with DXM w/out loads`
|                1.55 |      646,835,576.94 |    0.0% |      0.18 | `Complex operation 1 with Vectormath`
|                1.86 |      537,816,224.22 |    0.3% |      0.22 | `Complex operation 1 with move::math::* (float)`
|                4.17 |      239,644,102.38 |    0.1% |      0.50 | `Complex operation 1 with move::math::* (double)`
|               34.69 |       28,828,024.07 |    0.0% |      4.14 | `Complex operation 2 with SimpleMath::Vector3`
|                1.86 |      536,674,419.26 |    0.3% |      0.22 | `Complex operation 2 with glm::vec3`
|                1.86 |      538,128,576.10 |    0.1% |      0.22 | `Complex operation 2 with lab::vec3`
|                1.87 |      535,953,631.64 |    0.4% |      0.22 | `Complex operation 2 with DXM`
|                2.17 |      460,552,504.19 |    0.1% |      0.26 | `Complex operation 2 with DXM w/out loads`
|                1.55 |      646,120,970.32 |    0.1% |      0.19 | `Complex operation 2 with Vectormath`
|                1.87 |      536,054,176.16 |    0.6% |      0.22 | `Complex operation 2 with move::math (float)`
|                2.17 |      461,765,403.91 |    0.1% |      0.26 | `Complex operation 2 with move::math (double)`
|                1.86 |      538,092,965.89 |    0.2% |      0.22 | `Complex operation 3 with SimpleMath::Vector4`
|                1.55 |      646,691,020.46 |    0.1% |      0.18 | `Complex operation 3 with glm::vec4`
|                1.86 |      538,616,239.09 |    0.1% |      0.22 | `Complex operation 3 with lab::vec4`
|                1.55 |      646,666,519.33 |    0.1% |      0.19 | `Complex operation 3 with DXM`
|                1.86 |      538,891,067.86 |    0.1% |      0.22 | `Complex operation 3 with DXM w/out loads`
|                1.86 |      538,053,116.84 |    0.3% |      0.22 | `Complex operation 3 with Vectormath`
|                1.86 |      538,582,705.55 |    0.1% |      0.22 | `Complex operation 3 with move::math (float)`
|                2.17 |      460,884,396.11 |    0.2% |      0.26 | `Complex operation 3 with move::math (double)`
|                1.55 |      647,093,453.19 |    0.0% |      0.18 | `Complex operation 3 with rtm::vector4f`
|                8.96 |      111,550,409.57 |    0.1% |      1.07 | `Complex operation 3 with rtm::vector4d`
|               85.60 |       11,682,329.65 |    0.0% |     10.22 | `Construct model matrix SimpleMath`
|              171.58 |        5,828,122.45 |    0.0% |     20.49 | `Construct model matrix glm`
|               18.01 |       55,517,032.90 |    0.2% |      2.15 | `Construct model matrix LAB (~transformation matrix)`
|               68.41 |       14,618,467.93 |    0.1% |      8.18 | `Construct model matrix DXM (manual)`
|               63.50 |       15,748,624.31 |    0.0% |      7.59 | `Construct model matrix DXM (builtin)`
|               30.90 |       32,359,209.24 |    0.1% |      3.70 | `Construct model matrix Vectormath`
|              102.30 |        9,775,515.66 |    0.0% |     12.21 | `Construct model matrix move::math (manual, float)`
|               10.36 |       96,562,186.72 |    0.2% |      1.24 | `Construct model matrix move::math (builtin, float)`
|              162.76 |        6,144,005.16 |    0.1% |     19.43 | `Construct model matrix move::math (manual, double)`
|                1.55 |      647,166,997.15 |    0.1% |      0.18 | `Construct model matrix move::math (builtin, double)`
|                7.12 |      140,544,681.03 |    0.2% |      0.85 | `Construct rtm::qvvf (~transformation matrix)`
|                9.42 |      106,109,832.63 |    0.4% |      1.13 | `Construct rtm::qvvd (~transformation matrix)`
|                6.57 |      152,222,524.98 |    0.1% |      0.78 | `Construct model matrix rtm::matrix3x4f`
|               23.67 |       42,254,190.30 |    0.1% |      2.82 | `Construct model matrix rtm::matrix3x4d`
|                6.83 |      146,495,785.90 |    0.1% |      0.82 | `Construct model matrix rtm::matrix4x4f`
|               32.04 |       31,211,108.20 |    0.2% |      3.83 | `Construct model matrix rtm::matrix4x4d`
|               23.59 |       42,383,399.08 |    0.0% |      2.82 | `Construct view matrix SimpleMath`
|               17.99 |       55,578,927.88 |    0.2% |      2.15 | `Construct view matrix glm`
|               47.69 |       20,968,663.16 |    0.1% |      5.70 | `Construct view matrix LAB`
|               23.01 |       43,461,955.46 |    0.1% |      2.75 | `Construct view matrix DXM`
|               21.16 |       47,249,332.76 |    0.0% |      2.53 | `Construct view matrix Vectormath`
|                8.04 |      124,321,816.22 |    0.1% |      0.96 | `Construct view matrix move::math (float)`
|               63.39 |       15,774,195.55 |    0.0% |      7.58 | `Construct view matrix move::math (double)`
|                8.04 |      124,301,015.18 |    0.1% |      0.96 | `Construct view matrix rtm::matrix4x4f`
|               66.00 |       15,151,555.87 |    0.1% |      7.88 | `Construct view matrix rtm::matrix4x4d`
|               11.82 |       84,619,123.15 |    0.2% |      1.41 | `Construct perspective matrix SimpleMath`
|                8.63 |      115,878,351.72 |    0.1% |      1.03 | `Construct perspective matrix glm`
|                8.36 |      119,566,125.31 |    0.2% |      1.00 | `Construct perspective matrix LAB`
|               11.67 |       85,684,391.24 |    0.2% |      1.39 | `Construct perspective matrix DXM`
|                1.86 |      537,811,724.55 |    0.3% |      0.22 | `Construct perspective matrix Vectormath`
|                7.74 |      129,166,360.50 |    0.1% |      0.92 | `Construct perspective matrix move::math (float)`
|                8.06 |      124,026,537.36 |    0.3% |      0.96 | `Construct perspective matrix move::math (double)`
|                7.80 |      128,145,281.46 |    0.3% |      0.93 | `Construct perspective matrix rtm::matrix4x4f`
|                8.09 |      123,577,000.03 |    0.3% |      0.97 | `Construct perspective matrix rtm::matrix4x4d`
|                9.81 |      101,947,470.01 |    0.5% |      1.17 | `Construct ortho matrix SimpleMath`
|                8.66 |      115,455,838.94 |    0.1% |      1.03 | `Construct ortho matrix glm`
|                8.10 |      123,499,417.55 |    0.9% |      0.97 | `Construct ortho matrix lab`
|                7.11 |      140,744,362.70 |    0.1% |      0.85 | `Construct ortho matrix DXM`
|               12.83 |       77,925,941.96 |    9.0% |      1.57 | :wavy_dash: `Construct ortho matrix Vectormath` (Unstable with ~10,854,352.5 iters. Increase `minEpochIterations` to e.g. 108543525)
|                7.12 |      140,545,536.31 |    0.1% |      0.85 | `Construct ortho matrix move::math (float)`
|                8.38 |      119,380,363.67 |    0.8% |      1.00 | `Construct ortho matrix move::math (double)`
|                7.27 |      137,564,632.50 |    0.2% |      0.87 | `Construct ortho matrix rtm::matrix4x4f`
|                8.45 |      118,326,350.47 |    0.5% |      1.01 | `Construct ortho matrix rtm::matrix4x4d`
|                9.93 |      100,679,497.98 |    0.1% |      1.19 | `Vector matrix multiply SimpleMath`
|                9.28 |      107,723,247.98 |    0.1% |      1.11 | `Vector matrix multiply glm`
|               42.18 |       23,706,299.46 |    0.5% |      5.05 | `Vector matrix multiply lab`
|                8.11 |      123,371,689.43 |    0.1% |      0.97 | `Vector matrix multiply DXM`
|                7.05 |      141,896,747.94 |    0.1% |      0.84 | `Vector matrix multiply Vectormath`
|                9.28 |      107,788,703.96 |    0.1% |      1.11 | `Vector matrix multiply move::math (float)`
|               18.93 |       52,828,953.53 |    0.1% |      2.26 | `Vector matrix multiply move::math (double)`
|                2.17 |      461,467,907.00 |    0.1% |      0.26 | `Vector matrix multiply rtm::matrix4x4f`
|               12.75 |       78,462,078.60 |    0.3% |      1.52 | `Vector matrix multiply rtm::matrix4x4d`
|                3.75 |      266,967,234.40 |    0.1% |      0.45 | `Point QVV multiply rtm::qvvf`
|               13.13 |       76,187,744.09 |    0.3% |      1.57 | `Point QVV multiply rtm::qvvd`
|                9.90 |      101,015,905.49 |    0.5% |      1.19 | `Matrix matrix multiply SimpleMath`
|               19.82 |       50,442,434.46 |    0.5% |      2.37 | `Matrix matrix multiply glm`
|               22.08 |       45,285,092.44 |    0.4% |      2.64 | `Matrix matrix multiply LAB`
|                4.65 |      215,275,973.16 |    0.1% |      0.56 | `Matrix matrix multiply DXM`
|                4.47 |      223,877,089.43 |    0.6% |      0.53 | `Matrix matrix multiply Vectormath`
|                9.21 |      108,551,907.16 |    0.6% |      1.10 | `Matrix matrix multiply move::math (float)`
|               47.01 |       21,273,030.39 |    0.1% |      5.61 | `Matrix matrix multiply move::math (double)`
|                7.94 |      125,908,853.65 |    0.1% |      0.95 | `QVV QVV multiply rtm::qvvf`
|               22.45 |       44,549,346.80 |    0.2% |      2.68 | `QVV QVV multiply rtm::qvvd`
|                9.23 |      108,384,995.66 |    1.3% |      1.10 | `Matrix matrix multiply rtm::matrix4x4f`
|               46.98 |       21,286,050.31 |    0.1% |      5.61 | `Matrix matrix multiply rtm::matrix4x4d`
Benchmark complete
