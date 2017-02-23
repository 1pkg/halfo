#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "File.hpp"
#include <unordered_map>

namespace Components
{

struct Result
{
	unsigned int
		score,
		seconds,
		integral;
	Result(
		unsigned int score,
		unsigned int seconds,
		unsigned int integral
	);
	Result();
	bool operator<(const Result & result);
};

class Storage : public File
{
public:

	const std::string DISABLE_ADDS_FEATURE = "disable-adds";

	const std::string FIGURE_SKIN_SETTING = "figure-skin";
	const std::string HAMMER_SKIN_SETTING = "hammer-skin";

	Storage();
	void flush() const override;
	void pull() override;

	bool feature(const std::string & feature) const;
	std::string setting(const std::string & setting) const;
	const Result & result(unsigned int index) const;
	unsigned int total() const;

	void unblock(const std::string & feature);
	void change(const std::string & setting, const std::string & value);
	void update(const Result & score);

protected:

	std::string path() const override;
	cocos2d::Data serialize() const override;
	bool unserialize(const cocos2d::Data & buffer) override;
	void default() override;

private:

	const unsigned int RESULTS_LIMIT = 100;

	std::unordered_map<
		std::string,
		bool
	> _features;
	std::unordered_map<
		std::string,
		std::string
	> _settings;
	std::vector<Result> _results;
	unsigned int _total;

};

}

#endif