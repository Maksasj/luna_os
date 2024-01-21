function pst_command(bush, luna)
    return {
        keyword = "pst",
        _argumentCount = 0,
        _onCommand = function(arguments)
            bush:print_line("Currently running packages")
            for i = 1, #luna.runningPackages do
                local info = luna.runningPackages[i].info

                bush:print_line(i .. "." .. info.title .. " ".. info.version)
            end
        end
    }
end