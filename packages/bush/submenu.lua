submenu = {}

function submenu.create(parseCommand, commands)
    return {
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
            context.bushEngine:put_line("³L back³ Bush commands          ", 0, 0)
            context.bushEngine:put_line("ÀÄÄÄÄÄÄÙ                        ", 0, 1)

            for index = 1, #commands do
                context.bushEngine:put_line(" " .. index .. ". " .. commands[index].keyword, 0, index + 1)
            end

            context.bushEngine:putc(">", 0, self.data.selected + 1)
        end
    }
end

return submenu