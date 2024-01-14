kernel._require("packages/luna/libluna.lua")
kernel._require("packages/bush/engine.lua")
kernel._require("packages/bush/context.lua")


    -- local dirCommand = function()

    -- end

function main()
    bush = BushEngine.new()
    bush:setup(surfacec.MAIN_SCREEN)

    function redraw()
        bush:draw_lines(23)
        bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
    end

    redraw()

    commands = {
        {
            title = "ls",
            _argumentCount = 0,
            _onCommand = function(arguments)
               local dirp = kernel._opendir(".")
               if dirp == 0 then
                   bush:print_line("Failed to open directory")
               end

               while true do
                   local cur = kernel._readdir(dirp)

                   if cur == 0 then break end

                   local name = kernel._dirent_get_name(cur)
                   bush:print_line(name)
               end

               kernel._closedir(dirp)
            end
        },
        {
            title = "date",
            _argumentCount = 0,
            _onCommand = function(arguments)
                bush:print_line("Sun Jan 14 14:44:00 PKT 2024")
            end
        },
        {
            title = "pwd",
            _argumentCount = 0,
            _onCommand = function(arguments)
                bush:print_line("sd:/packages")
            end
        },
        {
            title = "clear",
            _argumentCount = 0,
            _onCommand = function(arguments)
                bush:clear()
                bush:flush_lines()

                redraw()
            end
        }
    }

    function parseCommand(commandString)
        local iterator = commandString:gmatch("%S+")

        local comTable = {}
        for i in iterator do
            comTable[#comTable + 1] = i
        end

        local index = -1
        for i = 1, #commands do
            if commands[i].title == comTable[1] then
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

    keyboardSubmenu = {
        title = "Virtual Keyboard",
        data = {},
        _enter = function(self, bushEngine)
            bushEngine:clear()
            bushEngine:flush_lines()

            bushEngine:print_lines({
                "³L back³ Virtual Keyboard 0.1.0v",
                "ÀÄÄÄÄÄÄÙ                        ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "Selected 'A' key                ",
                "ÚÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÄÄÄ¿",
                "³~³1³2³3³4³5³6³7³8³9³0³+³'³ <- ³",
                "ÃÄÁÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÂÄÄ´",
                "³tab³Q³W³E³R³T³Y³U³I³O³P³]³^³  ³",
                "ÃÄÄÄÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÄÁÂÁÄÄ´",
                "³Caps³A³S³D³F³G³H³J³K³L³\\ ³[³* ³",
                "ÃÄÄÂÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÂÄÁÄÄÄ´",
                "³  ³<³Z³X³C³V³B³N³M³,³.³-³     ³",
                "ÃÄÄÁÄÅÄÅÄÁÄÅÄÁÄÁÄÁÄÅÄÁÄÁÂÁÂÄÄÄÄ´",
                "³ctrl³ ³alt³       ³a.gr³ ³ctrl³",
                "ÀÄÄÄÄÙ ÀÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÙ ÀÄÄÄÄÙ"
            })
        end,
        _update = function(self)
            return false
        end,
        _draw = function(self, bushEngine)
            bushEngine:draw_lines(24)
        end
    }

    bushSubmenu = {
        title = "Bush commands",
        data = {},
        _enter = function(self, bushEngine)
            bushEngine:clear()
            bushEngine:flush_lines()

            self.data.selected = 1
        end,
        _update = function(self)
            if kernel._get_key(libluna.keycodes.KEY_UP) ~= 0 then
                if self.data.selected > 1 then
                    self.data.selected = self.data.selected - 1
                    return true
                end
            end

            if kernel._get_key(libluna.keycodes.KEY_DOWN) ~= 0 then
                if self.data.selected < #commands then
                    self.data.selected = self.data.selected + 1
                    return true
                end
            end

            if kernel._get_key(libluna.keycodes.KEY_A) ~= 0 then
                local command = commands[self.data.selected].title
                parseCommand(command)
                return true
            end

            return false
        end,
        _draw = function(self, bushEngine)
            bushEngine:put_line("³L back³ Bush commands          ", 0, 0)
            bushEngine:put_line("ÀÄÄÄÄÄÄÙ                        ", 0, 1)

            for index = 1, #commands do
                bushEngine:put_line(" " .. index .. ". " .. commands[index].title, 0, index + 1)
            end

            bushEngine:putc(">", 0, self.data.selected + 1)
        end
    }

    context = ContextEngine.new(surfacec.BOTTOM_SCREEN)
    context:add_submenu(keyboardSubmenu)
    context:add_submenu(bushSubmenu)

    context:draw()

    while true do
        if context:update() then
            context:draw()

            redraw()
        end

        kernel._wait_for_vblank()
    end
end

main()
