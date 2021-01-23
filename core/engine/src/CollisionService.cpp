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

    /*
     * @https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm
     *
     * using:
     *
     *
     * @param e  is the starting point of the ray,
     * @param d  is the direction vector of ray, from start to end
     * @param ci is the center of sphere you're testing against
     * @param r  is the radius of that sphere
     *
     * f = e - ci; is the vector from center sphere to ray start
     *
     * then the intersection is found by plugging:
     * p = e + t * d
     * into
     * (p.x - ci.x)^2 + (p.y - ci.y)^2 = r2
     *
     * by reforming the term we get an eqution of form:
     * t = a * x^2 + b * x^2 + c
     * where:
     * a = dot(d, d)
     * b = 2 * dot(f, d)
     * c = dot(f, f) - r^2
     *
     * here we can get the discriminant, to see if the line hits the circle:
     * [discriminant = 0] => two roots are equal, single result => touch
     * [discriminant < 0] => no root in real numbers, no result => miss
     * [discriminant > 0] => two roots arent equal, two results => hit
     *
     * on touch and miss we return false (no intersect), where touch is a design decision that is not accurate in math.
     * on hit we need to further analyse if the hit was on the line segment, by calculating the equation.
     */
    bool intersect (glm::vec2 e, glm::vec2 d, glm::vec2 ci, float r)
    {
        auto f = e - ci;

        auto a = glm::dot(d, d);
        auto b = 2.0f * glm::dot(f, d);
        auto c = glm::dot(f, f) - r * r;

        auto discriminant = b * b - 4.0f * a * c;

        if (discriminant > 0.0f)
        {
            discriminant = sqrt(discriminant);

            float t1 = (-b - discriminant) / (a + a);
            if (t1 >= 0.0f && t1 <= 1.0f)
                return true;

            float t2 = (-b + discriminant) / (a + a);
            if (t2 >= 0.0f && t2 <= 1.0f)
                return true;
        }

        return false;
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

        auto line_entities = reg.view<StaticCollisionLine>();
        auto circle_entities = reg.group<DynamicCollisionCircle>(entt::get<PositionComponent>);

        for (const auto circle_entity: circle_entities)
        {
            auto &circle = reg.get<DynamicCollisionCircle>(circle_entity);
            auto &circle_position = reg.get<PositionComponent>(circle_entity);

            LABEL_RELOOP:
            for (const auto static_comp: line_entities)
            {
                const auto &line = line_entities.get<StaticCollisionLine>(static_comp);

                // only check for collision if the circle moves against wall
                if (orient2dfast(line.position, line.position + line.direction, line.position + circle.direction_norm) > 0)
                {
                    // check whether the circle will intersect at target position
                    if (intersect(line.position, line.direction, circle_position + circle.velocity() * delta, circle.radius))
                    {
                        circle.velocity(glm::proj(circle.velocity(), glm::normalize(line.direction)));
                        goto LABEL_RELOOP;
                    }
                }
            }

            circle_position += circle.velocity() * delta;
            circle.direction_norm = {};
            circle.speed = 0.0f;
        }
    }
}
