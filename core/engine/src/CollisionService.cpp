#include <engine/service/CollisionService.hpp>

#include <engine/component/StaticCollisionLine.hpp>
#include <engine/component/DynamicCollisionCircle.hpp>

#include <glm/gtx/projection.hpp>

#include <spdlog/spdlog.h>
#include <cmath>

namespace
{
    /*
     * @https://www.cs.cmu.edu/~quake/robust.html
     *
     * Return a positive value if the points pa, pb, and pc occur
     * in counterclockwise order; a negative value if they occur
     * in clockwise order; and zero if they are collinear.  The
     * result is also a rough approximation of twice the signed
     * area of the triangle defined by the three points.
     */
    float orient2dfast (glm::vec2 pa, glm::vec2 pb, glm::vec2 pc)
    {
        const float acx = pa[0] - pc[0];
        const float bcx = pb[0] - pc[0];
        const float acy = pa[1] - pc[1];
        const float bcy = pb[1] - pc[1];
        return acx * bcy - acy * bcx;
    }

    bool intersect (glm::vec2 line_pos, glm::vec2 line_dir, glm::vec2 circle_pos, float circle_radius)
    {
        //@https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm

        auto d = line_dir;
        auto f = line_pos - circle_pos;
        auto r = circle_radius;

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
            float t1 = (-b - discriminant) / (a + a);
            float t2 = (-b + discriminant) / (a + a);

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
        static auto i = 0;
        ++i;

        using namespace component;
        delta = std::min(delta, 0.024f); // assume min 24 fps or drop time

        auto static_group = reg.view<StaticCollisionLine>();
        auto dynamic_group = reg.group<DynamicCollisionCircle>(entt::get<PositionComponent>);

        for (const auto dynamic_comp: dynamic_group)
        {
            auto &dynamic_i = reg.get<DynamicCollisionCircle>(dynamic_comp);
            auto &position_i = reg.get<PositionComponent>(dynamic_comp);

            LABEL_RELOOP:
            for (const auto static_comp: static_group)
            {
                const auto &line = static_group.get<StaticCollisionLine>(static_comp);

                glm::vec2 circle_pos = position_i + dynamic_i.velocity() * delta;

                // only check for collision if the circle moves against wall
                if (orient2dfast(line.position, line.position + line.direction, line.position + dynamic_i.direction_norm) > 0)
                {
                    // check whether the circle will intersect at target position
                    if (intersect(line.position, line.direction, circle_pos, dynamic_i.radius))
                    {
                        dynamic_i.velocity(glm::proj(dynamic_i.velocity(), glm::normalize(line.direction)));
                        goto LABEL_RELOOP;
                    }
                }
            }

            position_i += dynamic_i.velocity() * delta;
            dynamic_i.direction_norm = {};
            dynamic_i.speed = 0.0f;
        }
    }
}
