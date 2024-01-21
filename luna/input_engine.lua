InputEngine = {}
InputEngine.__index = InputEngine

function InputEngine.new()
    local engine = {}

    setmetatable(engine, InputEngine)

    engine.states = {}

    for k, v in pairs(libluna.io.keycodes) do
        engine.states[v] = {
            was_down = false,
            down = false
        }
    end

    return engine
end

function InputEngine:update()
    for k, v in pairs(libluna.io.keycodes) do
        self.states[v].was_down = self.states[v].down
        self.states[v].down = (kernel._get_key(v) ~= 0 and true or false)
    end
end

function InputEngine:is_key_pressed(key)
    return (self.states[key].was_down) and (not self.states[key].down)
end

function InputEngine:is_key_up(key)
    return not self.states[key].down
end

function InputEngine:is_key_down(key)
    return self.states[key].down
end