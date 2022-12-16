import chilon

chilon.logo()

font = chilon.FONT(chilon.Color['RED'], chilon.Color['BLUE'], chilon.Effect['BOLD'])

chilon.cprint(chilon.Color['CYAN'], chilon.Color['GREEN'], chilon.Effect['CROSSED'], "text test")
chilon.print('\n')
chilon.cprint2(font, "test red blue")
chilon.print('\n')
chilon.cprintf(chilon.Color['CYAN'], chilon.Color['GREEN'], chilon.Effect['CROSSED'], b"text test %d", 10)
chilon.print('\n')
chilon.cprintf2(font, b"text test %d", 20)
chilon.print('\n')

chilon.clear_screen(2)