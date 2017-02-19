#ifndef COMPONENTS_LOCAL_STORAGE
#define COMPONENTS_LOCAL_STORAGE

#include "Application\Wrapper.hpp"
#include <string>
#include <unordered_map>

namespace Components
{

class LocalStorage : public Application::Wrapper
{
public:

	const std::string DISABLE_ADDS_FEATURE = "disable-adds";

	const std::string HAMMER_SETTING = "hammer_setting";

	LocalStorage();
	~LocalStorage();

	bool feature(const std::string & feature) const;
	std::string setting(const std::string & setting) const;
	unsigned int score(unsigned int index) const;
	unsigned int total() const;

	void unblock(const std::string & feature);
	void change(
		const std::string & setting,
		const std::string & value
	);
	void update(
		unsigned int score,
		unsigned int seconds
	);

private:

	void default();
	std::string path() const;
	std::string hash(const std::string & file) const;

	std::unordered_map<
		std::string,
		bool
	> _features;
	std::unordered_map<
		std::string,
		std::string
	> _settings;
	std::vector<unsigned int> _scores;
	unsigned int _total;

};

}

#endif