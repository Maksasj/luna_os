require "luna.libluna.libluna"

local luna = {}

function luna:get_package(index)
    return self.runningPackages[index]
end

function luna:run_package(entryPoint)
    local packageInfo = require(entryPoint)
    local entry = require(packageInfo.entryPoint)

    local package = {
        uuid = libluna.uuid(),
        info = packageInfo,
        object = entry,
        thread = coroutine.create(function() entry:main(self) end)
    }

    table.insert(self.runningPackages, package)

    return package.uuid
end

function luna:get_package_index(uuid)
    for i = 1, #luna.runningPackages do
        if luna.runningPackages[i].uuid == uuid then
            return i
        end
    end

    return -1
end

function luna:stop_package(uuid)
    local index = self:get_package_index(uuid)

    if index ~= -1 then
        -- Todo stop coroutine

        table.remove(luna.runningPackages, index);
    end
end

local registry = {
    environment = {
        ["LUNA_PACKAGES"] = { "packages", "packages/bush", "luna/packages", "luna/packages/random.lua" }
    }
}

function is_package(path)
    return libluna.io.file_exist(path .. "/package.lua")
end

function registry:find(prompt)
    -- lets iterate over all registry variables
    for variable, values in pairs(self.environment) do

        -- then across all values in a variable
        for i = 1, #values do
            local value = values[i]

            if libluna.io.is_dir(value) then
                -- There is two possible scenario, if this is a package or folder that contains packages or files

                if is_package(value) then -- This is a package
                    local luaModule = value .. "/package"
                    luaModule = luaModule:gsub("/", ".")

                    local info = require(luaModule)

                    print("This is a package")
                else -- This is not a package
                    local folder = libluna.io.opendir(value)

                    -- Lets scan each folder in this folder, and check if it is runnable
                    folder:for_each_entry(function(entry)
                        local name = entry:get_name()

                        if entry:is_dir() then
                            if is_package(value .. "/" .. name) then
                                local luaModule = value .. "." .. name .. "/package"
                                luaModule = luaModule:gsub("/", ".")

                                local info = require(luaModule)
                                print("This is a package")
                            end
                        else
                            print("This is a file")
                        end
                    end)
                end
            elseif libluna.io.is_file(value) then
                -- Todo
                print("This is a file")
            end
        end
    end
end

function luna:main()
    registry:find("random")

    luna.runningPackages = {}

    self:run_package("packages.context.package")
    self:run_package("packages.bush.package")

    while true do
        for i = 1, #luna.runningPackages do
            coroutine.resume(luna.runningPackages[i].thread)
        end

        kernel._wait_for_vblank()
    end
end

luna:main()
