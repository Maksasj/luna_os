function clear_command(bush)
    return {
        keyword = "clear",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:clear()
            bush:flush_lines()

            bush:draw_lines(23)
            bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
        end
    }
end