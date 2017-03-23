#include "components.hpp"
#include "Over.hpp"

namespace Scenes
{

Over::Over()
	: Application::Scene(cocos2d::Scene::create()),
	_play(new Views::Ui::Button("Play", true)),
	_menu(new Views::Ui::Button("Menu", false)),
	_exit(new Views::Ui::Button("Exit", false)),
	_result(new Views::Ui::Label(MEDIUM_FONT_SIZE))
{
	_play->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_PLAY);
	_play->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.4f));
	_play->attach(this);

	_menu->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_MENU);
	_menu->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_menu->attach(this);

	_exit->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_EXIT);
	_exit->setPosition(Master::instance().get<Components::Metric>().center());
	_exit->attach(this);

	const Result result = Master::instance().get<Components::Statistic>().table()[0];
	_result->setText("Slice:" + to_string(result.slices) + "|Time:" + to_string(result.slices) + "|Mass:" + to_string(result.mass));
	_result->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height / 3.0f));
	_result->attach(this);
}

}