InputEngine = {}
InputEngine.__index = InputEngine

function InputEngine.new()
    local engine = {}

    setmetatable(engine, InputEngine)

    engine.states = {}

    for k, v in pairs(libluna.keycodes) do
        engine.states[v] = {
            was_down = false,
            down = false
        }
    end

    return engine
end

-- KEY_A = 0
-- KEY_B = 1
-- KEY_SELECT = 2
-- KEY_START = 3
-- KEY_RIGHT = 4
-- KEY_LEFT = 5
-- KEY_UP = 6
-- KEY_DOWN = 7
-- KEY_R = 8
-- KEY_L = 9
-- KEY_X = 10
-- KEY_Y = 11

function InputEngine:update()
    for k, v in pairs(libluna.keycodes) do
        self.states[v].was_down = self.states[v].down
        self.states[v].down = (kernel._get_key(v) == 1 and true or false)
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