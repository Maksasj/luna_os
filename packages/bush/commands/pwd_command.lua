function pwd_command(bush)
    return {
        keyword = "pwd",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:print_line("sd:/packages")
        end
    }
end