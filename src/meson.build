libsdb_sources = [
  'array.c',
  'set.c',
  'base64.c',
  'buffer.c',
  'cdb.c',
  'cdb_make.c',
  'dict.c',
  'diff.c',
  'disk.c',
  'fmt.c',
  'ht_uu.c',
  'ht_pp.c',
  'ht_up.c',
  'journal.c',
  'json.c',
  #'json/api.c',
  #'json/indent.c',
  #'json/js0n.c',
  #'json/path.c',
  #'json/rangstr.c',
  'lock.c',
  'ls.c',
  'match.c',
  'ns.c',
  'num.c',
  'query.c',
  'sdb.c',
  'sdbht.c',
  'util.c',
  'text.c'
]

libsdb_inc = include_directories(['..', '.'])

libsdb = library('sdb', libsdb_sources,
  include_directories: libsdb_inc,
  implicit_include_directories: false,
  soversion: sdb_libversion,
  install: not meson.is_subproject(),
  install_rpath: rpath_lib
)

sdb_dep = declare_dependency(
  link_with: libsdb,
  include_directories: libsdb_inc,
)

if not meson.is_subproject()
  pkgconfig_mod.generate(libsdb,
    name: 'sdb',
    filebase: 'sdb',
    description: 'Simple DataBase',
    subdirs: ['sdb'],
    version: sdb_version,
    url: 'https://github.com/rizinorg/sdb'
  )

  include_files = [
    'buffer.h',
    'cdb.h',
    'cdb_make.h',
    'config.h',
    'dict.h',
    'ht_inc.h',
    'ht_pp.h',
    'ht_up.h',
    'ht_uu.h',
    'ls.h',
    'sdb.h',
    'sdbht.h',
    'set.h',
    'types.h'
  ]
  install_headers(include_files)
  install_man(['sdb.1'])
endif
