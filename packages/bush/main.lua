require 'luna.input_engine'
require 'luna.context.context'
require 'luna.libluna'

require 'packages.bush.engine'

require 'packages.bush.commands.clear_command'
require 'packages.bush.commands.date_command'
require 'packages.bush.commands.ls_command'
require 'packages.bush.commands.pwd_command'

local package = {}

function package:init(system)
    function run_command(command)
        local iterator = command:gmatch("%S+")

        local comTable = {}
        for i in iterator do
            comTable[#comTable + 1] = i
        end

        local index = -1
        for i = 1, #self.commands do
            if self.commands[i].keyword == comTable[1] then
                index = i
            end
        end

        if index == -1 then
            print("unknown command")
            return
        end

        if #comTable >= 1 then
            self.commands[index]._onCommand(comTable)
        end
    end

    self.bush = BushEngine.new()
    self.bush:setup(surfacec.MAIN_SCREEN)
    self.bush:draw_lines(23)
    self.bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)

    self.commands = {
        ls_command(self.bush),
        date_command(self.bush),
        pwd_command(self.bush),
        clear_command(self.bush)
    }

    self.context = ContextEngine.new(surfacec.BOTTOM_SCREEN)

    local bushSubmenu = (require 'packages.bush.submenu').create(run_command, self.commands)
    local keyboardSubmenu = (require 'luna.context.submenus.keyboard').create()

    self.context:add_submenu(keyboardSubmenu)
    self.context:add_submenu(bushSubmenu)

    self.context:draw()
end

function package:update(system)
    return self.context:update()
end

function package:draw(system)
    self.context:draw()

    self.bush:draw_lines(23)
    self.bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
end

return package
