#include <dpp/dpp.h>
#include <map>
#include <iostream>

#include "woodybot.h"
#include "constants.h"
#include "command.h"
#include "ping.h"
#include "slap.h"

std::map<std::string, woodybot::command_base> commands = {
    {"ping", {"Tells you the bot's ping.", ping_handler}},
    {"slap", {
        "Slap a user", slap_handler, {
            {dpp::command_option(dpp::co_string, "target", "User to target", false)},
            {dpp::command_option(dpp::co_string, "weapon", "Weapon to use", false)}
        }
    }}
};

int main() {

    // General bot setup
    dpp::cluster bot("OTE0OTg3OTM4NjkyMDgzODUy.Ghs4PH.o5wTQixQtVOCIlszYhXuGQhZ6Yqh8-DWTkXHcY");

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct bulk_register>()) {
            std::vector<dpp::slashcommand> slash_commands;
            std::vector<dpp::slashcommand> no_commands; // Yeet the slash commands for the debuggycord server.

            for (auto& def : commands) {
                dpp::slashcommand cmd;
                cmd.set_name(def.first).
                    set_description(def.second.description).
                    set_application_id(bot.me.id);
                cmd.options = def.second.parameters;
                slash_commands.push_back(cmd);
            }

            bot.global_bulk_command_create(slash_commands, dpp::utility::log_error());
            bot.guild_bulk_command_create(no_commands, woodybot::debuggycord, dpp::utility::log_error());
        }
    });

    /* Handle slash command */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        dpp::command_interaction cmd_data{ event.command.get_command_interaction() };
        
        auto command_iter{ commands.find(cmd_data.name) };
        if (command_iter != commands.end()) {
            command_iter -> second.function(bot, event);
        }
    });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}
