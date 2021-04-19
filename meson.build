project('sdb', 'c', meson_version: '>=0.50.0', default_options: [
  'buildtype=debugoptimized', 'b_vscrt=from_buildtype', 'warning_level=3'
])
py3_exe = import('python').find_installation()
pkgconfig_mod = import('pkgconfig')
cc = meson.get_compiler('c')

sdb_incdir = get_option('includedir')
if get_option('sdb_includedir') != ''
  sdb_incdir = get_option('sdb_includedir')
endif

version_cmd = '''from sys import argv
with open(argv[1]) as fd:
  for line in fd:
    if line.startswith('SDBVER='):
      version_tuple = line.split('=')[1]
      print(version_tuple)
      break
'''
sdb_version = '0.0.1'
config_mk = files('config.mk')[0]
r = run_command(py3_exe, '-c', version_cmd, config_mk)
if r.returncode() == 0
  sdb_version = r.stdout().strip()
else
  warning('Cannot determine SDB version')
endif
message('SDB version = ' + sdb_version)
sdb_libversion = host_machine.system() == 'windows' ? '' : sdb_version

rpath_lib = ''
rpath_exe = ''
if get_option('local') and get_option('default_library') == 'shared'
  rpath_lib = '$ORIGIN'
  rpath_exe = '$ORIGIN/../' + get_option('libdir')
endif

userconf = configuration_data()
userconf.set10('HAVE_GETPID', cc.has_function('getpid', prefix: '#include <unistd.h>'))
userconf.set10('HAVE__GETPID', cc.has_function('_getpid', prefix: '#include <process.h>'))
sdb_userconf_h = configure_file(
  input : 'src/sdb_userconf.h.in',
  output : 'sdb_userconf.h',
  configuration : userconf,
  install_dir : join_paths(sdb_incdir, 'sdb'),
)

# Create sdb_version.h
versionconf = configuration_data()
versionconf.set_quoted('SDB_VERSION', sdb_version, description : 'From config.mk')
sdb_version_h = configure_file(
  output : 'sdb_version.h',
  configuration : versionconf,
  install_dir : join_paths(sdb_incdir, 'sdb'),
)

if get_option('static_runtime')
  if cc.has_argument('/MT')
    # Use -Db_vscrt=static_from_buildtype to avoid warnings due to multiple /M options
    add_project_arguments('/MT', language: 'c')
  elif cc.has_link_argument('-static')
    add_project_link_arguments('-static', language: 'c')
  endif
endif

if cc.get_id() == 'clang-cl'
  add_project_arguments('-D__STDC__=1', language: 'c')
  add_project_arguments('-D_CRT_DECLARE_NONSTDC_NAMES ', language: 'c')
  add_project_arguments('-D_CRT_SECURE_NO_WARNINGS', language: 'c')
  add_project_arguments('-D_CRT_NONSTDC_NO_DEPRECATE', language: 'c')
endif

if get_option('default_library') == 'shared'
  if cc.has_argument('-fvisibility=hidden')
    add_project_arguments('-fvisibility=hidden', language: 'c')
  endif
endif

subdir('src')

sdb_exe = executable('sdb', 'src/main.c',
  dependencies: sdb_dep,
  install: not meson.is_subproject(),
  install_rpath: rpath_exe,
  implicit_include_directories: false,
)

if meson.is_cross_build()
  sdb_native_exe = executable('sdb_native', 'src/main.c',
    dependencies: sdb_native_dep,
    install: false,
    native: true,
    implicit_include_directories: false,
  )
else
  sdb_native_exe = sdb_exe
endif

if not meson.is_subproject()
  subdir('test')
endif
