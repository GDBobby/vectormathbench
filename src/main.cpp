#include <math.h>
#include "glm/ext/matrix_clip_space.hpp"
#include "rtm/impl/matrix_common.h"
#include "rtm/scalard.h"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <type_traits>

#if __unix
namespace std
{
    inline float fabsf(float x)
    {
        return ::abs(x);
    }

    inline float sqrtf(float x)
    {
        return ::sqrtf(x);
    }

    inline float tanf(float x)
    {
        return ::tanf(x);
    }
}  // namespace std
#endif

// Sony vectormath
#include <vectormath.hpp>

#include "sse/internal.hpp"
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <DirectXMath.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <move/math/mat4x4.hpp>
#include <move/math/quat.hpp>
#include <move/math/vec2.hpp>
#include <move/math/vec3.hpp>
#include <move/math/vec4.hpp>
#include "simplemath.hpp"

#include <rtm/macros.h>
#include <rtm/math.h>
#include <rtm/matrix4x4d.h>
#include <rtm/matrix4x4f.h>
#include <rtm/quatd.h>
#include <rtm/quatf.h>
#include <rtm/qvvd.h>
#include <rtm/qvvf.h>
#include <rtm/vector4d.h>
#include <rtm/vector4f.h>

#include <LAB/Matrix.h>
#include <LAB/Vector.h>
#include <LAB/Camera.h>
#include <LAB/Transform.h>

// Sony vectormath
#include <vectormath.hpp>

namespace Vectormath
{
    using Vector3 = Vectormath::SSE::Vector3;
    using Vector4 = Vectormath::SSE::Vector4;
    using Matrix4 = Vectormath::SSE::Matrix4;
}  // namespace Vectormath

namespace rtm
{
    namespace camera
    {
        template <typename mat_type = rtm::matrix4x4f,
            typename vec_type = rtm::vector4f>
        RTM_DISABLE_SECURITY_COOKIE_CHECK RTM_FORCE_INLINE constexpr mat_type
        look_at_rh(
            const vec_type& eye, const vec_type& center, const vec_type& up)
        {
            // Largely taken from GLM's implementation
            using namespace rtm;
            const vec_type lookDir(vector_normalize3(vector_sub(eye, center)));
            const vec_type rightDir(
                vector_normalize3(vector_mul(vector_cross3(up, lookDir), 1)));
            const vec_type actualUpDir(vector_cross3(lookDir, rightDir));

            mat_type result = matrix_identity();
            result.x_axis = vector_set_w(rightDir, 0);
            result.y_axis = vector_set_w(actualUpDir, 0);
            result.z_axis = vector_set_w(lookDir, 0);
            result = matrix_transpose(result);

            if constexpr (std::is_same_v<mat_type, matrix4x4d>)
            {
                result.w_axis =
                    vector_set_w(vector_set(-double(vector_dot3(rightDir, eye)),
                                     -double(vector_dot3(actualUpDir, eye)),
                                     -double(vector_dot3(lookDir, eye))),
                        1);
            }
            else
            {
                result.w_axis =
                    vector_set_w(vector_set(-float(vector_dot3(rightDir, eye)),
                                     -float(vector_dot3(actualUpDir, eye)),
                                     -float(vector_dot3(lookDir, eye))),
                        1);
            }
            return result;
        }

        template <typename mat_type = rtm::matrix4x4f,
            typename vec_type = rtm::vector4f>
        RTM_DISABLE_SECURITY_COOKIE_CHECK RTM_FORCE_INLINE constexpr mat_type
        look_at_lh(
            const vec_type& eye, const vec_type& center, const vec_type& up)
        {
            // Largely taken from GLM's implementation
            using namespace rtm;
            const vec_type lookDir(vector_normalize3(vector_sub(center, eye)));
            const vec_type rightDir(
                vector_normalize3(vector_mul(vector_cross3(up, lookDir), 1)));
            const vec_type actualUpDir(vector_cross3(lookDir, rightDir));

            mat_type result = matrix_identity();
            result.x_axis = vector_set_w(rightDir, 0);
            result.y_axis = vector_set_w(actualUpDir, 0);
            result.z_axis = vector_set_w(lookDir, 0);
            result = matrix_transpose(result);

            if constexpr (std::is_same_v<mat_type, matrix4x4d>)
            {
                result.w_axis =
                    vector_set_w(vector_set(-double(vector_dot3(rightDir, eye)),
                                     -double(vector_dot3(actualUpDir, eye)),
                                     -double(vector_dot3(lookDir, eye))),
                        1);
            }
            else
            {
                result.w_axis =
                    vector_set_w(vector_set(-float(vector_dot3(rightDir, eye)),
                                     -float(vector_dot3(actualUpDir, eye)),
                                     -float(vector_dot3(lookDir, eye))),
                        1);
            }
            return result;
        }

        // template <typename mat_type = rtm::matrix4x4f>
        RTM_DISABLE_SECURITY_COOKIE_CHECK
        RTM_FORCE_INLINE rtm::matrix4x4f perspective_fov_rh(
            float fovY, float aspectRatio, float near, float far)
        {
            using mat_type = rtm::matrix4x4f;
            using value_type = float;

            assert(near > 0.f && far > 0.f);
            assert(!scalar_near_equal(fovY, 0.0f, 0.00001f * 2.0f));
            assert(!scalar_near_equal(aspectRatio, 0.0f, 0.00001f));
            assert(!scalar_near_equal(far, near, 0.00001f));

            value_type SinFov;
            value_type CosFov;
            rtm::scalar_sincos(0.5f * fovY, SinFov, CosFov);

            value_type Height = CosFov / SinFov;
            value_type Width = Height / aspectRatio;
            value_type fRange = far / (near - far);

            mat_type result;
            result.x_axis = vector_set(Width, 0.0f, 0.0f, 0.0f);
            result.y_axis = vector_set(0.0f, Height, 0.0f, 0.0f);
            result.z_axis = vector_set(0.0f, 0.0f, fRange, -1.0f);
            result.w_axis = vector_set(0.0f, 0.0f, fRange * near, 0.0f);
            return result;
        }

        RTM_DISABLE_SECURITY_COOKIE_CHECK
        RTM_FORCE_INLINE rtm::matrix4x4d perspective_fov_rh(
            double fovY, double aspectRatio, double near, double far)
        {
            using mat_type = rtm::matrix4x4d;
            using value_type = double;

            assert(near > 0. && far > 0.);
            assert(!scalar_near_equal(fovY, 0.0, 0.00001 * 2.0));
            assert(!scalar_near_equal(aspectRatio, 0.0, 0.00001));
            assert(!scalar_near_equal(far, near, 0.00001));

            value_type SinFov;
            value_type CosFov;
            rtm::scalar_sincos(0.5f * fovY, SinFov, CosFov);

            value_type Height = CosFov / SinFov;
            value_type Width = Height / aspectRatio;
            value_type fRange = far / (near - far);

            mat_type result;
            result.x_axis = vector_set(Width, 0.0, 0.0, 0.0);
            result.y_axis = vector_set(0.0, Height, 0.0, 0.0);
            result.z_axis = vector_set(0.0, 0.0, fRange, -1.0);
            result.w_axis = vector_set(0.0, 0.0, fRange * near, 0.0);
            return result;
        }

        RTM_DISABLE_SECURITY_COOKIE_CHECK
        RTM_FORCE_INLINE rtm::matrix4x4f ortho_rh(
            float width, float height, float near, float far)
        {
            using mat_type = rtm::matrix4x4f;
            using value_type = float;

            assert(!scalar_near_equal(width, 0.0f, 0.00001f));
            assert(!scalar_near_equal(height, 0.0f, 0.00001f));
            assert(!scalar_near_equal(far, near, 0.00001f));

            value_type fRange = 1.0f / (near - far);
            mat_type result;
            result.x_axis = vector_set(2.0f / width, 0.0f, 0.0f, 0.0f);
            result.y_axis = vector_set(0.0f, 2.0f / height, 0.0f, 0.0f);
            result.z_axis = vector_set(0.0f, 0.0f, fRange, 0.0f);
            result.w_axis = vector_set(0.0f, 0.0f, fRange * near, 1.0f);
            return result;
        }

        RTM_DISABLE_SECURITY_COOKIE_CHECK
        RTM_FORCE_INLINE rtm::matrix4x4d ortho_rh(
            double width, double height, double near, double far)
        {
            using mat_type = rtm::matrix4x4d;
            using value_type = double;

            assert(!scalar_near_equal(width, 0.0, 0.00001));
            assert(!scalar_near_equal(height, 0.0, 0.00001));
            assert(!scalar_near_equal(far, near, 0.00001));

            value_type fRange = 1.0f / (near - far);
            mat_type result;
            result.x_axis = vector_set(2.0 / width, 0.0, 0.0, 0.0);
            result.y_axis = vector_set(0.0, 2.0 / height, 0.0, 0.0);
            result.z_axis = vector_set(0.0, 0.0, fRange, 0.0);
            result.w_axis = vector_set(0.0, 0.0, fRange * near, 1.0);
            return result;
        }
    }  // namespace camera
}  // namespace rtm

namespace mathbench
{
    static struct result_t
    {
        result_t()
        {
        }

        ~result_t()
        {
        }

        int intnum;
        float floatnum;

        // SimpleMath
        DirectX::SimpleMath::Vector2 smVec2;
        DirectX::SimpleMath::Vector3 smVec3;
        DirectX::SimpleMath::Vector4 smVec4;
        DirectX::SimpleMath::Matrix smMat4a;
        DirectX::SimpleMath::Matrix smMat4b;
        DirectX::SimpleMath::Matrix smMat4c;

        // glm
        glm::vec2 glmVec2;
        glm::vec3 glmVec3;
        glm::vec4 glmVec4;
        glm::mat4 glmMat4a;
        glm::mat4 glmMat4b;
        glm::mat4 glmMat4c;

        // LAB
        LAB::Vector<float, 2> labVec2;
        LAB::Vector<float, 3> labVec3;
        LAB::Vector<float, 4> labVec4;
        LAB::Matrix<float, 4, 4> labMat4a;
        LAB::Matrix<float, 4, 4> labMat4b;
        LAB::Matrix<float, 4, 4> labMat4c;

        // DirectXMath
        DirectX::XMFLOAT2 dxVec2;
        DirectX::XMFLOAT3 dxVec3;
        DirectX::XMFLOAT4 dxVec4;
        DirectX::XMFLOAT4X4 dxMat4a;
        DirectX::XMFLOAT4X4 dxMat4b;
        DirectX::XMFLOAT4X4 dxMat4c;

        // Sony vectormath
        Vectormath::Vector2 sonyVec2;
        Vectormath::Vector3 sonyVec3;
        Vectormath::Vector4 sonyVec4;
        Vectormath::Matrix4 sonyMat4a;
        Vectormath::Matrix4 sonyMat4b;
        Vectormath::Matrix4 sonyMat4c;

        // move::math (float)
        move::math::float2 mvVec2f;
        move::math::fast_float3 mvVec3f;
        move::math::fast_float4 mvVec4f;
        move::math::float4x4 mvMat4x4fa;
        move::math::float4x4 mvMat4x4fb;
        move::math::float4x4 mvMat4x4fc;

        // move::math (double)
        move::math::double2 mvVec2d;
        move::math::fast_double3 mvVec3d;
        move::math::fast_double4 mvVec4d;
        move::math::double4x4 mvMat4x4da;
        move::math::double4x4 mvMat4x4db;
        move::math::double4x4 mvMat4x4dc;

        // rtm
        rtm::vector4f rtmVec4f;
        rtm::vector4f rtmVec4fa;
        rtm::vector4f rtmVec4fb;
        rtm::vector4d rtmVec4d;
        rtm::vector4d rtmVec4da;
        rtm::vector4d rtmVec4db;

        rtm::matrix3x4f rtmMat3x4f;
        rtm::matrix3x4f rtmMat3x4fa;
        rtm::matrix3x4d rtmMat3x4d;
        rtm::matrix3x4d rtmMat3x4da;

        rtm::matrix4x4f rtmMat4x4f;
        rtm::matrix4x4f rtmMat4x4fa;
        rtm::matrix4x4f rtmMat4x4fb;
        rtm::matrix4x4f rtmMat4x4fc;
        rtm::matrix4x4d rtmMat4x4d;
        rtm::matrix4x4d rtmMat4x4da;
        rtm::matrix4x4d rtmMat4x4db;
        rtm::matrix4x4d rtmMat4x4dc;
        rtm::qvvf rtmQvvf;
        rtm::qvvf rtmQvvfa;
        rtm::qvvf rtmQvvfb;
        rtm::qvvf rtmQvvfc;
        rtm::qvvd rtmQvvd;
        rtm::qvvd rtmQvvda;
        rtm::qvvd rtmQvvdb;
        rtm::qvvd rtmQvvdc;

        // DirectXMath
        DirectX::XMVECTOR dxVecA;
        DirectX::XMVECTOR dxVecB;
        DirectX::XMVECTOR dxVecC;
        DirectX::XMMATRIX dxMatA;
        DirectX::XMMATRIX dxMatB;
        DirectX::XMMATRIX dxMatC;

    } results;

    namespace vectors
    {
        void addition2(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smVec2 = DirectX::SimpleMath::Vector2(1.0f, 2.0f) +
                                     DirectX::SimpleMath::Vector2(3.0f, 4.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec2);
                });
            bench.run("glm",
                [&]
                {
                    results.glmVec2 =
                        glm::vec2(1.0f, 2.0f) + glm::vec2(3.0f, 4.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec2);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec2 = LAB::Vector<float, 2>(1.f, 2.f) +
                                      LAB::Vector<float, 2>(3.f, 4.f);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec2);
                });
            bench.run("DirectX",
                [&]
                {
                    DirectX::XMFLOAT2 lhs(1.0f, 2.0f);
                    DirectX::XMFLOAT2 rhs(3.0f, 4.0f);
                    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat2(&lhs);
                    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat2(&rhs);
                    DirectX::XMVECTOR result =
                        DirectX::XMVectorAdd(lhsVec, rhsVec);

                    DirectX::XMStoreFloat2(&results.dxVec2, result);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec2);
                });
            bench.run("Vectormath",
                [&]
                {
                    results.sonyVec2 = Vectormath::Vector2(1.0f, 2.0f) +
                                       Vectormath::Vector2(3.0f, 4.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec2);
                });
            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec2f = vec2f(1.0f, 2.0f) + vec2f(3.0f, 4.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec2f);
                });
            bench.run("move (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec2d = vec2d(1.0f, 2.0f) + vec2d(3.0f, 4.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec2d);
                });
        }

        void addition3(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smVec3 =
                        DirectX::SimpleMath::Vector3(1.0f, 2.0f, 3.0f) +
                        DirectX::SimpleMath::Vector3(3.0f, 4.0f, 5.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec3);
                });
            bench.run("glm",
                [&]
                {
                    results.glmVec3 = glm::vec3(1.0f, 2.0f, 3.0f) +
                                      glm::vec3(3.0f, 4.0f, 5.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec3);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec3 = LAB::Vector<float, 3>(1.f, 2.f, 3.f) +
                                      LAB::Vector<float, 3>(3.f, 4.f, 5.f);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec3);
                });

            bench.run("DirectX",
                [&]
                {
                    DirectX::XMFLOAT3 lhs(1.0f, 2.0f, 3.0f);
                    DirectX::XMFLOAT3 rhs(3.0f, 4.0f, 5.0f);
                    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat3(&lhs);
                    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat3(&rhs);
                    DirectX::XMVECTOR result =
                        DirectX::XMVectorAdd(lhsVec, rhsVec);

                    DirectX::XMStoreFloat3(&results.dxVec3, result);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec3);
                });

            bench.run("Vectormath",
                [&]
                {
                    results.sonyVec3 = Vectormath::Vector3(1.0f, 2.0f, 3.0f) +
                                       Vectormath::Vector3(3.0f, 4.0f, 5.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec3);
                });

            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec3f =
                        vec3f(1.0f, 2.0f, 3.0f) + vec3f(3.0f, 4.0f, 5.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3f);
                });

            bench.run("move (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec3d =
                        vec3d(1.0f, 2.0f, 3.0f) + vec3d(3.0f, 4.0f, 5.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3d);
                });
        }
        void addition4(ankerl::nanobench::Bench& bench)
        {


            bench.run("SimpleMath",
                [&]
                {
                    results.smVec4 =
                        DirectX::SimpleMath::Vector4(1.0f, 2.0f, 3.0f, 4.0f) +
                        DirectX::SimpleMath::Vector4(3.0f, 4.0f, 5.0f, 6.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });



            bench.run("glm",
                [&]
                {
                    results.glmVec4 = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f) +
                                      glm::vec4(3.0f, 4.0f, 5.0f, 6.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec4 = LAB::Vector<float, 4>(1.f, 2.f, 3.f, 4.f) +
                                      LAB::Vector<float, 4>(3.f, 4.f, 5.f, 6.f);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });


            bench.run("DXM",
                [&]
                {
                    results.dxVecC = DirectX::XMVectorAdd(
                        DirectX::XMVECTOR{}, DirectX::XMVECTOR{});
                    ankerl::nanobench::doNotOptimizeAway(results.dxVecC);
                });

            bench.run("Vectormath",
                [&]
                {
                    results.sonyVec4 =
                        Vectormath::Vector4(1.0f, 2.0f, 3.0f, 4.0f) +
                        Vectormath::Vector4(3.0f, 4.0f, 5.0f, 6.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec4);
                });
            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4f = vec4f(1.0f, 2.0f, 3.0f, 4.0f) +
                                      vec4f(3.0f, 4.0f, 5.0f, 6.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });
            bench.run("move (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4d = vec4d(1.0f, 2.0f, 3.0f, 4.0f) +
                                      vec4d(3.0f, 4.0f, 5.0f, 6.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4d);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f =
                        rtm::vector_add(vector_set(1.0f, 2.0f, 3.0f, 4.0f),
                            vector_set(3.0f, 4.0f, 5.0f, 6.0f));

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4d =
                        rtm::vector_add(vector_set(1.0, 2.0, 3.0, 4.0),
                            vector_set(3.0, 4.0, 5.0, 6.0));

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4d);
                });
        }

        void complex1(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector2 vec2a(1.0f, 2.0f);
                    DirectX::SimpleMath::Vector2 vec2b(3.0f, 4.0f);
                    DirectX::SimpleMath::Vector3 vec3a(1.0f, 2.0f, 3.0f);
                    DirectX::SimpleMath::Vector3 vec3b(3.0f, 4.0f, 5.0f);
                    DirectX::SimpleMath::Vector4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    DirectX::SimpleMath::Vector4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = vec2a.Dot(vec2b);
                    auto y = vec3a.Cross(vec3b).Dot(vec3b);
                    auto z = vec4a.Dot(vec4b);
                    auto w = (vec4a + vec4b).Dot(vec4b);

                    results.smVec4 = DirectX::SimpleMath::Vector4(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });

            bench.run("glm",
                [&]
                {
                    glm::vec2 vec2a(1.0f, 2.0f);
                    glm::vec2 vec2b(3.0f, 4.0f);
                    glm::vec3 vec3a(1.0f, 2.0f, 3.0f);
                    glm::vec3 vec3b(3.0f, 4.0f, 5.0f);
                    glm::vec4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    glm::vec4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = glm::dot(vec2a, vec2b);
                    auto y = glm::dot(glm::cross(vec3a, vec3b), vec3b);
                    auto z = glm::dot(vec4a, vec4b);
                    auto w = glm::dot(vec4a + vec4b, vec4b);

                    results.glmVec4 = glm::vec4(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB",
                [&]
                {
                    LAB::Vector<float, 2> vec2a(1.0f, 2.0f);
                    LAB::Vector<float, 2> vec2b(3.0f, 4.0f);
                    LAB::Vector<float, 3> vec3a(1.0f, 2.0f, 3.0f);
                    LAB::Vector<float, 3> vec3b(3.0f, 4.0f, 5.0f);
                    LAB::Vector<float, 4> vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    LAB::Vector<float, 4> vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = vec2a.DotProduct(vec2b);
                    auto y = LAB::DotProduct(LAB::CrossProduct(vec3a, vec3b), vec3b);
                    auto z = LAB::DotProduct(vec4a, vec4b);
                    auto w = LAB::DotProduct(vec4a + vec4b, vec4b);

                    results.labVec4 = LAB::Vector<float, 4>(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    XMFLOAT2 vec2a(1.0f, 2.0f);
                    XMFLOAT2 vec2b(3.0f, 4.0f);
                    XMFLOAT3 vec3a(1.0f, 2.0f, 3.0f);
                    XMFLOAT3 vec3b(3.0f, 4.0f, 5.0f);
                    XMFLOAT4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    XMFLOAT4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    XMVECTOR vec2aVec = XMLoadFloat2(&vec2a);
                    XMVECTOR vec2bVec = XMLoadFloat2(&vec2b);
                    XMVECTOR vec3aVec = XMLoadFloat3(&vec3a);
                    XMVECTOR vec3bVec = XMLoadFloat3(&vec3b);
                    XMVECTOR vec4aVec = XMLoadFloat4(&vec4a);
                    XMVECTOR vec4bVec = XMLoadFloat4(&vec4b);

                    auto x = XMVectorGetX(XMVector2Dot(vec2aVec, vec2bVec));
                    auto y = XMVectorGetX(XMVector3Dot(
                        XMVector3Cross(vec3aVec, vec3bVec), vec3bVec));
                    auto z = XMVectorGetX(XMVector4Dot(vec4aVec, vec4bVec));
                    auto w = XMVectorGetX(XMVector4Dot(
                        XMVectorAdd(vec4aVec, vec4bVec), vec4bVec));

                    XMStoreFloat4(&results.dxVec4, XMVectorSet(x, y, z, w));
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                });

            {
                using namespace DirectX;
                XMFLOAT2 vec2a(1.0f, 2.0f);
                XMFLOAT2 vec2b(3.0f, 4.0f);
                XMFLOAT3 vec3a(1.0f, 2.0f, 3.0f);
                XMFLOAT3 vec3b(3.0f, 4.0f, 5.0f);
                XMFLOAT4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                XMFLOAT4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);
                bench.run("DXM w/out loads",
                    [&]
                    {
                        XMVECTOR vec2aVec = XMLoadFloat2(&vec2a);
                        XMVECTOR vec2bVec = XMLoadFloat2(&vec2b);
                        XMVECTOR vec3aVec = XMLoadFloat3(&vec3a);
                        XMVECTOR vec3bVec = XMLoadFloat3(&vec3b);
                        XMVECTOR vec4aVec = XMLoadFloat4(&vec4a);
                        XMVECTOR vec4bVec = XMLoadFloat4(&vec4b);

                        auto x = XMVectorGetX(XMVector2Dot(vec2aVec, vec2bVec));
                        auto y = XMVectorGetX(XMVector3Dot(
                            XMVector3Cross(vec3aVec, vec3bVec), vec3bVec));
                        auto z = XMVectorGetX(XMVector4Dot(vec4aVec, vec4bVec));
                        auto w = XMVectorGetX(XMVector4Dot(
                            XMVectorAdd(vec4aVec, vec4bVec), vec4bVec));

                        XMStoreFloat4(&results.dxVec4, XMVectorSet(x, y, z, w));
                        ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                    });
            }

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    Vector2 vec2a(1.0f, 2.0f);
                    Vector2 vec2b(3.0f, 4.0f);
                    Vector3 vec3a(1.0f, 2.0f, 3.0f);
                    Vector3 vec3b(3.0f, 4.0f, 5.0f);
                    Vector4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    Vector4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = dot(vec2a, vec2b);
                    auto y = dot(cross(vec3a, vec3b), vec3b);
                    auto z = dot(vec4a, vec4b);
                    auto w = dot(vec4a + vec4b, vec4b);

                    results.sonyVec4 = Vector4(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec4);
                });

            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    vec2f vec2a(1.0f, 2.0f);
                    vec2f vec2b(3.0f, 4.0f);
                    vec3f vec3a(1.0f, 2.0f, 3.0f);
                    vec3f vec3b(3.0f, 4.0f, 5.0f);
                    vec4f vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    vec4f vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = vec2f::dot(vec2a, vec2b);
                    auto y = vec3f::dot(vec3f::cross(vec3a, vec3b), vec3b);
                    auto z = vec4f::dot(vec4a, vec4b);
                    auto w = vec4f::dot((vec4a + vec4b), vec4b);

                    results.mvVec4f = move::math::vec4f(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("move (double)",
                [&]
                {
                    using namespace move::math;
                    vec2d vec2a(1.0f, 2.0f);
                    vec2d vec2b(3.0f, 4.0f);
                    vec3d vec3a(1.0f, 2.0f, 3.0f);
                    vec3d vec3b(3.0f, 4.0f, 5.0f);
                    vec4d vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    vec4d vec4b(3.0f, 4.0f, 5.0f, 6.0f);

                    auto x = vec2d::dot(vec2a, vec2b);
                    auto y = vec3d::dot(vec3d::cross(vec3a, vec3b), vec3b);
                    auto z = vec4d::dot(vec4a, vec4b);
                    auto w = vec4d::dot((vec4a + vec4b), vec4b);

                    results.mvVec4d = move::math::vec4d(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4d);
                });
        }

        void complex2vec3(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector3 vec3a(1.0f, 2.0f, 3.0f);
                    DirectX::SimpleMath::Vector3 vec3b(3.0f, 4.0f, 5.0f);
                    DirectX::SimpleMath::Vector3 vec3c(5.0f, 6.0f, 7.0f);
                    DirectX::SimpleMath::Vector3 vec3d(7.0f, 8.0f, 9.0f);

                    results.smVec3 =
                        ((vec3a + vec3b) * vec3c - vec3d).Cross(vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec3);
                });

            bench.run("glm",
                [&]
                {
                    glm::vec3 vec3a(1.0f, 2.0f, 3.0f);
                    glm::vec3 vec3b(3.0f, 4.0f, 5.0f);
                    glm::vec3 vec3c(5.0f, 6.0f, 7.0f);
                    glm::vec3 vec3d(7.0f, 8.0f, 9.0f);

                    results.glmVec3 =
                        glm::cross((vec3a + vec3b) * vec3c - vec3d, vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec3);
                });
            bench.run("LAB",
                [&]
                {
                    LAB::Vector<float, 3> vec3a(1.0f, 2.0f, 3.0f);
                    LAB::Vector<float, 3> vec3b(3.0f, 4.0f, 5.0f);
                    LAB::Vector<float, 3> vec3c(5.0f, 6.0f, 7.0f);
                    LAB::Vector<float, 3> vec3d(7.0f, 8.0f, 9.0f);

                    //LAB::CrossProduct();
                    results.labVec3 = LAB::CrossProduct((vec3a + vec3b) * vec3c - vec3d, vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec3);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    XMFLOAT3 vec3a(1.0f, 2.0f, 3.0f);
                    XMFLOAT3 vec3b(3.0f, 4.0f, 5.0f);
                    XMFLOAT3 vec3c(5.0f, 6.0f, 7.0f);
                    XMFLOAT3 vec3d(7.0f, 8.0f, 9.0f);

                    XMVECTOR vec3aVec = XMLoadFloat3(&vec3a);
                    XMVECTOR vec3bVec = XMLoadFloat3(&vec3b);
                    XMVECTOR vec3cVec = XMLoadFloat3(&vec3c);
                    XMVECTOR vec3dVec = XMLoadFloat3(&vec3d);

                    XMVECTOR vec3 = XMVector3Cross(
                        XMVectorSubtract(
                            XMVectorMultiply(
                                XMVectorAdd(vec3aVec, vec3bVec), vec3cVec),
                            vec3dVec),
                        vec3aVec);

                    XMStoreFloat3(&results.dxVec3, vec3);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec3);
                });

            {
                using namespace DirectX;

                XMFLOAT3 vec3a(1.0f, 2.0f, 3.0f);
                XMFLOAT3 vec3b(3.0f, 4.0f, 5.0f);
                XMFLOAT3 vec3c(5.0f, 6.0f, 7.0f);
                XMFLOAT3 vec3d(7.0f, 8.0f, 9.0f);
                XMVECTOR vec3aVec = XMLoadFloat3(&vec3a);
                XMVECTOR vec3bVec = XMLoadFloat3(&vec3b);
                XMVECTOR vec3cVec = XMLoadFloat3(&vec3c);
                XMVECTOR vec3dVec = XMLoadFloat3(&vec3d);
                bench.run("DXM w/out loads",
                    [&]
                    {
                        XMVECTOR vec3 = XMVector3Cross(
                            XMVectorSubtract(
                                XMVectorMultiply(
                                    XMVectorAdd(vec3aVec, vec3bVec), vec3cVec),
                                vec3dVec),
                            vec3aVec);

                        XMStoreFloat3(&results.dxVec3, vec3);
                        ankerl::nanobench::doNotOptimizeAway(results.dxVec3);
                    });
            }

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    Vector3 vec3a(1.0f, 2.0f, 3.0f);
                    Vector3 vec3b(3.0f, 4.0f, 5.0f);
                    Vector3 vec3c(5.0f, 6.0f, 7.0f);
                    Vector3 vec3d(7.0f, 8.0f, 9.0f);

                    auto stepOne = (vec3a + vec3b);
                    auto stepTwo = vec3c - vec3d;

                    // Vectormath does not have a memberwise multiplication
                    results.sonyVec3 =
                        cross(Vector3(stepOne.getX() * stepTwo.getX(),
                                  stepOne.getY() * stepTwo.getY(),
                                  stepOne.getZ() * stepTwo.getZ()),
                            vec3a);

                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec3);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    vec3f vec3a(1.0f, 2.0f, 3.0f);
                    vec3f vec3b(3.0f, 4.0f, 5.0f);
                    vec3f vec3c(5.0f, 6.0f, 7.0f);
                    vec3f vec3d(7.0f, 8.0f, 9.0f);

                    auto stepOne = (vec3a + vec3b);
                    auto stepTwo = vec3c - vec3d;

                    results.mvVec3f = vec3f::cross((stepOne * stepTwo), vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3f);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    vec3d vec3a(1.0f, 2.0f, 3.0f);
                    vec3d vec3b(3.0f, 4.0f, 5.0f);
                    vec3d vec3c(5.0f, 6.0f, 7.0f);
                    vec3d vec3d(7.0f, 8.0f, 9.0f);

                    auto stepOne = (vec3a + vec3b);
                    auto stepTwo = vec3c - vec3d;

                    results.mvVec3d = vec3d::cross((stepOne * stepTwo), vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3d);
                });
        }

        void complex3vec4(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector4 vec3a(1.0f, 2.0f, 3.0f, 4.0f);
                    DirectX::SimpleMath::Vector4 vec3b(3.0f, 4.0f, 5.0f, 6.0f);
                    DirectX::SimpleMath::Vector4 vec3c(5.0f, 6.0f, 7.0f, 8.0f);
                    DirectX::SimpleMath::Vector4 vec3d(7.0f, 8.0f, 9.0f, 10.0f);

                    results.smVec4 = ((vec3a + vec3b) * vec3c - vec3d);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });

            bench.run("glm",
                [&]
                {
                    glm::vec4 vec3a(1.0f, 2.0f, 3.0f, 4.0f);
                    glm::vec4 vec3b(3.0f, 4.0f, 5.0f, 6.0f);
                    glm::vec4 vec3c(5.0f, 6.0f, 7.0f, 8.0f);
                    glm::vec4 vec3d(7.0f, 8.0f, 9.0f, 10.0f);

                    results.glmVec4 = (vec3a + vec3b) * vec3c - vec3d;
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB",
                [&]
                {
                    LAB::Vector<float, 4> vec3a(1.0f, 2.0f, 3.0f, 4.0f);
                    LAB::Vector<float, 4> vec3b(3.0f, 4.0f, 5.0f, 6.0f);
                    LAB::Vector<float, 4> vec3c(5.0f, 6.0f, 7.0f, 8.0f);
                    LAB::Vector<float, 4> vec3d(7.0f, 8.0f, 9.0f, 10.0f);

                    results.labVec4 = (vec3a + vec3b) * vec3c - vec3d;
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    XMFLOAT4 vec3a(1.0f, 2.0f, 3.0f, 4.0f);
                    XMFLOAT4 vec3b(3.0f, 4.0f, 5.0f, 6.0f);
                    XMFLOAT4 vec3c(5.0f, 6.0f, 7.0f, 8.0f);
                    XMFLOAT4 vec3d(7.0f, 8.0f, 9.0f, 10.0f);

                    XMVECTOR vec3aVec = XMLoadFloat4(&vec3a);
                    XMVECTOR vec3bVec = XMLoadFloat4(&vec3b);
                    XMVECTOR vec3cVec = XMLoadFloat4(&vec3c);
                    XMVECTOR vec3dVec = XMLoadFloat4(&vec3d);

                    XMVECTOR vec3 = XMVectorSubtract(
                        XMVectorMultiply(
                            XMVectorAdd(vec3aVec, vec3bVec), vec3cVec),
                        vec3dVec);

                    XMStoreFloat4(&results.dxVec4, vec3);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                });

            {
                using namespace DirectX;

                XMFLOAT4 vec3a(1.0f, 2.0f, 3.0f, 4.0f);
                XMFLOAT4 vec3b(3.0f, 4.0f, 5.0f, 6.0f);
                XMFLOAT4 vec3c(5.0f, 6.0f, 7.0f, 8.0f);
                XMFLOAT4 vec3d(7.0f, 8.0f, 9.0f, 10.0f);
                XMVECTOR vec3aVec = XMLoadFloat4(&vec3a);
                XMVECTOR vec3bVec = XMLoadFloat4(&vec3b);
                XMVECTOR vec3cVec = XMLoadFloat4(&vec3c);
                XMVECTOR vec3dVec = XMLoadFloat4(&vec3d);
                bench.run("DXM w/out loads",
                    [&]
                    {
                        XMVECTOR vec3 = XMVectorSubtract(
                            XMVectorMultiply(
                                XMVectorAdd(vec3aVec, vec3bVec), vec3cVec),
                            vec3dVec);

                        XMStoreFloat4(&results.dxVec4, vec3);
                        ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                    });
            }

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    Vector4 vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    Vector4 vec4b(3.0f, 4.0f, 5.0f, 6.0f);
                    Vector4 vec4c(5.0f, 6.0f, 7.0f, 8.0f);
                    Vector4 vec4d(7.0f, 8.0f, 9.0f, 10.0f);

                    Vector4 stepOne = (vec4a + vec4b);
                    Vector4 stepTwo = Vector4(stepOne.getX() * vec4c.getX(),
                        stepOne.getY() * vec4c.getY(),
                        stepOne.getZ() * vec4c.getZ(),
                        stepOne.getW() * vec4c.getW());

                    results.sonyVec4 = stepTwo - vec4d;
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec4);
                });

            bench.run("move::math(float)",
                [&]
                {
                    using namespace move::math;
                    vec4f vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    vec4f vec4b(3.0f, 4.0f, 5.0f, 6.0f);
                    vec4f vec4c(5.0f, 6.0f, 7.0f, 8.0f);
                    vec4f vec4dd(7.0f, 8.0f, 9.0f, 10.0f);

                    results.mvVec4f = (vec4a + vec4b) * vec4c - vec4dd;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    vec4d vec4a(1.0f, 2.0f, 3.0f, 4.0f);
                    vec4d vec4b(3.0f, 4.0f, 5.0f, 6.0f);
                    vec4d vec4c(5.0f, 6.0f, 7.0f, 8.0f);
                    vec4d vec4dd(7.0f, 8.0f, 9.0f, 10.0f);

                    results.mvVec4d = (vec4a + vec4b) * vec4c - vec4dd;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4d);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    vector4f vec4a = vector_set(1.0f, 2.0f, 3.0f, 4.0f);
                    vector4f vec4b = vector_set(3.0f, 4.0f, 5.0f, 6.0f);
                    vector4f vec4c = vector_set(5.0f, 6.0f, 7.0f, 8.0f);
                    vector4f vec4d = vector_set(7.0f, 8.0f, 9.0f, 10.0f);

                    vector4f stepOne =
                        vector_mul(vector_add(vec4a, vec4b), vec4c);
                    vector4f stepTwo = vector_sub(stepOne, vec4d);

                    results.rtmVec4f = stepTwo;
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    vector4d vec4a = vector_set(1.0, 2.0, 3.0, 4.0);
                    vector4d vec4b = vector_set(3.0, 4.0, 5.0, 6.0);
                    vector4d vec4c = vector_set(5.0, 6.0, 7.0, 8.0);
                    vector4d vec4d = vector_set(7.0, 8.0, 9.0, 10.0);

                    vector4d stepOne =
                        vector_mul(vector_add(vec4a, vec4b), vec4c);
                    vector4d stepTwo = vector_sub(stepOne, vec4d);

                    results.rtmVec4d = stepTwo;
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4d);
                });
        }
    }  // namespace vectors

    namespace matrices
    {
        void construct_model_matrix(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smMat4a =
                        DirectX::SimpleMath::Matrix::CreateTranslation(
                            1.0f, 2.0f, 3.0f) *
                        DirectX::SimpleMath::Matrix::CreateRotationX(0.5f) *
                        DirectX::SimpleMath::Matrix::CreateRotationY(0.5f) *
                        DirectX::SimpleMath::Matrix::CreateRotationZ(0.5f) *
                        DirectX::SimpleMath::Matrix::CreateScale(
                            1.0f, 2.0f, 3.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smMat4a);
                });

            bench.run("glm",
                [&]
                {
                    results.glmMat4a = glm::translate(glm::mat4(1.0f),
                                           glm::vec3(1.0f, 2.0f, 3.0f)) *
                                       glm::rotate(glm::mat4(1.0f), 0.5f,
                                           glm::vec3(1.0f, 0.0f, 0.0f)) *
                                       glm::rotate(glm::mat4(1.0f), 0.5f,
                                           glm::vec3(0.0f, 1.0f, 0.0f)) *
                                       glm::rotate(glm::mat4(1.0f), 0.5f,
                                           glm::vec3(0.0f, 0.0f, 1.0f)) *
                                       glm::scale(glm::mat4(1.0f),
                                           glm::vec3(1.0f, 2.0f, 3.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB (~transformation matrix)",
                [&]
                {
                    LAB::Transform<float, 3> transform{
                        LAB::Vector<float, 3>(1.0f, 2.0f, 3.0f), //translation
                        LAB::Vector<float, 3>(0.5f, 0.5f, 0.5f), //rotation,
                        LAB::Vector<float, 3>(1.f, 2.f, 3.f) //scale
                    };

                    results.labMat4a = transform.GetMatrix();
                    ankerl::nanobench::doNotOptimizeAway(results.labMat4a);
                });

            bench.run("DXM (manual)",
                [&]
                {
                    using namespace DirectX;
                    // Use XMMatrixMultiply

                    results.dxMatA = XMMatrixMultiply(
                        XMMatrixMultiply(
                            XMMatrixMultiply(
                                XMMatrixMultiply(
                                    XMMatrixTranslation(1.0f, 2.0f, 3.0f),
                                    XMMatrixRotationX(0.5f)),
                                XMMatrixRotationY(0.5f)),
                            XMMatrixRotationZ(0.5f)),
                        XMMatrixScaling(1.0f, 2.0f, 3.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("DXM (builtin)",
                [&]
                {
                    using namespace DirectX;

                    XMVECTOR ScalingOrigin = XMVectorZero();
                    XMVECTOR ScalingOrientationQuaternion =
                        XMQuaternionIdentity();
                    XMVECTOR Scaling = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
                    XMVECTOR RotationOrigin = XMVectorZero();
                    XMVECTOR RotationQuaternion =
                        XMQuaternionRotationRollPitchYaw(0.5f, 0.5f, 0.5f);
                    XMVECTOR Translation = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
                    //XMVECTOR Scale = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
                    //XMVECTOR Rotation = XMQuaternionRotationRollPitchYaw(0.5f, 0.5f, 0.5f);

                    results.dxMatA = XMMatrixTransformation(ScalingOrigin,
                        ScalingOrientationQuaternion, Scaling, RotationOrigin,
                        RotationQuaternion, Translation);
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyMat4a =
                        Matrix4::translation(Vector3(1.0f, 2.0f, 3.0f)) *
                        Matrix4::rotationX(0.5f) * Matrix4::rotationY(0.5f) *
                        Matrix4::rotationZ(0.5f) *
                        Matrix4::scale(Vector3(1.0f, 2.0f, 3.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.sonyMat4a);
                });

            bench.run("move::math (manual, float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        mat4x4f::translation({1, 2, 3}) *
                        mat4x4f::rotation_x(0.5f) * mat4x4f::rotation_y(0.5f) *
                        mat4x4f::rotation_z(0.5f) * mat4x4f::scale(1, 2, 3);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (builtin, float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa = mat4x4f::trs(
                        {1, 2, 3}, quatf::euler(0.5f, 0.5f, 0.5f), {1, 2, 3});

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (manual, double)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4da =
                        mat4x4d::translation({1, 2, 3}) *
                        mat4x4d::rotation(quatd::euler(0.5, 0.5, 0.5)) *
                        mat4x4d::scale(1, 2, 3);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("move::math (builtin, double)",
                [&]
                {
                    using namespace move::math;
                    // results.mvMat4x4da =
                    //     mat4x4d::trs(vec3d(1, 2, 3),
                    //         quatd::euler(0.5f, 0.5f, 0.5f),
                    //         vec3d(1, 2, 3));

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("rtm::qvvf (~transformation matrix)",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvf = qvv_set(quat_set(0.5f, 0.5f, 0.5f, 1.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f));

                    ankerl::nanobench::doNotOptimizeAway(results.rtmQvvf);
                });

            bench.run("rtm::qvvd (~transformation matrix)",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvd = qvv_set(quat_set(0.5, 0.5, 0.5, 1.0),
                        vector_set(1.0, 2.0, 3.0, 0.0),
                        vector_set(1.0, 2.0, 3.0, 0.0));

                    ankerl::nanobench::doNotOptimizeAway(results.rtmQvvf);
                });

            bench.run("rtm::matrix3x4f",
                [&]
                {
                    using namespace rtm;
                    auto qvv = qvv_set(quat_set(0.5f, 0.5f, 0.5f, 1.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f));

                    results.rtmMat3x4fa = matrix_from_qvv(qvv);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat3x4fa);
                });

            bench.run("rtm::matrix3x4d",
                [&]
                {
                    using namespace rtm;
                    auto qvv = qvv_set(quat_set(0.5, 0.5, 0.5, 1.0),
                        vector_set(1.0, 2.0, 3.0, 0.0),
                        vector_set(1.0, 2.0, 3.0, 0.0));

                    results.rtmMat3x4da = matrix_from_qvv(qvv);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat3x4da);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    auto qvv = qvv_set(quat_set(0.5f, 0.5f, 0.5f, 1.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f));

                    results.rtmMat4x4fa = matrix_cast(matrix_from_qvv(qvv));
                    results.rtmMat4x4fa.z_axis =
                        vector_set_w(results.rtmMat4x4fa.z_axis, 1);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    auto qvv = qvv_set(quat_set(0.5, 0.5, 0.5, 1.0),
                        vector_set(1.0, 2.0, 3.0, 0.0),
                        vector_set(1.0, 2.0, 3.0, 0.0));

                    results.rtmMat4x4da = matrix_cast(matrix_from_qvv(qvv));
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4da);
                });
        }

        void construct_view_matrix(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smMat4a = DirectX::SimpleMath::Matrix::CreateLookAt(
                        DirectX::SimpleMath::Vector3(1.0f, 2.0f, 3.0f),
                        DirectX::SimpleMath::Vector3(4.0f, 5.0f, 6.0f),
                        DirectX::SimpleMath::Vector3(7.0f, 8.0f, 9.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.smMat4a);
                });

            bench.run("glm",
                [&]
                {
                    results.glmMat4a = glm::lookAt(glm::vec3(1.0f, 2.0f, 3.0f),
                        glm::vec3(4.0f, 5.0f, 6.0f),
                        glm::vec3(7.0f, 8.0f, 9.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB",
                [&]
                {
                    results.labMat4a = LAB::CreateViewMatrix(
                        LAB::Vector<float, 3>(1.0f, 2.0f, 3.0f),
                        LAB::Vector<float, 3>(4.0f, 5.0f, 6.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.labMat4a);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    results.dxMatA =
                        XMMatrixLookAtLH(XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f),
                            XMVectorSet(4.0f, 5.0f, 6.0f, 0.0f),
                            XMVectorSet(7.0f, 8.0f, 9.0f, 0.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyMat4a = Matrix4::lookAt(
                        Point3(1.0f, 2.0f, 3.0f), Point3(4.0f, 5.0f, 6.0f),
                        Vector3(7.0f, 8.0f, 9.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.sonyMat4a);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa = mat4x4f::look_at(
                        vec3f(1, 2, 3), vec3f(4, 5, 6), vec3f(7, 8, 9));

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4da =
                        mat4x4d::look_at({1, 2, 3}, {4, 5, 6}, {7, 8, 9});

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa =
                        rtm::camera::look_at_rh<matrix4x4f, vector4f>(
                            vector_set(1.0f, 2.0f, 3.0f, 0.0f),
                            vector_set(4.0f, 5.0f, 6.0f, 0.0f),
                            vector_set(7.0f, 8.0f, 9.0f, 0.0f));
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4da =
                        rtm::camera::look_at_rh<matrix4x4d, vector4d>(
                            vector_set(1.0, 2.0, 3.0, 0.0),
                            vector_set(4.0, 5.0, 6.0, 0.0),
                            vector_set(7.0, 8.0, 9.0, 0.0));
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4da);
                });
        }

        void construct_perspective_projection_matrix(
            ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smMat4a = DirectX::SimpleMath::Matrix::
                        CreatePerspectiveFieldOfView(0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smMat4a);
                });

            bench.run("glm",
                [&]
                {
                    results.glmMat4a =
                        glm::perspective(0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB",
                [&]
                {
                    results.labMat4a = LAB::CreateProjectionMatrix(0.5f, 0.1f, 100.f);
                    ankerl::nanobench::doNotOptimizeAway(results.labMat4a);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    results.dxMatA =
                        XMMatrixPerspectiveFovLH(0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyMat4a =
                        Matrix4::perspective(0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyMat4a);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        mat4x4f::perspective(0.5f, 1.0f, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4da =
                        mat4x4d::perspective(0.5f, 1.0f, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa = rtm::camera::perspective_fov_rh(
                        0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4da =
                        rtm::camera::perspective_fov_rh(0.5, 1.0, 0.1, 100.0);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4da);
                });
        }

        void ortho_projection_matrix(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smMat4a =
                        DirectX::SimpleMath::Matrix::CreateOrthographic(
                            1280, 720, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.smMat4a);
                });

            bench.run("glm",
                [&]
                {
                    results.glmMat4a =
                        glm::ortho<float>(0, 1280, 0, 720, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB",
                [&]
                {
                    results.labMat4a = LAB::CreateOrthographicMatrix(0.f, 720.f, 0.f, 1280.f, 0.1f, 100.f);
                    ankerl::nanobench::doNotOptimizeAway(results.labMat4a);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    results.dxMatA =
                        XMMatrixOrthographicLH(1280, 720, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyMat4a =
                        Matrix4::orthographic(0, 1280, 0, 720, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.sonyMat4a);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        mat4x4f::orthographic(1280, 720, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4da =
                        mat4x4d::orthographic(1280, 720, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa =
                        rtm::camera::ortho_rh(1280.0f, 720.f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4da =
                        rtm::camera::ortho_rh(1280., 720., 0.1, 100.0);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4da);
                });
        }

        void vector_matrix_multiply(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smVec4 = DirectX::SimpleMath::Vector4::Transform(
                        results.smVec4, results.smMat4a);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });

            bench.run("glm",
                [&]
                {
                    results.glmVec4 = results.glmMat4a * results.glmVec4;
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB", 
                [&] {
                    results.labVec4 = results.labMat4a * results.labVec4;
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    results.dxVecA =
                        XMVector4Transform(results.dxVecA, results.dxMatA);
                    XMStoreFloat4(&results.dxVec4, results.dxVecA);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyVec4 = results.sonyMat4a * results.sonyVec4;
                    ankerl::nanobench::doNotOptimizeAway(results.sonyVec4);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4f = results.mvVec4f * results.mvMat4x4fa;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4d = results.mvVec4d * results.mvMat4x4da;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4d);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f = matrix_mul_vector(
                        results.rtmVec4fa, results.rtmMat4x4fa);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4d = matrix_mul_vector(
                        results.rtmVec4da, results.rtmMat4x4da);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4d);
                });

            bench.run("rtm::qvvf",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f =
                        qvv_mul_point3(results.rtmVec4fa, results.rtmQvvf);

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });

            bench.run("rtm::qvvd",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4d =
                        qvv_mul_point3(results.rtmVec4da, results.rtmQvvd);

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4d);
                });
        }

        void matrix_matrix_multiply(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smMat4a = results.smMat4b * results.smMat4c;
                    ankerl::nanobench::doNotOptimizeAway(results.smMat4a);
                });

            bench.run("glm",
                [&]
                {
                    results.glmMat4a = results.glmMat4b * results.glmMat4c;
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB",
                [&]
                {
                    results.labMat4a = results.labMat4b * results.labMat4c;
                    ankerl::nanobench::doNotOptimizeAway(results.labMat4a);

                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;

                    results.dxMatA =
                        XMMatrixMultiply(results.dxMatB, results.dxMatC);
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("Vectormath",
                [&]
                {
                    using namespace Vectormath;
                    results.sonyMat4a = results.sonyMat4b * results.sonyMat4c;
                    ankerl::nanobench::doNotOptimizeAway(results.sonyMat4a);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        results.mvMat4x4fb * results.mvMat4x4fc;
                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("move::math (double)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4da =
                        results.mvMat4x4db * results.mvMat4x4dc;
                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4da);
                });

            bench.run("rtm::qvvf",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvfa =
                        qvv_mul(results.rtmQvvfb, results.rtmQvvfc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmQvvf);
                });

            bench.run("rtm::qvvd",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvda =
                        qvv_mul(results.rtmQvvdb, results.rtmQvvdc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmQvvda);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa =
                        matrix_mul(results.rtmMat4x4fb, results.rtmMat4x4fc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });

            bench.run("rtm::matrix4x4d",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4da =
                        matrix_mul(results.rtmMat4x4db, results.rtmMat4x4dc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4da);
                });
        }
    }  // namespace matrices
}  // namespace mathbench

inline void test_camera_matrix_funcs()
{
    auto smMat = DirectX::SimpleMath::Matrix::CreateOrthographic(
        0.5f, 1.0f, 0.1f, 100.0f);
    auto glmMat = glm::ortho(0.5f, 1.0f, 0.1f, 100.0f);
    auto rtmMat = rtm::camera::ortho_rh(0.5f, 1.0f, 0.1f, 100.0f);

    printf("GLM: \n");
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            printf("%f ", glmMat[x][y]);
        }
        printf("\n");
    }

    printf("SimpleMath:\n");
    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
        float(smMat._11), float(smMat._12), float(smMat._13), float(smMat._14),
        float(smMat._21), float(smMat._22), float(smMat._23), float(smMat._24),
        float(smMat._31), float(smMat._32), float(smMat._33), float(smMat._34),
        float(smMat._41), float(smMat._42), float(smMat._43), float(smMat._44));

    printf("RTM: \n");
    printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
        float(rtm::vector_get_x(rtmMat.x_axis)),
        float(rtm::vector_get_y(rtmMat.x_axis)),
        float(rtm::vector_get_z(rtmMat.x_axis)),
        float(rtm::vector_get_w(rtmMat.x_axis)),
        float(rtm::vector_get_x(rtmMat.y_axis)),
        float(rtm::vector_get_y(rtmMat.y_axis)),
        float(rtm::vector_get_z(rtmMat.y_axis)),
        float(rtm::vector_get_w(rtmMat.y_axis)),
        float(rtm::vector_get_x(rtmMat.z_axis)),
        float(rtm::vector_get_y(rtmMat.z_axis)),
        float(rtm::vector_get_z(rtmMat.z_axis)),
        float(rtm::vector_get_w(rtmMat.z_axis)),
        float(rtm::vector_get_x(rtmMat.w_axis)),
        float(rtm::vector_get_y(rtmMat.w_axis)),
        float(rtm::vector_get_z(rtmMat.w_axis)),
        float(rtm::vector_get_w(rtmMat.w_axis)));
}

// Function to write a section of benchmarks
void WriteTable(std::ofstream& outFile, const std::string& section_name, std::vector<ankerl::nanobench::Result>& results) {

    outFile << "\n| " << section_name << "\n";
    outFile << "|      ns/op (median) |      ns/op(average) |    err% |  iterations | library\n";
    outFile << "|--------------------:|--------------------:|--------:|------------:|:----------\n";

    /*
    for (auto const& ret : results) {
        outFile << "| " << std::setw(19) << std::right << ret.median(ankerl::nanobench::Result::Measure::elapsed) * static_cast<double>(1000000000)
                << " | " << std::setw(19) << std::right << 1.0 / ret.median(ankerl::nanobench::Result::Measure::elapsed)
                << " | " << std::setw(6) << std::right << ret.medianAbsolutePercentError(ankerl::nanobench::Result::Measure::elapsed) * 100.0 << "%"
                << " | " << std::setw(9) << std::right << 0.0
                << " | " << ret.config().mBenchmarkName << "\n";
    }
    */
   //ret.mNameToMeasurements[(int)ankerl::nanobench::Result::Measure::elapsed]
    struct SortedResultsStruct {
        double median;
        double average;
        double errPerc;
        uint64_t totalIter;
        std::string libName;
    };
    std::vector<SortedResultsStruct> sortedResults{};
    sortedResults.reserve(results.size());

    for (auto& ret : results) {
        std::sort(ret.bbm.begin(), ret.bbm.end(), [](auto left, auto right) {return left.nanoseconds < right.nanoseconds; });

        std::size_t totalNano = 0;
        std::size_t totalIter = 0;
        for (auto const& bm : ret.bbm) {
            totalNano += bm.nanoseconds;
            totalIter += bm.iterCount;
        }
        auto& empBack = sortedResults.emplace_back();
        empBack.median = static_cast<double>(ret.bbm[ret.bbm.size() / 2].nanoseconds) / static_cast<double>(ret.bbm[ret.bbm.size() / 2].iterCount);
        empBack.average = static_cast<double>(totalNano) / static_cast<double>(totalIter);
        empBack.errPerc = ret.medianAbsolutePercentError(ankerl::nanobench::Result::Measure::elapsed) * 100.0;
        empBack.totalIter = totalIter;
        empBack.libName = ret.config().mBenchmarkName;
    }
    std::sort(sortedResults.begin(), sortedResults.end(), [](auto left, auto right) {return left.median < right.median; });
    for (auto& ret : sortedResults) {
        outFile
            << "| " << std::setw(19) << std::right << ret.median

            << " | " << std::setw(19) << std::right << ret.average

            << " | " << std::setw(6) << std::right << ret.errPerc << "%"

            << " | " << std::setw(11) << std::right << ret.totalIter

            << " | " << ret.libName << "\n";
    }
};


void BenchmarkWrapper(std::string const& name, std::ofstream& outFile, int const iterations, void(*benchFunction)(ankerl::nanobench::Bench&)) {
    ankerl::nanobench::Bench bench;
    bench.name(name);
    bench.minEpochIterations(iterations);
    benchFunction(bench);

    std::vector<ankerl::nanobench::Result> resultCopy = bench.results();
    WriteTable(outFile, name, resultCopy);
}


int main() {
    constexpr int iterations = 10000000;
    //constexpr int iterations = 1000; //quick testing
    // test_camera_matrix_funcs();
    std::ofstream file("benchmark_results.txt", std::ios::trunc);
    file << std::fixed << std::setprecision(2);

    try
    {
        {
            ankerl::nanobench::Bench noopBench;
            noopBench.name("noop");
            noopBench.minEpochIterations(iterations);
            int intnum;
            noopBench.run("Store int (reference 'no-op')",
                [&]
                {
                    intnum = 0;
                    ankerl::nanobench::doNotOptimizeAway(intnum);
                });
            auto resultCopy = noopBench.results();
            WriteTable(file, "no-op", resultCopy);
        }
        BenchmarkWrapper("vector 2", file, iterations, mathbench::vectors::addition2);
//this is here for quick testing. just toggle 0 to 1 for quick enable/disable
#if 1
        BenchmarkWrapper("vector 3", file, iterations, mathbench::vectors::addition3);
        BenchmarkWrapper("vector 4", file, iterations, mathbench::vectors::addition4);
        BenchmarkWrapper("complex1", file, iterations, mathbench::vectors::complex1);
        BenchmarkWrapper("complex2 vec3", file, iterations, mathbench::vectors::complex2vec3);
        BenchmarkWrapper("complex3 vec4", file, iterations, mathbench::vectors::complex3vec4);

        BenchmarkWrapper("model matrix", file, iterations, mathbench::matrices::construct_model_matrix);
        BenchmarkWrapper("view matrix", file, iterations, mathbench::matrices::construct_view_matrix);
        BenchmarkWrapper("perspective matrix", file, iterations, mathbench::matrices::construct_perspective_projection_matrix);
        BenchmarkWrapper("ortho matrix", file, iterations, mathbench::matrices::ortho_projection_matrix);
        BenchmarkWrapper("matrix * vector", file, iterations, mathbench::matrices::vector_matrix_multiply);
        BenchmarkWrapper("matrix * matrix", file, iterations, mathbench::matrices::matrix_matrix_multiply);
#endif

        printf("Benchmark complete\n");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}