require 'packages.luna.libluna'
require 'packages.luna.input_engine'
require 'packages.bush.engine'
require 'packages.bush.context'

function ls_command(bush)
    return {
        keyword = "ls",
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
    }
end

function date_command(bush)
    return {
        keyword = "date",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:print_line("Sun Jan 14 14:44:00 PKT 2024")
        end
    }
end

function pwd_command(bush)
    return {
        keyword = "pwd",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:print_line("sd:/packages")
        end
    }
end

function clear_command(bush)
    return {
        keyword = "clear",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:clear()
            bush:flush_lines()

            redraw()
        end
    }
end

function main()
    local bush = BushEngine.new()
    bush:setup(surfacec.MAIN_SCREEN)

    function redraw()
        bush:draw_lines(23)
        bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
    end
    redraw()

    local commands = {
        ls_command(bush),
        date_command(bush),
        pwd_command(bush),
        clear_command(bush)
    }

    function parseCommand(commandString)
        local iterator = commandString:gmatch("%S+")

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

    local keyboardSubmenu = {
        title = "Virtual Keyboard",
        data = {},
        _enter = function(context, self)
            context.bushEngine:clear()
            context.bushEngine:flush_lines()

            context.bushEngine:print_lines({
                "�L back� Virtual Keyboard 0.1.0v",
                "��������                        ",
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
                "������������������������������Ŀ",
                "�~�1�2�3�4�5�6�7�8�9�0�+�'� <- �",
                "������������������������������Ĵ",
                "�tab�Q�W�E�R�T�Y�U�I�O�P�]�^�  �",
                "������������������������������Ĵ",
                "�Caps�A�S�D�F�G�H�J�K�L�\\ �[�* �",
                "������������������������������Ĵ",
                "�  �<�Z�X�C�V�B�N�M�,�.�-�     �",
                "������������������������������Ĵ",
                "�ctrl� �alt�       �a.gr� �ctrl�",
                "������ ������������������ ������"
            })
        end,
        _update = function(context, self)
            return false
        end,
        _draw = function(context, self)
            context.bushEngine:draw_lines(24)
        end
    }

    local bushSubmenu = {
        title = "Bush commands",
        data = {},
        _enter = function(context, self)
            context.bushEngine:clear()
            context.bushEngine:flush_lines()

            self.data.selected = 1
        end,
        _update = function(context, self)
            local input = context.inputEngine

            if input:is_key_pressed(KEY_UP) then
                if self.data.selected > 1 then
                    self.data.selected = self.data.selected - 1
                    return true
                end
            end

            if input:is_key_pressed(KEY_DOWN) then
                if self.data.selected < #commands then
                    self.data.selected = self.data.selected + 1
                    return true
                end
            end

            if input:is_key_pressed(KEY_A) then
                local command = commands[self.data.selected].keyword
                parseCommand(command)
                return true
            end

            return false
        end,
        _draw = function(context, self)
            context.bushEngine:put_line("�L back� Bush commands          ", 0, 0)
            context.bushEngine:put_line("��������                        ", 0, 1)

            for index = 1, #commands do
                context.bushEngine:put_line(" " .. index .. ". " .. commands[index].keyword, 0, index + 1)
            end

            context.bushEngine:putc(">", 0, self.data.selected + 1)
        end
    }

    local context = ContextEngine.new(surfacec.BOTTOM_SCREEN)

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
