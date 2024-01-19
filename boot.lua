local luna = {}

function luna:get_package(index)
    return self.packages[index]
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

    table.insert(self.packages, package)

    return package.uuid
end

function luna:get_package_index(uuid)
    for i = 1, #luna.packages do
        if luna.packages[i].uuid == uuid then
            return i
        end
    end

    return -1
end

function luna:stop_package(uuid)
    local index = self:get_package_index(uuid)

    if index ~= -1 then
        -- Todo stop coroutine

        table.remove(luna.packages, index);
    end
end

function luna:main()
    luna.packages = {}

    self:run_package("packages.context.package")
    self:run_package("packages.bush.package")

    while true do
        for i = 1, #luna.packages do
            coroutine.resume(luna.packages[i].thread)
        end

        kernel._wait_for_vblank()
    end
end

luna:main()
