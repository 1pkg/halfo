#include "components.hpp"
#include "Architector.hpp"
#include "Objects/Figure.hpp"

namespace Components
{

std::unique_ptr<Objects::Figure>
Architector::provide()
{
	static bool side = false;
	cocos2d::Polygon pattern = generate(Master::instance().get<Components::Metric>().spawn());
	cocos2d::log("Provide figure %s on side: %s\n", to_string(pattern).data(), side ? "right" : "left");
	std::unique_ptr<Objects::Figure> figure(new Objects::Figure(pattern));

	float velocity =
		(side ? -1 : 1) * Master::instance().get<Components::Metric>().absolute(cocos2d::RandomHelper::random_real<>(100.0f, 300.0f));
	float angularVelocity =
		Master::instance().get<Components::Metric>().absolute(cocos2d::RandomHelper::random_real<>(0.5f, 1.0f));
	cocos2d::Vec2 spawn = Master::instance().get<Components::Metric>().spawn(side);
	cocos2d::log("Velocity: %f, AngularVelocity: %f, Spawn: %s\n", velocity, angularVelocity, to_string(spawn).data());
	figure->view()->body()->setVelocity(cocos2d::Vec2(velocity, 0.0f));
	figure->view()->body()->setAngularVelocity(angularVelocity);
	figure->view()->setPosition(spawn);
	side = !side;
	return figure;
}

cocos2d::Polygon
Architector::generate(const cocos2d::Size & boundary)
{
	std::random_device device;
    std::mt19937 generator(device());

	std::size_t count = cocos2d::RandomHelper::random_int<unsigned> (0, 9) + 3;
	float radius = boundary.width > boundary.height ? boundary.height / 2.0f : boundary.width / 2.0f;
	float irregularity = (cocos2d::RandomHelper::random_real<>(0.0f, 0.5f) + 0.25f) * 2.0f * M_PI / count;
    float spikeyness = (cocos2d::RandomHelper::random_real<>(0.0f, 0.6f) + 0.1f) * radius;

    std::vector<float> steps(count);
	for (std::size_t i = 0; i < count; ++i)
		steps[i] = cocos2d::RandomHelper::random_real<>((2.0f * M_PI / count) - irregularity, (2.0f * M_PI / count) + irregularity);

    float koef = std::accumulate(steps.begin(), steps.end(), 0.0f) / (2.0f * M_PI);
    for (std::size_t i = 0; i < count; ++i)
        steps[i] /= koef;

	std::vector<cocos2d::Vec2> points(count);
    std::normal_distribution<> distribution(radius, spikeyness);
	float angle = cocos2d::RandomHelper::random_real<float>(0.0f, 2.0f * std::_Pi);
    for (std::size_t i = 0; i < count; ++i)
	{
		float dist = distribution(generator);
        float base = (dist > 2.0f * radius) ? (2.0f * radius) : (dist < 0.0f ? 0.0f : dist);
        float x = base * std::cos(angle);
        float y = base * std::sin(angle);
        points[i] = cocos2d::Vec2(x, y);
        angle = angle + steps[i];
	}
    return points;
}

}