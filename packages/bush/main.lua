kernel._require("packages/luna/libluna.lua")
kernel._require("packages/bush/engine.lua")

function main()
    bushEngine = BushEngine:new();

    bushEngine:setup()

    bushEngine:print_line("poggers")
    bushEngine:print_line("another line")
    bushEngine:print_line("and again another")
    bushEngine:print_line("lol")

    function redraw()
        bushEngine:draw_lines()
        bushEngine:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
    end
    redraw()

    while true do
        if kernel._get_key(libluna.keycodes.KEY_B) ~= 0 then
            bushEngine:print_line("pressed key B")
            redraw()
        end

        if kernel._get_key(libluna.keycodes.KEY_A) ~= 0 then
            bushEngine:print_line("pressed key A")
            redraw()
        end

        kernel._wait_for_vblank()
    end
end


main()