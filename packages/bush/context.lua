ContextEngine = {}
ContextEngine.__index = ContextEngine

ContextEngineStates = {
    CONTEXT = 0,
    SUBMENU = 1
}

function ContextEngine.new(surface)
    local engine = {}

    setmetatable(engine, ContextEngine)

    engine.bushEngine = BushEngine.new()
    engine.bushEngine:setup(surface)

    engine.selected = 1
    engine.state = ContextEngineStates.CONTEXT
    engine.submenus = {}

    return engine
end

function ContextEngine:add_submenu(submenu)
    table.insert(self.submenus, submenu)
end

function ContextEngine:update()
    if self.state == ContextEngineStates.CONTEXT then
        if kernel._get_key(libluna.keycodes.KEY_UP) ~= 0 then
            if self.selected > 1 then
                self.selected = self.selected - 1
                return true
            end
        end

        if kernel._get_key(libluna.keycodes.KEY_DOWN) ~= 0 then
            if self.selected < #self.submenus then
                self.selected = self.selected + 1
                return true
            end
        end

        if kernel._get_key(libluna.keycodes.KEY_A) ~= 0 then
            self.state = ContextEngineStates.SUBMENU
            self.submenus[self.selected]._enter(self.submenus[self.selected], self.bushEngine)
            return true
        end
    else
        if kernel._get_key(libluna.keycodes.KEY_L) ~= 0 then
            self.state = ContextEngineStates.CONTEXT
            self.bushEngine:flush_lines()
            self.bushEngine:clear()
            return true
        end

        return self.submenus[self.selected]._update(self.submenus[self.selected])
    end

    return false
end

function ContextEngine:draw()
    if self.state == ContextEngineStates.CONTEXT then
        self.bushEngine:put_line("Context Menu", 0, 0)

        for index = 1, #self.submenus do
            self.bushEngine:put_line(" " .. index .. ". " .. self.submenus[index].title, 0, index)
        end

        self.bushEngine:putc(">", 0, self.selected)
    else
        self.submenus[self.selected]._draw(self.submenus[self.selected], self.bushEngine)
    end
end