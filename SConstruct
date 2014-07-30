cpu_env = Environment(tools = ['wla-dx'])
apu_env = cpu_env.Clone()

cpu_env['WLA_TARGET'] = '65816'
apu_env['WLA_TARGET'] = 'spc700'
ROMfile = SConscript(['src/SConscript'], exports=['cpu_env', 'apu_env'])

libretro_base = Dir('C:\\Users\\William\\Projects\\Games\\EMUL\\RetroArch\\')
libretro_core = libretro_base.File('cores/bsnes_accuracy_libretro.dll')

testROM = Command('testROM', ROMfile, \
	Action([['retroarch', '${SOURCE.abspath}', '-L', libretro_core]]), \
	chdir = libretro_base)

Default(ROMfile)
