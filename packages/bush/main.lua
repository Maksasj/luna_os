kernel.lua.require("packages/luna/libluna.lua")

kernel.lua.require("packages/bush/engine.lua")

bushEngine = BushEngine:new();

while true do
    bushEngine.putc("a", 0, 0, libluna.gfx.colors.YELLOW)
    bushEngine.put_line("test line", 0, 0, libluna.gfx.colors.YELLOW)

    kernel.gfx.wait_for_vblank()
end
