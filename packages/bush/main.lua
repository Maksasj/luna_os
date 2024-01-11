kernel.lua.require("packages/luna/libluna.lua")

kernel.lua.require("packages/bush/engine.lua")

bushEngine = BushEngine:new();

function redraw()
    bushEngine:draw_lines()

    bushEngine.put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
end

function main()
    bushEngine:print_line("poggers")
    bushEngine:print_line("another line")
    bushEngine:print_line("and again another")
    bushEngine:print_line("lol")

    redraw()

    while true do
        if kernel.lua.get_key(libluna.keycodes.KEY_B) ~= 0 then
            bushEngine:print_line("pressed key B")
            redraw()
        end

        if kernel.lua.get_key(libluna.keycodes.KEY_A) ~= 0 then
            bushEngine:print_line("pressed key A")
            redraw()
        end

        if kernel.lua.get_key(libluna.keycodes.KEY_UP) ~= 0 then
            bushEngine:print_line("pressed key UP")
            redraw()
        end

        if kernel.lua.get_key(libluna.keycodes.KEY_DOWN) ~= 0 then
            bushEngine:print_line("pressed key DOWN")
            redraw()
        end

        if kernel.lua.get_key(libluna.keycodes.KEY_LEFT) ~= 0 then
            bushEngine:print_line("pressed key LEFT")
            redraw()
        end

        if kernel.lua.get_key(libluna.keycodes.KEY_RIGHT) ~= 0 then
            bushEngine:print_line("pressed key RIGHT")
            redraw()
        end
        kernel.gfx.wait_for_vblank()
    end
end

main()
