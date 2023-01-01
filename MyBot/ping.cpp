#include "command.h"
#include "ping.h"

void ping_handler(dpp::cluster& bot, const dpp::slashcommand_t& event) {
	double ping{ bot.get_shard(0) -> websocket_ping };

	event.reply("Ping: " + std::to_string(ping));
}