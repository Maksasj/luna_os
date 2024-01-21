-- local folder = libluna.opendir("packages")
--
-- folder:for_each_entry(function(entry)
--
-- end)
--
-- folder:close()

function _file_exist(path)
    local file = kernel._fopen(path, "r")

    if file == 0 then
        return false
    end

    kernel._fclose(file)

    return true
end

function _is_dir(path)
    local stat = kernel._malloc(100) -- 100 should be enough for stat struct
    kernel._stat(path, stat)

    local st_mode = kernel._stat_st_mode(stat)

    kernel._free(stat)

    if ((st_mode & 0xF000) & 0x4000) ~= 0 then
        return true
    end

    return false
end

function _is_file(path)
    return not _is_dir(path)
end

function _opendir(directoryPath)
    local folder = {
        dirp = kernel._opendir(directoryPath)
    }

    if folder.dirp == 0 then
        -- Todo failed to open directory
    end

    function folder:for_each_entry(lambda)
        while true do
            local entry = {
                cur = kernel._readdir(self.dirp)
            }

            if entry.cur == 0 then break end

            function entry:get_name()
                return kernel._dirent_get_name(self.cur)
            end

            function entry:is_dir()
                return _is_dir(directoryPath .. "/" .. self:get_name())
            end

            function entry:is_file()
                return _is_file(directoryPath .. "/" .. self:get_name())
            end

            lambda(entry)
        end
    end

    function folder:close()
         kernel._closedir(self.dirp)
    end

    return folder
end

