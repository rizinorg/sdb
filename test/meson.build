if get_option('enable_tests')
  tests = [
    'siolpain',
    'fmt',
    'stack',
    'cas',
    'hook',
    'hook2',
    'stress1',
    'fmtarr',
    'bench-expire',
    'expire',
    'dumptwice',
    'syncget',
    'nsabuse',
    'drain',
    'merge',
    # 'chkkey', the test is empty anyway
  ]

  foreach test : tests
    exe = executable('test_@0@'.format(test), '@0@.c'.format(test),
      dependencies: [sdb_dep],
      install: false,
      implicit_include_directories: false
    )
    test(test, exe, workdir: join_paths(meson.current_source_dir()))
  endforeach

  subdir('bench')
  subdir('unit')
endif
