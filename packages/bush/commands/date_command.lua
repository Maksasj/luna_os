function date_command(bush)
    return {
        keyword = "date",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:print_line("Sun Jan 14 14:44:00 PKT 2024")
        end
    }
end