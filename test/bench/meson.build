tests = [
  'array',
  'new',
  'reset',
  'set',
  'stack',
  'sync'
]

foreach test : tests
  name = 'bench-' + test
  exe = executable(name, name + '.c',
    dependencies: sdb_dep,
  )
  benchmark(name, exe)
endforeach
