local luna = {}

function luna:get_package(index)
    return self.packages[index]
end

function luna:run_package(entryPoint)
    local packageInfo = require(entryPoint)
    local entry = require(packageInfo.entryPoint)

    local package = {
        info = packageInfo,
        object = entry,
        thread = coroutine.create(function() entry:main(self) end)
    }

    table.insert(self.packages, package)
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
