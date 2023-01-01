#include "command.h"
#include "slap.h"

void slap_handler(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    dpp::snowflake target = std::get<dpp::snowflake>(event.get_parameter("target"));
    std::string weapon = std::get<std::string>(event.get_parameter("weapon"));

    dpp::user cmdAuthor{ event.command.get_issuing_user() };

    dpp::user* targetUser = dpp::find_user(target);

    if (targetUser->id == cmdAuthor.id) {
        event.reply("The bot slaps " + cmdAuthor.username + " <:yeefpineapple:1002713544518799562>");
    }
    event.reply(std::string(cmdAuthor.username + " slaps " + targetUser->username + " with their " + weapon + '.'));
}