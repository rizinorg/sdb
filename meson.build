project('sdb', 'c', meson_version: '>=0.47.0')
py3_exe = import('python').find_installation('python3')
pkgconfig_mod = import('pkgconfig')

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

# Create sdb_version.h
conf_data = configuration_data()
conf_data.set_quoted('SDB_VERSION', sdb_version, description : 'From config.mk')
configure_file(
  output : 'sdb_version.h',
  configuration : conf_data,
  install_dir : join_paths(get_option('includedir'), 'sdb')
)

subdir('src')

sdb_exe = executable('sdb', 'src/main.c',
  dependencies: sdb_dep,
  install: not meson.is_subproject(),
  install_rpath: rpath_exe,
  implicit_include_directories: false,
)

if meson.is_cross_build()
  sdb_native_exe = executable('sdb_native', 'src/main.c',
    dependencies: sdb_dep,
    install: false,
    implicit_include_directories: false,
  )
else
  sdb_native_exe = sdb_exe
endif

if not meson.is_subproject()
  subdir('test')
endif
