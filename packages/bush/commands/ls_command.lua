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