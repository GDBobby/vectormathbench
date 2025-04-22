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

#include <random>

uint64_t random_float_iter = 0;
std::vector<float> random_float_values;

float PullRandomFloatVal(){
    float ret = random_float_values[random_float_iter];
    random_float_iter = (random_float_iter + 1) % random_float_values.size();
    return ret;
}

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

#include <array>

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

        // move::math (float)
        move::math::float2 mvVec2f;
        move::math::fast_float3 mvVec3f;
        move::math::fast_float4 mvVec4f;
        move::math::float4x4 mvMat4x4fa;
        move::math::float4x4 mvMat4x4fb;
        move::math::float4x4 mvMat4x4fc;

        // rtm
        rtm::vector4f rtmVec4f;
        rtm::vector4f rtmVec4fa;
        rtm::vector4f rtmVec4fb;

        rtm::matrix3x4f rtmMat3x4f;
        rtm::matrix3x4f rtmMat3x4fa;

        rtm::matrix4x4f rtmMat4x4f;
        rtm::matrix4x4f rtmMat4x4fa;
        rtm::matrix4x4f rtmMat4x4fb;
        rtm::matrix4x4f rtmMat4x4fc;
        rtm::qvvf rtmQvvf;
        rtm::qvvf rtmQvvfa;
        rtm::qvvf rtmQvvfb;
        rtm::qvvf rtmQvvfc;

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
                    results.smVec2 = DirectX::SimpleMath::Vector2(PullRandomFloatVal(), PullRandomFloatVal()) +
                                     DirectX::SimpleMath::Vector2(PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.smVec2);
                });
            bench.run("glm",
                [&]
                {
                    results.glmVec2 = glm::vec2(PullRandomFloatVal(), PullRandomFloatVal()) + glm::vec2(PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec2);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec2 = LAB::Vector<float, 2>(PullRandomFloatVal(), PullRandomFloatVal()) + LAB::Vector<float, 2>(PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.labVec2);
                });
            bench.run("DirectX",
                [&]
                {
                    DirectX::XMFLOAT2 lhs(PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::XMFLOAT2 rhs(PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat2(&lhs);
                    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat2(&rhs);
                    DirectX::XMVECTOR result =
                        DirectX::XMVectorAdd(lhsVec, rhsVec);

                    DirectX::XMStoreFloat2(&results.dxVec2, result);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec2);
                });
            bench.run("move (float)",
                [&]
                {
                    results.mvVec2f = move::math::vec2f(PullRandomFloatVal(), PullRandomFloatVal()) + move::math::vec2f(PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec2f);
                });
        }

        void addition3(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smVec3 =
                        DirectX::SimpleMath::Vector3(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                        DirectX::SimpleMath::Vector3(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.smVec3);
                });
            bench.run("glm",
                [&]
                {
                    results.glmVec3 = glm::vec3(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                                      glm::vec3(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec3);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec3 = LAB::Vector<float, 3>(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                                      LAB::Vector<float, 3>(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.labVec3);
                });

            bench.run("DirectX",
                [&]
                {
                    DirectX::XMFLOAT3 lhs(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::XMFLOAT3 rhs(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat3(&lhs);
                    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat3(&rhs);
                    DirectX::XMVECTOR result =
                        DirectX::XMVectorAdd(lhsVec, rhsVec);

                    DirectX::XMStoreFloat3(&results.dxVec3, result);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec3);
                });

            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec3f = vec3f(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) + vec3f(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3f);
                });
        }
        void addition4(ankerl::nanobench::Bench& bench)
        {


            bench.run("SimpleMath",
                [&]
                {
                    results.smVec4 =
                        DirectX::SimpleMath::Vector4(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                        DirectX::SimpleMath::Vector4(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });



            bench.run("glm",
                [&]
                {
                    results.glmVec4 = glm::vec4(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                                      glm::vec4(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB",
                [&]
                {
                    results.labVec4 = LAB::Vector<float, 4>(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                                      LAB::Vector<float, 4>(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });


            bench.run("DXM",
                [&]
                {
                    results.dxVecC = DirectX::XMVectorAdd(DirectX::XMVECTOR{PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()}, 
                    DirectX::XMVECTOR{PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()});
                    ankerl::nanobench::doNotOptimizeAway(results.dxVecC);
                });

            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4f = vec4f(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()) +
                                      vec4f(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f =
                        rtm::vector_add(vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()),
                            vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()));

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });
        }

        void complex1(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector2 vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector2 vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector4 vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector4 vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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
                    glm::vec2 vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec2 vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec4 vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec4 vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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
                    LAB::Vector<float, 2> vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 2> vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 3> vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 3> vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 4> vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 4> vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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
                    XMFLOAT2 vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT2 vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT4 vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT4 vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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
                XMFLOAT2 vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT2 vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT4 vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT4 vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
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

            bench.run("move (float)",
                [&]
                {
                    using namespace move::math;
                    vec2f vec2a(PullRandomFloatVal(), PullRandomFloatVal());
                    vec2f vec2b(PullRandomFloatVal(), PullRandomFloatVal());
                    vec3f vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec3f vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec4f vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec4f vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    auto x = vec2f::dot(vec2a, vec2b);
                    auto y = vec3f::dot(vec3f::cross(vec3a, vec3b), vec3b);
                    auto z = vec4f::dot(vec4a, vec4b);
                    auto w = vec4f::dot((vec4a + vec4b), vec4b);

                    results.mvVec4f = move::math::vec4f(x, y, z, w);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });
        }

        void complex2vec3(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector3 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector3 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.smVec3 =
                        ((vec3a + vec3b) * vec3c - vec3d).Cross(vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec3);
                });

            bench.run("glm",
                [&]
                {
                    glm::vec3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec3 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec3 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.glmVec3 =
                        glm::cross((vec3a + vec3b) * vec3c - vec3d, vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec3);
                });
            bench.run("LAB",
                [&]
                {
                    LAB::Vector<float, 3> vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 3> vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 3> vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 3> vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    //LAB::CrossProduct();
                    results.labVec3 = LAB::CrossProduct((vec3a + vec3b) * vec3c - vec3d, vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.labVec3);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    XMFLOAT3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT3 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT3 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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

                XMFLOAT3 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT3 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT3 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT3 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
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

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    vec3f vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec3f vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec3f vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec3f vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    auto stepOne = (vec3a + vec3b);
                    auto stepTwo = vec3c - vec3d;

                    results.mvVec3f = vec3f::cross((stepOne * stepTwo), vec3a);
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec3f);
                });
        }

        void complex3vec4(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    DirectX::SimpleMath::Vector4 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector4 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector4 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    DirectX::SimpleMath::Vector4 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.smVec4 = ((vec3a + vec3b) * vec3c - vec3d);
                    ankerl::nanobench::doNotOptimizeAway(results.smVec4);
                });

            bench.run("glm",
                [&]
                {
                    glm::vec4 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec4 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec4 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    glm::vec4 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.glmVec4 = (vec3a + vec3b) * vec3c - vec3d;
                    ankerl::nanobench::doNotOptimizeAway(results.glmVec4);
                });
            bench.run("LAB",
                [&]
                {
                    LAB::Vector<float, 4> vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 4> vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 4> vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    LAB::Vector<float, 4> vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.labVec4 = (vec3a + vec3b) * vec3c - vec3d;
                    ankerl::nanobench::doNotOptimizeAway(results.labVec4);
                });

            bench.run("DXM",
                [&]
                {
                    using namespace DirectX;
                    XMFLOAT4 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT4 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT4 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    XMFLOAT4 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

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

                XMFLOAT4 vec3a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT4 vec3b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT4 vec3c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                XMFLOAT4 vec3d(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
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

            bench.run("move::math(float)",
                [&]
                {
                    using namespace move::math;
                    vec4f vec4a(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec4f vec4b(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec4f vec4c(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vec4f vec4dd(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    results.mvVec4f = (vec4a + vec4b) * vec4c - vec4dd;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("rtm",
                [&]
                {
                    using namespace rtm;
                    vector4f vec4a = vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vector4f vec4b = vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vector4f vec4c = vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());
                    vector4f vec4d = vector_set(PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal());

                    vector4f stepOne = vector_mul(vector_add(vec4a, vec4b), vec4c);
                    vector4f stepTwo = vector_sub(stepOne, vec4d);

                    results.rtmVec4f = stepTwo;
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
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
                    results.labMat4a = LAB::Transform<float, 3>{
                        LAB::Vector<float, 3>(1.0f, 2.0f, 3.0f), //translation
                        LAB::Vector<float, 3>(0.5f, 0.5f, 0.5f), //rotation,
                        LAB::Vector<float, 3>(1.f, 2.f, 3.f) //scale
                    }.GetMatrix();
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

            bench.run("rtm::qvvf (~transformation matrix)",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvf = qvv_set(quat_set(0.5f, 0.5f, 0.5f, 1.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f),
                        vector_set(1.0f, 2.0f, 3.0f, 0.0f));

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

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa = mat4x4f::look_at(
                        vec3f(1, 2, 3), vec3f(4, 5, 6), vec3f(7, 8, 9));

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
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
                    results.glmMat4a = glm::perspective(0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.glmMat4a);
                });
            bench.run("LAB",
                [&]
                {
                    results.labMat4a = LAB::CreateProjectionMatrix(0.5f, 1920.f / 1080.f, 0.1f, 100.f);
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

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        mat4x4f::perspective(0.5f, 1.0f, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa = rtm::camera::perspective_fov_rh(
                        0.5f, 1.0f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
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

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa =
                        mat4x4f::orthographic(1280, 720, 0.1f, 100.0f);

                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa =
                        rtm::camera::ortho_rh(1280.0f, 720.f, 0.1f, 100.0f);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });
        }

        void vector_matrix_multiply(ankerl::nanobench::Bench& bench)
        {
            bench.run("SimpleMath",
                [&]
                {
                    results.smVec4 = DirectX::SimpleMath::Vector4::Transform(results.smVec4, results.smMat4a);
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
                    results.dxVecA = XMVector4Transform(results.dxVecA, results.dxMatA);
                    XMStoreFloat4(&results.dxVec4, results.dxVecA);
                    ankerl::nanobench::doNotOptimizeAway(results.dxVec4);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvVec4f = results.mvVec4f * results.mvMat4x4fa;
                    ankerl::nanobench::doNotOptimizeAway(results.mvVec4f);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f = matrix_mul_vector(results.rtmVec4fa, results.rtmMat4x4fa);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
                });

            bench.run("rtm::qvvf",
                [&]
                {
                    using namespace rtm;
                    results.rtmVec4f =
                        qvv_mul_point3(results.rtmVec4fa, results.rtmQvvf);

                    ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
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

                    results.dxMatA = XMMatrixMultiply(results.dxMatB, results.dxMatC);
                    ankerl::nanobench::doNotOptimizeAway(results.dxMatA);
                });

            bench.run("move::math (float)",
                [&]
                {
                    using namespace move::math;
                    results.mvMat4x4fa = results.mvMat4x4fb * results.mvMat4x4fc;
                    ankerl::nanobench::doNotOptimizeAway(results.mvMat4x4fa);
                });

            bench.run("rtm::qvvf",
                [&]
                {
                    using namespace rtm;
                    results.rtmQvvfa = qvv_mul(results.rtmQvvfb, results.rtmQvvfc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmQvvf);
                });

            bench.run("rtm::matrix4x4f",
                [&]
                {
                    using namespace rtm;
                    results.rtmMat4x4fa = matrix_mul(results.rtmMat4x4fb, results.rtmMat4x4fc);
                    ankerl::nanobench::doNotOptimizeAway(results.rtmMat4x4fa);
                });
        }
    }  // namespace matrices
}  // namespace mathbench

inline void test_camera_matrix_funcs()
{
    auto smMat = DirectX::SimpleMath::Matrix::CreateOrthographic(0.5f, 1.0f, 0.1f, 100.0f);
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


template<std::size_t Count>
void WriteAccuracyFile(std::ofstream& accuracyFile, std::string const& name, float* data){
    accuracyFile << "| " << std::setw(10) << std::right << name;
    for(uint8_t i = 0; i < Count; i++){
        accuracyFile << "| " << std::setw(10) << std::right << data[i];
    }
    accuracyFile << "\n";
}

template<std::size_t Count, typename T1, typename T2, typename T3, typename T4, typename T5>
requires(
    (sizeof(float) * Count) <= sizeof(T1),
    (sizeof(float) * Count) <= sizeof(T2),
    (sizeof(float) * Count) <= sizeof(T3),
    (sizeof(float) * Count) <= sizeof(T4),
    (sizeof(float) * Count) <= sizeof(T5)
)
void handle_accuracy_data(std::ofstream& accuracyFile, T1 sm, T2 glmV, T3 lab, T4 dx, T5 mv){
    constexpr std::size_t block_size = sizeof(float) * Count;

    std::array<std::array<float, Count>, 5> results;
    memcpy(&results[0][0], &sm, block_size);
    memcpy(&results[1][0], &glmV, block_size);
    memcpy(&results[2][0], &lab, block_size);
    memcpy(&results[3][0], &dx, block_size);
    memcpy(&results[4][0], &mv, block_size);

    accuracyFile << "|       lib |      val0 ";
    for(uint8_t i = 2; i <= Count; i++){
        accuracyFile << "| " << std::setw(10) << std::right << std::string("val") + std::to_string(i);
    }
    accuracyFile << "\n";
    for(uint8_t i = 0; i <= (Count - 1); i++){
        accuracyFile << "|----------:";
    }
    accuracyFile << "|:----------\n";
    std::string name = "sm";
    WriteAccuracyFile<Count>(accuracyFile, name, reinterpret_cast<float*>(&sm));
    name = "glm";
    WriteAccuracyFile<Count>(accuracyFile, name, reinterpret_cast<float*>(&glmV));
    name = "lab";
    WriteAccuracyFile<Count>(accuracyFile, name, reinterpret_cast<float*>(&lab));
    name = "dx";
    WriteAccuracyFile<Count>(accuracyFile, name, reinterpret_cast<float*>(&dx));
    name = "mv";
    WriteAccuracyFile<Count>(accuracyFile, name, reinterpret_cast<float*>(&mv));
} 

void CalculateAdd2Accuracy(std::ofstream& accuracyFile){
    float randomed[4] = {PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()};
    auto sm = DirectX::SimpleMath::Vector2(randomed[0], randomed[1]) + DirectX::SimpleMath::Vector2(randomed[2], randomed[3]);
    auto glmV = glm::vec2(randomed[0], randomed[1]) + glm::vec2(randomed[2], randomed[3]);
    auto lab = LAB::Vector<float, 2>(randomed[0], randomed[1]) + LAB::Vector<float, 2>(randomed[2], randomed[3]);
    
    DirectX::XMFLOAT2 lhs(randomed[0], randomed[1]);
    DirectX::XMFLOAT2 rhs(randomed[2], randomed[3]);
    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat2(&lhs);
    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat2(&rhs);
    DirectX::XMVECTOR result = DirectX::XMVectorAdd(lhsVec, rhsVec);
    DirectX::XMFLOAT2 dx;
    DirectX::XMStoreFloat2(&dx, result);

    auto mv = move::math::vec2f(randomed[0], randomed[1]) + move::math::vec2f(randomed[2], randomed[3]);

    handle_accuracy_data<2>(accuracyFile, sm, glmV, lab, dx, mv);
}
void CalculateAdd3Accuracy(std::ofstream& accuracyFile){

    float randomed[6] = {PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()};
    auto sm = DirectX::SimpleMath::Vector3(randomed[0], randomed[1], randomed[2]) +
                   DirectX::SimpleMath::Vector3(randomed[3], randomed[4], randomed[5]);
    auto glmV = glm::vec3(randomed[0], randomed[1], randomed[2]) +
                   glm::vec3(randomed[3], randomed[4], randomed[5]);
    auto lab = LAB::Vector<float, 3>(randomed[0], randomed[1], randomed[2]) +
                   LAB::Vector<float, 3>(randomed[3], randomed[4], randomed[5]);
                   
    DirectX::XMFLOAT3 lhs(randomed[0], randomed[1], randomed[2]);
    DirectX::XMFLOAT3 rhs(randomed[3], randomed[4], randomed[5]);
    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat3(&lhs);
    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat3(&rhs);
    DirectX::XMVECTOR result = DirectX::XMVectorAdd(lhsVec, rhsVec);

    DirectX::XMFLOAT3 dx;
    DirectX::XMStoreFloat3(&dx, result);
                    
    auto mv = move::math::vec3f(randomed[0], randomed[1], randomed[2]) + move::math::vec3f(randomed[3], randomed[4], randomed[5]);

    handle_accuracy_data<3>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(3);
}
void CalculateAdd4Accuracy(std::ofstream& accuracyFile){

    float randomed[8] = {PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()};
    auto sm = DirectX::SimpleMath::Vector4(randomed[0], randomed[1], randomed[2], randomed[3]) +
                   DirectX::SimpleMath::Vector4(randomed[4], randomed[5], randomed[6], randomed[7]);
    auto glmV = glm::vec4(randomed[0], randomed[1], randomed[2], randomed[3]) +
                   glm::vec4(randomed[4], randomed[5], randomed[6], randomed[7]);
    auto lab = LAB::Vector<float, 4>(randomed[0], randomed[1], randomed[2], randomed[3]) +
                   LAB::Vector<float, 4>(randomed[4], randomed[5], randomed[6], randomed[7]);
                   
    DirectX::XMFLOAT4 lhs(randomed[0], randomed[1], randomed[2], randomed[3]);
    DirectX::XMFLOAT4 rhs(randomed[4], randomed[5], randomed[6], randomed[7]);
    DirectX::XMVECTOR lhsVec = DirectX::XMLoadFloat4(&lhs);
    DirectX::XMVECTOR rhsVec = DirectX::XMLoadFloat4(&rhs);
    DirectX::XMVECTOR result = DirectX::XMVectorAdd(lhsVec, rhsVec);

    DirectX::XMFLOAT4 dx;
    DirectX::XMStoreFloat4(&dx, result);
                    
    auto mv = move::math::vec4f(randomed[0], randomed[1], randomed[2], randomed[3]) + move::math::vec4f(randomed[4], randomed[5], randomed[6], randomed[7]);
                 
    handle_accuracy_data<4>(accuracyFile, sm, glmV, lab, dx, mv);   
    //HANDLE_ACCURACY_DATA(4);
}
void CalculateComplex1Accuracy(std::ofstream& accuracyFile){

    float randomVals[4] = {
        PullRandomFloatVal(),
        PullRandomFloatVal(),
        PullRandomFloatVal(),
        PullRandomFloatVal()
    };
    DirectX::SimpleMath::Vector4 sm;
    {
        DirectX::SimpleMath::Vector2 vec2a(randomVals[0], randomVals[1]);
        DirectX::SimpleMath::Vector2 vec2b(randomVals[0], randomVals[1]);
        DirectX::SimpleMath::Vector3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::SimpleMath::Vector3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::SimpleMath::Vector4 vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        DirectX::SimpleMath::Vector4 vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        auto x = vec2a.Dot(vec2b);
        auto y = vec3a.Cross(vec3b).Dot(vec3b);
        auto z = vec4a.Dot(vec4b);
        auto w = (vec4a + vec4b).Dot(vec4b);
        sm = DirectX::SimpleMath::Vector4(x, y, z, w);
    }
    glm::vec4 glmV;
    {
        glm::vec2 vec2a(randomVals[0], randomVals[1]);
        glm::vec2 vec2b(randomVals[0], randomVals[1]);
        glm::vec3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        glm::vec3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        glm::vec4 vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        glm::vec4 vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        auto x = glm::dot(vec2a, vec2b);
        auto y = glm::dot(glm::cross(vec3a, vec3b), vec3b);
        auto z = glm::dot(vec4a, vec4b);
        auto w = glm::dot(vec4a + vec4b, vec4b);

        glmV = glm::vec4(x, y, z, w);
    }

    LAB::Vector<float, 4> lab;
    {
        LAB::Vector<float, 2> vec2a(randomVals[0], randomVals[1]);
        LAB::Vector<float, 2> vec2b(randomVals[0], randomVals[1]);
        LAB::Vector<float, 3> vec3a(randomVals[0], randomVals[1], randomVals[2]);
        LAB::Vector<float, 3> vec3b(randomVals[0], randomVals[1], randomVals[2]);
        LAB::Vector<float, 4> vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        LAB::Vector<float, 4> vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        auto x = vec2a.DotProduct(vec2b);
        auto y = LAB::DotProduct(LAB::CrossProduct(vec3a, vec3b), vec3b);
        auto z = LAB::DotProduct(vec4a, vec4b);
        auto w = LAB::DotProduct(vec4a + vec4b, vec4b);

        lab = LAB::Vector<float, 4>(x, y, z, w);
    }
    DirectX::XMFLOAT4 dx;
    {

        DirectX::XMFLOAT2 vec2a(randomVals[0], randomVals[1]);
        DirectX::XMFLOAT2 vec2b(randomVals[0], randomVals[1]);
        DirectX::XMFLOAT3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::XMFLOAT3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::XMFLOAT4 vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        DirectX::XMFLOAT4 vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        DirectX::XMVECTOR vec2aVec = XMLoadFloat2(&vec2a);
        DirectX::XMVECTOR vec2bVec = XMLoadFloat2(&vec2b);
        DirectX::XMVECTOR vec3aVec = XMLoadFloat3(&vec3a);
        DirectX::XMVECTOR vec3bVec = XMLoadFloat3(&vec3b);
        DirectX::XMVECTOR vec4aVec = XMLoadFloat4(&vec4a);
        DirectX::XMVECTOR vec4bVec = XMLoadFloat4(&vec4b);

        auto x = DirectX::XMVectorGetX(DirectX::XMVector2Dot(vec2aVec, vec2bVec));
        auto y = DirectX::XMVectorGetX(DirectX::XMVector3Dot(DirectX::XMVector3Cross(vec3aVec, vec3bVec), vec3bVec));
        auto z = DirectX::XMVectorGetX(DirectX::XMVector4Dot(vec4aVec, vec4bVec));
        auto w = DirectX::XMVectorGetX(DirectX::XMVector4Dot(DirectX::XMVectorAdd(vec4aVec, vec4bVec), vec4bVec));

        DirectX::XMStoreFloat4(&dx, DirectX::XMVectorSet(x, y, z, w));
    }
    move::math::vec4f mv;
    {
        using namespace move::math;

        vec2f vec2a(randomVals[0], randomVals[1]);
        vec2f vec2b(randomVals[0], randomVals[1]);
        vec3f vec3a(randomVals[0], randomVals[1], randomVals[2]);
        vec3f vec3b(randomVals[0], randomVals[1], randomVals[2]);
        vec4f vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        vec4f vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        auto x = vec2f::dot(vec2a, vec2b);
        auto y = vec3f::dot(vec3f::cross(vec3a, vec3b), vec3b);
        auto z = vec4f::dot(vec4a, vec4b);
        auto w = vec4f::dot((vec4a + vec4b), vec4b);

        mv = move::math::vec4f(x, y, z, w);
    }

    handle_accuracy_data<4>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(4);
}
void CalculateComplex2Accuracy(std::ofstream& accuracyFile){
    float randomVals[3] = {PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()};
    DirectX::SimpleMath::Vector3 sm;
    {
        DirectX::SimpleMath::Vector3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::SimpleMath::Vector3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::SimpleMath::Vector3 vec3c(randomVals[0], randomVals[1], randomVals[2]);
        DirectX::SimpleMath::Vector3 vec3d(randomVals[0], randomVals[1], randomVals[2]);

        sm = ((vec3a + vec3b) * vec3c - vec3d).Cross(vec3a);
    }
    glm::vec3 glmV;
    {
        glm::vec3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        glm::vec3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        glm::vec3 vec3c(randomVals[0], randomVals[1], randomVals[2]);
        glm::vec3 vec3d(randomVals[0], randomVals[1], randomVals[2]);

        glmV = glm::cross((vec3a + vec3b) * vec3c - vec3d, vec3a);
    }
    LAB::Vector<float, 3> lab;
    {
        LAB::Vector<float, 3> vec3a(randomVals[0], randomVals[1], randomVals[2]);
        LAB::Vector<float, 3> vec3b(randomVals[0], randomVals[1], randomVals[2]);
        LAB::Vector<float, 3> vec3c(randomVals[0], randomVals[1], randomVals[2]);
        LAB::Vector<float, 3> vec3d(randomVals[0], randomVals[1], randomVals[2]);

        //LAB::CrossProduct();
        lab = LAB::CrossProduct((vec3a + vec3b) * vec3c - vec3d, vec3a);
    }
    DirectX::XMFLOAT3 dx;
    {
        using namespace DirectX;
        XMFLOAT3 vec3a(randomVals[0], randomVals[1], randomVals[2]);
        XMFLOAT3 vec3b(randomVals[0], randomVals[1], randomVals[2]);
        XMFLOAT3 vec3c(randomVals[0], randomVals[1], randomVals[2]);
        XMFLOAT3 vec3d(randomVals[0], randomVals[1], randomVals[2]);

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

        XMStoreFloat3(&dx, vec3);
    }
    move::math::vec3f mv;
    {
        using namespace move::math;
        vec3f vec3a(randomVals[0], randomVals[1], randomVals[2]);
        vec3f vec3b(randomVals[0], randomVals[1], randomVals[2]);
        vec3f vec3c(randomVals[0], randomVals[1], randomVals[2]);
        vec3f vec3d(randomVals[0], randomVals[1], randomVals[2]);

        auto stepOne = (vec3a + vec3b);
        auto stepTwo = vec3c - vec3d;

        mv = vec3f::cross((stepOne * stepTwo), vec3a);
    }
    
    handle_accuracy_data<3>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(4);
}
void CalculateComplex3Accuracy(std::ofstream& accuracyFile){
    mathbench::vectors::complex3vec4;

    float randomVals[4] = {PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal(), PullRandomFloatVal()};

    DirectX::SimpleMath::Vector4 sm;
    {
        DirectX::SimpleMath::Vector4 vec3a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        DirectX::SimpleMath::Vector4 vec3b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        DirectX::SimpleMath::Vector4 vec3c(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        DirectX::SimpleMath::Vector4 vec3d(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        sm = ((vec3a + vec3b) * vec3c - vec3d);
    }
    glm::vec4 glmV;
    {
        glm::vec4 vec3a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        glm::vec4 vec3b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        glm::vec4 vec3c(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        glm::vec4 vec3d(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        glmV = (vec3a + vec3b) * vec3c - vec3d;
    }
    LAB::Vector<float, 4> lab;
    {
        LAB::Vector<float, 4> vec3a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        LAB::Vector<float, 4> vec3b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        LAB::Vector<float, 4> vec3c(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        LAB::Vector<float, 4> vec3d(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        lab = (vec3a + vec3b) * vec3c - vec3d;
    }

    DirectX::XMFLOAT4 dx;
    {
        using namespace DirectX;
        XMFLOAT4 vec3a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        XMFLOAT4 vec3b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        XMFLOAT4 vec3c(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        XMFLOAT4 vec3d(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        XMVECTOR vec3aVec = XMLoadFloat4(&vec3a);
        XMVECTOR vec3bVec = XMLoadFloat4(&vec3b);
        XMVECTOR vec3cVec = XMLoadFloat4(&vec3c);
        XMVECTOR vec3dVec = XMLoadFloat4(&vec3d);

        XMVECTOR vec3 = XMVectorSubtract(
            XMVectorMultiply(
                XMVectorAdd(vec3aVec, vec3bVec), vec3cVec),
            vec3dVec);

        XMStoreFloat4(&dx, vec3);
    }
    move::math::vec4f mv;
    {
        using namespace move::math;
        vec4f vec4a(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        vec4f vec4b(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        vec4f vec4c(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
        vec4f vec4dd(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

        mv = (vec4a + vec4b) * vec4c - vec4dd;
    }

    /*
    bench.run("rtm",
        [&]
        {
            using namespace rtm;
            vector4f vec4a = vector_set(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
            vector4f vec4b = vector_set(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
            vector4f vec4c = vector_set(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);
            vector4f vec4d = vector_set(randomVals[0], randomVals[1], randomVals[2], randomVals[3]);

            vector4f stepOne = vector_mul(vector_add(vec4a, vec4b), vec4c);
            vector4f stepTwo = vector_sub(stepOne, vec4d);

            results.rtmVec4f = stepTwo;
            ankerl::nanobench::doNotOptimizeAway(results.rtmVec4f);
        });
    */

    handle_accuracy_data<4>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(4);
}
void CalculateModelAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::construct_model_matrix;

    DirectX::SimpleMath::Matrix sm;
    {
        sm =
            DirectX::SimpleMath::Matrix::CreateTranslation(
                1.0f, 2.0f, 3.0f) *
            DirectX::SimpleMath::Matrix::CreateRotationX(0.5f) *
            DirectX::SimpleMath::Matrix::CreateRotationY(0.5f) *
            DirectX::SimpleMath::Matrix::CreateRotationZ(0.5f) *
            DirectX::SimpleMath::Matrix::CreateScale(
                1.0f, 2.0f, 3.0f);
    }

    glm::mat4 glmV;
    {
        glmV = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)) *
            glm::rotate(glm::mat4(1.0f), 0.5f, glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), 0.5f, glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f)
        );
    }
    LAB::Matrix<float, 4, 4> lab;
    {
        const LAB::Matrix<float, 4, 4> identity = LAB::Identity<float, 4>(1.f);
        lab = LAB::Translate(identity, LAB::Vector<float, 3>(1.f, 2.f, 3.f)) *
            LAB::Rotate(identity, 0.5f, LAB::Vector<float, 3>(1.f, 0.f, 0.f)) *
            LAB::Rotate(identity, 0.5f, LAB::Vector<float, 3>(0.f, 1.f, 0.f)) *
            LAB::Rotate(identity, 0.5f, LAB::Vector<float, 3>(0.f, 0.f, 1.f)) *
            LAB::Scale(identity, LAB::Vector<float, 3>(1.f, 2.f, 3.f)
        );
    }

    DirectX::XMMATRIX dx;
    {
        using namespace DirectX;
        // Use XMMatrixMultiply

        dx = XMMatrixMultiply(
            XMMatrixMultiply(
                XMMatrixMultiply(
                    XMMatrixMultiply(
                        XMMatrixTranslation(1.0f, 2.0f, 3.0f),
                        XMMatrixRotationX(0.5f)),
                    XMMatrixRotationY(0.5f)),
                XMMatrixRotationZ(0.5f)),
            XMMatrixScaling(1.0f, 2.0f, 3.0f));
    }

    move::math::float4x4 mv;
    {
        using namespace move::math;
        mv =
            mat4x4f::translation({1, 2, 3}) *
            mat4x4f::rotation_x(0.5f) * mat4x4f::rotation_y(0.5f) *
            mat4x4f::rotation_z(0.5f) * mat4x4f::scale(1, 2, 3);
    }

    handle_accuracy_data<16>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}
void CalculateViewAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::construct_view_matrix;

    DirectX::SimpleMath::Matrix sm;
    {
        sm = DirectX::SimpleMath::Matrix::CreateLookAt(
            DirectX::SimpleMath::Vector3(1.0f, 2.0f, 3.0f),
            DirectX::SimpleMath::Vector3(4.0f, 5.0f, 6.0f),
            DirectX::SimpleMath::Vector3(0.f, 1.f, 0.f));
    }

    glm::mat4 glmV;
    {
        glmV = glm::lookAt(glm::vec3(1.0f, 2.0f, 3.0f),
            glm::vec3(4.0f, 5.0f, 6.0f),
            glm::vec3(0.f, 1.f, 0.f));
    }

    LAB::Matrix<float, 4, 4> lab;
    LAB::Vector<float, 3> center = LAB::Vector<float, 3>(4.0f, 5.0f, 6.0f);
    LAB::Vector<float, 3> eye = LAB::Vector<float, 3>(1.0f, 2.0f, 3.0f);
    LAB::Vector<float, 3> lookat = (center - eye).Normalized();
    {
        lab = LAB::CreateViewMatrix(
            eye,
            lookat);
    }

    DirectX::XMMATRIX dx;
    {
        using namespace DirectX;
        dx =
            XMMatrixLookAtLH(XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f),
                XMVectorSet(4.0f, 5.0f, 6.0f, 0.0f),
                XMVectorSet(0.f, 1.f, 0.f, 0.f));
    }

    move::math::float4x4 mv;
    {
        using namespace move::math;
        mv = mat4x4f::look_at(
            vec3f(1, 2, 3), vec3f(4, 5, 6), vec3f(0.f, 1.f, 0.f));
    }

    handle_accuracy_data<16>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}
void CalculateProjectionAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::construct_perspective_projection_matrix;

    DirectX::SimpleMath::Matrix sm = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(0.5f, 1.0f, 0.1f, 100.0f);
    

    glm::mat4 glmV = glm::perspective(0.5f, 1.0f, 0.1f, 100.0f);
    
    
    LAB::Matrix<float, 4, 4> lab = LAB::CreateProjectionMatrix(0.5f, 1.f, 0.1f, 100.f);
    
        
    DirectX::XMMATRIX dx = DirectX::XMMatrixPerspectiveFovLH(0.5f, 1.0f, 0.1f, 100.0f);

    move::math::float4x4 mv = move::math::mat4x4f::perspective(0.5f, 1.0f, 0.1f, 100.0f);


    handle_accuracy_data<16>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}
void CalculateOrthoAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::ortho_projection_matrix;
    DirectX::SimpleMath::Matrix sm= DirectX::SimpleMath::Matrix::CreateOrthographic(1280, 720, 0.1f, 100.0f);
    glm::mat4 glmV = glm::ortho<float>(0, 1280, 0, 720, 0.1f, 100.0f);
    LAB::Matrix<float, 4, 4> lab = LAB::CreateOrthographicMatrix(0.f, 720.f, 0.f, 1280.f, 0.1f, 100.f);
    DirectX::XMMATRIX dx = DirectX::XMMatrixOrthographicLH(1280, 720, 0.1f, 100.0f);
    move::math::float4x4 mv = move::math::mat4x4f::orthographic(1280, 720, 0.1f, 100.0f);

    handle_accuracy_data<16>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}
void CalculateMatVecAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::vector_matrix_multiply;

    float randomVals[16];
    for(uint8_t i = 0; i < 16; i++){
        randomVals[i] = PullRandomFloatVal();
    }
    float randomVecVals[4];
    for(uint8_t i = 0; i < 4; i++){
        randomVecVals[i] = PullRandomFloatVal();
    }

    DirectX::SimpleMath::Matrix smMat;
    memcpy(&smMat, randomVals, sizeof(float) * 16);
    glm::mat4 glmMat;
    memcpy(&glmMat, randomVals, sizeof(float) * 16);
    LAB::Matrix<float, 4, 4> labMat;
    memcpy(&labMat, randomVals, sizeof(float) * 16);
    DirectX::XMMATRIX dxMat;
    memcpy(&dxMat, randomVals, sizeof(float) * 16);
    move::math::float4x4 mvMat;
    memcpy(&mvMat, randomVals, sizeof(float) * 16);


    DirectX::SimpleMath::Vector4 sm2;
    glm::vec4 glmV2;
    LAB::Vector<float, 4> lab2;
    DirectX::XMVECTOR dx2;
    move::math::fast_float4 mv2;
    memcpy(&sm2, randomVecVals, sizeof(float) * 4);
    memcpy(&glmV2, randomVecVals, sizeof(float) * 4);
    memcpy(&lab2, randomVecVals, sizeof(float) * 4);
    memcpy(&dx2, randomVecVals, sizeof(float) * 4);
    memcpy(&mv2, randomVecVals, sizeof(float) * 4);

    DirectX::SimpleMath::Vector4 sm = DirectX::SimpleMath::Vector4::Transform(sm2, smMat);
    glm::vec4 glmV = glmMat * glmV2;
    LAB::Vector<float, 4> lab = labMat * lab2;
    DirectX::XMFLOAT4 dx;
    DirectX::XMVECTOR dxA = DirectX::XMVector4Transform(dx2, dxMat);
    DirectX::XMStoreFloat4(&dx, dxA);

    move::math::fast_float4 mv;
    mv = mv2 * mvMat;

    handle_accuracy_data<4>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}
void CalculateMatMatAccuracy(std::ofstream& accuracyFile){
    mathbench::matrices::matrix_matrix_multiply;

    float randomVals[16];
    for(uint8_t i = 0; i < 16; i++){
        randomVals[i] = PullRandomFloatVal();
    }
    float randomVals2[16];
    for(uint8_t i = 0; i < 16; i++){
        randomVals2[i] = PullRandomFloatVal();
    }

    DirectX::SimpleMath::Matrix smMat;
    memcpy(&smMat, randomVals, sizeof(float) * 16);
    glm::mat4 glmMat;
    memcpy(&glmMat, randomVals, sizeof(float) * 16);
    LAB::Matrix<float, 4, 4> labMat;
    memcpy(&labMat, randomVals, sizeof(float) * 16);
    DirectX::XMMATRIX dxMat;
    memcpy(&dxMat, randomVals, sizeof(float) * 16);
    move::math::float4x4 mvMat;
    memcpy(&mvMat, randomVals, sizeof(float) * 16);
    
    DirectX::SimpleMath::Matrix smMat2;
    memcpy(&smMat2, randomVals2, sizeof(float) * 16);
    glm::mat4 glmMat2;
    memcpy(&glmMat2, randomVals2, sizeof(float) * 16);
    LAB::Matrix<float, 4, 4> labMat2;
    memcpy(&labMat2, randomVals2, sizeof(float) * 16);
    DirectX::XMMATRIX dxMat2;
    memcpy(&dxMat2, randomVals2, sizeof(float) * 16);
    move::math::float4x4 mvMat2;
    memcpy(&mvMat2, randomVals2, sizeof(float) * 16);


    DirectX::SimpleMath::Matrix sm = smMat * smMat2;

    glm::mat4 glmV = glmMat * glmMat2;

    LAB::Matrix<float, 4, 4> lab = labMat * labMat2;

    DirectX::XMMATRIX dx = DirectX::XMMatrixMultiply(dxMat, dxMat2);

    move::math::float4x4 mv = mvMat * mvMat2;


    handle_accuracy_data<16>(accuracyFile, sm, glmV, lab, dx, mv);
    //HANDLE_ACCURACY_DATA(16);
}


int main() {
    //constexpr int iterations = 1000000;
    constexpr int iterations = 1000; //quick testing
    // test_camera_matrix_funcs();

    std::random_device ran_dev{};
    std::mt19937 ran_eng{ran_dev()};
    std::uniform_real_distribution<float> distri(-10.f, 10.f);
    random_float_values.clear();
    random_float_values.reserve(1000);
    for(uint64_t i = 0; i < 1000; i++){
        random_float_values.push_back(distri(ran_eng));
    }

    std::ofstream file("benchmark_results.txt", std::ios::trunc);
    file << std::fixed << std::setprecision(2);

    std::ofstream accuracy_file("accuracy_results.txt", std::ios::trunc);
    accuracy_file << std::fixed << std::setprecision(2);

    {
        accuracy_file << "| add 2\n";
        CalculateAdd2Accuracy(accuracy_file);
        accuracy_file << "\n| add 3\n";
        CalculateAdd3Accuracy(accuracy_file);
        accuracy_file << "\n| add 4\n";
        CalculateAdd4Accuracy(accuracy_file);
        accuracy_file << "\n| compelx 1\n";
        CalculateComplex1Accuracy(accuracy_file);
        accuracy_file << "\n| complex 2\n";
        CalculateComplex2Accuracy(accuracy_file);
        accuracy_file << "\n| complex 3\n";
        CalculateComplex3Accuracy(accuracy_file);
        accuracy_file << "\n| model\n";
        CalculateModelAccuracy(accuracy_file);
        accuracy_file << "\n| view\n";
        CalculateViewAccuracy(accuracy_file);
        accuracy_file << "\n| projection\n";
        CalculateProjectionAccuracy(accuracy_file);
        accuracy_file << "\n| ortho\n";
        CalculateOrthoAccuracy(accuracy_file);
        accuracy_file << "\n| matvec\n";
        CalculateMatVecAccuracy(accuracy_file);
        accuracy_file << "\n| matmat\n";
        CalculateMatMatAccuracy(accuracy_file);
    }

    
    try
    {
        {
            ankerl::nanobench::Bench noopBench;
            noopBench.name("noop");
            noopBench.minEpochIterations(iterations);
            float floatnum = 0.f;
            noopBench.run("Store float (reference 'no-op')",
                [&]
                {
                    floatnum = 0.f;
                    ankerl::nanobench::doNotOptimizeAway(floatnum);
                });

            noopBench.run("Pull (1) Random Float And Store (reference 'no-op')",
                [&]
                {
                    floatnum = random_float_values[random_float_iter];
                    random_float_iter = (random_float_iter + 1) % random_float_values.size();
                    ankerl::nanobench::doNotOptimizeAway(floatnum);
                });

            noopBench.run("Pull (2) Random Float And Store (reference 'no-op')",
                [&]
                {
                    floatnum = PullRandomFloatVal() + PullRandomFloatVal();
                    ankerl::nanobench::doNotOptimizeAway(floatnum);
                });

            noopBench.run("Pull (3) Random Float And Store (reference 'no-op')",
                [&]
                {
                    floatnum = PullRandomFloatVal() + PullRandomFloatVal() + PullRandomFloatVal();
                    ankerl::nanobench::doNotOptimizeAway(floatnum);
                });

            noopBench.run("Pull (4) Random Float And Store (reference 'no-op')",
                [&]
                {
                    floatnum = PullRandomFloatVal() + PullRandomFloatVal() + PullRandomFloatVal() + PullRandomFloatVal();
                    ankerl::nanobench::doNotOptimizeAway(floatnum);
                });
            auto resultCopy = noopBench.results();
            WriteTable(file, "no-op", resultCopy);
        }
        BenchmarkWrapper("vec2 add", file, iterations, mathbench::vectors::addition2);
//this is here for quick testing. just toggle 0 to 1 for quick enable/disable
#if 1
        BenchmarkWrapper("vec3 add", file, iterations, mathbench::vectors::addition3);
        BenchmarkWrapper("vec4 add", file, iterations, mathbench::vectors::addition4);
        BenchmarkWrapper("dot and cross", file, iterations, mathbench::vectors::complex1);
        BenchmarkWrapper("add sub multi cross vec3", file, iterations, mathbench::vectors::complex2vec3);
        BenchmarkWrapper("add sub multi vec4", file, iterations, mathbench::vectors::complex3vec4);

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