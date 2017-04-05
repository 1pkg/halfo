#include "components.hpp"
#include "Menu.hpp"

namespace Scenes
{


Menu::Menu()
	: Application::Scene(cocos2d::Scene::create())
{
	cocos2d::Vec2 origin = Master::instance().get<Components::Metric>().origin();
	cocos2d::Size size = Master::instance().get<Components::Metric>().size();

	Views::Ui::Panel play;

	Views::Ui::Button button("play", "", std::bind(&Master::scene, &Master::instance(), "play"));
	play.attach(button);
	float scaleButton = size.width * 0.2f / button.getContentSize().width;
	button.setScale(scaleButton);
	button.setContentSize(button.getContentSize() * scaleButton);
	button.setPosition(cocos2d::Vec2(size.width * 0.15f - button.getContentSize().width * 0.5f, 0.0f));

	Views::Ui::Label label("TAP TO PLAY");
	play.attach(label);
	float scaleLabel = size.width * 0.3f / label.getContentSize().width;
	label.setScale(scaleLabel);
	label.setContentSize(label.getContentSize() * scaleLabel);
	label.setPosition(cocos2d::Vec2(0.0f, button.getContentSize().height + label.getContentSize().height));

	play.setContentSize(cocos2d::Size(label.getContentSize().width, button.getContentSize().height + label.getContentSize().height));
	play.setPosition(cocos2d::Vec2(size.width * 0.5f - play.getContentSize().width * 0.5f, size.height * 0.5f));

	Views::Ui::Panel menu;

	Views::Ui::Button scores("scores", "Scores", std::bind(&Master::scene, &Master::instance(), "scores"));
	menu.attach(scores);
	scores.setPosition(cocos2d::Vec2(0.0f, 0.0f));

	Views::Ui::Button purchase("purchase", "Purchase", std::bind(&Master::scene, &Master::instance(), "purchase"));
	menu.attach(purchase);
	purchase.setPosition(cocos2d::Vec2(purchase.getContentSize().width * 1.5f, 0.0f));

	Views::Ui::Button info("info", "Info", std::bind(&Master::scene, &Master::instance(), "info"));
	menu.attach(info);
	info.setPosition(cocos2d::Vec2(info.getContentSize().width * 3.0f, 0.0f));

	Views::Ui::Button settings("settings", "Settings", std::bind(&Master::scene, &Master::instance(), "settings"));
	menu.attach(settings);
	settings.setPosition(cocos2d::Vec2(settings.getContentSize().width * 4.5f, 0.0f));

	menu.setContentSize(cocos2d::Size(scores.getContentSize().width * 5.5f, scores.getContentSize().height * 1.2f));

	Views::Ui::Separator separator(cocos2d::Vec2(0.0f, 0.0f), cocos2d::Vec2(menu.getContentSize().width, 0.0f));
	menu.attach(separator);
	separator.setPosition(cocos2d::Vec2(menu.getContentSize().width * 0.5f, menu.getContentSize().height - 3.0f));

	float scaleMenu = size.width * 0.5f / menu.getContentSize().width;
	menu.setScale(scaleMenu);
	menu.setContentSize(menu.getContentSize() * scaleMenu);
	menu.setPosition(cocos2d::Vec2(size.width * 0.5f - menu.getContentSize().width * 0.5f, 0.0f) + origin);

	Views::Ui::Panel share;

	Views::Ui::Button review("review", "Review", std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), "review"));
	share.attach(review);
	review.setPosition(cocos2d::Vec2(0.0f, 0.0f));

	Views::Ui::Button facebook("facebook", "Facebook", std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), "facebook"));
	share.attach(facebook);
	facebook.setPosition(cocos2d::Vec2(facebook.getContentSize().width * 1.5f, 0.0f));

	Views::Ui::Button twitter("twitter", "Twitter", std::bind(&Components::Share::share, &Master::instance().get<Components::Share>(), "twitter"));
	share.attach(twitter);
	twitter.setPosition(cocos2d::Vec2(twitter.getContentSize().width * 3.0f, 0.0f));

	share.setContentSize(cocos2d::Size(review.getContentSize().width * 4.0f, review.getContentSize().width));
	float scaleShare = size.width * 0.2f / share.getContentSize().width;
	share.setScale(scaleShare);
	share.setContentSize(share.getContentSize() * scaleShare);
	share.setPosition(cocos2d::Vec2(size.width * 0.5f + menu.getContentSize().width * 0.5f - share.getContentSize().width, menu.getContentSize().height) + origin);

	cocos2d::Layer * ui = cocos2d::LayerColor::create(cocos2d::Color4B::WHITE);
	ui->addChild(play.node());
	ui->addChild(menu.node());
	ui->addChild(share.node());
	_scene->addChild(ui);
}

}