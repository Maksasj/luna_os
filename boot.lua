local luna = {}

function luna:main()
    self.packages = {
        require 'packages.bush.main',
    }

    for i = 1, (#self.packages - 1) do
        self.packages[i]:init(self)
    end

    while true do
        for i = 1, (#self.packages - 1) do
            if self.packages[i]:update(self) then
                self.packages[i]:draw(self)
            end
        end

        kernel._wait_for_vblank()
    end
end

luna:main()
