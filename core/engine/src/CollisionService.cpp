#include <engine/service/CollisionService.hpp>

#include <engine/component/StaticCollisionLine.hpp>
#include <engine/component/DynamicCollisionCircle.hpp>

#include <glm/gtx/projection.hpp>

#include <spdlog/spdlog.h>
#include <cmath>

namespace
{
    struct SCLine
    {
        glm::vec2 position{};
        glm::vec2 direction{};
    };

    struct DCCircle
    {
        glm::vec2 position{};
        float radius = 0.0f;
    };

    bool intersect (SCLine line, DCCircle circle)
    {
        //@https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm

        auto d = line.direction;
        auto f = line.position - circle.position;
        auto r = circle.radius;

        auto a = glm::dot(d, d);
        auto b = 2 * glm::dot(f, d);
        auto c = glm::dot(f, f) - r * r;

        auto discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
        {
            // no intersection
            return false;
        }
        else
        {
            // ray didn't totally miss sphere,
            // so there is a solution to
            // the equation.

            discriminant = sqrt(discriminant);

            // either solution may be on or off the ray so need to test both
            // t1 is always the smaller value, because BOTH discriminant and
            // a are nonnegative.
            float t1 = (-b - discriminant) / (a+a);
            float t2 = (-b + discriminant) / (a+a);

            // 3x HIT cases:
            //          -o->             --|-->  |            |  --|->
            // Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit),

            // 3x MISS cases:
            //       ->  o                     o ->              | -> |
            // FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

            if (t1 >= 0 && t1 <= 1)
            {
                // t1 is the intersection, and it's closer than t2
                // (since t1 uses -b - discriminant)
                // Impale, Poke
                return true;
            }

            // here t1 didn't intersect so we are either started
            // inside the sphere or completely past it
            if (t2 >= 0 && t2 <= 1)
            {
                // ExitWound
                return true;
            }

            // no intn: FallShort, Past, CompletelyInside
            return false;
        }
    }
}

namespace engine::service
{
    void Collision::init ()
    {
    }

    void Collision::update (entt::registry &reg, float delta)
    {
        using namespace component;
        delta = std::min(delta, 0.2f);

        auto static_group = reg.view<StaticCollisionLine>();
        auto dynamic_group = reg.group<DynamicCollisionCircle>(entt::get<PositionComponent>);

        for (const auto dynamic_comp: dynamic_group)
        {
            auto &dynamic_i = reg.get<DynamicCollisionCircle>(dynamic_comp);
            auto &position_i = reg.get<PositionComponent>(dynamic_comp);

            for (const auto static_comp: static_group)
            {
                const auto &line = static_group.get<StaticCollisionLine>(static_comp);

                if (intersect({line.position, line.direction}, {position_i + dynamic_i.velocity, dynamic_i.radius}))
                {
                    dynamic_i.velocity = glm::proj(dynamic_i.velocity, glm::normalize(line.direction));
                }
            }

            position_i += dynamic_i.velocity;
            dynamic_i.velocity = {};
        }
    }
}
