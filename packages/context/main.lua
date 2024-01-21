require 'luna.input_engine'
require 'luna.context.context'
require 'luna.libluna.libluna'

local package = {}

function package:add_submenu(submenu)
    self.context:add_submenu(submenu)
    self.context:draw()
end

function package:main(system)
    self.context = ContextEngine.new(surfacec.BOTTOM_SCREEN)

    local keyboardSubmenu = (require 'luna.context.submenus.keyboard').create()

    self.context:add_submenu(keyboardSubmenu)
    self.context:draw()

    while true do
        if self.context:update() then
            self.context:draw()
        end

        coroutine.yield()
    end
end

return package