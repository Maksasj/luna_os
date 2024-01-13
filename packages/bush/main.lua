kernel._require("packages/luna/libluna.lua")
kernel._require("packages/bush/engine.lua")

function main()
    bush = BushEngine.new();
    keyboard = BushEngine.new();

    bush:setup(surfacec.MAIN_SCREEN)
    keyboard:setup(surfacec.BOTTOM_SCREEN)

    keyboard:print_lines({
        "+-----+--LUNA_OS_0.1.0v--+-----+",
        "|     |                  |     |",
        "|     |                  |     |",
        "|     |                  |     |",
        "+-----+-----+------+-----+-----+",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "+-----+-----+------+-----+-----+",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "+-----+-----+------+-----+-----+",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "+-----+-----+------+-----+-----+",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "|     |     |      |     |     |",
        "+-----+-----+------+-----+-----+",
        "|                              |",
        "|Charge 43/50                  |",
        "+------------------------------+"
    })

    local dirp = kernel._opendir(".")
    if dirp == 0 then
        bush:print_line("Failed to open directory")
    end

    while true do
        local cur = kernel._readdir(dirp)

        if cur == 0 then break end

        local name = kernel._dirent_get_name(cur)
        bush:print_line(name)
    end

    kernel._closedir(dirp)

    function redraw()
        bush:draw_lines()
        keyboard:draw_lines()
        bush:put_line("bush> ", 0, 23, libluna.gfx.colors.WHITE)
    end
    redraw()

    while true do
        if kernel._get_key(libluna.keycodes.KEY_B) ~= 0 then
            bush:print_line("pressed key B")
            redraw()
        end

        if kernel._get_key(libluna.keycodes.KEY_A) ~= 0 then
            bush:print_line("pressed key A")
            redraw()
        end

        kernel._wait_for_vblank()
    end
end


main()