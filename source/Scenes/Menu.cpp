#include "components.hpp"
#include "Menu.hpp"

namespace Scenes
{


Menu::Menu()
	: Application::Scene(cocos2d::Scene::create()),
	_play(new Views::Ui::Button("Play", true)),
	_score(new Views::Ui::Button("Score", false)),
	_purchape(new Views::Ui::Button("Purchape", false)),
	_settings(new Views::Ui::Button("Settings", false)),
	_credits(new Views::Ui::Button("Credits", false)),
	_twitter(new Views::Ui::Button("Twitter", false)),
	_facebook(new Views::Ui::Button("Facebook", false)),
	_review(new Views::Ui::Button("Review", false))
{
	_play->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_PLAY);
	_play->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.4f));
	_play->attach(this);

	_score->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_score->attach(this);

	_purchape->setPosition(Master::instance().get<Components::Metric>().center());
	_purchape->attach(this);

	_settings->click = std::bind(&Master::scene, &Master::instance(), Master::SCENE_SETTINGS);
	_settings->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_settings->attach(this);

	_credits->setPosition(Master::instance().get<Components::Metric>().center() - cocos2d::Size(0.0f, Master::instance().get<Components::Metric>().size().height * 0.4f));
	_credits->attach(this);

	_twitter->click = std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), SHARE_TWITTER);
	_twitter->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(Master::instance().get<Components::Metric>().size().width * 0.3f, 0.0f));
	_twitter->attach(this);

	_facebook->click = std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), SHARE_FACEBOOK);
	_facebook->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(Master::instance().get<Components::Metric>().size().width * 0.3f, Master::instance().get<Components::Metric>().size().height * 0.2f));
	_facebook->attach(this);

	_review->click = std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), SHARE_REVIEW);
	_review->setPosition(Master::instance().get<Components::Metric>().center() + cocos2d::Size(Master::instance().get<Components::Metric>().size().width * 0.3f, -Master::instance().get<Components::Metric>().size().height * 0.2f));
	_review->attach(this);
}

}