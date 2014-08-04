#Custom builder for WLA-DX assembler suite

#Python includes
import re
import os.path

#SCons includes
import SCons.Defaults
import SCons.Scanner
import SCons.Tool

#Taken from NASM builder
ASSuffixes = ['.s', '.asm', '.ASM']
ASPPSuffixes = ['.spp', '.SPP', '.sx']
if SCons.Util.case_sensitive_suffixes('.s', '.S'):
	ASPPSuffixes.extend(['.S'])
else:
	ASSuffixes.extend(['.S'])

#Custom scanner
#http://stackoverflow.com/questions/4798149/ignore-comments-using-sed-but-keep-the-lines-untouched
include_re = re.compile(r'^\s*.include\s+"(\S+)"', re.M)
incbin_re = re.compile(r'^\s*.incbin\s+"(\S+)"', re.M)
incdir_re = re.compile(r'^\s*.incdir\s+"(\S+)"', re.M)

#http://scons.1086193.n5.nabble.com/path-function-SCons-Scanner-FindPathDirs-quot-never-works-td19957.html
#http://scons.tigris.org/ds/viewMessage.do?dsForumId=1272&dsMessageId=1580034
def wla_includes(node, env, path, arg=None):
	contents = node.get_text_contents()
	src_files = include_re.findall(contents)
	bin_files = incbin_re.findall(contents)
	incdirs = incdir_re.findall(contents)
	incdirs.insert(0, '.')
	dependencies = src_files + bin_files
	results = []
	for inc in dependencies:
		f = env.FindFile(inc, incdirs)
		if (f):
			results.append(f)
	
	for i in range(0, len(results)):
		print results[i]
	return results

#WLA uses a linkfile to link exes together.
def create_linkfile(target, source, env):
	with open(env['LINKFILE'], 'w') as linkfile:
		string = '[objects]\n'
		linkfile.write(string)
		for files in source:
			string = str(files)
			linkfile.write(string + '\n')
        # Code to build "target" from "source"
        return None

#Copied from Borland builder
def findIt(program, env):
    # First search in the SCons path and then the OS path:
    progpath = env.WhereIs(program) or SCons.Util.WhereIs(program)
    if progpath:
        dir = os.path.dirname(progpath)
        env.PrependENVPath('PATH', dir)
    return progpath	


#Modified from SCons.Tool.createProgBuilder- we add an extra Action to generate
#a linkfile! Possible improvement: Use the env.Textfile builder and just have
#Textfile be the source builder for linking?
def createWLAProgBuilder(env):
	"""This is a utility function that creates the Program
	Builder in an Environment if it is not there already.
	 
	If it is already there, we return the existing one.
	"""
	 
	try:
		program = env['BUILDERS']['Program']
	except KeyError:
		import SCons.Defaults
		program = SCons.Builder.Builder(action = 
		[SCons.Action.Action(create_linkfile, "Creating linkfile for $TARGET ..."),
		SCons.Action.Action("$LINKCOM", "$LINKCOMSTR")],
			emitter = '$PROGEMITTER',
			prefix = '$PROGPREFIX',
			suffix = '$PROGSUFFIX',
			src_suffix = '$OBJSUFFIX',
			src_builder = 'Object',
		target_scanner = SCons.Tool.ProgramScanner)
		env['BUILDERS']['Program'] = program
	return program


def generate(env):
	for progname in ['wla-65816', 'wla-spc700', 'wlalink']:
		findIt(progname, env)
	
	scan_wla = SCons.Scanner.Scanner(function = wla_includes)
	SCons.Tool.SourceFileScanner.add_scanner('.asm', scan_wla)
	static_obj, shared_obj = SCons.Tool.createObjBuilders(env)
	
	for suffix in ASSuffixes:
		static_obj.add_action(suffix, SCons.Defaults.ASAction)
		static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)
	
	"""for suffix in ASPPSuffixes:
		static_obj.add_action(suffix, SCons.Defaults.ASPPAction)
		static_obj.add_emitter(suffix, SCons.Defaults.StaticObjectEmitter)"""
        createWLAProgBuilder(env)
        
	env['AS'] = 'wla-${WLA_TARGET}'
	env['ASCOM'] = '$AS $ASFLAGS $SOURCES $TARGET'
	env['ASFLAGS'] = '-io'
	env['LINK'] = 'wlalink'
	env['LINKFLAGS'] = '-iSr'
	env['LINKFILE'] = 'linkfile.txt'
	env['LINKCOM'] = '$LINK $LINKFLAGS $LINKFILE $TARGET'
	env['PROGSUFFIX'] = '.bin'

def exists(env):
    return env.Detect('wla-dx')
