#ifndef COMPONENTS_STORAGE
#define COMPONENTS_STORAGE

#include "File.hpp"
#include <unordered_map>

namespace Components
{

class Storage : public File
{
public:

	struct Result
	{
		unsigned int score, seconds, integral;
		bool operator<(const Result & result){ return integral < result.integral || (integral == result.integral && score < result.score); }
	};

	const std::string DISABLE_ADDS_FEATURE = "disable-adds";

	const std::string FIGURE_SKIN_SETTING = "figure-skin";
	const std::string HAMMER_SKIN_SETTING = "hammer-skin";

	std::string path() const override;
	void flush() const override;
	void fetch() override;

	Storage();
	~Storage();

	bool feature(const std::string & feature) const;
	std::string setting(const std::string & setting) const;
	const Result & result(unsigned int index) const;
	unsigned int total() const;

	void unblock(const std::string & feature);
	void change(const std::string & setting, const std::string & value);
	void update(const Result & score);

private:

	const unsigned int RESULT_LIMIT = 100;

	void write() const;
	void read();
	void default();
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