#ifndef WOODYBOT_COMMAND_BASE
#define WOODYBOT_COMMAND_BASE

#include <dpp/dpp.h>

using command_function = std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>;

namespace woodybot {
	struct command_base {
		// The command's description.
		std::string description;

		// The command's callback function.
		command_function function;

		// The command's parameters if any.
		std::vector<dpp::command_option> parameters = {};
	};
}
#endif // !WOODYBOT_COMMAND_BASE