local submenu = {}

function submenu.create()
    return {
        title = "Virtual Keyboard",
        data = {},
        _enter = function(context, self)
            context.bushEngine:clear()
            context.bushEngine:flush_lines()

            context.bushEngine:print_lines({
                "³L back³ Virtual Keyboard 0.1.0v",
                "ÀÄÄÄÄÄÄÙ                        ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "                                ",
                "Selected 'A' key                ",
                "ÚÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÄÄÄ¿",
                "³~³1³2³3³4³5³6³7³8³9³0³+³'³ <- ³",
                "ÃÄÁÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÂÄÄ´",
                "³tab³Q³W³E³R³T³Y³U³I³O³P³]³^³  ³",
                "ÃÄÄÄÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÂÁÄÁÂÁÄÄ´",
                "³Caps³A³S³D³F³G³H³J³K³L³\\ ³[³* ³",
                "ÃÄÄÂÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÅÄÂÄÁÄÄÄ´",
                "³  ³<³Z³X³C³V³B³N³M³,³.³-³     ³",
                "ÃÄÄÁÄÅÄÅÄÁÄÅÄÁÄÁÄÁÄÅÄÁÄÁÂÁÂÄÄÄÄ´",
                "³ctrl³ ³alt³       ³a.gr³ ³ctrl³",
                "ÀÄÄÄÄÙ ÀÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÙ ÀÄÄÄÄÙ"
            })
        end,
        _update = function(context, self)
            return false
        end,
        _draw = function(context, self)
            context.bushEngine:draw_lines(24)
        end
    }
end

return submenu