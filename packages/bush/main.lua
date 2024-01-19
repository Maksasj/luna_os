require 'luna.input_engine'
require 'luna.context.context'
require 'luna.libluna'

require 'packages.bush.engine'

require 'packages.bush.commands.clear_command'
require 'packages.bush.commands.date_command'
require 'packages.bush.commands.ls_command'
require 'packages.bush.commands.pwd_command'
require 'packages.bush.commands.pst_command'

local package = {}

function package:main(system)
    function run_command(command)
        local iterator = command:gmatch("%S+")

        local comTable = {}
        for i in iterator do
            comTable[#comTable + 1] = i
        end

        local index = -1
        for i = 1, #commands do
            if commands[i].keyword == comTable[1] then
                index = i
            end
        end

        if index == -1 then
            print("unknown command")
            return
        end

        if #comTable >= 1 then
            commands[index]._onCommand(comTable)
        end
    end

    bush = BushEngine.new()
    bush:setup(surfacec.MAIN_SCREEN)
    bush:draw_lines(23)
    bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)

    commands = {
        ls_command(bush),
        date_command(bush),
        pwd_command(bush),
        clear_command(bush),
        pst_command(bush, system)
    }

    local context = system:get_package(1).object

    local bushSubmenu = (require 'packages.bush.submenu').create(run_command, commands)
    context:add_submenu(bushSubmenu)

    while true do
        bush:draw_lines(23)
        bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)

        coroutine.yield()
    end
end

return package